#ifndef FTPSERVER_H
#define FTPSERVER_H

#include <QObject>
#include <QTcpServer>
class FtpServer : public QObject
{
    Q_OBJECT
public:
    explicit FtpServer(QObject *parent,QMap<QString,QString> &mapServerSetting,
                       QMap<QString,bool> &mapFileLimit);

signals:

public slots:

private slots:
    void StartNewControlConnection();

private:
    QMap<QString,QString> mapServerSetting;
    QMap<QString,bool> mapFileLimit;

    QTcpServer *server;

    QVector<QString> encounteredIps;
};

#endif // FTPSERVER_H
