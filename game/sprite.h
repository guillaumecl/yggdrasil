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
#ifndef SPRITE_H
#define SPRITE_H

#include "basictypes.h"
#include "plane.h"
#include "common/archiver.h"

namespace draw
{

/**
 * @brief An image, which can be "alive" or not.
 *	@author Lightning Flik <flik@baobob.org>
 */
class Sprite
{
public:
	/**
	 * Sprite default constructor
	 */
	Sprite(FileReader &confFile, const char *sectionName, int pWidth, int pHeight);

	/**
	 * Sprite destructor
	 */
	~Sprite();

	/**
	 * @brief Draws the current image to the screen at position (x,y).
	 * @param x The X coordinate on the destination screen
	 * @param y The Y coordinate on the destination screen
	 * @param plane The plane to draw.
	 * @param direction The direction of the sprite to draw. If not applicable, set to 0.
	 * @see Screen::directions
	 */
	void draw(int x, int y, game::directions::DirectionType direction, planes::PlaneType plane);

	void nextFrame();
	void reset();

	int getNumFrames();

	void setSize(int pWidth, int pHeight);

	int numFrames;

	Plane *objectPlane;
	Plane *backgroundPlane;
	Plane *foregroundPlane;
private:

	int currentFrame;

	Plane *planes[3];
};


}

#endif
