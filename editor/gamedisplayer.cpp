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

#include <QMessageBox>
#include <QMenu>
#include <QMouseEvent>
#include "namechoose.h"
#include <QList>
#include <QApplication>

#include <map>

#include "common/drawmanager.h"
#include "common/exception.h"
#include "gamedisplayer.h"
#include "mime.h"
#include "game/screen.h"
#include "game/screenelement.h"
#include "qtcore/displaywidget.h"


namespace editor
{


using namespace game;

GameDisplayer::GameDisplayer(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *pSound, core::DisplayWidget *pDisplayWidget) :
	GLWrapper(pCore,pDraw,pSound,pDisplayWidget),
	currentScreen(NULL),
	movingItem(false),
	selectedItems(),
	selectionRectangle(),
	selectingItems(false),
	deleteAction(NULL),
	lockAction(NULL)
{
	deleteAction = new QAction(tr("Delete"),this);
	connect(deleteAction,SIGNAL(triggered()), this,SLOT(deleteSelected()));

	lockAction = new QAction(tr("Lock"), this);
	connect(lockAction, SIGNAL(triggered()), this, SLOT(lockSelected()));
}

GameDisplayer::~GameDisplayer()
{

}

bool GameDisplayer::hasObject() const
{
	return currentScreen != NULL;
}

int GameDisplayer::insideHeight() const
{
	if (currentScreen)
		return currentScreen->height();
	return 0;
}

int GameDisplayer::insideWidth() const
{
	if (currentScreen)
		return currentScreen->width();
	return 0;
}

void GameDisplayer::drawFunction()
{
	if (!currentScreen)
		return;
	currentScreen->drawBackground();
	currentScreen->drawObject();
	currentScreen->drawForeground();

	if (selectingItems)
		draw->fadeRect(0x40,selectionRectangleColor,
		               selectionRectangle.x(),
		               selectionRectangle.y(),
		               selectionRectangle.width(),
		               selectionRectangle.height());

	foreach(ScreenElement *el, selectedItems) {
		showSelection(el,selectionColor);
	}
}

void GameDisplayer::inputFunction()
{
	//if(animated)
	currentScreen->nextFrame();
	//if(animated_moving)
	currentScreen->updatePositions();
}

bool GameDisplayer::posContainsSelection(QPoint pos)
{
	ScreenElement* el;

	foreach(el, selectedItems) {
		if (QRect(el->x(),el->y(),el->width(),el->height()).contains(pos))
			return true;
	}
	return false;
}

void GameDisplayer::mousePressEvent(QMouseEvent *event)
{
	event->ignore();
	if (event->button() == Qt::MidButton
	    || (event->button() == Qt::LeftButton && event->modifiers() & Qt::ShiftModifier)
	    || (event->button() == Qt::LeftButton && posContainsSelection(getInsidePosition(event->pos())))) {
		if (!displayWidget->isAncestorOf(childAt(event->pos())))
			return;
		processMove(getInsidePosition(event->pos()));
		if (movingItem)
			event->accept();
	} else if (currentScreen != NULL && event->button() == Qt::LeftButton) {
		selectionStart = getInsidePosition(event->pos());
		selectionRectangle = QRect(selectionStart,QSize(1,1));
		selectingItems = true;

		foreach(ScreenElement *el,selectedItems) {
			emit itemUnselected(currentScreen,el);
		}

		if (!(event->modifiers() & Qt::ControlModifier))
			selectedItems.clear();
		previousSelection = selectedItems;

		updateSelection(getInsidePosition(event->pos()));

		event->accept();
	} else if (event->button() == Qt::RightButton) {
		if (selectedItems.size() > 0) {
			QMenu menu(this);
			menu.addAction(deleteAction);
			menu.addAction(lockAction);
			menu.exec(QCursor::pos());
		}
	}
	GLWrapper::mousePressEvent(event);
}

void GameDisplayer::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();
	if (movingItem) {
		QPoint insidePos = getInsidePosition(event->pos());
		int i;

		for (i=0; i<selectedItems.size(); i++) {
			ScreenElement *el = selectedItems[i];
			const QPoint &pos = initialPositions[i];

			QPoint newPos = insidePos - pos;
			el->setPosition(newPos.x(), newPos.y());

			if (selectedItems.size()==1)
				emit itemChanged(currentScreen,el);
		}
	}
	if (selectingItems) {
		updateSelection(getInsidePosition(event->pos()));
	}
	GLWrapper::mouseMoveEvent(event);
}

