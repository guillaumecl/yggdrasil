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
#include "qtglimage.h"

#include "common/exception.h"

#include <iostream>

namespace draw
{

static int getPowerOf2(int n)
{
	int k = 1;
	if (!(n & (n-1)))
		return n;

	n <<= 1;
	while (n & (n-1))
		n &= ~(1 << k++);

	return n;
}

QtGlImage::QtGlImage(const char *fileName) :
	Image(),
	id(0)
{
	QImage qImg, qImgResized, qGlImg;

	if (!qImg.load(fileName))
		throw exceptions::LoadException("Cannot load the image file",fileName);

	mWidth = qImg.width();
	mHeight = qImg.height();

	actualWidth = getPowerOf2(qImg.width());
	actualHeight = getPowerOf2(qImg.height());

	qImgResized = qImg.copy(0,0,actualWidth,actualHeight);

	qGlImg = qImgResized.rgbSwapped();

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	/* GL_NEAREST */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, actualWidth, actualHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, qGlImg.bits());
}

unsigned int QtGlImage::width()
{
	return mWidth;
}

unsigned int QtGlImage::height()
{
	return mHeight;
}

QtGlImage::~QtGlImage()
{
	glDeleteTextures(1,&id);
}

void QtGlImage::draw(int x, int y)
{
	/*x -= actualWidth - mWidth;
	y -= actualHeight - mHeight;*/
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2i(x				, y + actualHeight);
	glTexCoord2i(1, 0);
	glVertex2i(x + actualWidth	, y + actualHeight);
	glTexCoord2i(1, 1);
	glVertex2i(x + actualWidth	, y);
	glTexCoord2i(0, 1);
	glVertex2i(x				, y);
	glEnd();
	// unbind the texture (we can also do glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void QtGlImage::draw(int x, int y, int xImg, int yImg, int widthImg, int heightImg)
{
	GLdouble xCoord, yCoord, wI,hI;

	/*
		For the coords :
		0 -> xImg
		1 -> xImg + widthImg

		As we need to have a number between 0 and 1, we divide by the width of the texture.

		Same with y.
	*/

	/* Make wrapping ok, as long as you see only one image at once */
	xImg %= mWidth;
	yImg %= mHeight;

	/*	xImg += actualWidth - mWidth;
	*/
	yImg += actualHeight - mHeight;
	xCoord = static_cast<double>(xImg) / static_cast<double>(actualWidth);
	yCoord = static_cast<double>(yImg + mHeight) / static_cast<double>(actualHeight);

	wI = static_cast<double>(widthImg) / static_cast<double>(actualWidth);
	hI = static_cast<double>(heightImg) / static_cast<double>(actualHeight);

	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);

	glTexCoord2d(xCoord, yCoord);
	glVertex2i(x, y + heightImg);

	glTexCoord2d(xCoord+wI, yCoord);
	glVertex2i(x + widthImg, y + heightImg);

	glTexCoord2d(xCoord + wI, yCoord + hI);
	glVertex2i(x + widthImg, y);

	glTexCoord2d(xCoord, yCoord + hI);
	glVertex2i(x, y);

	glEnd();
	// unbind the texture (we can also do glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}


}
