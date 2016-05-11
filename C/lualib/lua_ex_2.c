/*
 * =====================================================================================
 *
 *       Filename:  lua_ex_2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年05月11日 09时28分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *         gcc lua_ex_2.c -o lua_ex_2 -I/usr/local/include/ -L/usr/local/lib/ -llua -lm -ldl 
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 * myTable = {
 *     [0] = { ["a"] = 4, ["b"] = 2 },
 *     [1] = { ["a"] = 13, ["b"] = 37 }
 * }
 * */
#include <stdlib.h>
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main()
{
    int res;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L); /*  bottom table */

    lua_newtable(L); /*  upper table */

    lua_pushinteger(L, 0);
    lua_pushinteger(L, 4);
    lua_settable(L, -3);  /*  uppertable[0] = 4; pops 0 and 4 */
    lua_pushinteger(L, 0);
    lua_insert(L, -2); /*  swap uppertable and 0 */
    lua_settable(L, -3); /*  bottomtable[0] = uppertable */
    lua_setglobal(L, "t"); /*  set bottom table as global variable t */

    res = luaL_dostring(L, "print(t[0][0] == 4)");
    if(res)
    {
        printf("Error: %s\n", lua_tostring(L, -1));
    }

    return 0;
}


