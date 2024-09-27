#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QByteArray>
class Comunication : public QObject
{
    Q_OBJECT
public:
    explicit Comunication(QObject *parent = nullptr);

signals:
    void sendpacket(const  QVector<double> &message);
public slots:
    void trigger();
private slots:
    void readDatagrams();

    void readDatagramsSimulateData();
private:
    QUdpSocket *myudpsocket;
    QTimer *timer;

};

#endif // COMUNICATION_H
