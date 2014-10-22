/***************************************************************************
 *   Copyright (C) 2007 by CLEMENT Guillaume                               *
 *   guillaume.clement@esial.uhp-nancy.fr                                  *
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


/**
 * @mainpage Yggdrasil
 *
 * Yggdrasil is a 2D Engine made to create games similar to Secret of Mana.
 *
 * @section Introduction
 *
 * Introduction of the doc
 *
 * @section nianiania test
 *
 * test
 *
 * @ref Truc
 *
 */

/**
 *
 * @page Truc
 *
 * Un truc
 *
 * @ref main Back to Index
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "common/log.h"
#include "common/core.h"
#include "common/exception.h"
#include "game/screen.h"

#include "common/plugin.h"

#include "common/archiver.h"

using draw::DrawManager;
using core::Core;
using sound::SoundManager;

using namespace game;

#include <iostream>

Screen *mainScreen;

void drawFunc()
{
	mainScreen->drawBackground();
	mainScreen->drawObject();
	mainScreen->drawForeground();
}

void inputFunc()
{
	mainScreen->nextFrame();
	mainScreen->updatePositions();
}



int main(int argc, char *argv[])
{
	core::Core *core = NULL;
	DrawManager *drawManager = NULL;
	SoundManager *soundManager = NULL;

	Plugin *coreLoader = NULL;
	Plugin *drawLoader = NULL;

	try {
		//log << "Loading the plugin loaders...\n";

		coreLoader = new Plugin("qtcore");
		drawLoader = new Plugin("qtdraw");

		core = static_cast<Core*>(coreLoader->create());
		core::Core::globalCore = core;

		drawManager = static_cast<DrawManager*>(drawLoader->create());

		/* Associate the core with the drawing and sound engines */
		core->setup(*drawManager, *soundManager);

		FileReader file("defaultScreen.scr");

		mainScreen = new Screen(file);

		core->setFrameRate(60);
		core->mainLoop(drawFunc,inputFunc);

		delete mainScreen;

		//log << "Main loop over. Freeing resources.\n";

		delete drawManager;
		drawManager = NULL;			/* in case any of the destructors throw exceptions */

		delete soundManager;
		soundManager = NULL;

		delete core;
		core = NULL;
	} catch (std::exception &e) {
		//log << "Exception in main : " << e.what() << "\n";

		delete drawManager;
		delete soundManager;
		delete core;
	}
	/*
		Plugins need to be freed after their objects. If not, the destructor cannot be called.
		This also the case of the exceptions raised by the plugins... which is why the plugins
		are loaded outside the try.
	*/

	delete drawLoader;
	delete coreLoader;

	return 0;
}
