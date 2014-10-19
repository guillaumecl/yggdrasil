#ifndef QTDRAWMANAGERBASE_H
#define QTDRAWMANAGERBASE_H

#include "common/drawmanager.h"
#include "qtcore/qtcore.h"

#include <QWidget>

namespace draw
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class QtDrawManagerBase : public DrawManager
{
public:
	QtDrawManagerBase() {}

	~QtDrawManagerBase() {}

	virtual QWidget *getWidget(QWidget *parent = NULL, const char *name = NULL) = 0;

	virtual void setup() = 0;
	virtual void update() = 0;
};

}

#endif // QTDRAWMANAGERBASE_H
