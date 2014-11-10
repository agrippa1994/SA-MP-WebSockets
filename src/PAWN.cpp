#include "PAWN.hpp"
#include <boost/scope_exit.hpp>

AMX *g_pAMX = 0;

Optional<std::string> string_from_cell(AMX *amx, cell p)
{
    cell len = 0, *addr = 0;

    amx_GetAddr(amx, p, &addr);
    amx_StrLen(addr, &len);

    if(!len)
        return nullptr;

    len++;
    char *buffer = new char[len];
    amx_GetString(buffer, addr, 0, len);

    BOOST_SCOPE_EXIT_ALL(&)
    {
        if(buffer)
            delete [] buffer;
    };

    return std::string(buffer);
}
