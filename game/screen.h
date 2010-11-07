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
#ifndef SCREENSCREEN_H
#define SCREENSCREEN_H

#include <list>
#include <map>
#include <string>

#include "basictypes.h"


/**
 * @namespace game
 * 
 * @brief This namespace contains all of the main tools used for the game.
 * 
 * Screens, objects, collisions, all interactions which is directly related to
 * the game rules are inside this namespace.
 */
namespace game
{

/**
	@author Lightning Flik <flik@baobob.org>
*/
class Screen
{
public:
	/**
	 * Default constructor for Screen
	 */
	Screen(FileReader &confFile);
	
	/**
	 * Create an empty screen. Used by the editor only.
	 */
	Screen();
	
	/**
	 * Destructor for Screen
	 */
	~Screen();
	
	void drawBackground();
	void drawObject();
    void drawForeground();
	
	void nextFrame();
	
	void updatePositions();
	
	/**
	 * Adds an object to the screen.
	 */
	void addObject(std::string name, ScreenElement *element);
	
	void load(FileReader &fr);
	
	ScreenElement *get(std::string name);
	void remove(std::string name);
	void remove(ScreenElement *el);
	ScreenElement *add(std::string name, std::string fileName);
	
	int width();
	int height();
	
	void setWidth(int pWidth);
	void setHeight(int pHeight);
	
	std::map<std::string, ScreenElement *> elements;
	
	bool nameExists(std::string pName);
private:
	int mWidth;
	int mHeight;
	
	ScreenElementPList sortedElements;
	CollisionScreenPList collisionScreens;
	
	void afterRemove(ScreenElement *el);
};

}

#endif
