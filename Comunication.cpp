#include "Comunication.h"
#include <QDebug>

Comunication::Comunication(QObject *parent)
    : QObject{parent}
{

}
void Comunication::trigger(){

    myudpsocket = new QUdpSocket(this);
    //QString hostid="10.42.0.1";
    //socket2->bind(QHostAddress::LocalHost, 4021); // Bind to localhost on port 2500
    myudpsocket->bind(QHostAddress::Any, 9000); // Bind to the specified local host address and port 7

    connect(myudpsocket, &QUdpSocket::readyRead, this, &Comunication::readDatagrams);


    //emit sendpacket("Hello from Sender!");

}

void Comunication::readDatagrams() {
    //qDebug() << " Inscope  :  ";
    QVector<double> yyDataz;
    while (myudpsocket->hasPendingDatagrams()) {
        // //qDebug() << " Enter While  :  ";

        // QElapsedTimer timer;
        // seriez->clear();
        // // Start the timer before the loop starts
        // timer.start();
        // //xxDataz.clear();
        // yyDataz.clear();
        // //yyDataz2.clear();

        QByteArray datagram;
        datagram.resize(myudpsocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        myudpsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        //Ensure the size of the received data is a multiple of 4 bytes (size of int32_t)
        if (datagram.size() % sizeof(int32_t) != 0) {
            qDebug() << "Received data size is not a multiple of 4 bytes";
            continue;
        }


        datagram=datagram.toHex();
        //qDebug() << " Recived Complete Data Gram  :  "<< datagram;

        int chunkSize = 8;

        for (int i = 0; i < datagram.size(); i += chunkSize) {

            QString chunk = datagram.mid(i, chunkSize);

            //qDebug() << " Recived Value Over WIFI HEX Individulae  :  "<< datagram[i];
            //qDebug() << " Recived Value Over WIFI HEX Chunk  :  "<< chunk;


            QString hexString =chunk;

            // Example hexadecimal string

            bool ok;
            int intValue = hexString.toInt(&ok, 16);  // 16 indicates hexadecimal base

            if (ok) {
                yyDataz.append(intValue);
                //qDebug() << "The integer value of :"<<chunk << "IS" << intValue;
            } else {
                qDebug() << "Conversion failed.";
            }
            //qDebug() << " Recived Value Over WIFI HEX Individulae  :  "<< datagram[i];


        }


        //do_processing();
        emit sendpacket(yyDataz);
        yyDataz.clear();


    }

}
