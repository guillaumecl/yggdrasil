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

#include "glwrapper.h"

#include "game/basictypes.h"

namespace editor
{

/**
 * The ObjectDisplayer object is like a game screen, except that no input action takes place here. It really uses the default core components like inside the game to make perfect compatibility.
 *
 *	@author Lightning Flik <flik@baobob.org>
 */
class ObjectDisplayer : public GLWrapper
{
	Q_OBJECT
public:
	/**
	 * Constructor for the ObjectDisplayer.
	 *
	 * @param pCore Core to use for screen display
	 * @param pDraw DrawManager to use for screen display
	 * @param pSound SoundManager to use for screen display
	 * @param pGlWidget GL Widget to use for better control on the screen
	 */
	ObjectDisplayer(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *sound, core::DisplayWidget *pDisplayWidget);

	/**
	 * Destructor for the ObjectDisplayer
	 */
	~ObjectDisplayer();

	/**
	 * The object that is shown by this ObjectDisplayer object
	 */
	game::ScreenElement *currentObject;

	/**
	 * Redraws the content with the objects. Does the same thing as the game one.
	 */
	void drawFunction();

	/**
	 * Function called once per frame, before the actual drawing. Updating of the object
	 * state happens here. Does the same thing as the game counterpart.
	 */
	void inputFunction();

public slots:
	/**
	 * Loads the specified screen inside the view.
	 *
	 * @param screen The screen to be shown
	 */
	void loadObject(game::ScreenElement *element);

	/**
	 * Closes the screen viewing.
	 *
	 * @param screen the screen that must be unloaded.
	 */
	void closeObject(game::ScreenElement *element);

signals:

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);


	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);

	virtual int insideWidth() const;
	virtual int insideHeight() const;
	virtual bool hasObject() const;

};

}
