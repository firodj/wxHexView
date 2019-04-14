#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/rawbmp.h>
#include <algorithm>
#include <inttypes.h>
#include "wxHexView.h"

#if defined(__WXMAC__)
typedef wxPixelFormat<uint16_t, 64, 0, 1, 2, 3> wxRGBA64PixelFormat;
typedef wxPixelData<wxBitmap, wxRGBA64PixelFormat> MyPixelData;
#else
typedef wxAlphaPixelData MyPixelData;
#endif

#define USE_BITMAP_CACHE 1

enum { CURSOR_TIMER = 1234, AUTOSCROLL_TIMER };
static wxColour g_very_dark_gray(0x1E1E1E);
static wxColour g_light_gray(0x808080);
static wxColour g_very_light_gray(0xD4D4D4);
static wxColour g_dark_blue(0xD69C56);
static wxColour g_bright_blue(0xCC7A00);
static wxColour g_light_blue(0xFEDC9C);
static wxColour g_dark_gray(0x342c28);
static wxColour g_purple(0x956664);
static wxColour g_select_blue(0x7B4E26);
static wxPen g_dark_blue_pen(g_dark_blue);
static wxPen g_dark_gray_pen(g_dark_gray);

#define COLUMN_NARROW (column_mode_ == 0)
#define LINE_SIZE (COLUMN_NARROW ? 8 : column_mode_ * 8)

wxIMPLEMENT_DYNAMIC_CLASS(wxHexView, wxWindow);

///////////////////////////////////////////////////////////////////////////////
// Events

BEGIN_EVENT_TABLE(wxHexView, wxWindow)
    EVT_PAINT(wxHexView::OnPaint)
    EVT_CHAR(wxHexView::OnChar)
    EVT_SIZE(wxHexView::OnSize)
    EVT_SCROLLWIN(wxHexView::OnScrollBar)
    EVT_TIMER(CURSOR_TIMER, wxHexView::OnCursorTimer)
    EVT_TIMER(AUTOSCROLL_TIMER, wxHexView::OnAutoScrollTimer)
    EVT_SET_FOCUS(wxHexView::OnSetFocus)
    EVT_KILL_FOCUS(wxHexView::OnKillFocus)
    EVT_MOTION(wxHexView::OnMouseMove)
    EVT_LEFT_DOWN(wxHexView::OnMouseLeftDown)
    EVT_LEFT_UP(wxHexView::OnMouseLeftUp)
    EVT_MOUSEWHEEL(wxHexView::OnMouseWheel)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////
// wxHexView

wxHexView::wxHexView()
{
    Init();
}

wxHexView::wxHexView(wxWindow *parent, wxWindowID id)
{
    Init();
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS|wxVSCROLL);
}

wxHexView::~wxHexView()
{
}

void
wxHexView::Init()
{
    data_provider_ = nullptr;
    scale_bmp_ = 1;

    cursor_blink_ = false;
    counter_blink_ = false;

    addr_start_ = 0;
    cursor_addr_ = 0;
    cursor_hot_ = true;
    cursor_hmod_ = 0;
    selecting_ = false;
    addr_begin_ = 0;
    addr_end_ = 0;
    wheel_rotation_ = 0;

    dragging_addr_ = 0;
    dragging_hmod_ = 0;

    scrollbar_width_ = 0; //wxSystemSettings::GetMetric(wxSYS_VSCROLL_ARROW_X);

    redraw_bmp_ = true;

    cursor_timer_.SetOwner(this, CURSOR_TIMER);
    autoscroll_timer_.SetOwner(this, AUTOSCROLL_TIMER);
    autoscroll_offset_ = 0;
    autoscroll_counter_ = 0;
    autoscroll_speed_ = 0;
  
#if defined(__WXMSW__)
    console_font_ = wxFont(wxFontInfo(10)
        .FaceName("Lucida Console")
        .Family(wxFONTFAMILY_MODERN)
        .Style(wxFONTSTYLE_NORMAL)
        .Encoding(wxFONTENCODING_CP437)
        .Weight(wxFONTWEIGHT_NORMAL)
        .Underlined(false));
#elif defined(__WXMAC__)
    console_font_ = wxFont(wxFontInfo(10)
        .FaceName("Monaco")
        .Family(wxFONTFAMILY_MODERN)
        .Style(wxFONTSTYLE_NORMAL)
        .Encoding(wxFONTENCODING_CP437)
        .Weight(wxFONTWEIGHT_NORMAL)
        .Underlined(false));
#endif

    SetCursor(wxCursor(wxCURSOR_IBEAM));

#if defined(__WXMSW__)
    SetBackgroundStyle(wxBG_STYLE_PAINT);
#endif
    SetBackgroundColour(g_very_dark_gray);
}

