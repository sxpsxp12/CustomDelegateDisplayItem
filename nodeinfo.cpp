#include "nodeinfo.h"

NodeInfo::NodeInfo()
{
    m_node_type = EMPTY_TYPE;
    m_node_name = "";
}

NodeInfo::NodeInfo(const NodeType node_type, const QString node_name)
{
    m_node_type = node_type;
    m_node_name = node_name;
}

QString getNodeTypeStr(NodeType type)
{
    if(type == FRUIT_TYPE)
        return QString("水果类");
    else if(type == LANGUAGE_TYPE)
        return QString("语言类");
    else if(type == SPORT_TYPE)
        return QString("运动类");
    else if(type == EMPTY_TYPE)
        return QString("");
}
