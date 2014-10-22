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
#pragma once

#include <QStackedWidget>
#include "game/basictypes.h"

#include "editor/ui_types.h"

namespace editor
{

namespace property
{

/**
	@author flik <flik@baobob.org>
*/
class PropertyWidget : public QStackedWidget
{
	Q_OBJECT

public:
	PropertyWidget(QWidget *parent=0);

	~PropertyWidget();

public slots:
	void selectScreen(game::Screen *scr);
	void selectScreenItem(game::Screen *scr, const QString &name);
	void selectScreenItem(game::Screen *scr, game::ScreenElement*el);
	void selectScreenElement(game::ScreenElement *el);
	void selectAction(game::ScreenElement *el,game::Action *act);
	void unselect();

private:
	ScreenProperties *screenProperties;
	ScreenElementProperties *screenElementProperties;
	ScreenItemProperties *screenItemProperties;
	ActionProperties *actionProperties;
signals:
	void screenUpdated(game::Screen *scr);
};

}

}
