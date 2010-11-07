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
#include "actionframe.h"
#include "archiver.h"

namespace game
{

ActionFrame::ActionFrame(const ActionFrame &defaultFrame,FileReader &confFile, const char *sectionName)
{
	*this = defaultFrame;
	if(confFile.hasVariable(sectionName,"Frame delay"))
		frameDelay = confFile.getInt(sectionName, "Frame delay",-1);

	if(confFile.hasVariable(sectionName,"forward"))
		move_forward = confFile.getInt(sectionName, "forward",0);

	if(confFile.hasVariable(sectionName,"move_height"))
		move_height = confFile.getInt(sectionName, "move_height",0);

	if(confFile.hasVariable(sectionName,"right"))
		move_right = confFile.getInt(sectionName, "right",0);

	if(confFile.hasVariable(sectionName,"rotate_right"))
		rotate_right = confFile.getInt(sectionName, "rotate_right",0);


}

ActionFrame::ActionFrame() :
	move_forward(0),
	move_right(0),
	move_height(0),
	rotate_right(0),
	frameDelay(0)
{
	/**
	 * @todo fix the frame delay which seems to be broken
	 */
}

}
