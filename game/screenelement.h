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
#include "common/archiver.h"

#include <list>
#include "rect.h"

/**
 * The different directions a character can have.
 */
namespace game
{

/**
 * @brief A screen Element is a part of the screen.
 *
 * It has a position inside the screen, actions that can make it move or be animated.
 * It can also take part of the collision system with a Mask.
 * @author Lightning Flik <flik@baobob.org>
 */
class ScreenElement
{
public:
	/**
	 * Creates an empty object. Used by the editor only.
	 */
	ScreenElement(const std::string &pName = "");

	ScreenElement(FileReader &confFile, const std::string &pName);

	void load(FileReader &confFile);

	void draw(draw::planes::PlaneType plane);

	void setPosition(int x, int y);

	void setSize(int pWidth, int pHeight);

	/**
	 * Default destructor.
	 */
	virtual ~ScreenElement();

	void nextFrame();

	void updatePosition();

	int height() {
		return mHeight;
	}
	int width() {
		return mWidth;
	}

	inline int x() {
		return _x;
	}
	inline int y() {
		return _y;
	}
	inline int z() {
		return _z;
	}

	std::string getName();
	void setName(std::string name);

	/**
	 * The differenta actions the screen element can have.
	 */
	std::map<std::string, Action *> actions;

	/**
	 * Changes the current action
	 */
	void changeAction(Action *act);

	/**
	 * Direction of the sprite.
	 * Possible directions are in game::directions
	 */
	directions::DirectionType direction;

	void checkCollision();

	const Rect &collisionRect() const;

	void addToCollisionScreen(CollisionScreen *scr);
	void removeFromCollisionScreen(CollisionScreen *scr);


	bool walkable;
private:
	/**
	 * Left coordinate of the sprite
	 */
	int _x;

	/**
	 * Down coordinate of the sprite
	 */
	int _y;

	/**
	 * Height coordinate of the sprite.
	 * This will be added to Y, except the mask will stay at y position.
	 * It is used to make the character jump.
	 */
	int _z;

	/**
	 * Object name. Can be shown to the player if necessary.
	 */
	std::string name;

	/**
	 * Current action the screen element is executing.
	 */
	Action *currentAction;

	int mWidth;
	int mHeight;

	/**
	 * A queue of actions that were triggered. They are ordered by priority.
	 * @todo See if this should be done or not..
	 * What would be better probably is a "next queued action". For example during a long non breakable action
	 * like a combo or getting hit, the player can type the keys for a new combo. if the player decides to make
	 * another combo instead because the enemy has moved for example, he can type another combo that will replace
	 * the current saved one. One key needs to be set to completely remove the next action (which will then
	 * become idle (defaut action) -> the user can walk/run)
	 */
	//priority_queue<Action *> triggeredActions;

	void rotateLeft();
	void rotateRight();
	void move(int pForward, int pRight);

	bool collideWith(Collision &type);
	ScreenElement(const ScreenElement &ref) {
		*this = ref;
	}
	CollisionScreenPList collisionScreens;

	void advanceFrame();
	void rollbackFrame();

	static directions::DirectionType rright(directions::DirectionType dir);
	static directions::DirectionType rleft(directions::DirectionType dir);

	void *mask;

	Rect mCollisionRect;

	bool tryDir(directions::DirectionType pDir, bool pSaveCollisions, CollisionList *pCollisions);
protected:

	virtual void collideFunction(Collision &type);
public:
	/**
	 * From this point, all the functions should only be used by the editor.
	 */
	bool locked;
	std::string defaultActionName;

	void loadEditorProperties(FileReader &confFile, const char *elName);

	bool operator<(const ScreenElement &compareTo);
};

}
