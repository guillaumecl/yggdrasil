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

#include "itemfilter.h"
#include "objectitem.h"
#include "mime.h"

namespace editor
{

namespace custom
{


ItemFilter::ItemFilter(QObject *parent):
	QSortFilterProxyModel(parent)
{
	setDynamicSortFilter(true);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
}


bool ItemFilter::filterAcceptsRow(int sourceRow,const QModelIndex &sourceParent) const
{
	QStandardItemModel *pModel = dynamic_cast<QStandardItemModel *>(sourceModel());
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
	if (pModel) {
		QStandardItem *pItem = pModel->itemFromIndex(index);

		if (pItem) {
			if (pItem->type() == item::Object || pItem->type() == item::Screen) {
				// IF this is an object in the screen tree, we don't filter it, but the screen instead.
				// the screen is filtered by a previous call so just return true.
				if (pItem->type() == item::Object && pItem->parent() && pItem->parent()->type() == item::Screen)
					return true;

				return pItem->text().contains(filterRegExp());
			} else if (pItem->type() == item::Folder) {
				// hide folders with no items.
				ObjectItem *item = dynamic_cast<ObjectItem*>(pItem);
				return item->hasVisibleChildren(filterRegExp());
			}
		}
	}
	return true;
}

bool ItemFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
	QStandardItemModel *pModel = dynamic_cast<QStandardItemModel *>(sourceModel());
	if (pModel) {
		ObjectItem *pLeft = dynamic_cast<ObjectItem*>(pModel->itemFromIndex(left));
		ObjectItem *pRight = dynamic_cast<ObjectItem*>(pModel->itemFromIndex(right));

		if (pLeft->type() == pRight->type()) {
			int ret = QString::localeAwareCompare(pLeft->text(), pRight->text());
			if (ret == 0)
				return QString::localeAwareCompare(pLeft->name(), pRight->name()) > 0;
			else
				return ret > 0;
		} else if (pLeft->type() == item::Folder)
			return false;
		else
			return true;
	}
	return true;
}

}

}
