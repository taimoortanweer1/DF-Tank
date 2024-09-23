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
    void do_plotting(QVector<double> &ydata,QVector<double> &xdata);

private slots:
    //void readDatagrams2();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void do_processing();
    void do_plotting();

private:
    Ui::df_tank_v1 *ui;
    QUdpSocket *socket2;

};
#endif // DF_TANK_V1_H
