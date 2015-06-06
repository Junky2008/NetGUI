#ifndef EDITNODE_H
#define EDITNODE_H

#include <QDialog>
#include "baseconfig.h"
#include "node.h"

namespace Ui {
class EditNode;
}

class EditNode : public QDialog
{
    Q_OBJECT

public:
    explicit EditNode(BaseConfig *baseConfig, Node *node, QWidget *parent = 0);
    ~EditNode();

private slots:
    void on_SaveButton_clicked();

    void on_CloseButton_clicked();

private:
    void load();
    Ui::EditNode *ui;
    BaseConfig *baseConfig;
    Node *node;

};

#endif // EDITNODE_H
