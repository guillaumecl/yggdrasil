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
#include "screen.h"

#include <sstream>

#include "common/exception.h"
#include "common/core.h"
#include "sprite.h"
#include "collisionscreen.h"

using draw::DrawManager;
using namespace std;

#include "screenelement.h"

namespace game
{

static bool compare(ScreenElement *el1, ScreenElement *el2)
{
	return !(*el1 < *el2);
}

Screen::Screen(FileReader &confFile)
{
	if (!core::Core::globalCore)
		throw exceptions::GenericException("Plugins must be run in order to create screens.");
	load(confFile);
}


Screen::~Screen()
{
	map<string, ScreenElement *>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++)
		delete it->second;
}


void Screen::nextFrame()
{
	map<string, ScreenElement *>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++)
		it->second->nextFrame();
}

void Screen::drawBackground()
{
	list<ScreenElement *>::iterator it;

	for (it = sortedElements.begin(); it != sortedElements.end(); it++)
		(*it)->draw(draw::planes::background);
}


void Screen::drawForeground()
{
	list<ScreenElement *>::iterator it;

	for (it = sortedElements.begin(); it != sortedElements.end(); it++)
		(*it)->draw(draw::planes::foreground);
}


void Screen::drawObject()
{
	list<ScreenElement *>::iterator it;
	for (it = sortedElements.begin(); it != sortedElements.end(); it++)
		(*it)->draw(draw::planes::object);
}

void Screen::updatePositions()
{
	map<string, ScreenElement *>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++)
		it->second->updatePosition();

	sortedElements.sort(compare);
}


Screen::Screen() :
	mWidth(2000),
	mHeight(2000)
{
	if (!core::Core::globalCore)
		throw exceptions::GenericException("Plugins must be run in order to create screens.");
}

/**
 * Adds an object to the screen.
 */
void Screen::addObject(std::string name, ScreenElement *element)
{
	if (elements.find(name) != elements.end())
		throw exceptions::GenericException("This object already exists.");

	elements[name] = element;
	sortedElements.push_front(element);
	sortedElements.sort(compare);

	if (element->walkable)
		return;

	CollisionScreenPList::iterator it;
	for (it = collisionScreens.begin(); it != collisionScreens.end(); it++)
		CollisionScreen::addIfNeeded(element,*it);
}

int Screen::width()
{
	return mWidth;
}

int Screen::height()
{
	return mHeight;
}

void Screen::setWidth(int pWidth)
{
	mWidth = pWidth;
}

void Screen::setHeight(int pHeight)
{
	mHeight = pHeight;
}

ScreenElement *Screen::get(string elementName)
{
	map<string, ScreenElement *>::iterator it;

	it = elements.find(elementName);
	if (it == elements.end())
		throw exceptions::LoadException("Element not found : ", elementName);

	return it->second;
}

void Screen::remove(string elementName)
{
	map<string, ScreenElement *>::iterator it;

	it = elements.find(elementName);
	if (it == elements.end())
		throw exceptions::LoadException("Element not found : ", elementName);

	ScreenElement *deletedItem = it->second;
	elements.erase(it);

	afterRemove(deletedItem);
}

void Screen::remove(ScreenElement *el)
{
	map<string, ScreenElement *>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++) {
		if (it->second == el) {
			elements.erase(it);
			break;
		}
	}
	afterRemove(el);
}

void Screen::afterRemove(ScreenElement *el)
{
	ScreenElementPList::iterator listIt;

	for (listIt = sortedElements.begin(); listIt != sortedElements.end(); listIt++) {
		if ((*listIt) == el) {
			sortedElements.erase(listIt);
			break;
		}
	}

	CollisionScreenPList::iterator it;
	for (it = collisionScreens.begin(); it != collisionScreens.end(); it++) {
		if ((*it)->has(el))
			(*it)->screenElements.remove(el);
	}

	delete el;
}

ScreenElement *Screen::add(std::string elementName, std::string fileName)
{
	ScreenElement *el;
	if (elements.find(elementName) != elements.end())
		throw exceptions::LoadException("Duplicate element in the screen : ", elementName);

	FileReader elFile(fileName.c_str());

	el = new ScreenElement(elFile,elementName);
	el->setPosition(0,0);

	addObject(elementName,el);

	return el;
}

void Screen::load(FileReader &confFile)
{
	ScreenElement *el = NULL;
	ostringstream elementVar;
	string elementName;

	mWidth = confFile.getInt("Screen","width",2000);
	mHeight = confFile.getInt("Screen","height",2000);

	CollisionScreen *collisionScreen = new CollisionScreen(0,0,mWidth,mHeight);
	collisionScreens.push_front(collisionScreen);

	int i = 1;

	elementVar << "element " << i;
	while (confFile.hasVariable("Screen",elementVar.str().c_str())) {
		elementName = confFile.getString("Screen",elementVar.str().c_str(),NULL);
		const char *elName = elementName.c_str();
		string fileName = confFile.getString(elName,"file","");

		int x,y;

		x = confFile.getInt(elName,"x",0);
		y = confFile.getInt(elName,"y",0);

		try {
			el = add(elementName,fileName);
			el->setPosition(x,y);
			el->loadEditorProperties(confFile,elName);
		} catch (const exception &e) {
			/**
			 * @fixme log the error
			 */
		}

		i++;
		elementVar.str("");
		elementVar << "element " << i;
	}
	sortedElements.sort(compare);
}

bool Screen::nameExists(std::string pName)
{
	std::map<std::string, ScreenElement *>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++) {
		if (it->first == pName)
			return true;
	}
	return false;
}

}
