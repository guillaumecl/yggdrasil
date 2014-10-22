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
#include "objecttree.h"

#include <QApplication>
#include <QDir>
#include <QMenu>
#include <QHeaderView>
#include <QDragEnterEvent>
#include <QDebug>

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include "mime.h"
#include "itemfilter.h"
#include "filterwidget.h"
#include "objectitem.h"

#include "common/exception.h"
#include "common/archiver.h"
#include "game/screenelement.h"

using game::ScreenElement;
using game::Action;

using std::map;
using std::string;

using editor::custom::FilterWidget;
using editor::custom::ObjectItem;
using editor::custom::ItemFilter;


namespace editor
{

ObjectTree::ObjectTree(QWidget *parent) :
	QTreeView(parent),
	iconObject(QString::fromUtf8(":/object.png")),
	iconAction(QString::fromUtf8(":/action.png")),
	iconFolderClosed(QString::fromUtf8(":/folder/folder.png")),
	iconFolderOpen(QString::fromUtf8(":/folder/folder_open.png")),
	itemModel(NULL),
	filterModel(NULL),
	actLoad(NULL),
	actRefresh(NULL),
	actClose(NULL)
{
	itemModel = new QStandardItemModel(this);
	itemModel->setColumnCount(1);

	filterModel = new ItemFilter(this);
	filterModel->setSourceModel(itemModel);
	header()->setHidden(true);

	setModel(filterModel);

	setSortingEnabled(true);

	actLoad = new QAction(tr("Load"),this);
	connect(actLoad,SIGNAL(triggered()), this,SLOT(on_load()));

	connect(this,SIGNAL(expanded(const QModelIndex &)),
	        this,SLOT(on_itemExpanded(const QModelIndex &)));

	connect(this,SIGNAL(collapsed(const QModelIndex &)),
	        this,SLOT(on_itemCollapsed(const QModelIndex &)));
}

QWidget *ObjectTree::insertFilter()
{
	FilterWidget *lineEd = new FilterWidget(this);

	connect(lineEd, SIGNAL(textEdited(const QString &)),
	        filterModel, SLOT(setFilterWildcard(const QString &)));

	return lineEd;
}

void ObjectTree::setFilterWidget(FilterWidget *filter)
{
	connect(filter, SIGNAL(textEdited(const QString &)),
	        filterModel, SLOT(setFilterWildcard(const QString &)));
}

ObjectTree::~ObjectTree()
{
	QList<QStandardItem *> items = itemModel->findItems("*", Qt::MatchRecursive | Qt::MatchWildcard);

	int i;

	for (i=0; i<items.size(); i++) {
		ObjectItem *item = dynamic_cast<ObjectItem*>(items[i]);
		if (item && item->screenElement())
			delete item->screenElement();
	}
}

void ObjectTree::scan(QDir curDir, QStandardItem *parent)
{
	if (!parent)
		itemModel->clear();

	curDir.setFilter(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot);
	curDir.setSorting(QDir::Name);

	QStringList dirList = curDir.entryList();
	QString dir;

	QStandardItem *p = parent;
	if (!p)
		p = itemModel->invisibleRootItem();

	foreach(dir, dirList) {
		QDir newDir(curDir);
		newDir.cd(dir);

		ObjectItem *folder = new ObjectItem(iconFolderClosed, dir, item::Folder);
		p->appendRow(folder);

		scan(newDir, folder);
	}

	curDir.setFilter(QDir::Files | QDir::Readable);
	curDir.setNameFilters(QStringList("*.elm"));
	curDir.setSorting(QDir::Name);

	QStringList objectList = curDir.entryList();

	for (int i = 0; i < objectList.size(); ++i)
		addObject(curDir.absoluteFilePath(objectList.at(i)), p);

	if (!parent)
		filterModel->invalidate();
}

void ObjectTree::addObject(QString objFile, QStandardItem *parent)
{
	FileReader fr(objFile.toLatin1().data());

	QString name = QString::fromStdString(fr.getString("ScreenEditor","name", QFileInfo(objFile).fileName().toLocal8Bit().constData()));

	QString iconName = QString::fromStdString(fr.getString("ScreenEditor","icon",""));
	QIcon *iconRef = &iconObject;

	if (!iconName.isEmpty()) {
		iconRef = new QIcon(iconName);
		if (iconRef->pixmap(16).isNull()) {
			delete iconRef;
			iconRef = &iconObject;
		}
	}


	ObjectItem *obj = new ObjectItem(*iconRef,name, objFile, item::Object);
	if (iconRef != &iconObject)
		delete iconRef;
	parent->appendRow(obj);
}

void ObjectTree::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
		dragStartPosition = event->pos();
	else if (event->button() == Qt::RightButton) {
		ObjectItem *obj = itemAt(event->pos());
		if (obj && obj->type() == item::Object && !obj->isLoaded()) {
			QMenu menu(this);

			menu.addAction(actLoad);
			menu.setDefaultAction(actLoad);

			menu.exec(event->globalPos());
		}
	}
}

ObjectItem *ObjectTree::itemAt(const QPoint &pos)
{
	return itemAt(indexAt(pos));
}

