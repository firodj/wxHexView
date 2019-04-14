#pragma once

#include <cstdint>
#include <wx/dynarray.h>

class wxHexLine
{
public:
    wxHexLine();

private:
    uint64_t addr_;
    wxString chars;
};

class wxHexDataProvider
{
public:
    wxHexDataProvider() {}
    virtual ~wxHexDataProvider() {}
    virtual uint64_t GetSize() { return 0; }
    virtual bool CharAt(uint64_t pos, uint8_t &ch) { return false; }
};

class wxHexView: public wxWindow
{
    wxDECLARE_DYNAMIC_CLASS(wxHexView);

public:
    wxHexView();
    wxHexView(wxWindow *parent, wxWindowID id);
    virtual ~wxHexView();
    void SetDataProvider(wxHexDataProvider *data_provider);

protected:
    void Init();
    void DrawBitmap();
    bool CreateBitmap();
    bool CreateGlyphs();

    void DrawCursor(wxGraphicsContext *gc);
    void DrawHighlight(wxGraphicsContext *gc);
    void DrawAddress(wxGraphicsContext *gc);
    void DrawHex(wxGraphicsContext *gc);
    void DrawAscii(wxGraphicsContext *gc);

    virtual void AdjustScrollbars(int pos);
    int CalcColumnMode(wxSize &sz);
    void CalcCharSize(wxDC &dc, wxSize &sz);
    void AdjustCursor();
    bool MouseToAddress(wxPoint cur, uint64_t &addr, bool &cursor_hot, unsigned char &cursor_hmod, bool locked);
    void AddressToPixel(uint64_t addr, wxPoint &pt, bool cursor_hot, unsigned char cursor_hmod);
    bool AddressToCell(uint64_t addr, wxPoint &cur);
    void ScrollToPos(int position);
    void ScrollToAddrStart(uint64_t addr);
    void ScrollToCursor();
    void ClearBitmap(wxBitmap &bmp);
  
    // Event Handler
    void OnPaint(wxPaintEvent &evt);
    void OnChar(wxKeyEvent &evt);
    void OnSize(wxSizeEvent &evt);
    void OnScrollBar(wxScrollWinEvent &evt);
    void OnCursorTimer(wxTimerEvent &evt);
    void OnAutoScrollTimer(wxTimerEvent &evt);
    void OnSetFocus(wxFocusEvent &evt);
    void OnKillFocus(wxFocusEvent &evt);
    void OnMouseWheel(wxMouseEvent &evt);
    void OnMouseLeftDown(wxMouseEvent &evt);
    void OnMouseLeftUp(wxMouseEvent &evt);
    void OnMouseMove(wxMouseEvent &evt);

private:
    double scale_bmp_;
    bool cursor_blink_;
    int counter_blink_;
    int scrollbar_width_;
    bool redraw_bmp_;
    bool cursor_hot_; // hex (1) or text (0)
    unsigned char cursor_hmod_; // high nibble (0), low nibble(1), space (2)
    uint64_t cursor_addr_;
    int wheel_rotation_;
  
    wxBitmap internal_bmp_;
    std::vector<wxBitmap> glyphs_bmp_;

    uint64_t addr_begin_, addr_end_; // selecting
    bool selecting_;
    uint64_t dragging_addr_;
    unsigned char dragging_hmod_;

    wxTimer cursor_timer_, autoscroll_timer_;
    int autoscroll_offset_;
    int autoscroll_speed_, autoscroll_counter_;
    wxFont console_font_;
    wxSize char_size_;
    wxSize viewport_;
    uint64_t addr_start_;

    int column_mode_;
    wxHexDataProvider *data_provider_;

    DECLARE_EVENT_TABLE()
};
