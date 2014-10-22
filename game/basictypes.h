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

#include <list>

namespace game
{

class Screen;

class ScreenElement;
typedef std::list<ScreenElement*> ScreenElementPList;

class Rect;

class Action;
typedef std::list<Action*> ActionPList;

class Collision;
typedef std::list<Collision> CollisionList;

class CollisionScreen;
typedef std::list<CollisionScreen*> CollisionScreenPList;


/**
 * @namespace game::directions
 *
 * @brief Contains the different directions a ScreenElement can have.
 *
 */
namespace directions
{
enum DirectionType {
        up,
        down,
        left,
        right,

        upLeft,
        upRight,
        downLeft,
        downRight
};
};


};

namespace draw
{
/**
 * @namespace draw::planes
 * The three planes used by a sprite.
 */
namespace planes
{
enum PlaneType {
        background,
        foreground,
        object
};
};
};

class FileReader;
