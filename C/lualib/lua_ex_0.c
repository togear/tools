/*
 * =====================================================================================
 *
 *       Filename:  lua_ex_0.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年05月11日 09时31分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h> 
#include <lua.h> 
#include <lauxlib.h> 
#include <lualib.h> 
 
int main(int argc, char *argv[]) 
{ 
    lua_State *L = luaL_newstate(); 
    luaL_openlibs(L); 
    luaL_dofile(L, "helloworld.lua"); 
    lua_close(L); 
    return 0; 
}

