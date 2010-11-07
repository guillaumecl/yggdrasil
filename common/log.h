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
#ifndef LOGLOG_H
#define LOGLOG_H

#include <sstream>
#include <string>

#include <iostream>

#include "core.h"

/**
 * @brief Logging facilities
 * @author Lightning Flik <flik@baobob.org>
 * This class is used for logging things to files or stderr.
*/
class Logger
{
public:
	std::ostringstream *stream;
	int numRef;
	int severity;

	inline Logger(int pSeverity) : stream(new std::ostringstream()), numRef(1), severity(pSeverity) {}
	inline Logger(const Logger &o):stream(o.stream) { ++numRef; }
	inline Logger &operator=(const Logger &other);
	inline ~Logger() {
		if (!--numRef) {

			if (severity == 2)
				std::cerr << "WARNING: ";
			else if (severity == 3)
				std::cerr << "ERROR: ";
			else if (severity == 4)
				std::cerr << "FATAL ERROR: ";

			std::cerr << stream->str() << std::endl;
			if (core::Core::getCore())
				core::Core::getCore()->showLog(severity, stream->str());

			delete stream;
		}
	}

	inline Logger &operator<<(bool t) { *stream << (t ? "true" : "false"); return *this; }
	inline Logger &operator<<(char t) { *stream << t; return *this; }
	inline Logger &operator<<(signed short t) { *stream << t; return *this; }
	inline Logger &operator<<(unsigned short t) { *stream << t; return *this; }
	inline Logger &operator<<(signed int t) { *stream << t; return *this; }
	inline Logger &operator<<(unsigned int t) { *stream << t; return *this; }
	inline Logger &operator<<(signed long t) { *stream << t; return *this; }
	inline Logger &operator<<(unsigned long t) { *stream << t; return *this; }
	inline Logger &operator<<(float t) { *stream << t; return *this; }
	inline Logger &operator<<(double t) { *stream << t; return *this; }
	inline Logger &operator<<(const char* t) { *stream << t; return *this; }
	inline Logger &operator<<(const void * t) { *stream << t; return *this; }
	inline Logger &operator<<(std::string s) { *stream << s.c_str(); return *this; }

};

inline Logger fatal() { return Logger(4); }
inline Logger error() { return Logger(3); }
inline Logger warning() { return Logger(2); }
inline Logger log() { return Logger(1); }

/*inline Logger &Logger::operator=(const Logger &other)
{
	return *this;
}*/


#endif
