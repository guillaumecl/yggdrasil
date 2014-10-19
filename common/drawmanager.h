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
#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

/**
 * @namespace draw
 *
 * @brief This namespace contains all of the tools that are needed to show something to the user screen.
 *
 * Most classes are implemented inside plugins, and possibly
 * architecture-dependent.
 */
namespace draw
{


class DrawManager;

/**
 * 	@brief Interface for the Image class.
 * 	@author Lightning Flik <flik@baobob.org>
 */
class Image
{
private:
	/**
	 * 	Disable copy constructor for Image. Will save some bugs...
	 */
	Image(const Image &) ;

	/**
	 * 	Disable copy constructor for Image. Will save some bugs...
	 */
	void operator=(const Image &) ;

public:
	/**
		* Default (unused) constructor. If removed, some compilers won't compile.
		*/
	Image() {};

	/**
	 *	@brief Image width.
	 * @returns the width of the complete image
	 */
	virtual unsigned int width() = 0;

	/**
	 *	@brief Image height.
	 * @returns the height of the complete image
	 */
	virtual unsigned int height() = 0;

	/**
	 * @brief Image destructor
	 */
	virtual ~Image() {}
};


/**
*	@brief Interface for the Font class.
*
*	A Font object allows its user to write text on the screen. Different fonts will have different looks.
*	The color may be passed as an argument to the drawing function, but size and looks are unique to one font.
* 	@author Lightning Flik <flik@baobob.org>
*/
class Font
{
private:
	/**
	 * 	Disable copy constructor for Font. Will save some bugs...
	 */
	Font(const Font &) ;

	/**
	 * 	Disable copy constructor for Font. Will save some bugs...
	 */
	void operator=(const Font &) ;

public:
	/**
	 * Default (unused) constructor. If removed, some compilers won't compile.
	 */
	Font() {};
	/**
	 * @brief Draws some text on the screen.
	 * @param text The text to draw. Must be NULL-terminated.
	 * @param x The X destination coordinate
	 * @param y The Y destination coordinate
	 */
	virtual void drawText(const char *text, int x, int y) = 0;

	/**
	 * @brief Returns the width of a text using this font
	 * @param text The text we need to get the width. Must be NULL-terminated.
	 * @returns The width that the text will have once drawn on the screen
	 * @see getTextHeight
	 */
	virtual unsigned int getTextWidth(const char *text) = 0;

	/**
	 * @brief Returns the height of a text using this font
	 * @param text The text we need to get the width. Must be NULL-terminated.
	 * @returns The height that the text will have once drawn on the screen
	 * @see getTextWidth
	 */
	virtual unsigned int getTextHeight(const char *text) = 0;

	/**
	 *	@brief Destructor for the Font
	 */
	virtual ~Font();
};

/**
* 	@brief Interface for the DrawManager class.
*
*	The Draw Manager is the object that handles all the drawings on the screen.
*
* 	@author Lightning Flik <flik@baobob.org>
*/
class DrawManager
{
private:
	/**
	 * 	Disable copy constructor for DrawManager. Will save some bugs...
	 */
	DrawManager(const DrawManager &) {}

	/**
	 * 	Disable copy constructor for DrawManager. Will save some bugs...
	 */
	void operator=(const DrawManager &) {}

public:
	/**
	 * Default (unused) constructor. If removed, some compilers won't compile.
	 */
	DrawManager() {};
	/**
	 *	@brief Destructor for the Draw Manager
	 */
	virtual ~DrawManager() {}

	/**
	 * 	Returns the specified image. If the image wasn't loaded yet, this function loads it.
	 * @param fileName File name of the image to load.
	 * @returns the image loaded and ready to be displayed.
	 * @throws Exception if the image format is not handled.
	 */
	virtual Image &getImage(const char *fileName) = 0;

	/**
	 *	@brief DrawManager initialization
	 * Initialises the video mode, and so on. This usually should create the surfaces, etc.
	 */
	virtual int initGraphics(int width, int height) = 0;

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
	virtual void beginDraw() = 0;

	/**
	 *	@brief Function that needs to be called after drawing a frame.
	 *
	 * Ends the drawing optimizations. Typical use of this function will be to undo the different things
	 * that were done inside beginDraw. Another frequent use is to flip the surfaces if double buffering is
	 * being done.
	 * @see beginDraw
	 */
	virtual void endDraw() = 0;

	/**
	 * @brief Draws the complete image to the screen at position (x,y).
	 * @param image The image to draw.
	 * @param x The X coordinate on the destination screen
	 * @param y The Y coordinate on the destination screen
	 */
	virtual void draw(Image *image, int x, int y) = 0;

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
	virtual void draw(Image *image, int x, int y, int xImg, int yImg, int widthImg, int heightImg) = 0;

	/**
	 *	@brief Sets the current drawing font.
	 *
	 * This font is the one that will be used with calls to drawText() .
	 * @param fnt The font to set
	 * @see drawText
	 */
	virtual void setFont(Font &fnt) = 0;

	/**
	 *	@brief Returns the current drawing font.
	 *
	 * This font is the one that will be used with calls to drawText() .
	 * @returns the current font that is used for drawing directly inside the Drawing Manager.
	 * @see drawText
	 */
	virtual Font &getFont() = 0;

	/**
	 * @brief Draws some text in the current font.
	 * @see Font::drawText
	 */
	virtual void drawText(const char *text, int x, int y) = 0;

	/**
	 * @brief Returns the text width in the current font.
	 * @see Font::getTextWidth
	 */
	virtual unsigned int getTextWidth(const char *text) = 0;

	/**
	 * @brief Returns the text height in the current font.
	 * @see Font::getTextHeight
	 */
	virtual unsigned int getTextHeight(const char *text) = 0;

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
	virtual void setGraphicOrigin(int x, int y) = 0;

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
	virtual void restoreGraphicOrigin() = 0;

	/**
	 * @brief Shakes the screen like an earthquake.
	 *
	 * @param strength Strength of the shake
	 *
	 * @see endShake
	 * @warning A corresponding call to endShake() needs to be done
	 */
	virtual void shake(int strength) = 0;

	/**
		* @brief Restore the "shake" of the screen.
		*
		* @see shake
		*/
	virtual void endShake() = 0;

	/**
	 * @brief Fades the screen to the specified color.
	 *
	 * @param p Value of the fade. 0 Means no fade has been done yet, 255 means the fade is done.
	 * @param color Color to fade to
	 */
	virtual void fade(unsigned char p, unsigned long color) = 0;

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
	virtual void fadeRect(unsigned char p, unsigned long color, int x, int y, int width, int height) = 0;

	/**
	 * @brief Scales the screen
	 *
	 * @param scale scale value to be applied.
	 */
	virtual void scale(double scale) = 0;

	/**
	 * @brief Restore the "scale" of the screen.
	 *
	 * @see scale
	 */
	virtual void endScale() = 0;

};


}

#endif
