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
#include <QStandardItem>

namespace editor
{
namespace mime
{
const QString Screen = "yggdrasil/screen";
const QString Object = "yggdrasil/object";
const QString Identifier = "yggdrasil/identifier";
}


namespace drag
{
	enum DragData
	{
		Name = Qt::UserRole+1,
		Type = Qt::UserRole+2,
		Pointer = Qt::UserRole+3,
	};

	enum DragType
	{
		Screen = 0,
		Object = 1,
	};

}

namespace item
{
	enum ItemType
	{
		Folder = QStandardItem::UserType+1,
		Object = QStandardItem::UserType+2,
		Action = QStandardItem::UserType+3,
		Screen = QStandardItem::UserType+4,
	};
}



}

