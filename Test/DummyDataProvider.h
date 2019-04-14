#pragma once

#include "wxHexView.h"

class DummyDataProvider: public wxHexDataProvider
{
public:
    virtual uint64_t GetSize() wxOVERRIDE {
        return 256 * 10;
    }

    virtual bool CharAt(uint64_t pos, uint8_t &ch) wxOVERRIDE {
        if (pos >= GetSize()) return false;
        ch = pos % 256;
        return true;
    }
};
