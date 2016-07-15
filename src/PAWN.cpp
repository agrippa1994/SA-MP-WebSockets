#include "PAWN.hpp"
#include <boost/scope_exit.hpp>

AMX *g_amx = nullptr;

void PAWN::SetAMX(AMX *amx) {
    g_amx = amx;
}

AMX *PAWN::GetAMX() {
    return g_amx;
}

std::string PAWN::CellToString(cell c) {
    cell len = 0, *addr = 0;

    amx_GetAddr(GetAMX(), c, &addr);
    amx_StrLen(addr, &len);

    if(!len)
        return {}; // Empty string

    len++; // Zero terminated string
    char *buffer = new char[len];
    amx_GetString(buffer, addr, 0, len);

    BOOST_SCOPE_EXIT_ALL(&) {
        if(buffer)
            delete [] buffer;
    };

    return std::string(buffer);
}
