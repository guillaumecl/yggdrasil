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
#include "screentree.h"

#include <QApplication>
#include <QMenu>
#include <QDir>
#include <QHeaderView>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMessageBox>

#include "mime.h"
#include "common/exception.h"
#include "game/screen.h"
#include "game/screenelement.h"

#include "objectitem.h"
#include "itemfilter.h"

#include "filterwidget.h"

using editor::custom::FilterWidget;
using editor::custom::ObjectItem;

using game::Screen;
using game::ScreenElement;

using editor::custom::ItemFilter;

using std::map;
using std::string;

namespace editor
{

ScreenTree::ScreenTree(QWidget *parent) :
	QTreeView(parent),
	iconObject(QString::fromUtf8(":/object.png")),
	iconScreen(QString::fromUtf8(":/screen.png")),
	iconFolderClosed(QString::fromUtf8(":/folder/folder.png")),
	iconFolderOpen(QString::fromUtf8(":/folder/folder_open.png"))
{
	itemModel = new QStandardItemModel(this);
	itemModel->setColumnCount(1);

	filterModel = new ItemFilter(this);
	filterModel->setSourceModel(itemModel);
	header()->setHidden(true);

	setModel(filterModel);

	setSortingEnabled(true);

	connect(this,SIGNAL(doubleClicked(const QModelIndex &)),
	        this,SLOT(openItem(const QModelIndex &)));

	actLoad = new QAction(tr("Load"),this);
	actRefresh = new QAction(tr("Refresh"),this);
	actClose = new QAction(tr("Close"),this);

	connect(actClose,SIGNAL(triggered()), this,SLOT(on_close()));
	connect(actRefresh,SIGNAL(triggered()), this,SLOT(on_refresh()));
	connect(actLoad,SIGNAL(triggered()), this,SLOT(on_load()));

	QFont fnt = actLoad->font();
	fnt.setBold(true);
	actLoad->setFont(fnt);
	actRefresh->setFont(fnt);

}


ScreenTree::~ScreenTree()
{
	QList<QStandardItem *> items = itemModel->findItems("*", Qt::MatchRecursive | Qt::MatchWildcard);

	int i;

	for (i=0; i<items.size(); i++) {
		ObjectItem *item = dynamic_cast<ObjectItem*>(items[i]);
		if (item && item->screen())
			delete item->screen();
	}
}

void ScreenTree::scan(QDir curDir, QStandardItem *parent)
{
	//TODO bug : if we scan when some screens are loaded, they stay loaded but are not marked so.
	if (!parent)
		itemModel->clear();

	QStandardItem *p = parent;
	if (!p)
		p = itemModel->invisibleRootItem();

	curDir.setFilter(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot);
	curDir.setSorting(QDir::Name);

	QStringList dirList = curDir.entryList();
	QString dir;

	foreach(dir, dirList) {
		QDir newDir(curDir);
		newDir.cd(dir);

		ObjectItem *folder = new ObjectItem(iconFolderClosed, dir, item::Folder);
		p->appendRow(folder);

		scan(newDir, folder);
	}

	curDir.setFilter(QDir::Files | QDir::Readable);
	curDir.setNameFilters(QStringList("*.scr"));
	curDir.setSorting(QDir::Name);

	QStringList screenList = curDir.entryList();

	for (int i = 0; i < screenList.size(); ++i)
		addScreen(curDir.absoluteFilePath(screenList.at(i)), p);

	if (!parent)
		filterModel->invalidate();
}

void ScreenTree::addScreen(QString scrFile, QStandardItem *folder)
{
	ObjectItem *scr = new ObjectItem(iconScreen, QFileInfo(scrFile).fileName(), scrFile, item::Screen);

	folder->appendRow(scr);
}

void ScreenTree::openItem(const QModelIndex &ind)
{
	ObjectItem *item = itemAt(ind);
	if (item->type() == item::Screen) {
		Screen *scr = item->screen();

		if (!scr) {
			try {
				scr = new Screen;
			} catch (const std::exception &e) {
				QMessageBox::warning(this, tr("Application"),
				                     tr(e.what()));
			}
			item->setScreen(scr);
			loadScreenInfo(item);
		} else
			updateScreenInfo(item);

		emit loadScreen(scr);
		emit screenSelected(scr);
		setExpanded(item->index(),false);
	}
}
void ScreenTree::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
		dragStartPosition = event->pos();
	else if (event->button() == Qt::RightButton) {
		QMenu menu(this);
		ObjectItem *it = itemAt(event->pos());
		if (!it)
			return;
		if (it->type() == item::Screen) {
			Screen *screen = it->screen();
			menu.setTitle(tr("Screen"));
			if (screen) {
				menu.addAction(actRefresh);
				menu.addAction(actClose);
			} else {
				menu.addAction(actLoad);
			}
		} else if (it->type() == item::Object) {
			menu.setTitle(tr("Object"));
		}
		if (!menu.isEmpty())
			menu.exec(event->globalPos());
	}
}

