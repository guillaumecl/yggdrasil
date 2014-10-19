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

#include <QMouseEvent>

#include "objectdisplayer.h"

#include "mime.h"
#include "sprite.h"

#include "screenelement.h"

namespace editor
{


using namespace game;

ObjectDisplayer::ObjectDisplayer(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *pSound, core::DisplayWidget *pDisplayWidget) :
	GLWrapper(pCore,pDraw,pSound,pDisplayWidget),
	currentObject(NULL)
{
}


ObjectDisplayer::~ObjectDisplayer()
{

}

int ObjectDisplayer::insideWidth() const
{
	if (currentObject)
		return currentObject->width();
	return 0;
}

int ObjectDisplayer::insideHeight() const
{
	if (currentObject)
		return currentObject->height();
	return 0;
}

bool ObjectDisplayer::hasObject() const
{
	return currentObject != NULL;
}

void ObjectDisplayer::drawFunction()
{
	currentObject->draw(draw::planes::background);
	currentObject->draw(draw::planes::object);
	currentObject->draw(draw::planes::foreground);
}

void ObjectDisplayer::inputFunction()
{
	//if(animated)
	currentObject->nextFrame();
	//if(animated_moving)
	//currentObject->updatePositions();
}

void ObjectDisplayer::mousePressEvent(QMouseEvent *event)
{
	event->ignore();
	if (currentObject != NULL && event->button() == Qt::LeftButton) {

	}
	GLWrapper::mousePressEvent(event);
}

void ObjectDisplayer::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();
	GLWrapper::mouseMoveEvent(event);
}

void ObjectDisplayer::mouseReleaseEvent(QMouseEvent *event)
{
	event->ignore();
	GLWrapper::mouseReleaseEvent(event);
}

void ObjectDisplayer::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *data = event->mimeData();

	if (data->hasFormat(mime::Object)) {
		if (event->possibleActions() & Qt::MoveAction) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}
}

void ObjectDisplayer::dropEvent(QDropEvent *event)
{
	const QMimeData *data = event->mimeData();
	if (data->hasFormat(mime::Object)) {
		QByteArray encodedData = data->data(mime::Object);
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		quint32 t;

		stream >> t;

		ScreenElement *el = (ScreenElement*)t;

		loadObject(el);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ObjectDisplayer::loadObject(game::ScreenElement *element)
{
	currentObject = element;

	QResizeEvent q(size(),size()) ;
	resizeEvent(&q);
}

void ObjectDisplayer::closeObject(game::ScreenElement *element)
{
	if (currentObject == element)
		loadObject(NULL);
}

}



