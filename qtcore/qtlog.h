#ifndef QTLOG_H
#define QTLOG_H

#include "log.h"
#include <iostream>
#include <sstream>

class QtLog : public Log
{
public:
	QtLog();

	std::stringbuf buffer;
};

#endif // QTLOG_H
