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
#include "plane.h"

#include "exception.h"
#include "core.h"
#include <string>

using std::string;

namespace draw
{

Image &getImage(FileReader &confFile, const char *sectionName)
{
	string imageName = confFile.getString(sectionName,"image","");

	if (imageName.size() == 0)
		throw new LoadException("no input", imageName, 0);
	string path = confFile.directory() + "/" + imageName;

	return core::Core::getDrawManager()->getImage(path.c_str());
}

Plane::Plane(FileReader &confFile, const char *sectionName, int defaultWidth, int defaultHeight)
try:
	image(getImage(confFile, sectionName))
{
	offsetX = confFile.getInt(sectionName,"offsetX",0);
	offsetY = confFile.getInt(sectionName,"offsetY",0);
	mWidth = confFile.getInt(sectionName,"width",defaultWidth);
	mHeight = confFile.getInt(sectionName,"height",defaultHeight);
} catch (...)
{
	/*
		We don't want to log the error if there is just no plane actually.
		This is why we put 0 to severity.
	*/
	string fName = confFile.getString(sectionName,"image","");
	if (fName.empty())
		throw LoadException("Image not specified in section",sectionName, 0);
	throw LoadException("Cannot load image : ",fName);
}

Plane::~Plane()
{
}

void Plane::draw(int x, int y, int currentFrame, game::directions::DirectionType direction)
{
	core::Core::getDrawManager()->draw(&image, x + offsetX,y + offsetY,currentFrame * mWidth,(int)direction*mHeight, mWidth, mHeight);
}

void Plane::setSize(int pWidth, int pHeight)
{
	mWidth = pWidth;
	mHeight = pHeight;
}

}
