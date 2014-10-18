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
#include "qtdrawmanager.h"

#include "exception.h"
#include <QPainter>

#include <iostream>

using std::map;
using std::string;

namespace draw
{

QtDrawManager::QtDrawManager()
	: QtDrawManagerBase(),
	  widget(NULL),
	  curScale(1),
	  scrWidth(0),
	  scrHeight(0),
	  scrOriginX(0),
	  scrOriginY(0)
{
}


QtDrawManager::~QtDrawManager()
{
	map<string,QtImage*>::iterator iter;
	for(iter = openedImages.begin(); iter != openedImages.end(); iter++)
		delete iter->second;
}

QWidget *QtDrawManager::getWidget(QWidget *parent, const char */*name*/)
{
	if (!widget)
		widget = new QRenderWidget(parent);

	return widget;
}

void QtDrawManager::setup()
{

}

void QtDrawManager::update()
{
	widget->update();
}

Image &QtDrawManager::getImage(const char *fileName)
{
	QtImage *img;
	map<string,QtImage *>::iterator ret;

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

		img = new QtImage(fileName);
		openedImages[fileName] = img;
	}
	return *img;
}

int QtDrawManager::initGraphics(int width, int height)
{
	scrWidth = width;
	scrHeight = height;
	return 0;
}

void QtDrawManager::beginDraw()
{
	widgetPainter = new QPainter(widget);
	painter = widgetPainter;
	painter->fillRect(QRect(0,0,widget->width(), widget->height()),Qt::black );
}

void QtDrawManager::endDraw()
{
	delete widgetPainter;
}

void QtDrawManager::setFont(Font &fnt)
{
	Q_UNUSED(fnt);
}

Font &QtDrawManager::getFont()
{
}

void QtDrawManager::drawText(const char *text, int x, int y)
{
	Q_UNUSED(text);
	Q_UNUSED(x);
	Q_UNUSED(y);
}

unsigned int QtDrawManager::getTextHeight(const char *text)
{
	Q_UNUSED(text);
	return 0;
}

unsigned int QtDrawManager::getTextWidth(const char *text)
{
	Q_UNUSED(text);
	return 0;
}

void QtDrawManager::setGraphicOrigin(int x, int y)
{
	scrOriginX = x;
	scrOriginY = y;
}

int QtDrawManager::mapYCoordinate(int y)
{
	return (scrHeight - y + scrOriginY);
}

int QtDrawManager::mapXCoordinate(int x)
{
	return  (x - scrOriginX);
}

void QtDrawManager::restoreGraphicOrigin()
{
	scrOriginX = 0;
	scrOriginY = 0;
}

void QtDrawManager::shake(int strength)
{
	Q_UNUSED(strength);
}

void QtDrawManager::endShake()
{

}

void QtDrawManager::fade(unsigned char p, unsigned long color)
{
	fadeRect(p, color, 0, 0, scrWidth, scrHeight);
}

void QtDrawManager::fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height)
{
	unsigned char *col = (unsigned char*)&color;
	QColor alphaColor(col[2], col[1], col[0], p);

	painter->fillRect(mapXCoordinate(x), mapYCoordinate(y) - height, width, height, alphaColor);
}

void QtDrawManager::scale(double pScale)
{
	if (pScale == 1)
		return;
	std::cerr << "Scaling with " << pScale << "\n";
	scaledView = QPixmap(scrHeight, scrWidth);
	scaledView.fill(Qt::black);
	painter = new QPainter(&scaledView);
	curScale = pScale;
}

void QtDrawManager::endScale()
{
	if (curScale == 1)
		return;
	delete painter;

	painter = widgetPainter;

	widgetPainter->drawPixmap(0, 0, widget->width() * curScale, widget->height() * curScale, scaledView);
}

void QtDrawManager::draw(Image *img, int x, int y)
{
	QtImage *image = (QtImage *)img;

	painter->drawPixmap(mapXCoordinate(x), mapYCoordinate(y) - image->height(), image->width(), image->height(), image->pixmap);
}

void QtDrawManager::draw(Image *img, int x, int y, int xImg, int yImg, int widthImg, int heightImg)
{
	QtImage *image = (QtImage *)img;

	painter->drawPixmap(QRect(mapXCoordinate(x), mapYCoordinate(y) - heightImg, widthImg, heightImg), image->pixmap,
						QRect(xImg, yImg, widthImg, heightImg));
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
		return new QtDrawManager();
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
		return "A portable draw manager that relies on Qt. Use with QtCore.";
	}

	const char *name()
	{
		return "Qt Draw";
	}
}
