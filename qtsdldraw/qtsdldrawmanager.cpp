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
#include "qtsdldrawmanager.h"

#include "exception.h"
#include <QGraphicsView>
#include "qrenderwidget.h"

#include "log.h"

using std::map;
using std::string;

namespace draw
{

QtSdlDrawManager::QtSdlDrawManager()
	: QtDrawManagerBase(),
		scrWidth(0),
		scrHeight(0),
		scrOriginX(0),
		scrOriginY(0),
		widget(NULL),
		curScale(1.0)
{
}


QtSdlDrawManager::~QtSdlDrawManager()
{
	map<string, SdlImage*>::iterator iter;
	for(iter = openedImages.begin(); iter != openedImages.end(); iter++)
		delete iter->second;
}

QWidget *QtSdlDrawManager::getWidget(QWidget *parent, const char *name)
{
	if (widget == NULL)
	{
		widget = new QRenderWidget(parent);
	}

	return widget;
}

void QtSdlDrawManager::setup()
{

}

void QtSdlDrawManager::update()
{
	core::Core::getCore()->mainLoopIteration();
}

Image &QtSdlDrawManager::getImage(const char *fileName)
{
	SdlImage *img;
	map<string,SdlImage *>::iterator ret;

	if(!fileName[0])
		throw LoadException("No file to load.",fileName,0);

	ret = openedImages.find(fileName);

	if(ret != openedImages.end())
	{
		/*
		This image is already loaded. Increment its counter and return it.
		* @todo: really increment the counter (check if its not done somewhere else)
		*/
		img = ret->second;
	}
	else
	{
		/*
		Image was not found. We need to load it and then add it.
		*/

		img = new SdlImage(fileName);
		openedImages[fileName] = img;
	}
	return *img;
}

int QtSdlDrawManager::initGraphics(int width, int height)
{
	scrWidth = width;
	scrHeight = height;

	log() << "Resized to (" << width << ", " << height << ").\n";

	return 0;
}

void QtSdlDrawManager::beginDraw()
{
	SDL_FillRect(widget->screen, NULL, 0);
}

void QtSdlDrawManager::endDraw()
{
	SDL_Flip(widget->screen);
}

void QtSdlDrawManager::setFont(Font &fnt)
{

}

Font &QtSdlDrawManager::getFont()
{
}

void QtSdlDrawManager::drawText(const char *text, int x, int y)
{
}

unsigned int QtSdlDrawManager::getTextHeight(const char *text)
{
}

unsigned int QtSdlDrawManager::getTextWidth(const char *text)
{
}

void QtSdlDrawManager::setGraphicOrigin(int x, int y)
{
	scrOriginX = x;
	scrOriginY = y;
}

void QtSdlDrawManager::restoreGraphicOrigin()
{
	scrOriginX = 0;
	scrOriginY = 0;
}

void QtSdlDrawManager::shake(int strength)
{

}

void QtSdlDrawManager::endShake()
{

}

void QtSdlDrawManager::fade(unsigned char p, unsigned long color)
{
	fadeRect(p, color, 0, 0, scrWidth, scrHeight);
}

void QtSdlDrawManager::fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height)
{
	int minX = mapXCoordinate(x);
	int maxX = mapXCoordinate(x + width);

	int minY = mapYCoordinate(y + height);
	int maxY = mapYCoordinate(y);

	unsigned char *rgba = (unsigned char*)&color;

	unsigned char *surfacePtr = (unsigned char*)widget->screen->pixels;

	if (minX < 0)					minX = 0;
	if (minY < 0)					minY = 0;
	if (maxX >= widget->screen->w)	maxX = widget->screen->w - 1;
	if (maxY >= widget->screen->h)	maxY = widget->screen->h - 1;

	for (y = minY ; y < maxY ; y++)
	{
		for (x = minX ; x < maxX ; x++)
		{
			int index = (y * widget->screen->w + x) << 2;

			surfacePtr[index+2] = (surfacePtr[index+2] * (256L - p) + rgba[2] * p) >> 8;
			surfacePtr[index+1] = (surfacePtr[index+1] * (256L - p) + rgba[1] * p) >> 8;
			surfacePtr[index+0] = (surfacePtr[index+0] * (256L - p) + rgba[0] * p) >> 8;
		}
	}

}

void QtSdlDrawManager::scale(double pScale)
{
	curScale = pScale;

	map<string, SdlImage*>::iterator iter;
	for(iter = openedImages.begin(); iter != openedImages.end(); iter++)
	{
		iter->second->scale(pScale);
	}
}

void QtSdlDrawManager::endScale()
{

}

int QtSdlDrawManager::mapYCoordinate(int y)
{
	return (scrHeight - y + scrOriginY);
}

int QtSdlDrawManager::mapXCoordinate(int x)
{
	return  (x - scrOriginX);
}

void QtSdlDrawManager::draw(Image *img, int x, int y)
{
	SdlImage *image = (SdlImage*)img;

	draw(image, x, y, 0, 0, image->width(),image-> height());
}

void QtSdlDrawManager::draw(Image *img, int x, int y, int xImg, int yImg, int widthImg, int heightImg)
{
	SdlImage *image = (SdlImage*)img;
	if (widthImg > image->width() || heightImg > image->height())
	{
		drawTiled(image, x, y, widthImg, heightImg);
		return;
	}

	SDL_Surface *screen = widget->screen;

	x = mapXCoordinate(x);
	y = mapYCoordinate(y + heightImg);

	if (x < 0)
	{
		xImg -= x;
		widthImg += x;
		x = 0;
	}

	if (y < 0)
	{
		yImg -= y;
		heightImg += y;
		y = 0;
	}

	if (y + heightImg >= scrHeight)
	{
		int diff = scrHeight - y - heightImg;
		heightImg += diff;
	}

	if (x + widthImg >= scrWidth)
	{
		int diff = scrWidth - x - widthImg;
		widthImg += diff;
	}

	if (heightImg <= 0 || widthImg <= 0)
		return;

	SDL_Rect srcRect = { xImg, yImg, widthImg, heightImg };
	SDL_Rect dstRect = { x, y, 0, 0};

	SDL_BlitSurface(image->image, &srcRect, screen, &dstRect);
}

void QtSdlDrawManager::drawTiled(SdlImage *image, int xDst, int yDst, int widthImg, int heightImg)
{
	SDL_Surface *screen = widget->screen;

	int tileX = widthImg / image->width();
	int tileY = heightImg / image->height();

	if (tileX == 0)
		tileX = 1;
	if (tileY == 0)
		tileY = 1;

	for (int y = 0;  y < tileY; y++)
	{
		for (int x = 0; x < tileX; x++)
		{
			int _x = xDst + x * image->width();
			int _y = yDst + y * image->height();

			draw(image, _x, _y, 0, 0, image->width(), image->height());
		}
	}
}

}




extern "C"
{
	using namespace draw;

	/**
	Those functions are exported to be the plugin interface.
	 */

	/**
	Create a draw manager
	 */
	DrawManager *create()
	{
		return new QtSdlDrawManager();
	}

	const char *author()
	{
		return "Lightning Flik <flik@baobob.org>";
	}

	const char *type()
	{
		return "draw";
	}

	const char *description()
	{
		return "A portable draw manager that relies on Qt and SDL. Use with QtCore on machines that do not support OpenGL (some netbooks, etc).";
	}

	const char *name()
	{
		return "Qt Draw";
	}
}
