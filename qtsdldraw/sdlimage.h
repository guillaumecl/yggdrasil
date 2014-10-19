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
#ifndef DRAWQTIMAGE_H
#define DRAWQTIMAGE_H

#include "common/drawmanager.h"

#include <QPixmap>

#ifdef Q_WS_WIN
#include <SDL.h>
#include <SDL_image.h>
#elif defined Q_WS_X11
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif
#undef main

namespace draw
{

/**
	@author Lightning Flik <flik@baobob.org>
*/
class SdlImage : public Image
{
public:
	SdlImage(const char *fileName);

	~SdlImage();

	unsigned int width();

	unsigned int height();

	void scale(double ratio);

	double curScale;
	SDL_Surface *image;
};

}

#endif
