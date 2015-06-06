#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>

class BaseConfig
{
public:
    BaseConfig(QString baseDir, QString filePath);
    void addNetwork(QString nodeName, QString adapter, QString network);
    void removeNetwork(QString nodeName, QString adapter);
    QString getNetwork(QString nodeName, QString adapter);
    QList<QString> getNodeList();
    void save();
    void reload();
private:
    void load();
    QString baseDir;
    QString filePath;
    QString before;
    QString after;
    QMap<QString, QString> networkConfig;
    QList<QString> nodeList;
};

#endif // BASECONFIG_H
