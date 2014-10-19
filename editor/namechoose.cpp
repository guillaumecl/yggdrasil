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


#include "namechoose.h"
#include <QMessageBox>
#include "game/screen.h"
#include "common/archiver.h"

namespace editor
{

NameChoose::NameChoose(QWidget* parent, game::Screen *pScr, Qt::WFlags fl) :
	QDialog(parent, fl),
	scr(pScr)
{
	setupUi(this);
}

NameChoose::~NameChoose()
{
}

QString NameChoose::text()
{
	return txtName->text();
}

void NameChoose::setText(QString pText)
{
	txtName->setText(pText);
	txtName->selectAll();
}

void NameChoose::on_buttonOk_clicked()
{
	if (text().isEmpty()) {
		QMessageBox::warning(this, tr("Yggdrasil Editor"),
		                     tr("All items must have a name."));
		return;
	}
	if (scr->nameExists(text().toStdString())) {
		QMessageBox::warning(this, tr("Yggdrasil Editor"),
		                     tr("An element with this name already exists : %1.").arg(text()));
		return;
	}
	accept();
}

void NameChoose::setName(QString pName)
{
	FileReader fr(pName.toLatin1().data());

	int try_number=1;
	QString baseName = QString::fromStdString(fr.getString("ScreenEditor","name",pName.toLatin1().data()));
	QString objectName = baseName;
	while (scr->nameExists(objectName.toStdString()))
		objectName = QString("%1 %2").arg(baseName).arg(++try_number);
	setText(objectName);
}

}
