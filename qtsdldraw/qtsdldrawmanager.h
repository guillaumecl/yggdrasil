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
#pragma once

#include "qtcore/qtdrawmanagerbase.h"

#include <map>
#include <string>

#include "sdlimage.h"
#include "qrenderwidget.h"

namespace draw
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class QtSdlDrawManager : public QtDrawManagerBase
{
public:
	QtSdlDrawManager();
	~QtSdlDrawManager();

private:
	std::map<std::string, SdlImage *> openedImages;

	virtual QWidget *getWidget(QWidget *parent = NULL, const char *name = NULL);

	void drawTiled(SdlImage *image, int x, int y, int totalWidth, int totalHeight);

	virtual void setup();
	virtual void update();

	int mapXCoordinate(int x);
	int mapYCoordinate(int y);

public:

	unsigned int scrWidth;
	unsigned int scrHeight;

	unsigned int scrOriginX;
	unsigned int scrOriginY;

	QRenderWidget *widget;
	double curScale;

	/**
	 * 	Returns the specified image. If the image wasn't loaded yet, this function loads it.
	 * @param fileName File name of the image to load.
	 * @returns the image loaded and ready to be displayed.
	 * @throws Exception if the image format is not handled.
	 */
	virtual Image &getImage(const char *fileName);

	/**
	 *	@brief DrawManager initialization
	 * Initialises the video mode, and so on. This usually should create the surfaces, etc.
	 */
	virtual int initGraphics(int width, int height);

	/**
	 *	@brief Function that needs to be called before drawing a frame.
	 *
	 * Prepares for the drawing of a number of images. A Drawing Manager may or may not do something
	 * here, this is mainly for optimization purposes. This will be called before each frame drawing by the
	 * associated Core.
	 * @see endDraw
	 *
	 * @warning A corresponding call to endDraw() is needed.
	 */
	virtual void beginDraw();

	/**
	 *	@brief Function that needs to be called after drawing a frame.
	 *
	 * Ends the drawing optimizations. Typical use of this function will be to undo the different things
	 * that were done inside beginDraw. Another frequent use is to flip the surfaces if double buffering is
	 * being done.
	 * @see beginDraw
	 */
	virtual void endDraw();

	/**
	 * @brief Draws the complete image to the screen at position (x,y).
	 * @param image The image to draw.
	 * @param x The X coordinate on the destination screen
	 * @param y The Y coordinate on the destination screen
	 */
	virtual void draw(Image *image, int x, int y);

	/**
	 * @brief Draws a portion of the image to the screen at position (x,y).
	 * @overload void Image::draw(int x, int y, int xImg, int yImg, int widthImg, int heightImg)
	 * The portion of the image is taken at coordinates (xImg, yImg) of the image
	 * with (widthImg, heightImg) size.
	 * @param image The image to draw.
	 * @param x The X coordinate on the destination screen
	 * @param y The Y coordinate on the destination screen
	 * @param xImg The X coordinate inside the image
	 * @param yImg The Y coordinate inside the image
	 * @param widthImg The width of the portion to take
	 * @param heightImg The height of the portion to take
	 * @warning No defined behaviour is required if xImg+widthImg>width() or  yImg+heightImg>height()
	 * @todo Make overlapping in those conditions ?
	 */
	virtual void draw(Image *image, int x, int y, int xImg, int yImg, int widthImg, int heightImg);

	/**
	 *	@brief Sets the current drawing font.
	 *
	 * This font is the one that will be used with calls to drawText() .
	 * @param fnt The font to set
	 * @see drawText
	 */
	virtual void setFont(Font &fnt);

	/**
	 *	@brief Returns the current drawing font.
	 *
	 * This font is the one that will be used with calls to drawText() .
	 * @returns the current font that is used for drawing directly inside the Drawing Manager.
	 * @see drawText
	 */
	virtual Font &getFont();

	/**
	 * @brief Draws some text in the current font.
	 * @see Font::drawText
	 */
	virtual void drawText(const char *text, int x, int y);

	/**
	 * @brief Returns the text width in the current font.
	 * @see Font::getTextWidth
	 */
	virtual unsigned int getTextWidth(const char *text);

	/**
	 * @brief Returns the text height in the current font.
	 * @see Font::getTextHeight
	 */
	virtual unsigned int getTextHeight(const char *text);

	/**
	 * @brief This sets the graphic origin.
	 *
	 * This will shift all the drawings accordingly.
	 * For example, after setting the origin to (3,4), drawing to (0,0) will have the same meaning
	 * as drawing to (3,4) before the call.
	 * @param x The new X origin
	 * @param y The new Y origin
	 * @note This function is not affected by itself, calling setGraphicOrigin(1,0) several times will not
	 * move the screen several times.
	 * @warning Each call to setGraphicOrigin() must have a corresponding call to restoreGraphicOrigin()
	 * @see restoreGraphicOrigin
	 */
	virtual void setGraphicOrigin(int x, int y);

	/**
	 * @brief Restores the graphic origin.
	 *
	 * The Drawing Manager may restore the state that it had before the call to
	 * setGraphicOrigin ; in particular, for drawing managers that are matrix based (like 3D wrappers) this
	 * call will pop the matrix.
	 *
	 * @warning Do not call this function if there is not a corresponding call to setGraphicOrigin()
	 * @see setGraphicOrigin
	 */
	virtual void restoreGraphicOrigin();

	/**
	 * @brief Shakes the screen like an earthquake.
	 *
	 * @param strength Strength of the shake
	 *
	 * @see endShake
	 * @warning A corresponding call to endShake() needs to be done
	 */
	virtual void shake(int strength);

	/**
		* @brief Restore the "shake" of the screen.
		*
		* @see shake
		*/
	virtual void endShake();

	/**
	 * @brief Fades the screen to the specified color.
	 *
	 * @param p Value of the fade. 0 Means no fade has been done yet, 255 means the fade is done.
	 * @param color Color to fade to
	 */
	virtual void fade(unsigned char p, unsigned long color);

	/**
	 * @brief Fades a region to the specified color.
	 *
	 * @param p Value of the fade. 0 Means no fade has been done yet, 255 means the fade is done.
	 * @param color Color to fade to
	 * @param x the X coordinate (from the left)
	 * @param y the Y coordinate (from the bottom)
	 * @param width the width of the rectangle to fade
	 * @param height the height of the rectangle to fade
	 */
	virtual void fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height);

	/**
	 * @brief Scales the screen
	 *
	 * @param scale scale value to be applied.
	 */
	virtual void scale(double scale);

	/**
	 * @brief Restore the "scale" of the screen.
	 *
	 * @see scale
	 */
	virtual void endScale();
};

}
