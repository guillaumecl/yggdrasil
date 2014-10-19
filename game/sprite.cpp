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
#include "sprite.h"
#include <string>

#include "exception.h"

using std::string;

namespace draw
{

using namespace draw::planes;

Sprite::Sprite(FileReader &confFile, const char *sectionName, int pWidth, int pHeight) :
	numFrames(0),
	objectPlane(NULL),
	backgroundPlane(NULL),
	foregroundPlane(NULL),
	currentFrame(0)
{
	string section = sectionName;

	numFrames = confFile.getInt(sectionName, "numFrames",1);


	/*
		The planes are optional. As they are initialized to NULL we don't have to handle
		loading errors.
	*/

	try {
		objectPlane = new Plane(confFile,sectionName,pWidth,pHeight);
	} catch (const exception &e) {	}

	try	{
		foregroundPlane = new Plane(confFile,(section + " foreground").c_str(),pWidth,pHeight);
	} catch (const exception &e) { }

	try {
		backgroundPlane = new Plane(confFile,(section + " background").c_str(),pWidth,pHeight);
	} catch (const exception &e) { }

	planes[foreground] = foregroundPlane;
	planes[object] = objectPlane;
	planes[background] = backgroundPlane;
}


Sprite::~Sprite()
{
	delete foregroundPlane;
	delete backgroundPlane;
	delete objectPlane;
}

void Sprite::draw(int x, int y, game::directions::DirectionType direction, PlaneType plane)
{
	if (planes[plane])
		planes[plane]->draw(x,y,currentFrame, direction);
}

void Sprite::nextFrame()
{
	currentFrame++;
	if (currentFrame >= numFrames)
		reset();
}

void Sprite::reset()
{
	currentFrame = 0;
}

int Sprite::getNumFrames()
{
	return numFrames;
}

void Sprite::setSize(int pWidth, int pHeight)
{
	if (foregroundPlane)
		foregroundPlane->setSize(pWidth,pHeight);

	if (objectPlane)
		objectPlane->setSize(pWidth,pHeight);

	if (backgroundPlane)
		backgroundPlane->setSize(pWidth,pHeight);
}

}

