#ifndef PAWN_HPP
#define PAWN_HPP

#define SN_TARGET_PS2

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#include "SynchronizationCall.hpp"
#include "Utils.hpp"

#include <boost/optional.hpp>
#include <string>

extern AMX *g_pAMX;

Optional<std::string> string_from_cell(AMX *amx, cell p);

#endif
