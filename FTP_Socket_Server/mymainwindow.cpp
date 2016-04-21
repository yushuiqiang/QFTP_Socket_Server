#include "mymainwindow.h"
#include "ui_mymainwindow.h"

#include <QHostInfo>
#include <QFileDialog>
#include <QMessageBox>

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
   ui->setupUi(this);

   this->setMaximumHeight(400);
   this->setMinimumHeight(400);
   this->setMaximumWidth(600);
   this->setMinimumWidth(600);

   this->GetLocalIP();
   ui->pushButtonStartServer->setEnabled(true);
   ui->pushButtonStopServer->setEnabled(false);

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

QString MyMainWindow::GetLocalIP()
{
    QString localHostName = QHostInfo::localHostName();

    qDebug() <<"localHostName:"<<localHostName;
    int i=0;
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            qDebug() <<"IPV4 Address: "<< address.toString();
            ui->comboBoxIPAddress->insertItem(i++,address.toString());

            ui->listWidgetIPAddress->addItem(address.toString());
        }
    }
    return 0;
}

void MyMainWindow::on_pushButtonStartServer_clicked()
{
    this->StartServer();
}

void MyMainWindow::StartServer()
{
    QString iUser=ui->lineEditUser->text();
    QString iPassword=ui->lineEditPassword->text();
    QString iPort=ui->lineEditPort->text();
    QString iRootPath=ui->lineEditRootPath->text();
    if(!ui->checkBoxAllowAnyOneLogin->isChecked())
    {
        if(iUser.isEmpty()||iUser[0]==' ')
        {
            QMessageBox::information(this,tr("错误"),tr("用户名不能为空！"),QMessageBox::Ok);
            return;
        }
        else if(iPassword.isEmpty()||iPassword[0]==' ')
        {
            QMessageBox::information(this,tr("错误"),tr("密码不能为空！"),QMessageBox::Ok);
            return;
        }
    }

    if(iPort.isEmpty()||iPort[0]==' ')
    {
        QMessageBox::information(this,tr("错误"),tr("端口不能为空！"),QMessageBox::Ok);
        return;
    }
    if(iRootPath.isEmpty()||iRootPath[0]==' ')
    {
        QMessageBox::information(this,tr("错误"),tr("文件路径不能为空！"),QMessageBox::Ok);
        return;
    }
    this->LoadSettings();
    server = new FtpServer(this,mapServerSetting,mapFileLimit);

    ui->pushButtonStopServer->setEnabled(true);
    ui->pushButtonStartServer->setText(tr("重启服务"));
}

void MyMainWindow::on_toolButtonRootPath_clicked()
{
    QString rootPath;
    rootPath = QFileDialog::getExistingDirectory(this, QString(), ui->lineEditRootPath->text());

    if (rootPath.isEmpty()) {
        return;
    }
    ui->lineEditRootPath->setText(rootPath);
}

void MyMainWindow::on_pushButtonStopServer_clicked()
{
    ui->pushButtonStopServer->setEnabled(false);
    ui->pushButtonStartServer->setText(tr("开启服务"));
    delete server;
}

void MyMainWindow::on_pushButtonDeleteIP_clicked()
{
    if(ui->listWidgetIPAddress->currentItem()!=Q_NULLPTR)
    {
        QListWidgetItem *item = ui->listWidgetIPAddress->takeItem(ui->listWidgetIPAddress->currentRow());
        delete item;
    }
}

void MyMainWindow::LoadSettings()
{
//    mapServerSetting = new QMap<QString,QString>;
//    mapFileLimit = new QMap<QString,bool>;
    mapServerSetting.clear();
    mapFileLimit.clear();

    mapServerSetting.insert(QString("IPAddress"),ui->comboBoxIPAddress->currentText());
    mapServerSetting.insert(QString("IPPort"),ui->lineEditPort->text());

    mapServerSetting.insert(QString("RootPath"),ui->lineEditRootPath->text());

    mapFileLimit.insert(QString("OnlyWrite"),ui->checkBoxOnlyWrite->isChecked());
    mapFileLimit.insert(QString("OnlyRead"),ui->checkBoxOnlyRead->isChecked());
    mapFileLimit.insert(QString("AllowAnyOneLogin"),ui->checkBoxAllowAnyOneLogin->isChecked());
    if(ui->checkBoxAllowAnyOneLogin->isChecked()==true)
    {
        mapServerSetting.insert(QString("UserName"),QString(""));
        mapServerSetting.insert(QString("UserPassword"),QString(""));
    }
    else
    {
        mapServerSetting.insert(QString("UserName"),ui->lineEditUser->text());
        mapServerSetting.insert(QString("UserPassword"),ui->lineEditPassword->text());
    }
    mapFileLimit.insert(QString("AllowOneIP"),ui->checkBoxAllowOneIP->isChecked());


}
