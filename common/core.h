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
#pragma once

#include "drawmanager.h"
#include "soundmanager.h"

#include <string>

/**
 * @namespace core
 *
 * @brief This namespace contains all of the tools that are needed to communicate with the OS.
 *
 * All classes are implemented inside plugins, and possibly architecture-dependent.
 */
namespace core
{


/**
 * @brief Interface for the Core class
 *
 *	@author Lightning Flik <flik@baobob.org>
 *
 *	This class is the link between yggdrasil and the OS. It creates the
 * window, contains the main loop, forwards the different events to the
 * different input systems if they requested them, and it calls the graphical
 * functions regularly, managing the frame rate.
 *
 *	Once the core is destroyed, the game quits.
 */
class Core
{
public:
	/**
	 * 	Destructor for Core.
	 */
	virtual ~Core() {}

	/**
	 *  Main loop of the core. Will update the screen, respond to user interaction...
	 */
	virtual void mainLoop(void (*drawFunc)(), void (*inputFunc)()) = 0;

	/**
	 *  Make one iteration of the main loop. Can be useful in editors to control the flow of the core.
	 */
	virtual void mainLoopIteration() = 0;

	/**
	  * Sends a log line to the core. The core is free not to reimplement this method if
	  * no special logging ability is needed.
	  * @param severity the severity (1 = info, 2 = warning, 3 = error, 4 = fatal)
	  */
	virtual void showLog(int severity, std::string log) {
		(void)severity;
		(void)log;
	};

	/**
	 * 	Associate the core with the drawing and sound engines.
	 *
	 * 	The engines may request some settings. For instance the
	 * input manager can typically ask for the joystick and keyboard
	 * events.
	 *
	 * @param draw The drawing Manager that will be used. The draw manager may request things to the Core and vice versa.
	 * @param sound The sound Manager that will be used. The sound manager may request things to the Core and vice versa.
	 */
	virtual void setup(draw::DrawManager &draw, sound::SoundManager &sound) = 0;

	/**
	 *  Sets the frame rate that the engine should not overdo. The engine
	 * can be slower than this framerate but not faster.
	 *
	 * @param frameRate The frame rate, in frames per second.
	 */
	virtual void setFrameRate(double frameRate) = 0;
	/**
	 *  Returns the real frame rate as calculated during the last 2 seconds.
	 */
	virtual double frameRate() = 0;

	static Core *getCore();
	static draw::DrawManager *getDrawManager();
	static sound::SoundManager *getSoundManager();

protected:
	/**
	 * 	Drawing manager for this core. Set by the setup function.
	 */
	draw::DrawManager *m_draw;

	/**
	 * 	Sound manager for this core. Set by the setup function.
	 */
	sound::SoundManager *m_sound;

	Core();
public:
	static Core *globalCore;

};

}
