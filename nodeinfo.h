#ifndef NODEINFO_H
#define NODEINFO_H

#include <QString>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

typedef enum{
    EMPTY_TYPE,
    FRUIT_TYPE, //水果
    LANGUAGE_TYPE,   //语言
    SPORT_TYPE
}NodeType;

QString getNodeTypeStr(NodeType type);

class NodeInfo
{
public:
    NodeInfo();
    NodeInfo(const NodeType node_type,const QString node_name);

    NodeType getNodeType() const{return m_node_type;}
    QString getNodeName() const{return m_node_name;}

private:
    NodeType m_node_type;
    QString m_node_name;
};

typedef QList<NodeInfo> nodeInfoList;

#endif // NODEINFO_H
