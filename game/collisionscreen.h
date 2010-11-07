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
#ifndef GAMECOLLISIONSCREEN_H
#define GAMECOLLISIONSCREEN_H

#include <list>
#include "basictypes.h"

namespace game {

class ScreenElement;

/**
 *	@author flik <flik@baobob.org>
 */
class CollisionScreen
{
public:
	CollisionScreen(int pX, int pY, int pWidth, int pHeight);

    ~CollisionScreen();

	ScreenElementPList screenElements;
	
	void updateElement(ScreenElement *el);
	
	static void addIfNeeded(ScreenElement *el,CollisionScreen *neighbour);
	bool has(ScreenElement *el);
private:
	CollisionScreen *leftScreen;
	CollisionScreen *rightScreen;
	
	CollisionScreen *topScreen;
	CollisionScreen *topLeftScreen;
	CollisionScreen *topRightScreen;
	
	CollisionScreen *bottomScreen;
	CollisionScreen *bottomLeftScreen;
	CollisionScreen *bottomRightScreen;
	
	int mX;
	int mY;
	
	int maxX;
	int maxY;
	
	bool fits(ScreenElement *el);
};

}

#endif
