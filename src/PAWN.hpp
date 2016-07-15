#pragma once
#define SN_TARGET_PS2

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#include <string>

namespace PAWN {
    void SetAMX(AMX *amx);
    AMX *GetAMX();

    std::string CellToString(cell c);
}
