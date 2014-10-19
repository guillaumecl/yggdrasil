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
#include "objectdockwidget.h"
#include <QVBoxLayout>

namespace editor
{

namespace custom
{

ObjectDockWidget::ObjectDockWidget(QDockWidget *parent) :
	QWidget(parent),
	mObjectTree(NULL)
{
	mObjectTree = new ObjectTree(this);
	QVBoxLayout *la = new QVBoxLayout(this);

	la->addWidget(mObjectTree->insertFilter());
	la->addWidget(mObjectTree);
	setLayout(la);

	parent->setWidget(this);
}


ObjectDockWidget::~ObjectDockWidget()
{
}

ObjectTree *ObjectDockWidget::objectTree() const
{
	return mObjectTree;
}

}

}


