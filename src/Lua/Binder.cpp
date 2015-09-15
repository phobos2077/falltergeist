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

// C++ standard includes
#include <vector>

// Libfalltergeist includes
#include "../Event/Event.h"
#include "../Exception.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Point.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../Lua/Binder.h"
#include "../Lua/ImageButton.h"
#include "../Lua/LuabridgeStack.h"
#include "../Lua/TextArea.h"
#include "../Lua/Script.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"

// Third party includes

using namespace luabridge;

namespace Falltergeist
{
namespace Lua
{

Binder::Binder(lua_State* luaState)
    : _luaState(luaState)
{
}

Binder::~Binder()
{
}

luabridge::Namespace Binder::_gameNamespace()
{
    return luabridge::getGlobalNamespace(_luaState).beginNamespace("game");
}

std::vector<std::string> vectorTest()
{
    return std::vector<std::string> {"Actual", "plain", "std", "vector!!"};
}

static std::vector<std::string> staticVec {"Actual", "plain", "std", "vector!!"};
const std::vector<std::string>& vectorConstTest()
{
    return staticVec;
}

void vectorParamConst(const std::vector<std::string>& vec)
{
    auto& log = Logger::info("Lua");
    log << "vectorParam: ";
    for (auto str : vec)
    {
        log << str << ';';
    }
    log << std::endl;
}

void vectorParam(std::vector<std::string> vec)
{
    vectorParamConst(vec);
}

std::list<Point> listTest()
{
    return { {1, 2}, {105, 92}, {-25, 0}, {777, 999} };
}

void listParamConst(const std::list<Point>& list)
{
    auto& log = Logger::info("Lua");
    log << "listParam: ";
    for (auto pt : list)
    {
        log << pt << ';';
    }
    log << std::endl;
}

std::map<std::string, int> mapTest()
{
    return {{"three", 3}, {"four", 4}, {"minus one", -1}};
};

void mapParam(std::map<std::string, int> map)
{
    auto& log = Logger::info("Lua");
    log << "mapParam: ";
    for (auto pt : map)
    {
        log << pt.first << '=' << pt.second << "; ";
    }
    log << std::endl;
}


void Binder::bindAll()
{
    // TODO: better solution?
    // luabridge::Namespace::addProperty cannot deduce setter type =(
    static Input::Mouse* (*const getterGameMouse)() = []() -> Input::Mouse*
    {
        return Game::getInstance()->mouse();
    };

    _gameNamespace()
        .beginClass<Falltergeist::Game::Game>("Game")
            //.addStaticFunction("getInstance", &Falltergeist::Game::Game::getInstance)
            .addFunction("setState", &Falltergeist::Game::Game::setState)
            .addFunction("pushState", &Falltergeist::Game::Game::pushState)
            .addFunction("popState", &Falltergeist::Game::Game::popState)
            .addFunction("quit", &Falltergeist::Game::Game::quit)
        .endClass()

        .addProperty("instance", &Falltergeist::Game::Game::getInstance, (void(*)(Game::Game*))nullptr)

        // game.translate
        .addFunction("translate", translate)

        .addFunction("vectorTest", vectorTest)
        .addFunction("vectorConstTest", vectorConstTest)
        .addFunction("vectorParam", vectorParam)
        .addFunction("vectorParamConst", vectorParamConst)
        .addFunction("listTest", listTest)
        .addFunction("listParamConst", listParamConst)

        .addFunction("mapTest", mapTest)
        .addFunction("mapParam", mapParam)

        // game.mouse
        .addProperty ("mouse", getterGameMouse, (void(*)(Input::Mouse*))nullptr)
    ;

    _bindBasicClasses();
    _bindStates();
    _bindUI();
}


void Binder::_bindBasicClasses()
{
    _gameNamespace()
        .beginClass<Falltergeist::Point>("Point")
            .addConstructor<void(*)(int, int)>()
            .addProperty("x", &Falltergeist::Point::x, &Falltergeist::Point::setX)
            .addProperty("y", &Falltergeist::Point::y, &Falltergeist::Point::setY)
            .addFunction("__add", &Falltergeist::Point::add)
            .addFunction("__sub", &Falltergeist::Point::sub)
            .addFunction("__mul", &Falltergeist::Point::mul)
            .addFunction("__div", &Falltergeist::Point::div)
        .endClass()

        .beginClass<Falltergeist::Size>("Size")
            .addConstructor<void(*)(int, int)>()
            .addProperty("width", &Falltergeist::Size::width, &Falltergeist::Size::setWidth)
            .addProperty("height", &Falltergeist::Size::height, &Falltergeist::Size::setHeight)
            .addFunction("__add", &Falltergeist::Size::add)
            .addFunction("__sub", &Falltergeist::Size::sub)
            .addFunction("__mul", &Falltergeist::Size::mul)
            .addFunction("__div", &Falltergeist::Size::div)
        .endClass()

        // game.Mouse
        .beginClass<Input::Mouse>("Mouse")
            .addProperty("x", &Input::Mouse::x, &Input::Mouse::setX)
            .addProperty("y", &Input::Mouse::y, &Input::Mouse::setY)
            .addProperty("position", &Input::Mouse::position, &Input::Mouse::setPosition)
            .addProperty("cursor", &Input::Mouse::cursor, &Input::Mouse::setCursor)
        .endClass()

        // game.Event
        .beginClass<Event::Event>("Event")
            .addProperty("name", &Event::Event::name, &Event::Event::setName)
        .endClass()
    ;
}

void Binder::_bindUI()
{
    _gameNamespace()
        .beginNamespace("ui")
            // game.ui.UI
            .beginClass<Falltergeist::UI::Base>("UI")
                .addProperty("position", &UI::Base::position, &UI::Base::setPosition)
            .endClass()

            // game.ui.Image
            .deriveClass<UI::Image, Falltergeist::UI::Base>("Image")
                .addConstructor<void(*)(char const*)>()
            .endClass()

            // game.ui.ImageButton
            .deriveClass<Falltergeist::UI::ImageButton, Falltergeist::UI::Base>("ImageButtonBase")
            .endClass()

            .deriveClass<Lua::ImageButton, Falltergeist::UI::ImageButton>("ImageButton")
                .addConstructor<void(*)(const std::string&, const std::string&, const std::string&, const std::string&, int, int)>()
                .addFunction("subclass", &Lua::ImageButton::subclass)
            .endClass()

            // game.ui.TextArea
            .deriveClass<Lua::TextArea, Falltergeist::UI::Base>("TextArea")
                .addConstructor<void(*)(const char*, int, int)>()
                //.addProperty("width", &Lua::TextArea::width, &Lua::TextArea::setWidth)
                .addProperty("horizontalAlign", &Lua::TextArea::luaHorizontalAlign, &Lua::TextArea::setLuaHorizontalAlign)
            .endClass()
    ;
}

void Binder::_bindStates()
{
    _gameNamespace()
        // game.State
        .beginClass<State::State>("StateBase")
        .endClass()
        .deriveClass<State::LuaState, State::State>("State")
            .addConstructor<void(*)(luabridge::LuaRef)>()
            .addProperty("position", &State::LuaState::position, &State::LuaState::setPosition)
            .addProperty("fullscreen", &State::LuaState::fullscreen, &State::LuaState::setFullscreen)
            .addProperty("modal", &State::LuaState::modal, &State::LuaState::setModal)
            .addFunction("addUI", &State::LuaState::addUI)
        .endClass()
    ;
}

/*
template <typename T>
void Binder::_bindVector(const char* name)
{
    _gameNamespace()
        .beginClass< LuaVector<T> >(name)
            .addFunction("__index", &LuaVector<T>::index)
            .addFunction("__newindex", &LuaVector<T>::newindex)
            .addFunction("__len", &LuaVector<T>::len)
            .addFunction("__eq", &LuaVector<T>::eq)
        .endClass()

        .beginClass< std::vector<T> >(name)
            .addFunction("__index", static_cast<const T& (std::vector<T>::*)(size_t) const>(&std::vector<T>::at))
            //.addFunction("__newindex", &LuaVector<T>::newindex)
            .addFunction("__len", &std::vector<T>::size)
            //.addFunction("__eq", static_cast<bool (*)(const std::vector<T>&, const std::vector<T>&)>(&std::operator==<T>))
        .endClass();
}
*/

}
}