void ScreenTree::mouseMoveEvent(QMouseEvent *event)
{
	QTreeView::mouseMoveEvent(event);
	if (!(event->buttons() & Qt::LeftButton)) return;
	if ((event->pos() - dragStartPosition).manhattanLength()
	    < QApplication::startDragDistance())
		return;

	ObjectItem *it = itemAt(dragStartPosition);

	if (!it || it->type() != item::Screen)
		return;

	QDrag *drag = new QDrag(this);
	bool load = true;

	/*
		Create an empty screen if it isn't loaded yet.
	This screen will be deleted if the drag is cancelled.
	*/
	Screen *screen = it->screen();
	if (!screen) {
		try {
			screen = new Screen();
		} catch (const std::exception &e) {
			QMessageBox::warning(this, tr("Application"),
			                     tr(e.what()));
		}
	} else
		load = false;

	QMimeData *data = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	stream << reinterpret_cast<quintptr>(screen);
	data->setData(mime::Screen, encodedData);
	drag->setMimeData(data);

	Qt::DropAction dropAction = drag->start(Qt::MoveAction);

	if (dropAction == Qt::MoveAction) {
		/*
			After a successful drop, effectively load the screen,
		or update it if it was already loaded.
		*/
		if (load) {
			it->setScreen(screen);
			loadScreenInfo(it);
			emit screenSelected(screen);
			emit loadScreen(screen);
		} else
			updateScreenInfo(it);
		setExpanded(it->index(),true);
	} else if (load)
		delete screen;
}

void ScreenTree::loadScreenInfo(ObjectItem *it)
{
	Screen *screen = it->screen();
	if (!screen)
		return;

	try {
		QString name = it->name();

		FileReader fr(name.toLatin1());
		screen->load(fr);

		updateScreenInfo(it);
	} catch (const std::exception &e) {
		QMessageBox::warning(this, tr("Application"),
		                     tr(e.what()));
	}
}

void ScreenTree::updateScreenInfo(ObjectItem *scr)
{
	Screen *screen = scr->screen();
	map<string, ScreenElement*>::iterator it;

	scr->removeRows(0,scr->rowCount());

	if (!screen)
		return;

	for (it = screen->elements.begin(); it != screen->elements.end() ; it++)
		addElement(it->first, it->second,scr);
}

void ScreenTree::addElement(std::string pName, game::ScreenElement *element, ObjectItem *scr)
{
	QString name(pName.c_str());
	ObjectItem *newItem = new ObjectItem(iconObject, name, item::Object);

	newItem->setScreenElement(element);

	scr->appendRow(newItem);
}

void ScreenTree::on_close()
{
	QModelIndexList selected = selectedIndexes();

	if (selected.size() != 1)
		return;

	ObjectItem *itm = itemAt(selected[0]);

	if (!itm)
		return;

	Screen *screen = itm->screen();
	if (!screen)
		return;

	emit closeScreen(screen);

	itm->setScreen(NULL);
	updateScreenInfo(itm);

	delete screen;
}

void ScreenTree::on_load()
{
	QModelIndexList selected = selectedIndexes();


	if (selected.size() != 1)
		return;

	ObjectItem *item = itemAt(selected[0]);

	try {
		item->setScreen(new Screen());
		loadScreenInfo(item);
		emit screenSelected(item->screen());
	} catch (const std::exception &e) {
		QMessageBox::warning(this, tr("Application"),
		                     tr(e.what()));
	}
}


void ScreenTree::on_refresh()
{
	QModelIndexList selected = selectedIndexes();

	if (selected.size() == 1)
		updateScreenInfo(itemAt(selected[0]));
}

ObjectItem *ScreenTree::getWidgetForScreen(game::Screen *pScr)
{
	int i;
	QStandardItem *root = itemModel->invisibleRootItem();
	int n = root->rowCount();
	for (i=0; i<n; i++) {
		ObjectItem *it = dynamic_cast<ObjectItem*>(root->child(i));
		if (it) {
			Screen *scr = it->screen();

			if (scr == pScr) /* Note: this is REALLY a pointer comparison :) */
				return it;
		}
	}
	return NULL;
}

