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
#ifndef DRAWPLANE_H
#define DRAWPLANE_H

#include "basictypes.h"
#include "common/drawmanager.h"
#include "common/archiver.h"

namespace draw
{

/**
 * There are three planes and three steps during the display of the screen.
 * First the background of the objects is drawn, then the object themselves, then the foreground of the objects.
 * These are called the different planes.
 * @author Lightning Flik <flik@baobob.org>
 */
class Plane
{
public:
	/**
	 * Default constructor for Plane
	 */
	Plane(FileReader &confFile, const char *sectionName, int defaultWidth, int defaultHeight);

	/**
	 * Destructor for Plane
	 */
	~Plane();

	/**
	 * @brief Draws the plane to the screen.
	 *
	 * @param x X coordinate on the screen
	 * @param y Y coordinate on the screen
	 * @param xImg X coordinate inside the image
	 * @param yImg Y coordinate inside the image
	 * @param width Width of the portion of the image to draw
	 * @param height Height of the portion of the image to draw
	 */
	void draw(int x, int y, int currentFrame, game::directions::DirectionType direction);

	void setSize(int pWidth, int pHeight);
private:
	/**
	 * Image to draw
	 */
	Image &image;
public:
	/**
	 * Offset to add to this plane X coordinate
	 */
	int offsetX;

	/**
	 * Offset to add to this plane Y coordinate
	 */
	int offsetY;

	/**
	 * Width of an image
	 */
	int mWidth;

	/**
	 * Height of an image
	 */
	int mHeight;

	std::string fileName;

};

}

#endif
