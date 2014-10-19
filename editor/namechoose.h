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

#ifndef NAMECHOOSE_H
#define NAMECHOOSE_H

#include <QDialog>
#include "game/basictypes.h"
#include "ui_nameChoose.h"

namespace editor
{

class NameChoose : public QDialog, private Ui::nameChoose
{
	Q_OBJECT

public:
	NameChoose(QWidget* parent, game::Screen *pScr,Qt::WFlags fl = 0);
	~NameChoose();
	QString text();
	void setText(QString newText);
	void setName(QString pName);
private:
	NameChoose() {}
	game::Screen *scr;
public slots:
	void on_buttonOk_clicked();
};

}

#endif
