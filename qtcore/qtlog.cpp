#include "qtlog.h"
#include <QDebug>

using namespace std;

void callback(ios_base::event ev, ios_base& iosobj, int index)
{
	switch (ev)
	{
	case ios_base::copyfmt_event:
		cout << "copyfmt_event\n"; break;
	case ios_base::imbue_event:
		cout << "imbue_event\n"; break;
	case ios_base::erase_event:
		cout << "erase_event\n"; break;
	}
}


QtLog::QtLog() :
	Log()
{
	rdbuf(&buffer);
}
