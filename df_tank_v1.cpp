#include "df_tank_v1.h"
#include "ui_df_tank_v1.h"
#include "qchartview.h"
#include <QDebug>
#include "Comunication.h"
#include "DoWork.h"

int x_itr=1, x_lop=0,top_count;
//int numSamples = 1000000;    // 1 million samples
int angl=1, pkt_loss=1 ;
double f1=400000000;
double f2=5900000000;
int x_itr1z=0, x_lop1z=1;
// float angle_to_addz=0.1757;
float angle_to_addz=0.0078;
//QVector<double> xxDataz;
//QVector<double> yyDataz;
//QVector<double> yyDataz2;

QPolarChart *polarChartz;
QLineSeries *series11z;
QScatterSeries *series1z;
QValueAxis *angularAxisz;
QValueAxis *radialAxisz;
QChartView *chartViewz;
#include <QtCharts/QSplineSeries>
QSplineSeries *seriez;
QSplineSeries *seriez2;
QVector<QPointF> peaks_info; // New vector to store the highest point

df_tank_v1::df_tank_v1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::df_tank_v1)
{
    ui->setupUi(this);

    //===========Initailzing Custom Plot==========================================================================
    ui->customplot->setBackground(QBrush(QColor(0, 0, 0))); // Set background color to black (RGB: 0, 0, 0)
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Set plot labels and titles
    ui->customplot->xAxis->setLabel("Frequency (MHz/GHz)");
    ui->customplot->yAxis->setLabel("Amplitude (Db)");


    // Set font color to white for x-axis label
    ui->customplot->xAxis->setLabelColor(QColor(27, 196, 145));

    // Set font color to white for y-axis label
    ui->customplot->yAxis->setLabelColor(QColor(27, 196, 145));

    // Set font color to white for graph text
    ui->customplot->graph(0)->setPen(QColor(27, 196, 145));

    // Set font color to white for axis ticks and labels
    ui->customplot->xAxis->setTickLabelColor(QColor(27, 196, 145));
    ui->customplot->yAxis->setTickLabelColor(QColor(27, 196, 145));

    // Set font color to white for axis line
    ui->customplot->xAxis->setBasePen(QColor(27, 196, 145));
    ui->customplot->yAxis->setBasePen(QColor(27, 196, 145));

    // Set font color to white for axis grid lines
    ui->customplot->xAxis->grid()->setPen(QColor(212, 175, 55));
    ui->customplot->yAxis->grid()->setPen(QColor(212, 175, 55));

    // Set font color to white for legend
    ui->customplot->legend->setBrush(QColor(27, 196, 145));
    ui->customplot->legend->setTextColor(QColor(27, 196, 145));


    QPen pen;
    pen.setColor(Qt::red);  // Set color to red
    ui->customplot->addGraph();
    ui->customplot->graph(1)->setPen(pen);
    ui->customplot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph(1)->setLineStyle(QCPGraph::lsNone);
    //========================================Polar Satart=========================================================

    polarChartz = new QPolarChart();
    //polarChartz->setAnimationOptions(QChart::AllAnimations);

    // polarChart->setTitle("Direction Finder");
    QColor rgbaColor(43, 53, 86); // Red color with 50% transparency
    rgbaColor.setAlpha(30);
    QBrush brush(rgbaColor);
    polarChartz->setBackgroundBrush(brush);
    QColor rgbaColor3(0, 0, 0); // Red color with 50% transparency
    //rgbaColor3.setAlpha(80);
    QBrush brush3(rgbaColor3);
    polarChartz->setPlotAreaBackgroundVisible(true);
    polarChartz->setPlotAreaBackgroundBrush(brush3);


    // // Create angular and radial axes
    angularAxisz = new QValueAxis();
    angularAxisz->setTickCount(9); // 8 sectors + 1 to complete the circle
    angularAxisz->setLabelFormat("%.0f");
    angularAxisz->setRange(0, 360);
    angularAxisz->setLabelsColor(Qt::white);
    angularAxisz->setGridLineColor(Qt::green);
    polarChartz->addAxis(angularAxisz, QPolarChart::PolarOrientationAngular);

    radialAxisz = new QValueAxis();
    //radialAxisz->setShadesVisible(QGradient::TrueSunset);
    //radialAxisz->setShadesBrush(QBrush(QColor(249, 249, 55)));

    radialAxisz->setTickCount(10);
    radialAxisz->setLabelFormat("%.1f");
    radialAxisz->setRange(0, 10000); // Example range, can be adjusted
    radialAxisz->setLabelsColor(Qt::white);
    radialAxisz->setGridLineColor(Qt::green);
    polarChartz->addAxis(radialAxisz,QPolarChart::PolarOrientationRadial);

    // // Create a scatter series to plot points in sector 7 (270 to 315 degrees)
    //series = new QScatterSeries();
    //series = new QLineSeries();
    seriez = new QSplineSeries();
    seriez->setPointsVisible(true);
    seriez->setMarkerSize(8);
    seriez->setName("Ploting Channel 7");
    seriez->append(45, 205); // Example point (angle, radius)
    seriez->append(75, 150);
    seriez->append(115, 50);
    seriez->append(0, 0);
    seriez->append(0, 0);
    seriez->append(225, 50); // main lobe start
    seriez->append(250, 100); // maib lobe mid
    seriez->append(275, 50); // main lobe end
    seriez->append(0, 0);
    seriez->append(0, 0);
    seriez->append(360,0);
    seriez->append(15, 105); //back lobe
    seriez->append(45, 205); //backlobe

    // series->sortByAngle();

    // // Set series properties
    // series->setConnectPoints(true); // Enable line connections between points
    // series->setWrapAround(true);

    //// Define area series for filling
    //QAreaSeries *areaSeries = new QAreaSeries(seriez, seriez2);
    //areaSeries->setName("Filled Area");

    //// Customize the appearance of the filled area
    //areaSeries->setBrush(QBrush(QColor(255, 0, 0, 100))); // Set fill color with transparency (e.g., semi-transparent red)
    //areaSeries->setPen(QPen(QColor(255, 0, 0))); // Set border color

    QBrush markerBrush(Qt::green);
    seriez->setBrush(markerBrush);
    // // Set the outline color of the points to black
    QPen black_pen = *new QPen();
    black_pen = seriez->pen(); // Get current pen settings
    black_pen.setColor(Qt::white); // Set outline color to black
    //black_pen.brush()
    black_pen.setWidth(2); // Set outline width (optional)
    seriez->setPen(black_pen); // Apply the updated pen to the series



    //polarChartz->addSeries(areaSeries);
    polarChartz->addSeries(seriez);

    //polarChartz->createDefaultAxes();

    // Attach the series to the axes
    seriez->attachAxis(angularAxisz);
    seriez->attachAxis(radialAxisz);

    // // Create a chart view with zooming enabled
    chartViewz = new QChartView(polarChartz);
    chartViewz->setRenderHint(QPainter::Antialiasing);

    QColor rgbaColor2(43, 53, 86); // Red color with 50% transparency
    rgbaColor2.setAlpha(30);
    QBrush brush2(rgbaColor2);

    chartViewz->setBackgroundBrush(brush2);

    // Create a scene and add the chart to it
    QGraphicsScene *scene = new QGraphicsScene(chartViewz);
    scene->addItem(polarChartz);
    chartViewz->setScene(scene);


    //chartView->setMinimumSize(200, 380);

    ui->gridLayout->addWidget(chartViewz);
}

