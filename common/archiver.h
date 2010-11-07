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
#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>
#include <map>

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class FileReader{
public:
    FileReader(const char *fileName);

    ~FileReader();
	
	std::string getString( const char *section, const char *varName, const char *defValue);
	int getInt(const char *section, const char *varName, int defValue);
	bool hasSection(const char *section) const;
	bool hasVariable(const char *section, const char *varName);
	
	const std::string fileName() const;
	const std::string directory() const;
	
private:
	FileReader(FileReader&);
	FileReader& operator=(FileReader&);
	
	bool goToSection(const char *section);
	std::ifstream file;
	std::map<std::string, int> sections;
	std::string m_fileName;
	
	static std::string trim(std::string scr);
};

#endif
