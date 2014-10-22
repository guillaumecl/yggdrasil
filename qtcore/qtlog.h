#pragma once

#include "log.h"
#include <iostream>
#include <sstream>

class QtLog : public Log
{
public:
	QtLog();

	std::stringbuf buffer;
};
