/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// Falltergeist includes
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode80AAHandler.h"
#include "../../Game/GameCritterObject.h"
#include "../../Engine/Exception.h"
#include "../../VM/VM.h"




// Third party includes

namespace Falltergeist
{

Opcode80AAHandler::Opcode80AAHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80AAHandler::_run()
{
  Logger::debug("SCRIPT") << "[80AA] [+] int get_skill(GameCritterObject* who, int number) " << std::endl;
  int number = _vm->popDataInteger();
  if (number > 17) throw Exception("VM::opcode80AA - number out of range: " + std::to_string(number));
  auto object = static_cast<GameCritterObject*>(_vm->popDataPointer());
  if (!object) throw Exception("VM::opcode80AA pointer error");
  _vm->pushDataInteger(object->skill(number));
}

}