ObjectItem *ObjectTree::itemAt(const QModelIndex &index)
{
	return dynamic_cast<ObjectItem*>(itemModel->itemFromIndex(filterModel->mapToSource(index)));
}
void ObjectTree::mouseMoveEvent(QMouseEvent *event)
{
	QTreeView::mouseMoveEvent(event);
	if (!(event->buttons() & Qt::LeftButton)) return;
	if ((event->pos() - dragStartPosition).manhattanLength()
	    < QApplication::startDragDistance())
		return;
	ObjectItem *it = itemAt(dragStartPosition);
	if (!it || it->type() !=  item::Object)
		return;

	QDrag *drag = new QDrag(this);

	bool load = true;

	/*
		Create an empty screen if it isn't loaded yet.
	This screen will be deleted if the drag is cancelled.
	*/
	ScreenElement *scrEl = it->screenElement();
	if (!scrEl) {
		try {
			scrEl = new ScreenElement();
		} catch (exception &e) {
			QMessageBox::warning(this, tr("Application"),
			                     tr(e.what()));
		}
	} else
		load = false;
	QMimeData *data = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	stream << (quintptr)scrEl;
	data->setData(mime::Object, encodedData);

	QDataStream streamId(&encodedData,QIODevice::WriteOnly);
	streamId << it->name();
	data->setData(mime::Identifier, encodedData);

	drag->setMimeData(data);

	Qt::DropAction dropAction = drag->start(Qt::MoveAction);

	if (dropAction == Qt::MoveAction) {
		/*
			After a successful drop, effectively load the screen,
		or update it if it was already loaded.
		*/
		if (load) {
			QString name = it->name();

			FileReader fr(name.toLatin1());
			scrEl->load(fr);

			it->setScreenElement(scrEl);
			scanObject(it);
		}
		emit objectSelected(scrEl);
		emit loadObject(scrEl);
		setExpanded(it->index(),true);
	} else if (load)
		delete scrEl;
}

void ObjectTree::on_itemExpanded(const QModelIndex &ind)
{
	ObjectItem *item = dynamic_cast<ObjectItem*>(itemModel->itemFromIndex(filterModel->mapToSource(ind)));
	if (!item || item->type() != item::Folder)
		return;
	item->setIcon(iconFolderOpen);
}

void ObjectTree::on_itemCollapsed(const QModelIndex &ind)
{
	ObjectItem *item = dynamic_cast<ObjectItem*>(itemModel->itemFromIndex(filterModel->mapToSource(ind)));
	if (!item || item->type() != item::Folder)
		return;
	item->setIcon(iconFolderClosed);
}

void ObjectTree::mouseDoubleClickEvent(QMouseEvent * event)
{
	QTreeView::mouseDoubleClickEvent(event);
	on_load();
	ObjectItem *it = itemAt(event->pos());
	if (it->screenElement())
		emit loadObject(it->screenElement());
}

void ObjectTree::on_load()
{
	QModelIndexList list = selectedIndexes();
	if (list.size() != 1)
		return;
	QModelIndex ind = list[0];

	ObjectItem *el = dynamic_cast<ObjectItem*>(itemModel->itemFromIndex(filterModel->mapToSource(ind)));

	if (!el || el->type() != item::Object)
		return;

	if (el->isLoaded())
		return;

	/*
	 * Load the object.
	 */

	try {
		FileReader fr(el->name().toLatin1().data());
		ScreenElement *scrEl = new ScreenElement(fr, "");

		el->setScreenElement(scrEl);
		scanObject(el);
		emit objectSelected(scrEl);
	} catch (const exception &e) {
		QMessageBox::warning(this, tr("Application"),
		                     tr(e.what()));
	}
}

void ObjectTree::scanObject(ObjectItem *obj)
{
	if (!obj || obj->type() != item::Object || !obj->isLoaded())
		return;

	ScreenElement *scrEl = obj->screenElement();
	map<string, Action *>::iterator iter;

	for (iter = scrEl->actions.begin(); iter != scrEl->actions.end(); iter++) {
		QString name = QString::fromStdString(iter->first);
		Action *act = iter->second;

		ObjectItem *it = new ObjectItem(iconAction,name,item::Action);
		obj->appendRow(it);
		it->setAction(act);
	}

	setExpanded(filterModel->mapFromSource(obj->index()), true);
}


void ObjectTree::currentChanged(const QModelIndex &selected, const QModelIndex &previous)
{
	/* could happen, maybe !*/
	ObjectItem *item = itemAt(selected);
	if (!item)
		return;
	if (item->type() == item::Object) {
		ScreenElement *scrEl = item->screenElement();
		/*
		 * Note: item->screenElement() can be NULL in the case the screen isn't
		 * loaded. In this case, the properties will hide the properties.
		 */
		emit objectSelected(scrEl);
	} else if (item->type() == item::Action) {
		ScreenElement *scrEl = item->parent()->screenElement();
		Action *act = item->action();
		scrEl->changeAction(act);
		emit actionSelected(scrEl,act);
	} else
		emit objectSelected(NULL);
	Q_UNUSED(previous);
}

void ObjectTree::on_itemLoaded(game::ScreenElement *scrEl)
{
	(void)scrEl;
}


}
