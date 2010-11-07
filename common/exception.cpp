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
#include "exception.h"
#include "log.h"

using std::string;

namespace exceptions
{

/**
 * Creates a generic exception.
 * @param reason Description of the problem that occurred.
 * @param severity Severity of the exception. See the description for
 * m_severity for different possible values.
 */
BaseException::BaseException(string reason, int severity) :
	m_reason(reason),
	m_severity(severity)
{
	if(severity == 0)
		return;
	else if(severity <= 2)
		log() << m_reason;
	else if(severity < 10)
		warning() << m_reason;
	else if(severity < 20)
		error() << m_reason;
	else
		fatal() << m_reason;
}

BaseException::~BaseException()
	throw()
{
}



/**
	@returns the error message associated to this exception.
*/
const char * BaseException::what() const throw()
{
	return m_reason.c_str();
}



MemoryException::MemoryException(string reason, int severity) :
	BaseException(reason,severity)
{

}


ImageFormatException::ImageFormatException(string reason, string fileName, int severity) :
	BaseException(reason + " " + fileName,severity)
{

}

LoadException::LoadException(string reason, string fileName, int severity) :
	BaseException(reason + " " + fileName,severity)
{

}

FunctionException::FunctionException(string reason, int severity) :
	BaseException(reason,severity)
{

}

GenericException::GenericException(string reason, int severity) :
	BaseException(reason,severity)
{

}

FontException::FontException(string reason, int severity) :
	BaseException(reason,severity)
{

}

KeyException::KeyException(string reason, int severity) :
	BaseException(reason,severity)
{

}


}
