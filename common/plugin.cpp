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
#include "plugin.h"
#include "log.h"

#ifdef WIN32
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

#include "exception.h"

typedef void *(*PVoidFunc)();
typedef void *(*PVoidFunc1)(void*);

#include <string>

using std::string;

#ifdef WIN32

Plugin::Plugin(const char *file) :
		hinstDLL(NULL)
{
	string sFile(file);

	sFile += ".dll";

	hinstDLL=LoadLibraryA(sFile.c_str());

	if(!hinstDLL)
		throw LoadException("LoadLibrary",sFile.c_str());

	log() << "Loading plugin \"" << name() << "\" which is a " << type() << " plugin written by " << author() << ".\n\n Information on this plugin : \n" << description();
}

Plugin::~Plugin()
{
	if(hinstDLL)
		FreeLibrary(hinstDLL);
}


void *Plugin::call0(const char *funcName)
{
	PVoidFunc func = (PVoidFunc)GetProcAddress(hinstDLL, funcName);
	if (func)
		return func();
	throw LoadException("GetProcAddress", funcName);
}


void *Plugin::call1(const char *funcName, void *param)
{
	PVoidFunc1 func = (PVoidFunc1)GetProcAddress(hinstDLL, funcName);
	if (func)
		return func(param);
	throw LoadException("GetProcAddress", funcName);
}

#else
Plugin::Plugin(const char *file) :
	handler(NULL)
{
	string sFile(file);

	if(sFile[0] != '/')
		sFile = string("./lib") + sFile;

	sFile += ".so";

	dlerror();
	handler = dlopen(sFile.c_str(), RTLD_LAZY);
	if(handler == NULL)
		throw LoadException(dlerror(),sFile.c_str());
	log() << "Loading plugin \"" << name() << "\" which is a " << type() << " plugin written by " << author() << ".\n\n Information on this plugin : \n" << description() << "\n";
}

Plugin::~Plugin()
{
	if(handler)
		dlclose(handler);
}

void *Plugin::call0(const char *funcName)
{
/* clear the dl error status */
	dlerror();
	PVoidFunc func = (PVoidFunc) dlsym(handler, funcName);
	const char *dlsym_error = dlerror();
	if (dlsym_error || (func==NULL))
		throw FunctionException(dlsym_error);
	return func();
}

void *Plugin::call1(const char *funcName, void *param)
{
/* clear the dl error status */
	dlerror();
	PVoidFunc1 func = (PVoidFunc1) dlsym(handler, funcName);
	const char *dlsym_error = dlerror();
	if (dlsym_error || (func==NULL))
		throw FunctionException(dlsym_error);
	return func(param);
}
#endif


void *Plugin::create()
{
	return call0("create");
}

const char *Plugin::name()
{
	return (const char *)call0("name");
}

const char *Plugin::author()
{
	return (const char *)call0("author");
}

const char *Plugin::description()
{
	return (const char *)call0("description");
}

const char *Plugin::type()
{
	return (const char *)call0("type");
}
