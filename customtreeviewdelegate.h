#ifndef CUSTOMTREEVIEWDELEGATE_H
#define CUSTOMTREEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class customtreeViewDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    customtreeViewDelegate(QObject *parent = 0);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // CUSTOMTREEVIEWDELEGATE_H
