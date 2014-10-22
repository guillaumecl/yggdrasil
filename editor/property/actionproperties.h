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
#ifndef EDITOR_PROPERTYACTIONPROPERTIES_H
#define EDITOR_PROPERTYACTIONPROPERTIES_H

#include "propertytree.h"
#include "game/basictypes.h"

namespace editor
{

namespace property
{

/**
	@author flik <flik@baobob.org>
*/
class ActionProperties : public PropertyTree
{
	Q_OBJECT
public:
	ActionProperties(QWidget *parent=0);

	~ActionProperties();

	virtual void sync(void *item);
	virtual void itemUpdated(PropertyItem *item);
	virtual void setReadOnly(bool pReadOnly);

	PropertyItem *displayName;
	PropertyItem *defaultFrame;
	PropertyItem *name;
	PropertyItem *spr;
	PropertyItem *baseOffsetY;

	/**
	 * Sprite properties
	 */
	PropertyItem *backgroundPlane;
	PropertyItem *foregroundPlane;
	PropertyItem *objectPlane;
	PropertyItem *numFrames;

	/**
	 * Background plane properties
	 */
	PropertyItem *background_fileName;
	PropertyItem *background_height;
	PropertyItem *background_width;
	PropertyItem *background_offsetX;
	PropertyItem *background_offsetY;

	/**
	 * Object plane properties
	 */
	PropertyItem *object_fileName;
	PropertyItem *object_height;
	PropertyItem *object_width;
	PropertyItem *object_offsetX;
	PropertyItem *object_offsetY;

	/**
	 * Foreground plane properties
	 */
	PropertyItem *foreground_fileName;
	PropertyItem *foreground_height;
	PropertyItem *foreground_width;
	PropertyItem *foreground_offsetX;
	PropertyItem *foreground_offsetY;

	game::Action *current;
};

}

}

#endif
