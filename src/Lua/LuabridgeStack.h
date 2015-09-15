/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_LUA_LUABRIDGESTACK_H
#define FALLTERGEIST_LUA_LUABRIDGESTACK_H

// C++ standard includes
#include <list>
#include <map>
#include <vector>

// Libfalltergeist includes
#include "../Lua/Binder.h"

// Third party includes
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "LuaBridge.h"


/**
 * Specializations for luabridge::Stack<T>.
 */
namespace luabridge
{

/**
 * Stack specialization for std::vector.
 * Creates new table every time vector is returned to Lua and new vector from table other way around.
 */
template<>
template<typename T>
struct Stack<std::vector<T>>
{
public:
    static inline void push(lua_State* L, std::vector<T> vec)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::listToTable<std::vector<T>>(table, vec);
        table.push(L);
    }

    static inline std::vector<T> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToList<std::vector<T>>(LuaRef::fromStack(L, index));
    }
};

/**
 * Stack specialization for std::vector. Const reference version.
 */
template<>
template<typename T>
struct Stack<const std::vector<T>&>
{
public:
    static inline void push(lua_State* L, const std::vector<T>& vec)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::listToTable<std::vector<T>>(table, vec);
        table.push(L);
    }

    static inline std::vector<T> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToList<std::vector<T>>(LuaRef::fromStack(L, index));
    }
};

/**
 * Stack specialization for std::list. Converts list to Lua table and vice versa.
 */
template<>
template<typename T>
struct Stack<std::list<T>>
{
public:
    static inline void push(lua_State* L, std::list<T> list)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::listToTable<std::list<T>>(table, list);
        table.push(L);
    }

    static inline std::list<T> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToList<std::list<T>>(LuaRef::fromStack(L, index));
    }
};

/**
 * Stack specialization for std::list. Const ref version.
 */
template<>
template<typename T>
struct Stack<const std::list<T>&>
{
public:
    static inline void push(lua_State* L, const std::list<T>& list)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::listToTable<std::list<T>>(table, list);
        table.push(L);
    }

    static inline std::list<T> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToList<std::list<T>>(LuaRef::fromStack(L, index));
    }
};



/**
 * Stack specialization for std::map. Converts map to Lua table and vice versa.
 */
template<>
template<typename TK, typename TV>
struct Stack<std::map<TK, TV>>
{
public:
    static inline void push(lua_State* L, std::map<TK, TV> map)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::mapToTable(table, map);
        table.push(L);
    }

    static inline std::map<TK, TV> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToMap<std::map<TK, TV>>(LuaRef::fromStack(L, index));
    }
};

/**
 * Stack specialization for std::map. Const ref version.
 */
template<>
template<typename TK, typename TV>
struct Stack<const std::map<TK, TV>&>
{
public:
    static inline void push(lua_State* L, const std::map<TK, TV>& map)
    {
        auto table = LuaRef::newTable(L);
        Falltergeist::Lua::Binder::mapToTable(table, map);
        table.push(L);
    }

    static inline std::map<TK, TV> get(lua_State* L, int index)
    {
        return Falltergeist::Lua::Binder::tableToMap<std::map<TK, TV>>(LuaRef::fromStack(L, index));
    }
};

}

#endif //FALLTERGEIST_LUA_LUABRIDGESTACK_H
