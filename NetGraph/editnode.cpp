#include "editnode.h"
#include "ui_editnode.h"
#include <QFile>

EditNode::EditNode(BaseConfig *baseConfig, Node *node, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNode)
{
    ui->setupUi(this);
    for(int i = 0; i < 5; i++)
    {
        ui->NetworkSelect0->addItem(QString((char)(65+i)));
        ui->NetworkSelect1->addItem(QString((char)(65+i)));
        ui->NetworkSelect2->addItem(QString((char)(65+i)));
    }
    ui->NetworkSelect2->addItem("tap");

    ui->NetworkSelect0->addItem("None");
    ui->NetworkSelect1->addItem("None");
    ui->NetworkSelect2->addItem("None");
    ui->NetworkSelect0->setCurrentIndex(5);
    ui->NetworkSelect1->setCurrentIndex(5);
    ui->NetworkSelect2->setCurrentIndex(6);
    this->baseConfig = baseConfig;
    this->node = node;
    load();
}

EditNode::~EditNode()
{
    delete ui;
}

void EditNode::load()
{
    ui->StartupEdit->setPlainText(node->getStartup());
    ui->ShutdownEdit->setPlainText(node->getShutdown());
    ui->NetworkSelect0->setCurrentIndex(ui->NetworkSelect0->findText(baseConfig->getNetwork(node->getName(), "0")));
    ui->NetworkSelect1->setCurrentIndex(ui->NetworkSelect1->findText(baseConfig->getNetwork(node->getName(), "1")));
    QString name = baseConfig->getNetwork(node->getName(), "2");
    if(name.contains("tap"))
    {
        ui->NetworkSelect2->addItem(name);
    }
    ui->NetworkSelect2->setCurrentIndex(ui->NetworkSelect2->findText(name));
}

void EditNode::on_SaveButton_clicked()
{
    node->setStartup(ui->StartupEdit->toPlainText());
    node->setShutdown(ui->ShutdownEdit->toPlainText());
    baseConfig->addNetwork(node->getName(), "0", ui->NetworkSelect0->currentText());
    baseConfig->addNetwork(node->getName(), "1", ui->NetworkSelect1->currentText());
    QString name = ui->NetworkSelect2->currentText();
    if(name.contains("tap") && name.size() < 5)
    {
        name = QString("tap,10.0.0.1,10.0.0.2");
    }
    baseConfig->addNetwork(node->getName(), "2", name);
    node->save();
    baseConfig->save();
}

void EditNode::on_CloseButton_clicked()
{
    this->hide();
}
