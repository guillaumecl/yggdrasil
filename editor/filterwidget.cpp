/***************************************************************************
 *   Copyright (C) 2007 by flik   *
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
#include "filterwidget.h"
#include <QApplication>

namespace editor
{

namespace custom
{
/*
	TRANSLATOR editor::FilterWidget
*/
FilterWidget::FilterWidget(QWidget *parent) :
	QLineEdit(parent),
	noText(true)
{
	setFilterTextMode();
}


FilterWidget::~FilterWidget()
{
}

void FilterWidget::setFilterTextMode()
{
	noText = true;
	setText(tr("Type here to filter items"));

	QFont fnt = font();
	fnt.setItalic(true);
	setFont(fnt);
}

void FilterWidget::focusInEvent(QFocusEvent *event)
{
	QLineEdit::focusInEvent(event);
	if (noText) {
		noText = false;
		setText("");
		QFont fnt = font();
		fnt.setItalic(false);
		setFont(fnt);
	}
}

void FilterWidget::focusOutEvent(QFocusEvent *event)
{
	QLineEdit::focusOutEvent(event);
	if (text().isEmpty())
		setFilterTextMode();
}


}

}
