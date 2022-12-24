#include "PAWN.hpp"

std::string PAWN::CellToString(cell c, AMX *amx, cell len) {
    cell *addr = 0;

	if(amx_GetAddr(amx, c, &addr) != AMX_ERR_NONE)
		return {}; // Empty string

	if(len == -1) if(amx_StrLen(addr, &len) != AMX_ERR_NONE)
		return {};

    if(!len)
        return {};

	std::string buffer;
	buffer.resize(len);
    amx_GetString(&buffer[0], addr, 0, len + 1);

    return std::string(buffer);
}
