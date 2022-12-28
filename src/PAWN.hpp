#pragma once
#define SN_TARGET_PS2

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#include <string>

namespace PAWN {
    std::string CellToString(cell c, AMX* amx, cell len = -1);
}
