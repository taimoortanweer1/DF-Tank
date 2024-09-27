#ifndef DF_TANK_V1_H
#define DF_TANK_V1_H

#include <QMainWindow>
#include <windows.h>
#include <QTimer>
#include <QVector>
#include <QUdpSocket>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QElapsedTimer>
#include <QtGui/QPixmap>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QDebug>
#include <QtCharts/QPolarChart>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCharts/QSplineSeries>
#include "ui_df_tank_v1.h"
#include "qchartview.h"
#include <QDebug>
#include "Comunication.h"
#include "DoWork.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class df_tank_v1;
}
QT_END_NAMESPACE

class df_tank_v1 : public QMainWindow
{
    Q_OBJECT

public:
    df_tank_v1(QWidget *parent = nullptr);
    ~df_tank_v1();
public slots:
    void do_plotting(QVector<double> ydata,QVector<double> xdata);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:

    Comunication comunication;
    DoWork dowork;

    Ui::df_tank_v1 *ui;
    QUdpSocket *socket2;

    int x_itr=1, x_lop=0,top_count;
    //int numSamples = 1000000;    // 1 million samples
    int angl=1, pkt_loss=1 ;
    double f1=400000000;
    double f2=5900000000;
    int x_itr1z=0, x_lop1z=1;
    // float angle_to_addz=0.1757;
    float angle_to_addz=0.0078;


    QPolarChart *polarChartz;
    QLineSeries *series11z;
    QScatterSeries *series1z;
    QValueAxis *angularAxisz;
    QValueAxis *radialAxisz;
    QChartView *chartViewz;
    QSplineSeries *seriez;
    QSplineSeries *seriez2;
    QVector<QPointF> peaks_info; // New vector to store the highest point

};
#endif // DF_TANK_V1_H
