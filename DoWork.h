#ifndef DOWORK_H
#define DOWORK_H

#include <QObject>

class DoWork : public QObject
{
    Q_OBJECT
public:
    explicit DoWork(QObject *parent = nullptr);

    double f1;
    double f2;
    int x_itr;
    int numSamples;    // 1 million samples
    int data_size = 5760;

    QVector<double> xxDataz;
    QVector<double> yyDataz;
    QVector<double> yyDataz2;
    QVector<double> random_data;
    QVector<double> dB_list;
    QVector<double> index_list;





signals:
    void workFinished(QVector<double> ydata,QVector<double> xdata);

public slots:
    void myworkerfunction(const  QVector<double> &message);
private:

    int res;
};

#endif // DOWORK_H
