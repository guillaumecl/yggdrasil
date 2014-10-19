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
#include "action.h"
#include <string>

#include "common/core.h"
#include "common/exception.h"

#include <sstream>

using namespace std;

namespace game
{

Action::Action(FileReader &confFile, const char *actionName, int pWidth, int pHeight) :
	name(actionName),
	spr(confFile, actionName,pWidth,pHeight),
	baseOffsetY(0),
	defaultFrame(ActionFrame(),confFile,actionName),
	frameTimer(0),
	curFrame(0)
{
	if (!core::Core::globalCore)
		throw GenericException("Plugins must be run in order to create actions.");
	int numFrames = spr.getNumFrames();
	int frameDelay;
	frames.reserve(numFrames);

	/*
		Load the action frames.
	*/

	frameDelay = confFile.getInt(actionName,"Frame delay",1);
	baseOffsetY = confFile.getInt(actionName,"baseOffsetY",0);

	ostringstream actFrame;
	int i;
	string baseActFrame = string(actionName) + " frame ";
	string baseActFrameName;
	ActionFrame *actionFrame;

	if (defaultFrame.frameDelay < 0)
		defaultFrame.frameDelay = frameDelay;

	for (i=0 ; i<numFrames ; i++) {
		actFrame.clear();
		actFrame.str("");
		actFrame << baseActFrame << (i+1);
		baseActFrameName = actFrame.str();

		if (confFile.hasSection(baseActFrameName.c_str()))
			actionFrame = new ActionFrame(defaultFrame,confFile, baseActFrameName.c_str());
		else
			actionFrame = &defaultFrame;
		frames.push_back(actionFrame);
	}
}

/*
int Action::width()
{
	return spr.width();
}

int Action::height()
{
	return spr.height();
}*/

Action::~Action()
{
	vector<ActionFrame *>::iterator iter;

	for (iter = frames.begin() ; iter != frames.end() ; iter++) {
		if (*iter != &defaultFrame)
			delete *iter;
	}
	frames.clear();
}

bool Action::nextFrame()
{
	frameTimer++;
	if (frameTimer >= getCurrentFrame().frameDelay) {
		frameTimer = 0;
		curFrame++;
		if (curFrame >= frames.size())
			reset();
		spr.nextFrame();
		return true;
	}
	return false;
}

bool Action::isOver()
{
	return curFrame ==0;
}

void Action::reset()
{
	curFrame = 0;
}

void Action::draw(int x, int y, directions::DirectionType direction, draw::planes::PlaneType plane)
{
	spr.draw(x,y+baseOffsetY,direction,plane);
}

const ActionFrame &Action::getCurrentFrame()
{
	ActionFrame *frm = frames[curFrame];
	return (*frm);
}

void Action::setSize(int pWidth, int pHeight)
{
	spr.setSize(pWidth, pHeight);
}

}
