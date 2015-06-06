#include "baseconfig.h"

BaseConfig::BaseConfig(QString baseDir, QString filePath)
{
    this->baseDir = baseDir;
    this->filePath = filePath;
    load();
}

void BaseConfig::addNetwork(QString nodeName, QString adapter, QString network)
{
    if(networkConfig.contains(nodeName + "," + adapter))
    {
        networkConfig.insert(nodeName + "," + adapter, network);
    }
    else
    {
        networkConfig.insert(nodeName + "," + adapter, network);
    }
}

void BaseConfig::removeNetwork(QString nodeName, QString adapter)
{
    if(networkConfig.contains(nodeName + "," + adapter))
    {
        networkConfig.remove(nodeName + "," + adapter);
    }
}

QString BaseConfig::getNetwork(QString nodeName, QString adapter)
{
    if(networkConfig.contains(nodeName + "," + adapter))
    {
        return networkConfig.value(nodeName + "," + adapter);
    }
    return "None";
}

QList<QString> BaseConfig::getNodeList()
{
    return nodeList;
}

void BaseConfig::save()
{
    QFile configFile(baseDir + QString("/lab.conf"));
    configFile.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream configstream(&configFile);
    configstream << before;
    for(int i = 0; i < nodeList.size(); i++)
    {
        QString network0 = getNetwork(nodeList.at(i), "0");
        if(!network0.contains("None"))
        {
            configstream << QString(nodeList.at(i) + QString("[0]=") + network0 + QString("\n"));
        }
        QString network1 = getNetwork(nodeList.at(i), "1");
        if(!network1.contains("None"))
        {
            configstream << QString(nodeList.at(i) + QString("[1]=") + network1 + QString("\n"));
        }
        QString network2 = getNetwork(nodeList.at(i), "2");
        if(!network2.contains("None"))
        {
            configstream << QString(nodeList.at(i) + QString("[2]=") + network2 + QString("\n"));
        }
    }
    configstream << after;
    configFile.close();
}

void BaseConfig::reload()
{

}

void BaseConfig::load()
{
    QDirIterator dir(baseDir, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    while(dir.hasNext())
    {
        dir.next();
        nodeList.append(dir.fileName());
    }
    QFile configFile(baseDir + QString("/lab.conf"));
    if(configFile.exists())
    {
        configFile.open(QIODevice::ReadOnly | QIODevice::Text);
        bool above = true;
        while(!configFile.atEnd())
        {
            QString line = configFile.readLine();
            bool contains = false;
            for(int i = 0; i < nodeList.size() && !contains; i++)
            {
                if(line.contains(nodeList.at(i) + QString('[')))
                {
                    contains = true;
                }
            }
            if(contains)
            {
                if(above)
                {
                    above = false;
                }
                QString nodeName = line.mid(0, line.indexOf('['));
                QString adapter = line.mid(line.indexOf('[') + 1, 1);
                QString network = line.mid(line.indexOf('=') + 1, 1);
                if(network.contains('t'))
                {
                    network = line.mid(line.indexOf('=') + 1, (line.indexOf('\n') - line.indexOf('=')) - 1);
                }
                addNetwork(nodeName, adapter, network);
            }
            else
            {
                if(above)
                {
                    before.append(line);
                }
                else
                {
                    after.append(line);
                }
            }
        }
    }
}




