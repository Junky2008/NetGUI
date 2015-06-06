#include "netgui.h"
#include "ui_netgui.h"

NetGUI::NetGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetGUI)
{
    ui->setupUi(this);
    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->AddButton->setEnabled(false);
    ui->RemoveButton->setEnabled(false);
    ui->EditButton->setEnabled(false);
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(MenuClicked(QAction*)));
}

NetGUI::~NetGUI()
{
    delete ui;
}

void NetGUI::MenuClicked(QAction *action)
{
    if(action->text().contains("Load"))
    {
        BaseDir = QFileDialog::getExistingDirectory(this, QString("Open Directory"), QString("/home"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        loadNetKit();
    }
    else if(action->text().contains("New"))
    {
        BaseDir = QFileDialog::getExistingDirectory(this, QString("Open Directory"), QString("/home"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        QDir configDir(BaseDir);
        if(configDir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
        {
            QFile configFile(BaseDir + QString("/lab.conf"));
            configFile.open(QIODevice::Text | QIODevice::WriteOnly);
            configFile.close();
            loadNetKit();
        }
    }
    else if(action->text().contains("Report"))
    {
        QString SaveDir = QFileDialog::getExistingDirectory(this, QString("Open Directory"), QString("/home"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        QFile saveFile(SaveDir + QString("/Report.txt"));
        saveFile.open(QIODevice::Text | QIODevice::WriteOnly);
        for(int i = 0; i < nodes.size(); i++)
        {
            saveFile.write(nodes[i].getName().toStdString().c_str());
            saveFile.write("\n");
            QString network0 = baseConfig->getNetwork(nodes[i].getName(), QString("0"));
            QString network1 = baseConfig->getNetwork(nodes[i].getName(), QString("1"));
            QString network2 = baseConfig->getNetwork(nodes[i].getName(), QString("2"));
            saveFile.write("\neth0: ");
            saveFile.write(network0.toStdString().c_str());
            saveFile.write("\neth1: ");
            saveFile.write(network1.toStdString().c_str());
            saveFile.write("\neth2: ");
            saveFile.write(network2.toStdString().c_str());
            if(nodes[i].getStartup() != "")
            {
                saveFile.write("\n\nStartup:\n");
                saveFile.write(nodes[i].getStartup().toStdString().c_str());
            }
            else
            {
                saveFile.write("\n\nNo Startup");
            }
            if(nodes[i].getShutdown() != "")
            {
                saveFile.write("\n\nShutdown:");
                saveFile.write(nodes[i].getShutdown().toStdString().c_str());
            }
            else
            {
                saveFile.write("\n\nNo Shutdown");
            }
            saveFile.write("\n\n");
        }
        saveFile.close();
    }
}


void NetGUI::loadNetKit()
{
    QString configFile = BaseDir + "/lab.conf";
    QFile labFile(configFile);
    if(!labFile.exists())
    {
        //notify user
        return;
    }
    nodes.clear();
    ui->NodeList->clear();
    if(baseConfig == NULL)
    {
        delete baseConfig;
    }
    baseConfig = new BaseConfig(BaseDir, configFile);

    QList<QString> nodeList = baseConfig->getNodeList();
    for(int i = 0; i < nodeList.size(); i++)
    {
        Node node(BaseDir, nodeList.at(i));
        nodes.append(node);
        ui->NodeList->addItem(nodeList.at(i));
    }
    ui->StartButton->setEnabled(true);
    ui->EditButton->setEnabled(true);
    ui->AddButton->setEnabled(true);
    ui->RemoveButton->setEnabled(true);
}

void NetGUI::on_EditButton_clicked()
{
    QString nodeName = ui->NodeList->selectedItems().at(0)->text();
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].getName() == nodeName)
        {
            node = new EditNode(baseConfig, &nodes[i], this);
            node->show();
        }
    }
}

void NetGUI::on_StartButton_clicked()
{
    //if a device has a tap, start from console!
    ui->StartButton->setEnabled(false);
    ui->EditButton->setEnabled(false);
    ui->AddButton->setEnabled(false);
    ui->RemoveButton->setEnabled(false);
    QString pro = "lstart -d " + BaseDir;
    system(pro.toStdString().c_str());
    ui->StopButton->setEnabled(true);
}

void NetGUI::on_StopButton_clicked()
{
    ui->StopButton->setEnabled(false);
    QString pro = "lcrash -d " + BaseDir;
    system(pro.toStdString().c_str());
    ui->StartButton->setEnabled(true);
    ui->EditButton->setEnabled(true);
    ui->AddButton->setEnabled(true);
    ui->RemoveButton->setEnabled(true);
}

void NetGUI::on_AddButton_clicked()
{
    bool ok;
    QString nodeName = QInputDialog::getText(this, QString("New Node"), QString("Node name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (ok && !nodeName.isEmpty())
    {
        QDir().mkdir(BaseDir + QString("/") + nodeName);
        loadNetKit();
    }
}

void NetGUI::on_RemoveButton_clicked()
{
    QString nodeName = ui->NodeList->selectedItems().at(0)->text();
    QDir nodeDir(BaseDir + QString("/") + nodeName);
    if(nodeDir.exists())
    {
        nodeDir.removeRecursively();
    }
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].getName() == nodeName)
        {
            nodes[i].Delete();
        }
    }
    baseConfig->removeNetwork(nodeName, "0");
    baseConfig->removeNetwork(nodeName, "1");
    baseConfig->removeNetwork(nodeName, "2");
    baseConfig->save();
    loadNetKit();
}