void
wxHexView::CalcCharSize(wxDC &dc, wxSize &sz)
{
    wxDouble width;
    wxDouble height;
    wxDouble descent;
    wxDouble externalLeading; 

    wxGraphicsContext *gc = wxGraphicsContext::Create(*dynamic_cast<wxWindowDC*>(&dc));
    if (gc) {
        gc->SetFont(console_font_, g_very_light_gray);
        gc->GetTextExtent("M", &width, &height, &descent, &externalLeading);
        delete gc;
    }

    sz.x = ceil(width);
    sz.y = ceil(height);
}

bool
wxHexView::CreateBitmap()
{
    wxClientDC dc(this);
    if (!char_size_.GetWidth())
        CalcCharSize(dc, char_size_);

    wxSize sz = dc.GetSize();
    column_mode_ = CalcColumnMode(sz);

    if (internal_bmp_.IsOk()) {
        wxSize bmp_sz(internal_bmp_.GetSize());
        bmp_sz /= scale_bmp_;
        if (sz.x <= bmp_sz.x && sz.y <= bmp_sz.y) return true;
    }
  
#if defined(__WXMAC__)
    // https://github.com/wxWidgets/wxWidgets/commit/ab605398107b153d89305d494e12415166f848cc
    wxRect rect(sz);
    internal_bmp_= dc.GetAsBitmap(&rect);
    scale_bmp_ = internal_bmp_.GetWidth() / sz.GetWidth();
#else
    scale_bmp_ = dc.GetContentScaleFactor();
    internal_bmp_.CreateScaled(sz.x, sz.y, wxBITMAP_SCREEN_DEPTH, scale_bmp_);
#endif

    return true;
}

bool
wxHexView::CreateGlyphs()
{
    wxClientDC dc(this);
    if (!char_size_.GetWidth())
        CalcCharSize(dc, char_size_);
    if (glyphs_bmp_.size()) return true;
  
    /**
     * https://en.wikipedia.org/wiki/Code_page_437
     * var symbol = []; $('table.chset td').each((x, i) => { symbols.push(  $('small', i)[0].innerText ); } )
     * var str = ""; for (var i = 0; i < symbols.length; i++) { str += "0x" + symbols[i] + ", "; if (i%16 == 15) str += "\n"; }
     */
    static const wchar_t symbols[] = {
        0x0000, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022, 0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
        0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8, 0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B2, 0x25BC,
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x2302,
        0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7, 0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
        0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9, 0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x20A7, 0x0192,
        0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA, 0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
        0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556, 0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
        0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F, 0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
        0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B, 0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
        0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4, 0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
        0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248, 0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0,
    };
  
    unsigned char i = 0;
    do {
        glyphs_bmp_.emplace_back();
        wxBitmap &bmp = glyphs_bmp_.back();
#if defined(__WXMAC__)
        bmp.CreateScaled(char_size_.x, char_size_.y, 64, scale_bmp_);
#else
        bmp.CreateScaled(char_size_.x, char_size_.y, wxBITMAP_SCREEN_DEPTH, scale_bmp_);
#endif
        ClearBitmap(bmp);
        wxMemoryDC dc_bmp(bmp);
        wxGraphicsContext *gc_bmp = wxGraphicsContext::Create(dc_bmp);
        gc_bmp->SetFont(console_font_, g_very_light_gray);
        gc_bmp->DrawText(symbols[i], 0, 0);
        delete gc_bmp;
        i++;
    } while (i);
  
    return true;
}

