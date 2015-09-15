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

#ifndef FALLTERGEIST_LUA_BINDER_H
#define FALLTERGEIST_LUA_BINDER_H

// C++ standard includes
#include <list>
#include <map>
#include <vector>

// Libfalltergeist includes

// Third party includes
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "LuaBridge.h"

namespace Falltergeist
{
namespace Lua
{

/**
 * Class for Luabridge bindings
 */
class Binder
{
public:
    Binder(lua_State* luaState);
    ~Binder();

    void bindAll();

    /**
     * Converts Lua list-like table to std containers like vector, list.
     */
    template <class T>
    static T tableToList(const luabridge::LuaRef& table)
    {
        T list;
        if (table.isTable())
        {
            for (size_t i = 1, n = (size_t)table.length(); (i <= n && !table[i].isNil()); i++)
            {
                list.push_back(table[i]); // implicit conversion from luabridge::Proxy should be called here
            }
        }
        return list;
    }

    /**
     * Assigns values from containers like list/vector to Lua list-like Table.
     */
    template <class T>
    static void listToTable(luabridge::LuaRef& table, const T& list)
    {
        for (auto el : list)
        {
            table.append(el);
        }
    }

    /**
     * Converts Lua table to std::map containers.
     */
    template <class T>
    static T tableToMap(const luabridge::LuaRef& table)
    {
        T map;
        if (table.isTable())
        {
            for (luabridge::Iterator iter(table); !iter.isNil(); ++iter)
            {
                map[iter.key()] = iter.value(); // implicit conversion from LuaRefs should be called here
            }
        }
        return map;
    }

    /**
     * Assigns values from map containers to Lua Table.
     */
    template <class T>
    static void mapToTable(luabridge::LuaRef& table, const T& map)
    {
        for (auto el : map)
        {
            table[el.first] = el.second;
        }
    }

private:
    lua_State* _luaState;
    luabridge::Namespace _gameNamespace();

    void _bindBasicClasses();
    void _bindUI();
    void _bindStates();
//
//    template <typename T>
//    void _bindVector(const char* name);


};

/**
 * A wrapper for std::vector to be used from Lua.
 */
//template <typename T>
//class LuaVector
//{
//public:
//    /**
//     * Move constructor
//     */
//    LuaVector(std::vector<T>&& vec) : _vec(vec)
//    {
//    }
//
//    LuaVector(const std::vector<T>& vec) : _vec(vec)
//    {
//    }
//
//public:
//    T index(size_t idx)
//    {
//        return _vec.at(idx);
//    }
//
//    void newindex(size_t idx, T value)
//    {
//        _vec.at(idx) = value;
//    }
//
//    int len()
//    {
//        return _vec.size();
//    }
//
//    bool eq(const std::vector<T>& other)
//    {
//        return _vec == other;
//    }
//
//private:
//    std::vector<T> _vec;
//};



}
}

#endif //FALLTERGEIST_LUA_BINDER_H
