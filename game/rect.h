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
#pragma once

namespace game
{

/**
	@author flik <flik@baobob.org>
*/
class Rect
{
public:
	Rect();

	/**
	 *	Convenience constructor: equivalent to Rect(baseX+x, baseY+y,width, height)
	 */
	Rect(int pBaseX, int pBaseY, int pX, int pY, int pWidth, int pHeight);

	/**
	 * Creates a rect with the specified parameters
	 */
	Rect(int pX, int pY, int pWidth, int pHeight);

	/**
	 * Creates a rect with the specified parameters
	 */
	Rect(int pX, int pX2, int pY, int pY2, bool unused);

	/**
	 * Creates a new Rect which is the intersection between this one and the other.
	 * If there is no intersection, the given rect will not be valid (width or height will be negative)
	 */
	Rect intersection(const Rect &Rect) const;

	inline int &rx() {
		return mX;
	}
	inline int &ry() {
		return mY;
	}

	inline int x() const {
		return mX;
	}
	inline int y() const {
		return mY;
	}
	inline int width() const {
		return mWidth;
	}
	inline int height() const {
		return mHeight;
	}

	inline int x2() const {
		return mX + mWidth;
	}
	inline int y2() const {
		return mY + mHeight;
	}

	inline bool isValid() const {
		return mWidth > 0 && mHeight > 0;
	}

	void set(int pX, int pY, int pWidth, int pHeight);
private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;

	//Rect &operator=(const Rect&);
	//Rect(const Rect&);
};

}
