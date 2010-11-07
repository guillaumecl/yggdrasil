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
#include "sdlimage.h"
#include "exception.h"

#include "qtsdldrawmanager.h"
#include <QPainter>

#include "log.h"

using std::string;

namespace draw {

SdlImage::SdlImage(const char *fileName) :
	Image(),
	image(NULL)
{
	/*if (!qtImage.load(fileName))
		throw LoadException("Cannot load the image file",fileName);*/
	image = IMG_Load(fileName);
	if (!image)
		throw LoadException("Cannot load the image file",fileName);

	curScale = 0.0;
	//scale(1.0);
}

SdlImage::~SdlImage()
{
	if (image)
		SDL_FreeSurface(image),
		image = NULL;
}

unsigned int SdlImage::width()
{
	return image->w;
}

unsigned int SdlImage::height()
{
	return image->h;
}

void SdlImage::scale(double ratio)
{
	/*if (curScale == ratio)
		return;

	if (ratio == 1.0)
		scaledImage = qtImage;
	else
	{
		scaledImage = qtImage.scaled(ratio * qtImage.size(), Qt::KeepAspectRatio, Qt::FastTransformation);
		// test Qt::SmoothTransformation too

	}

	if (image)
		SDL_FreeSurface(image);

	image = SDL_CreateRGBSurface(SDL_SWSURFACE,
		scaledImage.width(), scaledImage.height(), 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	Uint32 *pixels = (Uint32*)image->pixels;

	for(int y = 0; y < scaledImage.height(); y++)
	{
		for(int x = 0; x < scaledImage.width(); x++)
		{
			pixels[y * image->w + x] = scaledImage.pixel(x, y);
		}
	}

	curScale = ratio;*/
}

}
