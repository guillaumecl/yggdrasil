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
#pragma once

#include "basictypes.h"

namespace game
{

/**
 * What to do at a specific frame of the action. This includes the movements and the delay until next frame.
 * @author Lightning Flik <flik@baobob.org>
*/
class ActionFrame
{
public:
	/**
	 * Default constructor for ActionFrame
	 */
	ActionFrame(const ActionFrame &defaultAction, FileReader &confFile, const char *sectionName);
	ActionFrame();

	int move_forward;	/* Movement to the direction of the char (backwards if negative) */

	int move_right;		/* Movement to the right of the char (to the left if negative) */

	int move_height;	/* Movement of the char in the Z axis (for jumps) */

	int rotate_right;	/* Number of rotations of 45� to the right (to the left if negative) */

	int frameDelay;		/* Delay before the next frame */
};

}
