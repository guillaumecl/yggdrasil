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
#include "qtdrawglmanager.h"

#include "exception.h"

using std::map;
using std::string;

namespace draw
{

QtDrawGlManager::QtDrawGlManager()
	: QtDrawManagerBase(),
		scrWidth(0),
		scrHeight(0),
		scrOriginX(0),
		scrOriginY(0),
		widget(NULL)
{
}


QtDrawGlManager::~QtDrawGlManager()
{
	map<string,QtGlImage*>::iterator iter;
	for(iter = openedImages.begin(); iter != openedImages.end(); iter++)
		delete iter->second;
}

QWidget *QtDrawGlManager::getWidget(QWidget *parent, const char *name)
{
	if (!widget)
		widget = new GLWidget(parent, name);

	return widget;
}

void QtDrawGlManager::setup()
{
	widget->makeCurrent();
}

void QtDrawGlManager::update()
{
	widget->updateGL();
}

Image &QtDrawGlManager::getImage(const char *fileName)
{
	QtGlImage *img;
	map<string,QtGlImage *>::iterator ret;

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

		img = new QtGlImage(fileName);
		openedImages[fileName] = img;
	}
	return *img;
}

int QtDrawGlManager::initGraphics(int width, int height)
{
	glClearColor(0, 0, 0, 0);

	scrWidth = width;
	scrHeight = height;

	glViewport(0,0, scrWidth, scrHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	return 0;
}

void QtDrawGlManager::beginDraw()
{
	int vPort[4];

	glClear(GL_COLOR_BUFFER_BIT);

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void QtDrawGlManager::endDraw()
{
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void QtDrawGlManager::setFont(Font &fnt)
{
	Q_UNUSED(fnt);
}

Font &QtDrawGlManager::getFont()
{
}

void QtDrawGlManager::drawText(const char *text, int x, int y)
{
	Q_UNUSED(text);
	Q_UNUSED(x);
	Q_UNUSED(y);
}

unsigned int QtDrawGlManager::getTextHeight(const char *text)
{
	Q_UNUSED(text);
	return 0;
}

unsigned int QtDrawGlManager::getTextWidth(const char *text)
{
	Q_UNUSED(text);
	return 0;
}

void QtDrawGlManager::setGraphicOrigin(int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-x,-y,0);

	scrOriginX = x;
	scrOriginY = y;
}

void QtDrawGlManager::restoreGraphicOrigin()
{
	scrOriginX = 0;
	scrOriginY = 0;
	glPopMatrix();
}

void QtDrawGlManager::shake(int strength)
{
	int r1,r2;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	r1 = strength - rand() % (strength * 2+1);
	r2 = strength - rand() % (strength * 2+1);

	glTranslated(r1,r2,0);
}

void QtDrawGlManager::endShake()
{
	glPopMatrix();
}

void QtDrawGlManager::fade(unsigned char p, unsigned long color)
{
	fadeRect(p,color,scrOriginX, scrOriginY, scrWidth, scrHeight);
}

void QtDrawGlManager::fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height)
{
	GLubyte *t = (GLubyte*)&color;
	GLubyte col[4] = {t[2],t[1],t[0],p};

	glBegin(GL_QUADS);
	{
		glColor4ubv(col);

		glVertex2i(x, y + height);
		glVertex2i(x + width,y + height);
		glVertex2i(x + width, y);
		glVertex2i(x, y);

		glColor4ub(0xFF,0xFF,0xFF,0xFF);
	}
	glEnd();
}

void QtDrawGlManager::scale(double pScale)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glScaled(pScale,pScale,0);
}

void QtDrawGlManager::endScale()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void QtDrawGlManager::draw(Image *image, int x, int y)
{
	((QtGlImage*)image)->draw(x, y);
}

void QtDrawGlManager::draw(Image *image, int x, int y, int xImg, int yImg, int widthImg, int heightImg)
{
	((QtGlImage*)image)->draw(x, y, xImg, yImg, widthImg, heightImg);
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
		return new QtDrawGlManager();
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
