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

#include "screenelementproperties.h"

#include "game/basictypes.h"

namespace editor
{

namespace property
{

/**
 *	@author flik <flik@baobob.org>
 *
 * This class contains the properties for a ScreenElement that is located
 * inside a Screen.
 *
 * It defines all attributes that are defined only in the screen, such as the coordinates.
 */
class ScreenItemProperties : public ScreenElementProperties
{
	Q_OBJECT
public:
	ScreenItemProperties(QWidget *parent=0);

	~ScreenItemProperties();

	virtual void sync(void *item);
	virtual void itemUpdated(PropertyItem *item);
	virtual void setReadOnly(bool pReadOnly);

	PropertyItem *x;
	PropertyItem *y;
	PropertyItem *name;
	PropertyItem *locked;

	game::ScreenElement *current;
};

}

}
