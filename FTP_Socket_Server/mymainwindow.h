#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "ftpserver.h"


namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();
private slots:

    void on_pushButtonStartServer_clicked();

    void on_toolButtonRootPath_clicked();

    void on_pushButtonStopServer_clicked();

    void on_pushButtonDeleteIP_clicked();

private:
    Ui::MyMainWindow *ui;

    FtpServer *server;

    QString GetLocalIP();

    void StartServer();

    void StopServer();

    void LoadSettings();

    QMap<QString,QString> mapServerSetting;
    QMap<QString,bool> mapFileLimit;

};

#endif // MYMAINWINDOW_H