df_tank_v1::~df_tank_v1()
{
    delete ui;
    delete socket2;
}

// void df_tank_v1::do_processing(){
//     float x_freq=(f2-f1)/5760;
//     int pkt_nbr= yyDataz[1];

//     if(pkt_nbr <=89){
//         for (int d = 8; d < yyDataz.size(); ++d) {

//             float xfreq=f1+(x_freq*x_itr);
//             xxDataz.append(xfreq);
//             //xxDataz.append(x_itr);
//             yyDataz2.append(yyDataz[d]);
//             //qDebug() << " Y Value after Process :  "<< qAbs(yyDataz[d]);
//             x_itr=x_itr+1;

//             xxDataz.reserve(numSamples);
//             yyDataz.reserve(numSamples);
//             yyDataz2.reserve(numSamples);


//         }
//         if(pkt_nbr ==89){
//             do_plotting();
//         }
//     }

// }
void df_tank_v1::do_plotting(QVector<double> &ydata,QVector<double> &xdata){
    if(ydata.size() == 5760){
        qDebug() << "Recived Packet number 90================================================ SIZE: " << ydata.size() ;
        //qDebug() << "Recived Packet number 90================================================ XDATA SIZE: " << xxDataz.size() ;

        ui->customplot->graph(0)->setData(xdata, ydata);

        ui->customplot->xAxis->setRange(f1,f2);
        //ui->customplot->xAxis->setRange(0,xxDataz.size());
        //ui->customplot_1->yAxis->setRange(-250,dbval1); // Adjust range as needed
        ui->customplot->yAxis->setRange(-150,3000); // Adjust range as needed
        ui->customplot->replot();


        // //polar plotting start here---
        if(angl==1){
            float Qs=0.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 1");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));
                //ui->label_31->setText( QString::number(xxDataz[z]));


                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_32->setText( QString::number(highestPoint.y()));
            ui->label_73->setText( QString::number(highestPoint.x()));


            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 1 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==2){
            float Qs=45.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 2");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_37->setText( QString::number(highestPoint.y()));
            ui->label_74->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            qDebug() << " Y high values ch 2 "<<highestPoint;

            //series->replace(newData);
            newData.clear();

        }
        if(angl==3){
            float Qs=90.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 3");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_42->setText( QString::number(highestPoint.y()));
            ui->label_75->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 3 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==4){
            float Qs=135.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            //seriez->setName("Ploting Channel 4");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_47->setText( QString::number(highestPoint.y()));
            ui->label_76->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 4 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==5){
            float Qs=180.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 5");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_52->setText( QString::number(highestPoint.y()));
            ui->label_77->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 5 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==6){
            float Qs=225.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 6");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_57->setText( QString::number(highestPoint.y()));
            ui->label_78->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 6 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==7){
            float Qs=270.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 7");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_67->setText( QString::number(highestPoint.y()));
            ui->label_79->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 7 "<<highestPoint;

            //series->replace(newData);
            newData.clear();
        }
        if(angl==8){
            angl=0;
            float Qs=315.0;
            QPointF highestPoint;
            qreal maxY = std::numeric_limits<qreal>::lowest();

            float detaa=Qs+angle_to_addz;
            QVector<QPointF> newData;

            seriez->setName("Ploting Channel 8");
            for(int z=0;z<ydata.size();++z){
                newData.append(QPointF(detaa, qAbs(ydata[z])));

                //qDebug() << "Q theta Values: " << detaa << " Y values "<<yyData[z];

                // series->append(detaa,yyData[z]);
                detaa=detaa+angle_to_addz;

            }

            for (const QPointF &point : newData) {
                if (point.y() > maxY) {
                    maxY = point.y();
                    highestPoint = point;
                }
            }

            ui->label_72->setText( QString::number(highestPoint.y()));
            ui->label_80->setText( QString::number(highestPoint.x()));
            // Store the highest point in newData1
            peaks_info.append(highestPoint);
            //qDebug() << " Y high values ch 8 "<<highestPoint;
            seriez->replace(peaks_info);
            //series->append(newData1);
            polarChartz->update();
            chartViewz->update();
            chartViewz->clearFocus();
            polarChartz->clearFocus();
            //series->replace(newData);
            newData.clear();
            peaks_info.clear();


        }
        //after if
        angl +=1;





    }
    else{
        qDebug() << "Recived Packet number 90================================================ SIZE: " << ydata.size() ;
        qDebug() << "Recived Packet number 90================================================ XDATA SIZE: " << xdata.size() ;
        qDebug() << "Total packet lost-------------------------------:  "<<pkt_loss;
        pkt_loss +=1;

    }
    //finally
    //xxDataz.clear();
    //yyDataz.clear();
    //yyDataz2.clear();
    x_itr=1;

}

