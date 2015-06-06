#ifndef NETGUI_H
#define NETGUI_H

#include <QMainWindow>
#include <QList>
#include <QInputDialog>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include "editnode.h"
#include "baseconfig.h"
#include "node.h"

namespace Ui {
class NetGUI;
}

class NetGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetGUI(QWidget *parent = 0);
    ~NetGUI();

private slots:
    void MenuClicked(QAction* action);

    void on_EditButton_clicked();

    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_AddButton_clicked();

    void on_RemoveButton_clicked();

private:
    void loadNetKit();
    Ui::NetGUI *ui;
    EditNode *node;
    BaseConfig *baseConfig;
    QList<Node> nodes;
    QString BaseDir;
};

#endif // NETGUI_H
