/***************************************************************************
 *   Copyright (C) 2007 by CLEMENT Guillaume   *
 *   guillaume.clement@esial.uhp-nancy.fr   *
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
#include "propertyitemdelegate.h"

#include <QDebug>

#include <QMetaMethod>
#include "propertyitem.h"
#include "propertyitemmodel.h"

namespace editor
{

namespace property
{

PropertyItemDelegate::PropertyItemDelegate(QObject *parent, PropertyItemModel *pModel) :
	QItemDelegate(parent),
	model(pModel)
{
}


PropertyItemDelegate::~PropertyItemDelegate()
{
}

QWidget *PropertyItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	PropertyItem *item = model->itemFromIndex(index);

	if (item && item->custom())
		return item->createEditor(parent, option);

	QWidget *editor = QItemDelegate::createEditor(parent, option, index);

	/* Now we attempt to link the editing signals to our update function. This way,
	 * we can see the result before validating.
	 */

	/* QSpinBox */
	try_connect(editor,"valueChanged(int)",SIGNAL(valueChanged(int)));
	try_connect(editor,"valueChanged(QString)",SIGNAL(valueChanged(QString)));

	/* QDoubleSpinBox */
	try_connect(editor,"valueChanged(double)",SIGNAL(valueChanged(double)));

	/* QLineEdit */
	try_connect(editor,"textChanged(QString)",SIGNAL(textChanged(QString)));

	/* QComboBox */
	try_connect(editor,"currentIndexChanged(int)",SIGNAL(currentIndexChanged(int)));

	return editor;
}

void PropertyItemDelegate::valueChanged()
{
	emit commitData((QWidget*)sender());
}

void PropertyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	PropertyItem *item = model->itemFromIndex(index);

	if (item && item->custom())
		item->setter(editor);
	else
		QItemDelegate::setEditorData(editor, index);
}

void PropertyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
	PropertyItem *item = model->itemFromIndex(index);

	if (item && item->custom()) {
		item->getter(editor);
		//pModel->setData(index,item->get(),Qt::DisplayRole);
	} else
		QItemDelegate::setModelData(editor, pModel, index);
}

void PropertyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	PropertyItem *item = model->itemFromIndex(index);
	if (item->custom()) {
		if (item->paint(painter,option))
			return;
	}
	QItemDelegate::paint(painter,option,index);
}


QSize PropertyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	PropertyItem *item = model->itemFromIndex(index);
	if (item->custom()) {
		QSize sizeHint = item->sizeHint(option);
		if (sizeHint != QSize(0,0))
			return sizeHint;
	}
	return QItemDelegate::sizeHint(option,index);
}

void PropertyItemDelegate::try_connect(QWidget *editor,const char *sigName, const char *signal) const
{
	QByteArray sig = QMetaObject::normalizedSignature(sigName);
	sigName = sig.data();
	const QMetaObject *meta = editor->metaObject();
	if (meta->indexOfMethod(sigName) >= 0)
		connect(editor,signal,this,SLOT(valueChanged()));
}

}

}