// void df_tank_v1::readDatagrams2() {
//     //qDebug() << " Inscope  :  ";

//     while (socket2->hasPendingDatagrams()) {
//         //qDebug() << " Enter While  :  ";

//         QElapsedTimer timer;
//         seriez->clear();
//         // Start the timer before the loop starts
//         timer.start();
//         //xxDataz.clear();
//         yyDataz.clear();
//         //yyDataz2.clear();



//         QByteArray datagram;
//         datagram.resize(socket2->pendingDatagramSize());
//         QHostAddress sender;
//         quint16 senderPort;

//         socket2->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

//         //Ensure the size of the received data is a multiple of 4 bytes (size of int32_t)
//         if (datagram.size() % sizeof(int32_t) != 0) {
//             qDebug() << "Received data size is not a multiple of 4 bytes";
//             continue;
//         }

//         // // Interpret the received data as int32_t values
//         //const  uint32_t *intArray = reinterpret_cast<const uint32_t*>(datagram.constData());
//         //int numInts = datagram.size() / sizeof(uint32_t);
//         //qDebug() << "Received Values : "<<numInts;

//         datagram=datagram.toHex();
//         //qDebug() << " Recived Complete Data Gram  :  "<< datagram;

//         int chunkSize = 8;

//         for (int i = 0; i < datagram.size(); i += chunkSize) {
//             // QString hexString;
//             // hexString =&""+[datagram[i]]+datagram[i+1]+datagram[i+2]+datagram[i+3]+datagram[i+4]+datagram[i+5]+datagram[i+6]+datagram[i+7];

