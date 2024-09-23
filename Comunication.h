#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <QObject>
#include <QUdpSocket>

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

private:
    QUdpSocket *myudpsocket;

};

#endif // COMUNICATION_H
