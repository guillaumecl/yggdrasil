/***************************************************************************
 *   Copyright (C) 2007 by flik   *
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
#ifndef EDITOROBJECTITEM_H
#define EDITOROBJECTITEM_H

#include "game/basictypes.h"

#include <QStandardItem>

namespace editor
{

namespace custom
{

class ObjectItem: public QStandardItem
{
	int mType;
	QString mName;
	bool hasPointer;
	void *mPointer;

public:
	ObjectItem(const QIcon &pIcon, const QString &pText, const QString &pName, int pType);
	ObjectItem(const QIcon &pIcon, const QString &pText, int pType);
	int type() const;


	/**
	 * Functions used to access the pointer.
	 */
	void *pointer() const;
	game::Screen *screen() const;
	game::ScreenElement *screenElement() const;
	game::Action *action() const;

	ObjectItem *parent() const;

	QString name() const;

	void setName(const QString &pName);
	void setPointer(void *pPointer);
	void setScreen(game::Screen *el);
	void setScreenElement(game::ScreenElement *el);
	void setAction(game::Action *act);

	bool isLoaded() const;
	bool hasVisibleChildren(QRegExp pFilter);
};

}

}

#endif
