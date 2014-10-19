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
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::exception;

namespace exceptions
{



/**
 *	@author Lightning Flik <flik@baobob.org>
 *
 *	This class is a simple exception class. It logs the raised
 * exceptions in the log file according to their severity.
 *
 *	This exception class should be subclassed to allow nicer control.
 *
 */
class BaseException : public exception
{
public:
	BaseException(std::string reason, int severity = 10);

	virtual ~BaseException() throw();

	const char *what() const throw();

protected:
	/**
	 *	This is the reason why the exception was raised.
	 */
	std::string m_reason;

	/**
	 *	The severity of the exception represents how bad it will be to
	 * recover from it. According to the settings of the log, some exceptions
	 * will not be shown if their severity is low.
	 *
	 *	0 : info
	 *	2 : warning
	 *	10 : recoverable error
	 *	20 : unrecoverable error
	 */
	int m_severity;

	BaseException(const BaseException &) : std::exception() {};
	BaseException &operator =(const BaseException &) {
		return *this;
	};

};

struct MemoryException : public BaseException {
	MemoryException(std::string reason, int severity = 10);
};

struct ImageFormatException : public BaseException {
	ImageFormatException(std::string reason, std::string fileName, int severity = 10);
};


struct LoadException : public BaseException {
	LoadException(std::string reason, std::string fileName, int severity = 10);
};


struct FunctionException : public BaseException {
	FunctionException(std::string reason, int severity = 10);
};

struct GenericException : public BaseException {
	GenericException(std::string reason, int severity = 10);
};

struct FontException : public BaseException {
	FontException(std::string reason, int severity = 10);
};

struct KeyException : public BaseException {
	KeyException(std::string reason, int severity = 10);
};


}

using namespace exceptions;

#endif