void
wxHexView::DrawHex(wxGraphicsContext *gc)
{
    uint64_t addr = addr_start_;
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;
  
    wxColour *next_clr = &g_very_light_gray;
    wxColour *last_clr = next_clr;
    gc->SetFont(console_font_, *next_clr);
  
    int x0 = COLUMN_NARROW ? 0 : 10;

    // Draw Vertical
    gc->SetPen(g_dark_gray_pen);
    for (int x = 8; x < LINE_SIZE; x+= 8) {
        const int xx = (x0 + x * 3 - 1) * char_size_.x + (char_size_.x / 2);
        wxPoint pt1 (xx, 0);
        wxPoint pt2 (xx, viewport_.y * char_size_.y);
        gc->StrokeLine(pt1.x, pt1.y, pt2.x, pt2.y);
    }

    for (int y = 0; y < viewport_.y; y++) {
        if (addr >= addr_max) break;

        if (COLUMN_NARROW) {
            if (y % 5 == 0) continue;
        }
      
      
#if 0
        wxString str;
        for (int x = 0; x < LINE_SIZE; x++) {
            uint8_t ch;
          
            if (addr >= addr_max) break;

            if (data_provider_->CharAt(addr++, ch)) {
                str += wxString::Format("%02X ", ch);
            } else {
                str += "   ";
            }
        }
        gc->DrawText(str, x0 * char_size_.x, y * char_size_.y);

#else
        for (int x = 0; x < LINE_SIZE; x++) {
            uint8_t ch;
            wxString str;
            if (addr >= addr_max) break;
            if (! data_provider_) break;

            if (data_provider_->CharAt(addr++, ch)) {
                str = wxString::Format("%02X", ch);
                next_clr = (ch == 0) ? &g_light_gray : &g_very_light_gray;
            } else
                continue;

            if (last_clr != next_clr) {
                last_clr = next_clr;
                gc->SetFont(console_font_, *next_clr);
            }

            gc->DrawText(str, (x0 + x * 3) * char_size_.x, y * char_size_.y);
        }
#endif
    }
}

void
wxHexView::DrawAddress(wxGraphicsContext *gc)
{
    uint64_t addr = addr_start_;
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;
  
    gc->SetFont(console_font_, g_dark_blue);
  
    int x0 = 0;

    for (int y = 0; y < viewport_.y; y++) {
        if (addr >= addr_max) break;

        if (COLUMN_NARROW) {
            if (y % 5 != 0) {
                addr += LINE_SIZE;
                continue;
            }
        }
        gc->DrawText(wxString::Format("%8" PRIx64, addr), x0 * char_size_.x, y * char_size_.y);
        if (!COLUMN_NARROW) addr += LINE_SIZE;
    }
}

void
wxHexView::DrawAscii(wxGraphicsContext *gc)
{
    uint64_t addr = addr_start_;
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;
  
    wxColour *next_clr = &g_very_light_gray;
    wxColour *last_clr = next_clr;
  
    // gc->SetFont(console_font_, *next_clr);
  
    int x0 = COLUMN_NARROW ?
        LINE_SIZE*3 + 2 :
        10 + (LINE_SIZE*3) + 2
        ;
  
    // Draw Vertical
    gc->SetPen(g_dark_gray_pen);
    for (int x = 8; x < LINE_SIZE; x+= 8) {
        const int xx = (x0 + x) * char_size_.x;
        wxPoint pt1 (xx, 0);
        wxPoint pt2 (xx, viewport_.y * char_size_.y);
        gc->StrokeLine(pt1.x, pt1.y, pt2.x, pt2.y);
    }
  
    for (int y = 0; y < viewport_.y; y++) {
        if (addr >= addr_max) break;

        if (COLUMN_NARROW) {
            if (y % 5 == 0) continue;
        }
#if 0
        wxString str;
        for (int x = 0; x < LINE_SIZE; x++) {
            uint8_t ch;
          
            if (addr >= addr_max) break;

            if (data_provider_->CharAt(addr++, ch)) {
                if (ch >= 0x20 && ch <= 126)
                    str += ch;
                else
                    str += '.';
            } else {
                str += ' ';
            }
        }
        gc->DrawText(str, x0 * char_size_.x, y * char_size_.y);
#else
        for (int x = 0; x < LINE_SIZE; x++) {
            uint8_t ch;
            if (addr >= addr_max) break;

            if (! data_provider_) break;

            if (data_provider_->CharAt(addr++, ch)) {
                next_clr = ch == 0 ? &g_light_gray : &g_very_light_gray;
            } else
                continue;
          
            if (last_clr != next_clr) {
                last_clr = next_clr;
            }
          
            if (ch != 0 || ch != ' ') {
                gc->DrawBitmap(glyphs_bmp_[ch], (x0 + x) * char_size_.x, y * char_size_.y,
                    glyphs_bmp_[0].GetWidth() / scale_bmp_,
                    glyphs_bmp_[0].GetHeight() / scale_bmp_);
            }
            // gc->DrawText(ch, (x0 + x) * char_size_.x, y * char_size_.y);
        }
#endif
    }
}

