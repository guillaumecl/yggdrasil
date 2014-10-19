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
#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

/**
 * @brief Implements calls from external files such as so files or DLLs.
 * Plugins are used to load
 * @author Lightning Flik <flik@baobob.org>
 */
class Plugin
{
public:
	/**
	 * Loads the specified file.
	 */
	Plugin(const char *file);

	/**
	 * Destructor for Plugin
	 */
	~Plugin();

	/**
	 *	Returns an object created by the plugin. It is derivated from either :
	 *		Core for core plugins
	 *		DrawManager for drawing plugins
	 *		SoundManager for sound plugins
	 *	and so on.
	 */
	void *create();

	/**
	 *	Type of the plugin.
	 *
	 *	It can be one of : "sound", "core", "draw", "input"
	 */
	const char *type();

	/**
	 *	Description of the plugin (how to use it, incompatibilities, ...)
	 */
	const char *description();


	/**
	 *	Author(s) of the plugin along with their email addresses if they wish.
	 */
	const char *author();

	/**
	 *	Name of the plugin
	 */
	const char *name();

	/**
	 * Call a function with one parameter.
	 */
	void *call1(const char *pFileName, void *param);

private:
#ifdef WIN32
	HINSTANCE hinstDLL;
#else
	/**
	 *	Instance of the DLL. Used for freeing the DLL after the code is not used anymore.
	 */
	void *handler;
#endif

	/**
	 *	Calls the specified function with 0 parameter. Returns a pointer.
	 */
	void *call0(const char *funcName);
};


#endif
