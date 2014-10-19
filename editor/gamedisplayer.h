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
#ifndef EDITORSCREENEDITOR_H
#define EDITORSCREENEDITOR_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>

#include "glwrapper.h"

#include "basictypes.h"

namespace editor
{

/**
 * The GameDisplayer object is like a game screen, except that no input action takes place here. It really uses the default core components like inside the game to make perfect compatibility.
 *
 *	@author Lightning Flik <flik@baobob.org>
 */
class GameDisplayer : public GLWrapper
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
	GameDisplayer(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *sound, core::DisplayWidget *pDisplayWidget);

	/**
	 * Destructor for the GameDisplayer
	 */
	~GameDisplayer();

	/**
	 * The screen that is shown by this GameDisplayer object
	 */
	game::Screen *currentScreen;

	/**
	 * True while moving an object with the middle button
	 */
	bool movingItem;

	/**
	 * Redraws the content with the objects. Does the same thing as the game one.
	 */
	virtual void drawFunction();

	/**
	 * Function called once per frame, before the actual drawing. Updating of the object
	 * state happens here. Does the same thing as the game counterpart.
	 */
	virtual void inputFunction();

	void showSelection(game::ScreenElement *el, uint pColor);
	void updateSelection(const QPoint &newPos);
	void processMove(const QPoint &inPos);

	/**
	 * Selected items inside currentScreen, if any.
	 */
	QList<game::ScreenElement*> selectedItems;

public slots:
	/**
	 * Loads the specified screen inside the view.
	 *
	 * @param screen The screen to be shown
	 */
	void loadScreen(game::Screen *screen);

	/**
	 * Closes the screen viewing.
	 *
	 * @param screen the screen that must be unloaded.
	 */
	void closeScreen(game::Screen *screen);

	/**
	 * Selects the item of the specified screen.
	 *
	 * @param screen The screen containing the item to select. This screen is loaded if it's not active already.
	 * @param scrElName The name of the Screen Element to select. Does nothing if the screen element is not valid.
	 */
	void selectItem(game::Screen *screen, const QString &scrElName);

	void removeItem(game::Screen *screen, game::ScreenElement *el);

	void deleteSelected();
	void lockSelected();

signals:
	void itemSelected(game::Screen *pScreen, game::ScreenElement *element);
	void itemUnselected(game::Screen *pScreen, game::ScreenElement *element);
	void itemChanged(game::Screen *pScreen, game::ScreenElement *element);
	void objectCreated(game::Screen *pScreen, game::ScreenElement *element);
	void objectRemoved(game::Screen *pScreen, game::ScreenElement *element);

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);


	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);

	virtual int insideWidth() const;
	virtual int insideHeight() const;
	virtual bool hasObject() const;

	virtual void keyPressEvent(QKeyEvent *event);
private:
	QRect selectionRectangle;
	bool selectingItems;
	QPoint selectionStart;
	QList<QPoint> initialPositions;

	/**
	 * Selected items before the selection.
	 */
	QList<game::ScreenElement*> previousSelection;

	QAction *deleteAction;
	QAction *lockAction;

	static const uint selectionColor = 0x4579FF;
	static const uint selectionRectangleColor = 0xFF4579;

	bool posContainsSelection(QPoint pos);
};

}

#endif