void GameDisplayer::mouseReleaseEvent(QMouseEvent *event)
{
	event->ignore();
	if (movingItem) {
		movingItem = false;
		event->accept();
		QApplication::restoreOverrideCursor();
	}
	if (selectingItems) {
		QPoint newPos = getInsidePosition(event->pos());
		if ((selectionRectangle.topLeft() - selectionRectangle.bottomRight()).manhattanLength() < 3) {
			/*
				Selecting only one item !
			*/

			QPoint pos = newPos;
			QMenu menu(this);
			int x = pos.x();
			int y = pos.y();
			int numItems = 0;
			QString name;
			ScreenElement *el = NULL;
			ScreenElement *selected = NULL;

			std::map<std::string, ScreenElement *>::iterator it;

			selectedItems = previousSelection;

			for (it = currentScreen->elements.begin(); it != currentScreen->elements.end(); it++) {
				el = it->second;
				if (!el->locked &&
				    x >= el->x() && x < el->x() + el->width() &&
				    y >= el->y() && y < el->y() + el->height()) {
					name = QString::fromStdString(el->getName());
					QAction *act = menu.addAction(name);
					act->setData(QVariant::fromValue((void*)el));
					selected = el;
					numItems++;
				}
			}

			if (numItems > 1) {
				QAction *act = menu.exec(QCursor::pos());
				if (act == NULL)
					selected = NULL; /* simulate "nothing found at cursor" */
				else
					selected = (ScreenElement*)act->data().value<void*>();
			}

			if (selected) {
				if (selectedItems.contains(selected))
					selectedItems.removeAll(selected);
				else
					selectedItems.append(selected);
			}
		} else
			updateSelection(newPos);
		selectingItems = false;
	}
	GLWrapper::mouseReleaseEvent(event);
}

void GameDisplayer::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *data = event->mimeData();

	if (data->hasFormat(mime::Screen)) {
		if (event->possibleActions() & Qt::MoveAction) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}
	if (currentScreen && data->hasFormat(mime::Object)) {
		if (event->possibleActions() & Qt::CopyAction) {
			event->setDropAction(Qt::CopyAction);
			event->accept();
		}
	}
}

void GameDisplayer::dropEvent(QDropEvent *event)
{
	const QMimeData *data = event->mimeData();
	if (data->hasFormat(mime::Screen)) {
		QByteArray encodedData = data->data(mime::Screen);
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		Screen *screen;
		quintptr t;

		stream >> t;

		screen = (Screen*)t;

		loadScreen(screen);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	} else if (currentScreen && data->hasFormat(mime::Object)) {
		if (!displayWidget->isAncestorOf(childAt(event->pos())))
			return;
		QByteArray encodedData = data->data(mime::Identifier);
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		QString name;

		stream >> name;

		NameChoose nm(this,currentScreen);
		nm.setName(name);
		QApplication::setOverrideCursor(Qt::ArrowCursor);
		//nm.setText(name);
		if (nm.exec() == QDialog::Accepted && nm.text().size() > 0) {
			std::string stlString = nm.text().toStdString();

			QPoint pos = getInsidePosition(event->pos());

			try {
				FileReader fr(name.toLatin1().data());
				ScreenElement *el = new ScreenElement(fr,stlString);

				currentScreen->addObject(stlString,el);

				el->setPosition(pos.x(),pos.y());

				event->setDropAction(Qt::CopyAction);
				event->accept();

				emit objectCreated(currentScreen,el);
			} catch (std::exception &e) {
				QMessageBox::warning(this, tr("Yggdrasil Editor"),
				                     tr(e.what()));
			}
		}
		QApplication::restoreOverrideCursor();
	}

}

