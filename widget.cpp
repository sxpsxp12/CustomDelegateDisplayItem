#include "widget.h"
#include "ui_widget.h"
#include "customtreeviewdelegate.h"
#include <QDebug>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initNodeInfoList();

    initUi();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initNodeInfoList()
{
    //初始化
    m_infoList.clear();

    NodeInfo info1(FRUIT_TYPE,"香蕉");
    NodeInfo info2(FRUIT_TYPE,"芒果");
    NodeInfo info3(FRUIT_TYPE,"樱桃");

    NodeInfo info4(LANGUAGE_TYPE,"英语");
    NodeInfo info5(LANGUAGE_TYPE,"中文");
    NodeInfo info6(LANGUAGE_TYPE,"法语");

    NodeInfo info7(SPORT_TYPE,"跑步");
    NodeInfo info8(SPORT_TYPE,"竞走");
    NodeInfo info9(SPORT_TYPE,"跨栏");

    m_infoList.append(info1);
    m_infoList.append(info2);
    m_infoList.append(info3);
    m_infoList.append(info4);
    m_infoList.append(info5);
    m_infoList.append(info6);
    m_infoList.append(info7);
    m_infoList.append(info8);
    m_infoList.append(info9);
}

void Widget::initUi()
{
    m_treeview_model = new QStandardItemModel(this);
    m_treeview_model->clear();

    ui->treeView->setModel(m_treeview_model);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setIndentation(0);        //
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setItemDelegate(new customtreeViewDelegate(this));
    ui->treeView->setExpandsOnDoubleClick(false);

    for(int i = 0;i < m_infoList.count();++i)
    {
        NodeInfo info = m_infoList.at(i);

        QStandardItem *mainItem = NULL;
        QList<QStandardItem *> item_list;
        getAllItem(m_treeview_model->invisibleRootItem(),item_list);

        foreach (QStandardItem *item, item_list) {
            if(isMainItem(item->index()) && info.getNodeType() == (NodeType)item->data(nodetype_role).toInt())
            {
                mainItem = item;
                break;
            }
        }

        if(!mainItem)
        {
            mainItem = new QStandardItem(getNodeTypeStr(info.getNodeType()));
            mainItem->setData(info.getNodeType(),nodetype_role);
            mainItem->setSizeHint(QSize(210,50));
            mainItem->setCheckable(true);
            m_treeview_model->appendRow(mainItem);  //主节点添加到模型中
        }

        QStandardItem *childItem = NULL;
        for(int row = 0; row < mainItem->rowCount();++row)
        {
            if(mainItem->child(row)->index().data().toString() == info.getNodeName())
            {
                childItem = mainItem->child(row);
                break;
            }
        }
        if(!childItem)  //添加子节点
        {
            childItem = new QStandardItem(info.getNodeName());
            childItem->setData(info.getNodeType(),nodetype_role);
            childItem->setSizeHint(QSize(210,50));
            childItem->setCheckable(true);

            mainItem->appendRow(childItem);
        }

        ui->treeView->sortByColumn(0,Qt::AscendingOrder);
        ui->treeView->expandAll();
    }
}

void Widget::getAllItem(QStandardItem *item, QList<QStandardItem *> &item_list)
{
    if(!item)
        return;

    for(int i = 0;i < item->rowCount();++i)
    {
        item_list.append(item->child(i));

        getAllItem(item->child(i),item_list);
    }
}

bool Widget::isMainItem(const QModelIndex &index)
{
    return !index.parent().isValid();
}



void Widget::on_treeView_clicked(const QModelIndex &index)
{
    if(isMainItem(index))   //是mainitem
    {
        if(m_treeview_model->itemFromIndex(index)->checkState() == Qt::Unchecked)
        {
            m_treeview_model->itemFromIndex(index)->setCheckState(Qt::Checked);
            ui->treeView->update(index);

            QList<QStandardItem *> allItems;
            allItems.clear();
            getAllItem(m_treeview_model->invisibleRootItem(),allItems);

            for(int i = 0;i < allItems.count();++i)
            {
                QStandardItem *item = allItems.at(i);
                if(isMainItem(item->index()))
                {
                    if(item->index() != index)
                    {
                        item->setCheckState(Qt::Unchecked);
                    }else
                    {
                        item->setCheckState(Qt::Checked);
                    }
                    ui->treeView->update(item->index());
                }else
                {
                    if(item->parent()->index() != index)
                    {
                        item->setCheckState(Qt::Unchecked);
                        ui->treeView->update(item->index());
                    }else
                    {
                        item->setCheckState(Qt::Checked);
                        ui->treeView->update(item->index());
                    }
                }
            }

        }else
        {
            m_treeview_model->itemFromIndex(index)->setCheckState(Qt::Unchecked);
            ui->treeView->update(index);

            QList<QStandardItem *> allItems;
            allItems.clear();
            getAllItem(m_treeview_model->itemFromIndex(index),allItems);

            for(int i = 0;i < allItems.count();++i)
            {
                QStandardItem *item = allItems.at(i);
                item->setCheckState(Qt::Unchecked);
                ui->treeView->update(item->index());
            }
        }
    }else
    {
        QList<QStandardItem *> allItems;
        int selectedSum = 0;
        allItems.clear();
        getAllItem(m_treeview_model->invisibleRootItem(),allItems);

        if(m_treeview_model->itemFromIndex(index)->checkState() == Qt::Unchecked)
        {
            m_treeview_model->itemFromIndex(index)->setCheckState(Qt::Checked);
            ui->treeView->update(index);

            for(int i = 0; i < allItems.count();++i)
            {
                QStandardItem *item = allItems.at(i);
                if(isMainItem(item->index()))    //其他父节点的选中状态变为未选中状态
                {
                    if(item->index() != index.parent())
                        if(item->checkState())
                        {
                            item->setCheckState(Qt::Unchecked);
                            ui->treeView->update(item->index());
                        }
                }else
                {
                    if(item->index().parent() != index.parent())   //其他父节点的节点状态为未选中
                    {
                        item->setCheckState(Qt::Unchecked);
                        ui->treeView->update(item->index());
                    }else if(item->checkState() == Qt::Checked)
                    {
                        ++selectedSum;
                    }
                }
            }
        }else
        {
            m_treeview_model->itemFromIndex(index)->setCheckState(Qt::Unchecked);
            ui->treeView->update(index);

            for(int i = 0; i < allItems.count();++i)
            {
                QStandardItem *item = allItems.at(i);

                if(!isMainItem(item->index()) && item->parent()->index() == index.parent() && item->checkState() == Qt::Checked)
                {
                    ++selectedSum;
                }
            }
        }

        if(selectedSum == m_treeview_model->itemFromIndex(index)->parent()->rowCount())
        {
            m_treeview_model->itemFromIndex(index)->parent()->setCheckState(Qt::Checked);
        }else if(selectedSum == 0)
        {
            m_treeview_model->itemFromIndex(index)->parent()->setCheckState(Qt::Unchecked);
        }else
            m_treeview_model->itemFromIndex(index)->parent()->setCheckState(Qt::PartiallyChecked);

        ui->treeView->update(index.parent());
    }

}
