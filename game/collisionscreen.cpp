/***************************************************************************
 *   Copyright (C) 2007 by CLEMENT Guillaume   *
 *   guillaume.clement@esial.uhp-nancy.fr   *
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
#include "collisionscreen.h"
#include "screenelement.h"

namespace game
{

CollisionScreen::CollisionScreen(int pX, int pY, int pWidth, int pHeight) :
	leftScreen(NULL),
	rightScreen(NULL),
	topScreen(NULL),
	topLeftScreen(NULL),
	topRightScreen(NULL),
	bottomScreen(NULL),
	bottomLeftScreen(NULL),
	bottomRightScreen(NULL),
	mX(pX),
	mY(pY),
	maxX(pX+pWidth),
	maxY(pY+pHeight)
{
}


CollisionScreen::~CollisionScreen()
{
}

bool CollisionScreen::fits(ScreenElement *el)
{
	int x1 = el->x();
	int x2 = el->x() + el->width();
	int y1 = el->y();
	int y2 = el->y() + el->height();

	return (x1 <= maxX && x2 >= mX && y1 <= maxY && y2 >= mY);
}

void CollisionScreen::updateElement(ScreenElement *el)
{
	/*
		Note: this works only for moves that do not cross 2 collision screens at the time (for instance warping from one side of the screen to the other won't work)
	*/
	int x1 = el->x();
	int x2 = el->x() + el->width();
	int y1 = el->y();
	int y2 = el->y() + el->height();

	if (x1 >= maxX || x2 <= mX || y1 >= maxY || y2 <= mY) {
		screenElements.remove(el);
		el->removeFromCollisionScreen(this);
	}

	if (x2 >= maxX) {
		addIfNeeded(el,rightScreen);
		addIfNeeded(el,topRightScreen);
		addIfNeeded(el,bottomRightScreen);
	}
	if (x1 <= mX) {
		addIfNeeded(el,leftScreen);
		addIfNeeded(el,topLeftScreen);
		addIfNeeded(el,bottomLeftScreen);
	}
}


void CollisionScreen::addIfNeeded(ScreenElement *el, CollisionScreen *neighbour)
{
	if (neighbour && neighbour->fits(el) && !neighbour->has(el)) {
		neighbour->screenElements.push_back(el);
		el->addToCollisionScreen(neighbour);
	}
}

bool CollisionScreen::has(ScreenElement *el)
{
	ScreenElementPList::iterator it;

	for (it = screenElements.begin(); it != screenElements.end(); it++)
		if (*it == el)
			return true;

	return false;
}

}
