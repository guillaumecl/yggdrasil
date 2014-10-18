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
#ifndef DRAWQTDRAWMANAGER_H
#define DRAWQTDRAWMANAGER_H

#include "qtdrawmanagerbase.h"

#include <map>
#include <string>
#include "qrenderwidget.h"

#include "qtimage.h"

namespace draw
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class QtDrawManager : public QtDrawManagerBase
{
public:
	QtDrawManager();

	~QtDrawManager();

	void draw(Image *image, int x, int y);
	void draw(Image *image, int x, int y, int xImg, int yImg, int widthImg, int heightImg);

	virtual QWidget *getWidget(QWidget *parent = NULL, const char *name = NULL);

	virtual void setup();
	virtual void update();

	virtual Image &getImage(const char *fileName);

	virtual int initGraphics(int width, int height);

	virtual void beginDraw();

	virtual void endDraw();

	virtual void setFont(Font &fnt);

	virtual Font &getFont();

	virtual void drawText(const char *text, int x, int y);

	virtual unsigned int getTextHeight(const char *text);

	virtual unsigned int getTextWidth(const char *text);

	virtual void setGraphicOrigin(int x, int y);

	virtual void restoreGraphicOrigin();

	virtual void shake(int strength);

	virtual void endShake();

	virtual void fade(unsigned char p, unsigned long color);
	virtual void fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height);

	virtual void scale(double pScale);

	virtual void endScale();
private:
	int mapYCoordinate(int y);
	int mapXCoordinate(int x);

	QRenderWidget *widget;
	QPainter *widgetPainter;
	QPainter *painter;
	QPixmap scaledView;
	double curScale;

	std::map<std::string, QtImage *> openedImages;

	unsigned int scrWidth;
	unsigned int scrHeight;

	unsigned int scrOriginX;
	unsigned int scrOriginY;
};

}

#endif
