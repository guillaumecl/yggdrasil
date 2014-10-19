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
#include "archiver.h"

#include "exception.h"
#include <sstream>

using std::string;
using std::map;

FileReader::FileReader(const char *fileName) :
	file(fileName), m_fileName(fileName)
{
	if (!file)
		throw LoadException("Cannot open the file", fileName);

	string line;

	/*
		Build the section list.
	*/
	while (getline(file,line)) {
		unsigned int begin = line.find_first_not_of(" 	");
		unsigned int end = line.find_last_of(']');
		if (begin != string::npos && line[begin] == '[' && end != string::npos) {
			/*
				This is a section.
			*/
			string sectionName = line.substr(begin+1,end-1);

			sections.insert(make_pair(sectionName , file.tellg()));
		}
	}
}


FileReader::~FileReader()
{
}

const string FileReader::fileName() const
{
	return m_fileName;
}

const string FileReader::directory() const
{
	int i = m_fileName.find_last_of('/', m_fileName.size() - 1);
	if (i < 0)
		return ".";
	return m_fileName.substr(0, i);
}

string FileReader::getString(const char *section, const char *varName, const char *defValue)
{
	string line;

	if (!goToSection(section))
		return defValue;

	while (getline(file,line)) {
		unsigned int begin = line.find_first_not_of(" 	");
		unsigned int end = line.find_first_of('=',begin);

		if (begin != string::npos && line[begin] == '[') {
			/*
				This is a section. This means that the variable was not found.
			*/
			break;
		}
		if (begin != string::npos && line[begin] != ';' && end != string::npos) {
			/*
				This is a variable name.
			*/
			string variableName = line.substr(begin,end);
			unsigned int realEnd = variableName.find_last_not_of(" 	");
			if (realEnd != string::npos)
				variableName = variableName.substr(0,realEnd+1);

			if (variableName == varName) {
				begin = line.find_first_not_of(" 	",end+1);
				end = line.find_last_not_of(" 	");

				if (begin != string::npos && end != string::npos)
					return line.substr(begin,end);
				else
					return "";
			}
		}
	}
	return defValue;
}

bool FileReader::goToSection(const char *section)
{
	map<string,int>::iterator ret;

	ret = sections.find(section);
	if (ret == sections.end())
		return false;
	/*
		Clear the states (could be EOF / read error, ...)
	*/
	file.clear();

	file.seekg(ret->second);

	return true;
}

int FileReader::getInt(const char *section, const char *varName, int defValue)
{
	int iResult;
	string sResult = getString(section,varName,"");
	std::istringstream resultConverter(sResult);

	if (resultConverter >> iResult)
		return iResult;
	return defValue;

}

bool FileReader::hasSection(const char *section) const
{
	return sections.find(section) != sections.end();
}

bool FileReader::hasVariable(const char *section, const char *varName)
{
	try {
		getString(section,varName,NULL);
		return true;
	} catch (exception &e) {
		return false;
	}
}

string FileReader::trim(string s)
{
	string drop = " 	";
	std::string r=s.erase(s.find_last_not_of(drop)+1);
	return r.erase(0,r.find_first_not_of(drop));
}
