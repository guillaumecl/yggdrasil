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
#include "rect.h"

namespace game {


inline static int min(int x, int y)
{
	if(x < y)
		return x;
	return y;
}

inline static int max(int x, int y)
{
	if(x > y)
		return x;
	return y;
}

Rect::Rect() :
	mX(0),
	mY(0),
	mWidth(-1),
	mHeight(-1)
{
}

Rect::Rect(int pBaseX, int pBaseY, int pX, int pY, int pWidth, int pHeight) :
	mX(pBaseX + pX),
	mY(pBaseY + pY),
	mWidth(pWidth),
	mHeight(pHeight)
{
}

Rect::Rect(int pX, int pY, int pWidth, int pHeight) :
	mX(pX),
	mY(pY),
	mWidth(pWidth),
	mHeight(pHeight)
{
}

Rect::Rect(int pX, int pX2, int pY, int pY2, bool pUnused) :
	mX(pX),
	mY(pY),
	mWidth(pX2-pX),
	mHeight(pY2-pY)
{
	pUnused = true;
	(void)pUnused;
}

Rect Rect::intersection(const Rect &pRect) const
{
	return Rect(max(x(),pRect.x()),
	            min(x2(),pRect.x2()),
	            max(y(),pRect.y()),
	            min(y2(),pRect.y2()),
	            false);
}

void Rect::set(int pX, int pY, int pWidth, int pHeight)
{
	mX = pX;
	mY = pY;
	mWidth = pWidth;
	mHeight = pHeight;
}

}