void
wxHexView::DrawCursor(wxGraphicsContext *gc)
{
    if (!cursor_blink_) return;

    gc->SetBrush( wxBrush(g_very_light_gray) );
    gc->SetPen( *wxTRANSPARENT_PEN );
    wxPoint pt;
  
    if (selecting_) return;
  
    AddressToPixel(cursor_addr_, pt, cursor_hot_, cursor_hmod_ );

    gc->DrawRectangle(pt.x, pt.y,
        2, char_size_.y);
}

void
wxHexView::DrawHighlight(wxGraphicsContext *gc)
{
    gc->SetBrush( wxBrush(g_dark_gray) );
    gc->SetPen( *wxTRANSPARENT_PEN );

    wxPoint pt;
    AddressToPixel(cursor_addr_, pt, !cursor_hot_, 0);
    double w, h;
    gc->GetSize(&w, &h);
    gc->DrawRectangle(0, pt.y, w, char_size_.y);

    gc->SetBrush( wxBrush(g_purple) );
    gc->DrawRectangle(pt.x, pt.y,
        char_size_.x * (!cursor_hot_ ? 2 : 1), char_size_.y);

    if (selecting_) { do {
        uint64_t a, b;
        a = addr_begin_;
        b = addr_end_;

        int h = viewport_.y;
        if (COLUMN_NARROW) h -= 1 + (h / 5);
        if (h <= 0) break;
        if (b < addr_start_) break;
        uint64_t addr_stop = addr_start_ + (h * LINE_SIZE) - 1;
        if (a > addr_stop) break;

        gc->SetBrush( wxBrush(g_select_blue) );

        uint32_t x_hex = COLUMN_NARROW ? 0 : 10;
        uint32_t x_text = x_hex + (LINE_SIZE * 3) + 2;

        uint64_t addr = addr_start_;
        for (int y = 0; y < viewport_.y; y++) {
            if (COLUMN_NARROW) {
                if (y % 5 == 0) continue;
            }

            if (b < addr) break;

            uint64_t addr_next = addr + LINE_SIZE;
            if (a >= addr_next) { addr = addr_next; continue; }

            int x0 = a > addr ? (a - addr) : (addr - addr);
            int x1 = b > addr_next ? addr_next - addr : b - addr;

            int w = (x1 - x0);
            if (w > 0) {
                gc->DrawRectangle((x_text + x0) * char_size_.x,
                    (y * char_size_.y),
                    w * char_size_.x,
                    char_size_.y);
              
                w = w * 3 - 1;
              
                gc->DrawRectangle((x_hex + x0 * 3) * char_size_.x,
                    (y * char_size_.y),
                    w * char_size_.x,
                    char_size_.y);
            }

            addr = addr_next;
        }
    } while(false); }
}

void
wxHexView::SetDataProvider(wxHexDataProvider *data_provider)
{
    data_provider_ = data_provider;
    addr_start_ = 0;
    cursor_addr_ = 0;
    redraw_bmp_ = true;
    Refresh(false);
    AdjustScrollbars(0);
    AdjustCursor();
}

int
wxHexView::CalcColumnMode(wxSize &sz)
{
    int column_mode = 0;
    int max_width = (sz.GetWidth() - scrollbar_width_) / char_size_.x;
    // 8-Hex: 8 | (8 * 3) + 1 + 8  [mode-0]
    if (max_width < 44) {
        sz.SetWidth(34 * char_size_.x);
        column_mode = 0;
    // 8-Hex: 8 + 2 + (8 * 3) + 1 + 8  [mode-1]
    } else if (max_width < 76) {
        sz.SetWidth(44 * char_size_.x);
        column_mode = 1;
    // 16-Hex: 8 + 2 + (16 * 3) + 1 + 16
    } else if (max_width < 108) {
        sz.SetWidth(76 * char_size_.x);
        column_mode = 2;
    // 24-Hex: 8 + 2 + (24*3) + 1 + 24 
    } else if (max_width < 140) {
        sz.SetWidth(108 * char_size_.x);
        column_mode = 3;
    // 32-Hex: 8 + 2 + (32*3) + 1 + 32
    } else {
        sz.SetWidth(140 * char_size_.x);
        column_mode = 4;
    }
    int max_height = sz.GetHeight() / char_size_.y;
    sz.SetHeight(max_height * char_size_.y);
    return column_mode;
}

