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
#ifndef INPUTINPUTCONDITION_H
#define INPUTINPUTCONDITION_H

#include <vector>

namespace input
{
namespace buttons
{

enum ButtonType
{
	up = 0,
	down,
	left,
	right,

	b1,
	b2,
	b3,
	b4,

	l,
	r,

	start,

	// Maximum number of real buttons
	max = start,

	anyDir,

	// Maximum number of buttons including special keys (like "any dir")
	maxSpecials = anyDir
};

}

/**
 * 	@author Lightning Flik <flik@baobob.org>
 */
class InputCondition
{
public:
    InputCondition();

    ~InputCondition();
	
	/**
	 * @todo see if this should be converted into a bitset<32> like in Input.
	 * Keys that must be pressed
	 */
	std::vector<buttons::ButtonType> pressed;
	
	/**
	 * @todo see if this should be converted into a bitset<32> like in Input.
	 * Keys that must not be pressed
	 */
	std::vector<buttons::ButtonType> released;
	
	/**
	 * Combo (list of keys that must appear in the buffer in the right order)
	 */
	std::vector<buttons::ButtonType> combo;
};

}

#endif
