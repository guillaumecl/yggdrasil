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
	std::vector<unsigned char> pressed;
	
	/**
	 * @todo see if this should be converted into a bitset<32> like in Input.
	 * Keys that must not be pressed
	 */
	std::vector<unsigned char> released;
	
	/**
	 * Combo (list of keys that must appear in the buffer in the right order)
	 */
	std::vector<unsigned char> combo;
};

}

#endif