void
wxHexView::AdjustScrollbars(int pos)
{
    if (!data_provider_) return;

    if (viewport_.y == 0) return;

    int range = ((double)data_provider_->GetSize() + LINE_SIZE) / LINE_SIZE;
    if (range == GetScrollRange(wxVERTICAL)) return;

    int height = COLUMN_NARROW ? viewport_.y - (viewport_.y / 5) : viewport_.y;

    bool need_scrollbar = range > height;
    if (need_scrollbar) {
        int thumbSize = range / height;
        SetScrollbar(wxVERTICAL, pos, thumbSize, range);
    } else {
        addr_start_ = 0;
        SetScrollbar(wxVERTICAL, 0, 0, -1);
#if defined(__WXMSW__)
        Refresh(false);
#endif
    }
}

void
wxHexView::AdjustCursor()
{
    if (!data_provider_) return;
    if (viewport_.y == 0) return;

    if (cursor_addr_ < 0) 
        cursor_addr_ = 0;
    else if (cursor_addr_ >= data_provider_->GetSize()) 
        cursor_addr_ = data_provider_->GetSize()-1;

    counter_blink_ = 0;
    cursor_blink_ = true;
}

void
wxHexView::AddressToPixel(uint64_t addr, wxPoint &pt, bool cursor_hot, unsigned char cursor_hmod)
{
    wxPoint cur;
    AddressToCell(addr, cur);

    uint32_t y0 = COLUMN_NARROW ? 1 + (cur.y / 4) : 0;
    uint32_t x0 = COLUMN_NARROW ? 0 : 10;
    uint32_t x2 = x0 + (LINE_SIZE * 3) + 2;
    if (cursor_hot) {
        if (cursor_hmod == 1) x0 += 1;
    }
    
    int yl = (y0 + cur.y) * char_size_.y;
    int xl = ((cursor_hot ? x0 : x2) + (cur.x * (cursor_hot ? 3 : 1))) * char_size_.x;

    pt.x = xl;
    pt.y = yl;
}

bool
wxHexView::AddressToCell(uint64_t addr, wxPoint &cur)
{
    int h = COLUMN_NARROW ? viewport_.y - (1 + ((viewport_.y-1) / 5)) : viewport_.y;
  
    cur.x =
        (addr - addr_start_) % LINE_SIZE;
    cur.y =
        (addr - addr_start_) / LINE_SIZE;
  
    return cur.x >= 0 && cur.y >= 0 && cur.x < viewport_.x && cur.y < h;
}

