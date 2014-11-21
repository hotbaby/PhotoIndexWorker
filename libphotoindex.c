/*************************************************************************
> File Name: gworker.c
> Author: yy
> Mail: mengyy_linux@163.com
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

#include <lauxlib.h>
#include <lua.h>

#define TRUE            (1)
#define FALSE           (0)
#define BUF_SIZE        (32*1024)   /* 32k */
#define MODULE_NAME     ("libphotoindex")
#define WORKER_META     ("libphotoindex.meta")

typedef unsigned int bool;


typedef struct
{
    bool    initialized;
}photoindex_ctx_t;

static int libphotoindex_lua_gc(lua_State *L)
{
    return 0;
}

static int libphotoindex_lua_initialize(lua_State *L)
{
    size_t sz;
    photoindex_ctx_t * ctx = NULL;

    fprintf(stderr, "call function %s\n", __func__);

    ctx = (photoindex_ctx_t*)lua_newuserdata(L, sizeof(*ctx));
    ctx->initialized = TRUE;

    luaL_getmetatable(L, WORKER_META);
    lua_setmetatable(L, -2);

    return 1;
}

static int libphotoindex_lua_test_func(lua_State *L)
{
    fprintf(stderr, "call function %s\n", __func__);

    photoindex_ctx_t *ctx = NULL;
    const char *s = NULL;

    ctx = lua_touserdata(L, 1);
    if (ctx->initialized != TRUE)
    {
        lua_pushboolean(L, FALSE);
        return 1;
    }

    /* call test lib function */
    s = strdup(lua_tostring(L, 2));
    test_func(s);
    free((void*)s);
    s = NULL;

    lua_pushboolean(L, TRUE);

    return 1; /* number of results */
}

static const luaL_Reg libphotoindex[] = {
    {"__gc",       libphotoindex_lua_gc},
    {"initialize", libphotoindex_lua_initialize},
    {"test_func", libphotoindex_lua_test_func},
    {NULL, NULL}
};

static int meta_lua_test(lua_State *L)
{
    fprintf(stderr, "call function %s.\n", __func__);

    photoindex_ctx_t *ctx = NULL;
    const char *s = NULL;

    ctx = lua_touserdata(L, 1);
    if (ctx->initialized != TRUE)
    {
        lua_pushboolean(L, FALSE);
        return 1;
    }

    s = strdup(lua_tostring(L, 2));
    fprintf(stderr, "%s\n", s);
    free((void*)s);
    s = NULL;

    lua_pushboolean(L, TRUE);
    return 1;
}

static const luaL_Reg meta[] = {
    {"meta_func", meta_lua_test},
    {NULL, NULL}
};

int luaopen_libphotoindex(lua_State *L)
{
#if 1
    /* ceate metatable */
    luaL_newmetatable(L, WORKER_META);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);

    /* metatable.__index = metatable */
    lua_rawset(L, -3);

    /* Fill metatable */
    luaL_openlib(L, NULL, meta, 0);

    lua_pop(L, 1);
#else

    luaL_newmetatable(L, WORKER_META);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, meta);
    lua_pop(L, 1);
#endif

    luaL_register(L, MODULE_NAME, libphotoindex);

    return 0;
}
