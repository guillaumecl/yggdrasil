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
#ifndef INPUTINPUT_H
#define INPUTINPUT_H

#include "inputcondition.h"
#include <vector>
#include <bitset>
#include <list>

namespace input
{


/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class Input
{
public:
    Input();

    ~Input();
	
	bool isValidated(InputCondition &in);
	
	bool hasKey(unsigned char key);
	bool hasNewKey(unsigned char key);
	
	bool b1();
	bool b2();
	bool b3();
	bool b4();
	
	bool up();
	bool down();
	bool left();
	bool right();
	
	bool l();
	bool r();
	
	bool start();
	
	void addCombo(unsigned char key);
	void resetCombo();
	
	virtual void updateState() = 0;
	
	static const unsigned int MAX_COMBO = 20;
	
protected:
	/**
	 * Last pressed keys. Used for combos.
	 */
	std::list<unsigned char> keyMemory;
	std::bitset<32> lastKeys;
	std::bitset<32> currentKeys;
	
	bool keyPressed(std::bitset<32> &keys, unsigned char key);
};

	
namespace buttons
{

enum
{
	BUTTON_UP = 0,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	
	BUTTON_B1,
	BUTTON_B2,
	BUTTON_B3,
	BUTTON_B4,
	
	BUTTON_L,
	BUTTON_R,
	
	BUTTON_START,
	
	MAX_BUTTON = BUTTON_START,
	
	BUTTON_ANY_DIR,
	
	MAX_BUTTONS = BUTTON_ANY_DIR
};

}

}

#endif