void GameDisplayer::loadScreen(game::Screen *screen)
{
	if (currentScreen != screen) {
		foreach(ScreenElement *el, selectedItems) {
			emit itemUnselected(currentScreen,el);
		}
		selectedItems.clear();
	}
	currentScreen = screen;

	QResizeEvent q(size(),size()) ;
	resizeEvent(&q);
}

void GameDisplayer::closeScreen(game::Screen *screen)
{
	if (currentScreen == screen)
		loadScreen(NULL);
}

void GameDisplayer::selectItem(game::Screen *screen, const QString &elName)
{
	if (!screen)
		return;

	std::string name = elName.toStdString();
	ScreenElement *scrEl = screen->elements[name];

	if (!scrEl) {
		QMessageBox::warning(this, tr("Application"),
		                     tr("Element named %1 was not found in the screen.").arg(elName));
		return;
	}

	if (currentScreen != screen)
		loadScreen(screen);

	selectedItems.clear();
	selectedItems.append(scrEl);
}

void GameDisplayer::showSelection(game::ScreenElement *el, uint pColor)
{
	draw->fadeRect(0x40,pColor,el->x(),el->y(),el->width(),el->height());
}

void GameDisplayer::updateSelection(const QPoint &newPos)
{
	int x1,x2,y1,y2;
	QPoint curPoint = newPos;
	x1 = qMin(curPoint.x(),selectionStart.x());
	x2 = qMax(curPoint.x(),selectionStart.x());
	y1 = qMin(curPoint.y(),selectionStart.y());
	y2 = qMax(curPoint.y(),selectionStart.y());

	selectionRectangle = QRect(QPoint(x1,y1),QSize(x2-x1+1,y2-y1+1));

	if ((selectionRectangle.topLeft() - selectionRectangle.bottomRight()).manhattanLength() < 3) {

	}
	QList<game::ScreenElement*> currentSelection = selectedItems;
	selectedItems = previousSelection;

	ScreenElement *el = NULL;

	std::map<std::string, ScreenElement *>::iterator it;

	for (it = currentScreen->elements.begin(); it != currentScreen->elements.end(); it++) {
		el = it->second;
		if (!el->locked &&
		    selectionRectangle.intersects(QRect(el->x(),el->y(),el->width(),el->height()))) {
			if (previousSelection.contains(el))
				selectedItems.removeAll(el);
			else
				selectedItems.append(el);
		}
	}

	if (selectedItems != currentSelection) {
		if (selectedItems.size() == 1)
			emit itemSelected(currentScreen,selectedItems[0]);
		else
			emit itemUnselected(currentScreen, NULL);
	}
}

void GameDisplayer::processMove(const QPoint &inPos)
{
	bool needMove = false;
	foreach(ScreenElement *el,selectedItems) {
		if (inPos.x() >= el->x() && inPos.x() < el->x() + el->width() &&
		    inPos.y() > el->y() && inPos.y() <= el->y() + el->height()) {
			needMove = true;
			break;
		}
	}

	initialPositions.clear();
	if (!needMove)
		return;

	for (int i=0; i<selectedItems.size(); i++) {
		ScreenElement *el = selectedItems[i];

		initialPositions.append(inPos - QPoint(el->x(),el->y()));
	}
	movingItem = true;
	QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
}

void GameDisplayer::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete) {
		deleteSelected();
		return;
	}

	event->ignore();
	GLWrapper::keyPressEvent(event);
}

void GameDisplayer::removeItem(game::Screen *pScr, game::ScreenElement *pEl)
{
	if (currentScreen == pScr) {
		if (selectedItems.contains(pEl)) {
			selectedItems.removeAll(pEl);
			if (selectedItems.size() == 0)
				emit itemUnselected(currentScreen,pEl);
		}
	}
	pScr->remove(pEl);
}

void GameDisplayer::deleteSelected()
{
	while (selectedItems.size() > 0) {
		ScreenElement *el = selectedItems.takeFirst();

		emit objectRemoved(currentScreen,el);
		removeItem(currentScreen,el);
	}
}

void GameDisplayer::lockSelected()
{
	ScreenElement *el;
	foreach(el, selectedItems) {
		el->locked = true;

		emit itemChanged(currentScreen, el);
	}
}


}