bool
wxHexView::MouseToAddress(wxPoint cur, uint64_t &addr, bool &cursor_hot, unsigned char &cursor_hmod, bool locked)
{
    if (! data_provider_) return false;

    uint32_t x0 = COLUMN_NARROW ? 0 : 10;
    uint32_t x1 = x0 + (LINE_SIZE * 3) - 1;
    uint32_t x2 = x1 + 1 + 2;
    uint32_t x3 = x2 + LINE_SIZE;
    uint32_t y0 = COLUMN_NARROW ? 1 + (cur.y / 5) : 0;

    if (COLUMN_NARROW && cur.y % 5 == 0) return false;
    cur.y -= y0;

    if (!COLUMN_NARROW && cur.x == x0 - 1) {
        if (locked && cursor_hot != true) return false;
    
        cur.x = 0;
        if (cur.y == 0 && addr_start_ == 0) {
            cursor_hmod = 0;
        } else {
            cursor_hmod = 2;
        }
        cursor_hot = true;
    } else if (cur.x >= x0 && cur.x < x1) {
        cur.x -= x0;
        if (locked && cursor_hot != true) return false;

        cursor_hmod = cur.x % 3;
        cur.x /= 3;
        if (cursor_hmod == 2) cur.x += 1;
        cursor_hot = true;
    } else
    if (cur.x >= x2 && cur.x < x3) {
        cur.x -= x2;
        if (locked && cursor_hot != false) return false;
        cursor_hot = false;
        cursor_hmod = 0;
    } else
        return false;

    addr = addr_start_ + (cur.y * LINE_SIZE) + cur.x;
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;

    if (addr < 0) { 
        addr = 0;
    } else if (addr >= addr_max) {
        addr = addr_max - 1;
        AddressToCell(addr, cur);
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////

void
wxHexView::OnPaint(wxPaintEvent &evt)
{
    if (!CreateBitmap()) return;
    if (!CreateGlyphs()) return;

#if defined(__WXMSW__)
    wxBufferedPaintDC dc(this);

    dc.SetBackground(wxBrush(g_very_dark_gray));
    dc.Clear();
#else
    wxPaintDC dc(this);
    dc.SetBackground(wxNullBrush);
#endif
    
    wxGraphicsContext *gc = wxGraphicsContext::Create( dc );
    //gc->SetAntialiasMode(wxANTIALIAS_NONE);
    if (gc)
    {
        DrawHighlight(gc);

#if USE_BITMAP_CACHE
        if (internal_bmp_.IsOk()) {
            if (redraw_bmp_) {
                redraw_bmp_ = false;
              
                ClearBitmap(internal_bmp_);
                wxMemoryDC dc_img(internal_bmp_);
                wxGraphicsContext *gc_img = wxGraphicsContext::Create(dc_img);
                //gc_img->SetAntialiasMode(wxANTIALIAS_NONE);
#else
                wxGraphicsContext *gc_img = gc;
#endif
                DrawAddress(gc_img);
                DrawHex(gc_img);
                DrawAscii(gc_img);
#if USE_BITMAP_CACHE
                delete gc_img;
            }

            gc->DrawBitmap(internal_bmp_, 0, 0, internal_bmp_.GetWidth()/ scale_bmp_, internal_bmp_.GetHeight() /scale_bmp_);
        }
#endif
      
        //#if defined(__WXMAC__)
        // CGContextRef const * gc_native = reinterpret_cast<CGContextRef *>(gc_img->GetNativeContext());
        // gc_img->ClearRectangle(0, 0, 100, 100);
        //#elif defined(__WXMSW__)
        // Graphics * const gc_native = reinterpret_cast<Graphics *>(gc_img->GetNativeContext());
        // gc_native->Clear(Color(128, 0, 0, 0));
        //#elif defined(__WXGTK3__)
        // cairo_t const * gc_native = reinterpret_cast<cairo_t*>(gc_img->GetNativeContext());
        //#endif
      
        DrawCursor(gc);
      
        delete gc;
    }
}

void
wxHexView::OnChar(wxKeyEvent &evt)
{
    if (! data_provider_) return;

    int line_size = LINE_SIZE;
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;
    switch ( evt.GetKeyCode() )
    {
        case WXK_UP:
            cursor_addr_ = (line_size > cursor_addr_) ? cursor_addr_ : cursor_addr_ - line_size;
            break;
        case WXK_DOWN:
            cursor_addr_ = (cursor_addr_ + line_size >= addr_max) ? cursor_addr_ : cursor_addr_ + line_size;
            break;
        case WXK_LEFT:
            if (cursor_hot_) {
                if (cursor_hmod_ == 1) cursor_hmod_ = 0;
                else if (cursor_addr_ > 0) {
                    cursor_hmod_ = 1;
                    cursor_addr_ -= 1;
                }
            } else
                cursor_addr_ = (1 > cursor_addr_) ? 0 : cursor_addr_ - 1;
            break;
        case WXK_RIGHT:
            if (cursor_hot_) {
                if (cursor_hmod_ == 0) cursor_hmod_ = 1;
                else if (cursor_addr_ + 1 < addr_max) {
                    cursor_hmod_ = 0;
                    cursor_addr_ += 1;
                }
            } else
                cursor_addr_ = (cursor_addr_ + 1 >= addr_max) ? cursor_addr_ : cursor_addr_ + 1;
        
            break;
        default:
            evt.Skip();
            return;
    }
    selecting_ = false;
    ScrollToCursor();
    redraw_bmp_ |= false;
    Refresh(false);
    AdjustCursor();
}

void
wxHexView::OnSize(wxSizeEvent &evt)
{
    wxSize sz = evt.GetSize();

    if (!char_size_.x) {
        wxClientDC dc(this);
        CalcCharSize(dc, char_size_);
    }

    if (char_size_.y)
        viewport_.y = sz.y / char_size_.y;
    if (char_size_.x)
        viewport_.x = sz.x / char_size_.x;

    column_mode_ = CalcColumnMode(sz);
    redraw_bmp_ |= true;
    int pos = addr_start_ / LINE_SIZE;
    addr_start_ = pos * LINE_SIZE;

#if defined(__WXMSW__)
    Refresh(false);
#endif
    AdjustScrollbars(pos);
    AdjustCursor();
}

void
wxHexView::OnScrollBar(wxScrollWinEvent &evt)
{
    if (evt.GetOrientation() == wxVERTICAL) {
        if (evt.GetEventType() == wxEVT_SCROLLWIN_BOTTOM)
            wxLogDebug("You scrollwin Bottom: %d", evt.GetPosition())
            ;
        else if (evt.GetEventType() == wxEVT_SCROLLWIN_TOP)
            wxLogDebug("You scrollwin Top: %d", evt.GetPosition())
            ;
        else if (evt.GetEventType() == wxEVT_SCROLLWIN_LINEDOWN)
            wxLogDebug("You scrollwin Line Down: %d", evt.GetPosition()) // LineDown()
            ;
        else if (evt.GetEventType() == wxEVT_SCROLLWIN_LINEUP)
            wxLogDebug("You scrollwin Line Up: %d", evt.GetPosition()) // LineUp()
            ;
        else if (evt.GetEventType() == wxEVT_SCROLLWIN_PAGEUP ||
            evt.GetEventType() == wxEVT_SCROLLWIN_PAGEDOWN ||
            evt.GetEventType() == wxEVT_SCROLLWIN_THUMBTRACK ||
            evt.GetEventType() == wxEVT_SCROLLWIN_THUMBRELEASE)
        {
            ScrollToPos(evt.GetPosition());
        }
    }
}

void
wxHexView::ScrollToPos(int position)
{
    int range = GetScrollRange(wxVERTICAL);
    if (position < 0) position = 0;
    else if (position >= range) position = range -1;
  
    uint64_t new_addr_start = position * LINE_SIZE;

    if (addr_start_ == new_addr_start) return;
  
    addr_start_ = new_addr_start;
    redraw_bmp_ |= true;
#if defined(__WXMSW__)
    Refresh(false);
#endif
  
    AdjustCursor();
    SetScrollPos(wxVERTICAL, position);
}

void
wxHexView::ScrollToAddrStart(uint64_t addr)
{
    uint64_t addr_max = data_provider_ ? data_provider_->GetSize() : 0;

    if (addr < 0) addr = 0;
    if (addr >= addr_max) addr = addr_max - 1;
  
    int range = GetScrollRange(wxVERTICAL);
    int position = 0;
  
    addr -= addr % LINE_SIZE;
    addr_start_ = addr;
    if (addr_max) position = addr_start_ * range / addr_max;

    redraw_bmp_ |= true;
    Refresh(false);
  
    AdjustCursor();
    SetScrollPos(wxVERTICAL, position);
}

void
wxHexView::ScrollToCursor()
{
    wxPoint cur;
    int h = COLUMN_NARROW ? viewport_.y - (1 + ((viewport_.y-1) / 5)) : viewport_.y;
  
    if (AddressToCell(cursor_addr_, cur)) return;
    uint64_t addr = cursor_addr_;
    addr -= addr % LINE_SIZE;
  
    if (!(cur.y < 0)) {
        addr -= LINE_SIZE * (h - 1);
    }
  
    ScrollToAddrStart(addr);
}

void
wxHexView::OnCursorTimer(wxTimerEvent &evt)
{
    counter_blink_ = (counter_blink_+1)% 10;
    if (counter_blink_ == 0) {
        cursor_blink_ = !cursor_blink_;
        Refresh(false);
    }
    evt.Skip();
}

void
wxHexView::OnSetFocus(wxFocusEvent &evt)
{
    counter_blink_ = 0;
    cursor_blink_ = true;
    cursor_timer_.Start(33);
    Refresh(false);
}

void
wxHexView::OnKillFocus(wxFocusEvent &evt)
{
    cursor_timer_.Stop();
    cursor_blink_ = false;
    Refresh(false);
}

void
wxHexView::OnMouseWheel(wxMouseEvent &evt)
{
    wheel_rotation_ += evt.GetWheelRotation();
    int lines = wheel_rotation_ / evt.GetWheelDelta();
    wheel_rotation_ -= lines * evt.GetWheelDelta();
  
    if (lines != 0)
    {
        if ( evt.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL ) {
            int offset = - lines * LINE_SIZE;
            uint64_t addr = (offset < 0 && -offset > addr_start_) ? 0 : addr_start_ + offset;
            ScrollToAddrStart(addr);
        }
    }
}

void
wxHexView::OnMouseLeftDown(wxMouseEvent &evt)
{
    wxPoint cur;
    evt.Skip();
  
    if (!char_size_.x) return;

    cur.x = evt.GetPosition().x / char_size_.x;
    cur.y = evt.GetPosition().y / char_size_.y;
    selecting_ = false;
  
    if (!MouseToAddress(cur, dragging_addr_, cursor_hot_, dragging_hmod_, false))
        return;
  
    cursor_addr_ = dragging_addr_;
    cursor_hmod_ = dragging_hmod_;
  
    if (cursor_hot_ && dragging_hmod_ == 2) {
        if (((dragging_addr_ + 1) % LINE_SIZE) == 0) {
            cursor_hmod_ = 1;
        } else {
            cursor_addr_ = dragging_addr_ + 1;
            cursor_hmod_ = 0;
        }
    }
  
    CaptureMouse();
    redraw_bmp_ |= false;
    Refresh(false);
}

void
wxHexView::OnMouseLeftUp(wxMouseEvent &evt)
{
    if (wxWindow::GetCapture() == this) {
        ReleaseMouse();
        autoscroll_timer_.Stop();
        autoscroll_counter_ = 0;
    }
}

void
wxHexView::OnMouseMove(wxMouseEvent &evt)
{
    if (wxWindow::GetCapture() == this) {
        if (!char_size_.x) return;
        wxPoint cur;

        cur.x = evt.GetPosition().x / char_size_.x;
        cur.y = evt.GetPosition().y / char_size_.y;
        if (evt.GetPosition().y < 0) {
            autoscroll_speed_ = -cur.y;
            autoscroll_offset_ = -1 * LINE_SIZE;
            if (! autoscroll_timer_.IsRunning()) autoscroll_timer_.Start(25);
            return;
        } else if (cur.y >= viewport_.y) {
            autoscroll_speed_ = cur.y - viewport_.y;
            autoscroll_offset_ = +1 * LINE_SIZE;
            if (! autoscroll_timer_.IsRunning()) autoscroll_timer_.Start(25);
            return;
        } else {
            autoscroll_timer_.Stop();
        }
    
        if (!MouseToAddress(cur, cursor_addr_, cursor_hot_, cursor_hmod_, true)) return;
      
        if (cursor_addr_ < dragging_addr_) {
            addr_begin_ = cursor_addr_;
            addr_end_ = dragging_addr_ + (dragging_hmod_ == 1 ? 1 : 0);
        } else {
            addr_begin_ = dragging_addr_;
            addr_end_ = cursor_addr_ + 1;
        }

        selecting_ = true;
        redraw_bmp_ |= false;
        Refresh(false);
    }
}

void
wxHexView::OnAutoScrollTimer(wxTimerEvent &evt)
{
    if (autoscroll_offset_) {
        autoscroll_counter_ += 1 + autoscroll_speed_;
        uint64_t addr = addr_start_;
        while (autoscroll_counter_ >= 5) {
            autoscroll_counter_ -= 5;
            addr = (autoscroll_offset_ < 0 && -autoscroll_offset_ >= addr) ? 0 : addr + autoscroll_offset_;
        }
        if (addr_start_ != addr)
            ScrollToAddrStart(addr);
    }
}

void
wxHexView::ClearBitmap(wxBitmap &bmp)
{
    MyPixelData data(bmp);
    if (data) {
        MyPixelData::Iterator p(data);
        //memset(p.m_ptr, 0, data.GetHeight() * data.GetRowStride());
        for (int y = 0; y < data.GetHeight(); ++y)
        {
            MyPixelData::Iterator rowStart = p;
            for (int x = 0; x < data.GetWidth(); ++x, ++p)
            {
                p.Red() = 0x00;
                p.Green() = 0x00;
                p.Blue() = 0x00;
                p.Alpha() = wxALPHA_TRANSPARENT;
            }
            p = rowStart;
            p.OffsetY(data, 1);
        }
    }
}
