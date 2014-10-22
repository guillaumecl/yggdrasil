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

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>

#include "qtcore/qtcore_types.h"
#include "common/common_types.h"

namespace editor
{

/**
 * The GameDisplayer object is like a game screen, except that no input action takes place here. It really uses the default core components like inside the game to make perfect compatibility.
 *
 *	@author Lightning Flik <flik@baobob.org>
 */
class GLWrapper : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Constructor for the GameDisplayer.
	 *
	 * @param pCore Core to use for screen display
	 * @param pDraw DrawManager to use for screen display
	 * @param pSound SoundManager to use for screen display
	 * @param pGlWidget GL Widget to use for better control on the screen
	 */
	GLWrapper(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *sound, core::DisplayWidget *pDisplayWidget);

	/**
	 * Destructor for the GameDisplayer
	 */
	~GLWrapper();

	/**
	 * Core object that was created in the constructor
	 */
	core::QtCore *core;

	/**
	 * Draw Manager object that was created in the constructor
	 */
	draw::DrawManager *draw;

	/**
	 * Sound Manager object that was created in the constructor
	 */
	sound::SoundManager *sound;

	/**
	 * The GL Widget is a special kind of part of the Core object, created only by the QtCore plugin. This gives some control to insert the drawing inside our Main window.
	 */
	core::DisplayWidget *displayWidget;

	/**
	 * State of the scrollbar at the beginning of the move when moving the origin with middle button
	 */
	QPoint scrollStart;

	/**
	 * Selection point at the beginning of the move when moving with the origin middle button (moving == true).
	 *
	 * Offset inside the object when moving an object with the middle button (movingItem == true)
	 */
	QPoint moveStart;

	/**
	 * True while moving the origin with the middle button
	 */
	bool moving;

	/**
	 * Zoom factor. 1.0 is normal size, 0.5 is half size, etc.
	 */
	double scale;

	static void drawFunc();
	static void inputFunc();

public slots:
	/**
	 * Puts the GL widget in Screen displaying mode. Call this when the
	 * GameDisplayer in shown.
	 */
	void activate();

	void deactivate();

signals:
	void mouseMoved(const QPoint &newPos);

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);


	virtual void wheelEvent(QWheelEvent *event);

	virtual void showEvent(QShowEvent *event);
	virtual void hideEvent(QHideEvent *event);

	/**
	 * Redraws the content with the objects. Does the same thing as the game one.
	 */
	virtual void drawFunction() = 0;

	/**
	 * Function called once per frame, before the actual drawing. Updating of the object
	 * state happens here. Does the same thing as the game counterpart.
	 */
	virtual void inputFunction() = 0;

	virtual int insideWidth() const = 0;
	virtual int insideHeight() const = 0;
	virtual bool hasObject() const = 0 ;

	virtual QSize sizeHint() const;

	QPoint getInsidePosition(QPoint relPos);
	bool isValidPosition(QPoint insidePos);
private:
	QVBoxLayout *vboxLayout;
	QHBoxLayout *hboxLayout;
	QScrollBar *verticalScrollBar;
	QScrollBar *horizontalScrollBar;
	QWidget *hScrollSmall;

	void setupUi();

	void baseDrawFunction();
	void baseInputFunction();

	static GLWrapper *editor;

	static bool widgetSetup;

	QWidget *hWidget;

	int hValue();
	int vValue();
};

}
