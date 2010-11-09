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
		"ANY_DIR"};


using namespace buttons;

Input::Input()
{
}


Input::~Input()
{
}

bool Input::keyPressed(bitset<32> &keys, unsigned char key)
{
	if(key <= MAX_BUTTON)
		return keys[key];
	/*
		Special keys
	*/

	if(key == BUTTON_ANY_DIR)
		return 	keys[BUTTON_UP] || keys[BUTTON_DOWN] ||
				keys[BUTTON_LEFT] || keys[BUTTON_RIGHT];

	/* Should not happen */
	return false;
}

bool Input::hasKey(unsigned char key)
{
	return keyPressed(currentKeys,key);
}

bool Input::hasNewKey(unsigned char key)
{
	return keyPressed(currentKeys,key) && !keyPressed(lastKeys,key);
}

bool Input::b1()
{
	return hasKey(BUTTON_B1);
}

bool Input::b2()
{
	return hasKey(BUTTON_B2);
}

bool Input::b3()
{
	return hasKey(BUTTON_B3);
}

bool Input::b4()
{
	return hasKey(BUTTON_B4);
}


bool Input::up()
{
	return hasKey(BUTTON_UP);
}

bool Input::down()
{
	return hasKey(BUTTON_DOWN);
}

bool Input::left()
{
	return hasKey(BUTTON_LEFT);
}

bool Input::right()
{
	return hasKey(BUTTON_RIGHT);
}


bool Input::l()
{
	return hasKey(BUTTON_L);
}

bool Input::r()
{
	return hasKey(BUTTON_R);
}


bool Input::start()
{
	return hasKey(BUTTON_START);
}


bool Input::isValidated(InputCondition &in)
{
	vector<unsigned char>::iterator iter;

	/*
		if pAct had no "keys" option, it shouldn't be considered triggered.
	If there is no "key" option, it will only be activated by another action,
	or by an event.
	*/
	if(!in.pressed.size() && !in.released.size() && !in.combo.size())
		return false;

	for(iter = in.pressed.begin(); iter != in.pressed.end(); iter++)
	{
		if(!hasKey(*iter))
			return false;
	}

	for(iter = in.released.begin(); iter != in.released.end(); iter++)
	{
		if(hasKey(*iter))
			return false;
	}

	return std::search(keyMemory.begin(), keyMemory.end(), in.combo.begin(), in.combo.end()) != keyMemory.end();
}

void Input::addCombo(unsigned char key)
{
	keyMemory.push_back(key);

	if(keyMemory.size() > MAX_COMBO)
		keyMemory.pop_front();
}

const char *keyName(unsigned char key)
{
	return key_names[key];
}

unsigned char key(const char *name)
{
	int i;

	for(i=0;i < MAX_BUTTONS ; i++)
	{
		if(!strcmp(keyName(i),name))
			return i;
	}
	throw KeyException(name);
}

void Input::resetCombo()
{
	keyMemory.clear();
}


}