ObjectItem *ScreenTree::getWidgetForObject(ObjectItem *base, game::ScreenElement *scrEl)
{
	int i;
	int n = base->rowCount();
	for (i=0; i<n; i++) {
		ObjectItem *it = dynamic_cast<ObjectItem*>(base->child(i));

		if (it) {
			QString name = it->name();

			if (name == QString::fromStdString(scrEl->getName())) /* Note: this is REALLY a pointer comparison :) */
				return it;
		}
	}
	return NULL;
}

void ScreenTree::on_selectItem(game::Screen *scr, game::ScreenElement *scrEl)
{
	ObjectItem *it = getWidgetForScreen(scr);
	if (!it)
		return;
	it = getWidgetForObject(it, scrEl);
	if (!it)
		return;

	const QModelIndex &oldInd = currentIndex();
	setCurrentIndex(it->index());
	update(oldInd);
}

void ScreenTree::on_objectAdded(game::Screen *scr, game::ScreenElement *scrEl)
{
	ObjectItem *it = getWidgetForScreen(scr);
	if (!it)
		return;

	addElement(scrEl->getName(), scrEl,it);
}

void ScreenTree::on_unselectItem(game::Screen *scr, game::ScreenElement *scrEl)
{
	if (!scrEl)
		return;
	ObjectItem *it = getWidgetForScreen(scr);
	if (!it)
		return;
	it = getWidgetForObject(it, scrEl);
	if (!it)
		return;
	clearSelection();
	setCurrentIndex(itemModel->invisibleRootItem()->index());
}

void ScreenTree::currentChanged(const QModelIndex &selected, const QModelIndex &previous)
{
	/* could happen, maybe !*/
	ObjectItem *item = itemAt(selected);
	if (!item)
		return;
	if (item->type() == item::Object) {
		Screen *scr = item->parent()->screen();
		QString name = item->name();
		emit itemSelected(scr,name);
	} else if (item->type() == item::Screen) {
		/*
		 * Note: item->screen() can be NULL in the case the screen isn't loaded.
		 * In this case, the properties will hide the screen properties.
		 */
		emit screenSelected(item->screen());
	}
	Q_UNUSED(previous);
}

ObjectItem *ScreenTree::itemAt(const QPoint &pos)
{
	return itemAt(indexAt(pos));
}


ObjectItem *ScreenTree::itemAt(const QModelIndex &ind)
{
	return dynamic_cast<ObjectItem*>(itemModel->itemFromIndex(filterModel->mapToSource(ind)));
}

void ScreenTree::setCurrentIndex(const QModelIndex &ind)
{
	QTreeView::setCurrentIndex(filterModel->mapFromSource(ind));
}

void ScreenTree::setExpanded(const QModelIndex &ind, bool pExpanded)
{
	QTreeView::setExpanded(filterModel->mapFromSource(ind), pExpanded);
}

QWidget *ScreenTree::insertFilter()
{
	FilterWidget *lineEd = new FilterWidget(this);

	connect(lineEd, SIGNAL(textEdited(const QString &)),
	        filterModel, SLOT(setFilterWildcard(const QString &)));

	return lineEd;
}

void ScreenTree::setFilterWidget(FilterWidget *filter)
{
	connect(filter, SIGNAL(textEdited(const QString &)),
	        filterModel, SLOT(setFilterWildcard(const QString &)));
}

void ScreenTree::on_objectRemoved(game::Screen *scr, game::ScreenElement *scrEl)
{
	ObjectItem *base = getWidgetForScreen(scr);
	if (!base)
		return;

	ObjectItem *it = getWidgetForObject(base,scrEl);
	if (!it)
		return;

	setCurrentIndex(base->index());

	base->removeRow(it->row());

}

void ScreenTree::keyPressEvent(QKeyEvent *event)
{
	event->ignore();
	if (event->key() == Qt::Key_Delete) {
		ObjectItem *it = itemAt(currentIndex());
		if (it->screenElement()) {
			ObjectItem *base = it->parent();
			Screen *scr = NULL;
			ScreenElement *el = it->screenElement();
			if (base)
				scr = base->screen();

			if (scr) {
				on_objectRemoved(scr,el);
				emit removeObject(scr,el);
				return;
			}
		}
	}
	QTreeView::keyPressEvent(event);
}


}
