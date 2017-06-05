#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "nodeinfo.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>

namespace Ui {
class Widget;
}

const int nodetype_role = Qt::UserRole+10;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    nodeInfoList m_infoList;
    QStandardItemModel *m_treeview_model;

    void initNodeInfoList();
    void initUi();

    void getAllItem(QStandardItem *item, QList<QStandardItem *> &item_list);
    bool isMainItem(const QModelIndex &index);
};

#endif // WIDGET_H
