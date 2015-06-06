#include "node.h"

Node::Node(QString baseDir, QString name)
{
    this->baseDir = baseDir;
    this->name = name;
    load();
}

void Node::Delete()
{
    QFile startupFile(baseDir + QString("/") + name + QString(".startup"));
    if(startupFile.exists())
    {
        startupFile.remove();
    }
    QFile shutdownFile(baseDir + QString("/") + name + QString(".shutdown"));
    if(shutdownFile.exists())
    {
        shutdownFile.remove();
    }
}

QString Node::getStartup()
{
    return startup;
}

QString Node::getShutdown()
{
    return shutdown;
}

QString Node::getName()
{
    return name;
}

void Node::setStartup(QString startup)
{
    this->startup = startup;
}

void Node::setShutdown(QString shutdown)
{
    this->shutdown = shutdown;
}

void Node::save()
{
    if(startup.size() > 0)
    {
        QFile startupFile(baseDir + QString("/") + name + QString(".startup"));
        startupFile.open(QIODevice::Text | QIODevice::WriteOnly);
        QTextStream startstream(&startupFile);
        startstream << startup;
        startupFile.close();
    }
    else
    {
        QFile startupFile(baseDir + QString("/") + name + QString(".startup"));
        if(startupFile.exists())
        {
            startupFile.remove();
        }
    }
    if(shutdown.size() > 0)
    {
        QFile shutdownFile(baseDir + QString("/") + name + QString(".shutdown"));
        shutdownFile.open(QIODevice::Text | QIODevice::WriteOnly);
        QTextStream shutdownstream(&shutdownFile);
        shutdownstream << shutdown;
        shutdownFile.close();
    }
    else
    {
        QFile shutdownFile(baseDir + QString("/") + name + QString(".shutdown"));
        if(shutdownFile.exists())
        {
            shutdownFile.remove();
        }
    }
}

void Node::reload()
{

}

void Node::load()
{
    QFile startupFile(baseDir + QString("/") + name + QString(".startup"));
    if(startupFile.exists())
    {
       startupFile.open(QIODevice::ReadOnly | QIODevice::Text);
       startup = startupFile.readAll();
       startupFile.close();
    }
    QFile shutdownFile(baseDir + QString("/") + name + QString(".shutdown"));
    if(shutdownFile.exists())
    {
        shutdownFile.open(QIODevice::ReadOnly | QIODevice::Text);
        shutdown = shutdownFile.readAll();
        shutdownFile.close();
    }
}
