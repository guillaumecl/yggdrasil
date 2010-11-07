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
#include "screenelement.h"
#include <sstream>
#include "exception.h"

#include "action.h"

using namespace std;

using namespace game::directions;

#include "core.h"
#include "collisionscreen.h"
#include "collision.h"
#include "rect.h"

namespace game
{

ScreenElement::ScreenElement(FileReader &confFile, const std::string &pName) :
	direction(0),
	walkable(true),
	_x(0),
	_y(0),
	_z(0),
	name(pName),
	currentAction(NULL),
	mask(NULL),
	mCollisionRect(0,0,0,0),
	locked(false)
{
	load(confFile);
}


ScreenElement::ScreenElement(const std::string &pName) :
	direction(0),
	walkable(true),
	_x(0),
	_y(0),
	_z(0),
	name(pName.c_str()),
	currentAction(NULL),
	mask(NULL),
	mCollisionRect(0,0,-1,-1)
{
	if(!core::Core::globalCore)
		throw GenericException("Plugins must be run in order to create screen elements.");
}

ScreenElement::~ScreenElement()
{
	map<string, Action *>::iterator iter;
	
	for(iter = actions.begin(); iter != actions.end(); iter++)
		delete iter->second;
}

void ScreenElement::load(FileReader &confFile)
{
	try
	{
		if(!core::Core::globalCore)
			throw GenericException("Plugins must be run in order to create screen elements.");
		Action *act = NULL;
		ostringstream actionVar;
		string actionName;
		
		int i = 1;
		
		mWidth = confFile.getInt("ScreenElement", "width",0);
		if(mWidth <= 0)
			throw LoadException("Bad width in file :", confFile.fileName());
		
		mHeight = confFile.getInt("ScreenElement", "height",0);
		if(mHeight <= 0)
			throw LoadException("Bad height in file :", confFile.fileName());
		
		
		actionVar << "action " << i;
		while(confFile.hasVariable("ScreenElement",actionVar.str().c_str()))
		{
			actionName = confFile.getString("ScreenElement",actionVar.str().c_str(),"");
			
			/*
				Useless, but the case where two action numbers refer to the same action is
			handled. Saves from memory leaks in this case.
			*/
			if(actions.find(actionName) == actions.end())
			{
				act = new Action(confFile,actionName.c_str(),mWidth,mHeight);
				actions[actionName] = act;
			}
			
			i++;
			actionVar.clear();
			actionVar.str("");
			actionVar << "action " << i;
		}
		
		if(!confFile.hasVariable("ScreenElement","defaultAction"))
			throw LoadException("This ScreenElement contains no default action.",confFile.fileName());
		
		defaultActionName = confFile.getString("ScreenElement","defaultAction","");
		
		map<string, Action*>::iterator ret;
		
		ret = actions.find(defaultActionName);
		
		if(ret == actions.end())
		{
			act = new Action(confFile,defaultActionName.c_str(),mWidth,mHeight);
			actions[defaultActionName] = act;
		}
		else
			act = ret->second;
		
		currentAction = act;
		
		walkable = confFile.hasVariable("ScreenElement","walkable");
		if(!walkable)
			mCollisionRect.set(_x,_y,mWidth,mHeight);
		
		/*
		* Editor only properties
		*/

	}
	catch(const exception &e)
	{
		/**
		 * This frees the loaded action in case an exception occurred during the
		 * load of an action.
		 */
		map<string, Action *>::iterator iter;
		
		for(iter = actions.begin(); iter != actions.end(); iter++)
			delete iter->second;
		throw;
	}
}

void ScreenElement::draw(int plane)
{
	if(currentAction)
		currentAction->draw(_x, _y+_z, direction, plane);
}

void ScreenElement::setPosition(int pX, int pY)
{
	_x = pX;
	_y = pY;
	mCollisionRect.rx() = _x;
	mCollisionRect.ry() = _y;
}

void ScreenElement::setSize(int pWidth, int pHeight)
{
	/*if(!currentAction)
		return;
	currentAction->setSize(pWidth, pHeight);*/
	mWidth = pWidth;
	mHeight = pHeight;
}

void ScreenElement::nextFrame()
{
	if(!currentAction)
		return;
	
	if(currentAction->nextFrame())
	{
		const ActionFrame &action = currentAction->getCurrentFrame();
		int i;
		/*
			Usually the user will want the rotation to be done only once per frame
		*/
		if(action.rotate_right > 0)
		{
			/* Rotate the sprite like the user requested */
			for(i=0 ; i < action.rotate_right ; i++)
				rotateRight();
		}
		else
		{
			/* if 0 we won't enter the loop anyway... so a test is useless */
			for(i=0 ; i < -action.rotate_right ; i++)
				rotateLeft();
		}
	}
	if(currentAction->isOver())
	{
		/**
		 * @todo find next action
		 * This depends on which decision is choosen in screenelement.h regarding the queuedaction.
		 * Basically this could be just "currentAction = queuedAction ? queuedAction : &defaultAction; currentAction->reset();
		 */
		
	}
}

void ScreenElement::rotateRight()
{
	direction = rright(direction);
}

void ScreenElement::rotateLeft()
{
	direction = rleft(direction);
}

int ScreenElement::rright(int dir)
{
	static int rot[] = 
	{
		DIR_UP_RIGHT,	// DIR_UP,
		DIR_DOWN_LEFT,	// DIR_DOWN,
		DIR_UP_LEFT,	// DIR_LEFT,
		DIR_DOWN_RIGHT,	// DIR_RIGHT,
		
		DIR_UP,			// DIR_UP_LEFT,
		DIR_RIGHT,		// DIR_UP_RIGHT,
		DIR_LEFT,		// DIR_DOWN_LEFT,
		DIR_DOWN,		// DIR_DOwN_RIGHT
	};
	return rot[dir];
}

int ScreenElement::rleft(int dir)
{
	static int rot[] = 
	{
		DIR_UP_LEFT,	// DIR_UP,
		DIR_DOWN_RIGHT,	// DIR_DOWN,
		DIR_DOWN_LEFT,	// DIR_LEFT,
		DIR_UP_RIGHT,	// DIR_RIGHT,
		
		DIR_LEFT,		// DIR_UP_LEFT,
		DIR_UP,			// DIR_UP_RIGHT,
		DIR_DOWN,		// DIR_DOWN_LEFT,
		DIR_RIGHT,		// DIR_DOwN_RIGHT
	};
	return rot[dir];
}

/*
	Moves the sprite. iForward represent the amount of pixels in the direction,
iRight the amount of pixels to the right of the sprite (the left in the point of
view of the sprite).

	Negative values can be specified.
*/
inline void ScreenElement::move(int iForward, int iRight)
{
	/*
		perp[i] is the direction of i rotated by 90� to the right.
	*/
	static int perp[] = 
	{
		DIR_RIGHT,		// DIR_UP,
		DIR_LEFT,		// DIR_DOWN,
		DIR_UP,			// DIR_LEFT,
		DIR_DOWN,		// DIR_RIGHT,
		
		DIR_UP_RIGHT,	// DIR_UP_LEFT,
		DIR_DOWN_RIGHT,	// DIR_UP_RIGHT,
		DIR_UP_LEFT,	// DIR_DOWN_LEFT,
		DIR_DOWN_LEFT,	// DIR_DOwN_RIGHT
	};
	
	static int xDir[] = 
	{
		0,	// DIR_UP,
		0,	// DIR_DOWN,
		-1,	// DIR_LEFT,
		1,	// DIR_RIGHT,
		
		-1,	// DIR_UP_LEFT,
		1,	// DIR_UP_RIGHT,
		-1,	// DIR_DOWN_LEFT,
		1,	// DIR_DOwN_RIGHT
	};
	
	static int yDir[] = 
	{
		1,	// DIR_UP,
		-1,	// DIR_DOWN,
		0,	// DIR_LEFT,
		0,	// DIR_RIGHT,
		
		1,	// DIR_UP_LEFT,
		1,	// DIR_UP_RIGHT,
		-1,	// DIR_DOWN_LEFT,
		-1,	// DIR_DOwN_RIGHT
	};
	
	setPosition(_x + iForward * xDir[direction] + iRight * xDir[perp[direction]],
	            _y + iForward * yDir[direction] + iRight * yDir[perp[direction]]);
}

void ScreenElement::updatePosition(/** @todo add a CollisionScreen parameter */)
{
	if(!currentAction)
		return;
	
	const ActionFrame &action = currentAction->getCurrentFrame();
	
	/*
	 * 	Z position is updated anytime, even if a collision occurs. If not, when walking towards a wall, a character
	 * would get stuck in the air.
	 */
	_z += action.move_height;
	
	/*
	 *	No need to check collisions if we're not moving !
	 */
	if(!action.move_forward && !action.move_right)
		return;
	
	checkCollision();
}

std::string ScreenElement::getName()
{
	return name;
}


void ScreenElement::loadEditorProperties(FileReader &confFile, const char *elName)
{
	locked = confFile.getInt(elName,"locked",0);
}

void ScreenElement::changeAction(Action *act)
{
	act->reset();
	currentAction = act;
}

void ScreenElement::setName(std::string pName)
{
	name = pName;
}

void ScreenElement::checkCollision()
{
	bool can_straight = true;
	bool can_left = true;
	bool can_right = true;
	
	const int dir_NoMove = direction;
	const int dir_Left = rleft(direction);
	const int dir_Right = rright(direction);
	
	CollisionList collisions;
	
	/*
		We always try to go straight, because we need to remember the collisions.
	*/
	can_straight = tryDir(dir_NoMove,true,&collisions);
	
	if(!can_straight)
	{
		/*
			We try to go at the nearest directions to the left or the right. In case we already know there
		is a collision, we just stop trying them since we will then use the normal direction.
		*/
		can_left = tryDir(dir_Left,false,&collisions);
		
		if(!can_left)
		{
			can_right = tryDir(dir_Right,false,&collisions);
		}
	}

	if(can_straight)
		direction = dir_NoMove;
	else if(can_left)
		direction = dir_Left;
	else if(can_right)
		direction = dir_Right;
	else
	{
		/* Do the collision as if we didn't try the other moves*/
		direction = dir_NoMove;
		CollisionList::iterator it;
		for(it = collisions.begin(); it != collisions.end(); it++)
			collideWith(*it);
		return;
	}
	/*
		Advance frame only if no collision was detected.
	*/
	advanceFrame();
	
	/*
		Restore the direction.
	*/
	direction = dir_NoMove;
}

const Rect &ScreenElement::collisionRect() const
{
	return mCollisionRect;
}

bool ScreenElement::collideWith(Collision &collision)
{
	const ScreenElement &dest = collision.destination;
	Rect intersection = collisionRect().intersection(dest.collisionRect());
	
	if(!intersection.isValid())
		return false;
	
	if(mask && dest.mask)
	{
		//check the collision between the two masks
	}
	else if(!mask && !dest.mask)
	{
		// we have a collision since we can only rely on the rects.
		collision.rect = intersection;
		return true;
	}
	else if(mask)
	{
		// check the collision between the mask and intersection
	}
	else
	{
		// check the collision between el->mask and intersection
	}
	return false;
}

void ScreenElement::advanceFrame()
{
	const ActionFrame &action = currentAction->getCurrentFrame();
	
	move(action.move_forward,action.move_right);
}

void ScreenElement::rollbackFrame()
{
	const ActionFrame &action = currentAction->getCurrentFrame();
	
	move(-action.move_forward,-action.move_right);
}

void ScreenElement::collideFunction(Collision &coll)
{
	rollbackFrame();
}

bool ScreenElement::tryDir(int pDir, bool pSaveCollisions, CollisionList *pCollisions)
{
	bool result = true;
	direction = pDir;
	advanceFrame();
	
	list<CollisionScreen*>::iterator i;
	list<ScreenElement*>::iterator j;
	
	for(i = collisionScreens.begin(); i != collisionScreens.end(); i++)
	{
		CollisionScreen *c = *i;
		for(j = c->screenElements.begin(); j != c->screenElements.end(); j++)
		{
			ScreenElement *el = *j;
			if(el == this)
				continue;
			
			Collision coll(*this,*el);
			if(collideWith(coll))
			{
				if(pSaveCollisions)
				{
					pCollisions->push_back(coll);
					result = false;
				}
				else
				{
					rollbackFrame();
					return false;
				}
			}
		}
	}
	rollbackFrame();
	return result;
}

void ScreenElement::addToCollisionScreen(CollisionScreen *scr)
{
	collisionScreens.push_back(scr);
}

void ScreenElement::removeFromCollisionScreen(CollisionScreen *scr)
{
	collisionScreens.remove(scr);
}

bool ScreenElement::operator<(const ScreenElement &compareTo)
{
	if(_y==compareTo._y)
	{
		if(_x == compareTo._x)
			/*
			 *	In last case, we use the pointer comparison. 
			 * This ensures that the items will always be ordered 
			 * the same way, if they have the same coordinates.
			 */
			return (void*)this < (void*)&compareTo;
		return _x < compareTo._x;
	}
	return _y < compareTo._y;
}
/**
 * 
 * @todo find a way that when a collision takes place between two objects,
 * when the other object does the doesCollide function at the same frame,
 * the testing and collision functions are not called once again.
 */

}
