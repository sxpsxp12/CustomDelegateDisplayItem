﻿#include "customtreeviewdelegate.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QStandardItemModel>
customtreeViewDelegate::customtreeViewDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

void customtreeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QStandardItemModel *model = qobject_cast<const QStandardItemModel *>(index.model());

    if(!index.parent().isValid())
    {
        painter->setPen(QColor(Qt::black));
        painter->setFont(QFont("Times", 9, QFont::Bold));
        painter->drawText(option.rect.x()+5,option.rect.y(),option.rect.width(),option.rect.height(), Qt::AlignLeft|Qt::AlignVCenter, index.data().toString());

        auto data = model->data(index, Qt::CheckStateRole);
        QStyleOptionButton checkBoxStyle;
        if(data == Qt::Unchecked)
        {
            checkBoxStyle.state |= QStyle::State_Off;
        }
        else if(data == Qt::PartiallyChecked)
        {
            checkBoxStyle.state |= QStyle::State_NoChange;
        }
        else if(data == Qt::Checked)
        {
            checkBoxStyle.state |= QStyle::State_On;
        }
        checkBoxStyle.state |= QStyle::State_Enabled;
        checkBoxStyle.iconSize = QSize(20, 20);
        checkBoxStyle.rect = QRect(QPoint(option.rect.right()-30,option.rect.top()+5),
                                   QPoint(option.rect.right()-10,option.rect.bottom()-5));

        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxStyle, painter);
    }else
    {
        if( (option.state & QStyle::State_MouseOver || model->itemFromIndex(index)->checkState() == Qt::Checked) && (option.state & QStyle::State_Enabled))
        {
            painter->setBrush(QColor("#28163d"));
        }else
        {
            painter->setBrush(QColor("#a5a5a5"));
        }
        painter->setPen(Qt::NoPen);
        painter->drawRect(QRect(QPoint(2,option.rect.top()+4),
                                QPoint(option.rect.right()-2,option.rect.bottom()-4)));
        painter->setFont(QFont("SimSun", 9));
        painter->setPen(QColor("#ffffff"));
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
    }
    painter->restore();
}

QSize customtreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.parent().isValid())
        return QSize(option.rect.width(), 30);
    else
        return QSize(option.rect.width(), 40);
}
