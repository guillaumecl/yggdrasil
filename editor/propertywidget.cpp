/***************************************************************************
 *   Copyright (C) 2007 by CLEMENT Guillaume   *
 *   guillaume.clement@esial.uhp-nancy.fr   *
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
#include "propertywidget.h"
#include <QVBoxLayout>
#include <QDebug>

#include "screenproperties.h"
#include "screenitemproperties.h"

namespace editor
{

namespace property
{

PropertyWidget::PropertyWidget(QWidget *parent) :
	QStackedWidget(parent),
	screenProperties(NULL),
	screenElementProperties(NULL),
	screenItemProperties(NULL)
{
	screenProperties = new ScreenProperties(this);
	screenElementProperties = new ScreenElementProperties(this);
	screenItemProperties = new ScreenItemProperties(this);
	actionProperties = new ActionProperties(this);

	addWidget(new QWidget());
	addWidget(screenProperties);
	addWidget(screenElementProperties);
	addWidget(screenItemProperties);
	addWidget(actionProperties);

	connect(screenProperties, SIGNAL(screenUpdated(game::Screen*)), this, SIGNAL(screenUpdated(game::Screen*)));

	unselect();
}


PropertyWidget::~PropertyWidget()
{
}

void PropertyWidget::selectScreen(game::Screen *scr)
{
	if (scr) {
		screenProperties->sync(scr);
		setCurrentWidget(screenProperties);
	} else
		unselect();
}

void PropertyWidget::selectScreenItem(game::Screen *scr, const QString &elementName)
{
	game::ScreenElement *el = NULL;
	if (scr)
		el = scr->elements[elementName.toStdString()];

	if (el)
		selectScreenItem(scr,el);
	else
		unselect();
}

void PropertyWidget::selectScreenItem(game::Screen *scr, game::ScreenElement *el)
{
	if (el) {
		screenItemProperties->sync(el);
		setCurrentWidget(screenItemProperties);
	} else
		unselect();
	Q_UNUSED(scr);
}

void PropertyWidget::unselect()
{
	setCurrentIndex(0);
}


void PropertyWidget::selectScreenElement(game::ScreenElement *el)
{
	if (el) {
		screenElementProperties->sync(el);
		setCurrentWidget(screenElementProperties);
	} else
		unselect();
}

void PropertyWidget::selectAction(game::ScreenElement *el,game::Action *act)
{
	Q_UNUSED(el);
	if (act) {
		actionProperties->sync(act);
		setCurrentWidget(actionProperties);
	} else
		unselect();
}

}

}
