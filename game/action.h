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
#ifndef GAMEACTION_H
#define GAMEACTION_H

#include "basictypes.h"
#include "actionframe.h"

#include "sprite.h"
#include <vector>


namespace game
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class Action
{
public:
	Action(FileReader &confFile, const char *actionName, int pWidth, int pHeight);

    ~Action();

	const char *displayName() const;
	
	int priority() const;
	
	void draw(int x, int y, directions::DirectionType direction, draw::planes::PlaneType plane);
	
	bool nextFrame();
	
	bool isOver();
	
	void reset();
	/*
	int width();
	int height();*/
	
	void setSize(int pWidth, int pHeight);
	
	const ActionFrame &getCurrentFrame();
	
	std::string name;
	
	const char *mDisplayName;

	draw::Sprite spr;
	
	/**
	 * @todo add a CollisionRectangle here. 
	 * This will be the basic calculation for collision purposes.
	 * the mask will always be located inside this rectangle. If a mask is provided, the collision rectangle
	 * will be updated to be at the best size containing the mask. If not, only the rectangle will be used
	 * to check the collision status.
	 * 
	 * maybe this could/should be added to the sprite instead of the action.
	 */
	
	int baseOffsetY;
	
private:
	/**
	 * Default movements for this action. Used to save space.
	 */
	ActionFrame defaultFrame;
	
	/**
	 * Different action frames.
	 */
	std::vector<ActionFrame *> frames;
	
	int frameTimer;
	unsigned int curFrame;
	
};

}

#endif
