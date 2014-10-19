/***************************************************************************
 *   Copyright (C) 2007 by Lightning Flik   *
 *   flik@baobob.org   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "input.h"
#include "exception.h"
#include "string.h"

#include <algorithm>

using namespace std;

namespace input
{

static const char *key_names[] = {"UP","DOWN","LEFT","RIGHT",
                                  "B1","B2","B3","B4","L","R","START",
                                  "ANY_DIR"
                                 };


Input::Input()
{
}


Input::~Input()
{
}

bool Input::keyPressed(bitset<32> &keys, buttons::ButtonType key)
{
	if (key <= buttons::max)
		return keys[(int)key];
	/*
		Special keys
	*/

	if (key == buttons::anyDir)
		return 	keys[buttons::up] || keys[buttons::down] ||
		        keys[buttons::left] || keys[buttons::right];

	/* Should not happen */
	return false;
}

bool Input::hasKey(buttons::ButtonType key)
{
	return keyPressed(currentKeys,key);
}

bool Input::hasNewKey(buttons::ButtonType key)
{
	return keyPressed(currentKeys,key) && !keyPressed(lastKeys,key);
}

bool Input::b1()
{
	return hasKey(buttons::b1);
}

bool Input::b2()
{
	return hasKey(buttons::b2);
}

bool Input::b3()
{
	return hasKey(buttons::b3);
}

bool Input::b4()
{
	return hasKey(buttons::b4);
}


bool Input::up()
{
	return hasKey(buttons::up);
}

bool Input::down()
{
	return hasKey(buttons::down);
}

bool Input::left()
{
	return hasKey(buttons::left);
}

bool Input::right()
{
	return hasKey(buttons::right);
}


bool Input::l()
{
	return hasKey(buttons::l);
}

bool Input::r()
{
	return hasKey(buttons::r);
}


bool Input::start()
{
	return hasKey(buttons::start);
}


bool Input::isValidated(InputCondition &in)
{
	vector<buttons::ButtonType>::iterator iter;

	/*
		if pAct had no "keys" option, it shouldn't be considered triggered.
	If there is no "key" option, it will only be activated by another action,
	or by an event.
	*/
	if (!in.pressed.size() && !in.released.size() && !in.combo.size())
		return false;

	for (iter = in.pressed.begin(); iter != in.pressed.end(); iter++) {
		if (!hasKey(*iter))
			return false;
	}

	for (iter = in.released.begin(); iter != in.released.end(); iter++) {
		if (hasKey(*iter))
			return false;
	}

	return std::search(keyMemory.begin(), keyMemory.end(), in.combo.begin(), in.combo.end()) != keyMemory.end();
}

void Input::addCombo(buttons::ButtonType key)
{
	keyMemory.push_back(key);

	if (keyMemory.size() > MAX_COMBO)
		keyMemory.pop_front();
}

const char *keyName(buttons::ButtonType key)
{
	return key_names[(int)key];
}

buttons::ButtonType key(const char *name)
{
	int i;

	for (i=0; i < buttons::maxSpecials ; i++) {
		if (!strcmp(keyName(static_cast<buttons::ButtonType>(i)),name))
			return static_cast<buttons::ButtonType>(i);
	}
	throw KeyException(name);
}

void Input::resetCombo()
{
	keyMemory.clear();
}


}
