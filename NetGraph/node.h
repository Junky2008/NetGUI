#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Node
{
public:
    Node(QString baseDir, QString name);
    void Delete();
    QString getStartup();
    QString getShutdown();
    QString getName();
    void setStartup(QString startup);
    void setShutdown(QString shutdown);
    void save();
    void reload();
private:
    void load();
    QString baseDir;
    QString name;
    QString startup;
    QString shutdown;
};

#endif // NODE_H