//             QString chunk = datagram.mid(i, chunkSize);

//             //qDebug() << " Recived Value Over WIFI HEX Individulae  :  "<< datagram[i];
//             //qDebug() << " Recived Value Over WIFI HEX Chunk  :  "<< chunk;


//             QString hexString =chunk;

//             // Example hexadecimal string

//             bool ok;
//             int intValue = hexString.toInt(&ok, 16);  // 16 indicates hexadecimal base

//             if (ok) {
//                 yyDataz.append(intValue);
//                 //qDebug() << "The integer value of :"<<chunk << "IS" << intValue;
//             } else {
//                 qDebug() << "Conversion failed.";
//             }
//             //qDebug() << " Recived Value Over WIFI HEX Individulae  :  "<< datagram[i];


//         }


//         do_processing();

//     }

// }


void df_tank_v1::on_pushButton_clicked()
{
    //Start Button
    ui->pushButton->setStyleSheet("QPushButton { "
                                  "background-color:rgb(50, 82, 123);"
                                  "} "
                                  "QPushButton:hover { "
                                  "background-color: #a3a3a3; "
                                  "} ");
    qDebug() << " Clicked Start ";
    DoWork dowork;
    Comunication comunication;


    QObject::connect(&comunication, &Comunication::sendpacket, &dowork, &DoWork::myworkerfunction);

    comunication.trigger();

    QObject::connect(&dowork, &DoWork::workFinished, this, &df_tank_v1::do_plotting);



    //openudp


    //socket2 = new QUdpSocket(this);
    //QString hostid="10.42.0.1";
    //socket2->bind(QHostAddress::LocalHost, 4021); // Bind to localhost on port 2500
    //socket2->bind(QHostAddress::Any, 9000); // Bind to the specified local host address and port 7

    //ui->radioButton_2->setStyleSheet("QRadioButton::indicator {width: 15px; height: 15px;border-radius: 7px; background-color: #1bc43a; }");
    qDebug() << " Port set  :  ";

    //connect(socket2, &QUdpSocket::readyRead, this, &df_tank_v1::readDatagrams2);
    qDebug() << " Port Open  :  ";

}


void df_tank_v1::on_pushButton_2_clicked()
{


}


void df_tank_v1::on_pushButton_4_clicked()
{
    // send data udp

    QUdpSocket udpSocket;

    QString f1="4000000000";
    QString f2="5900000000000";


    // Convert the integers to QByteArray
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << f1 << f2;

    // Define the target address and port
    QHostAddress targetAddress("192.168.18.12"); // Change to your target IP address
    quint16 targetPort =6500; // Change to your target port

    // Send the datagram
    qint64 bytesWritten = udpSocket.writeDatagram(datagram, targetAddress, targetPort);

    if (bytesWritten == -1) {
        qCritical() << "Failed to send datagram:" << udpSocket.errorString();
    } else {
        qDebug() << "Datagram sent:" << bytesWritten << "bytes.";
    }
}


void df_tank_v1::on_pushButton_5_clicked()
{
    //Stop Button

    // // Disconnect the readyRead signal
    // disconnect(socket2, &QUdpSocket::readyRead, this, &df_tank_v1::readDatagrams2);

    // // Close the UDP socket
    // socket2->close();
}

