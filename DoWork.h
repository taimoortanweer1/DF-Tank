#ifndef DOWORK_H
#define DOWORK_H

#include <QObject>

class DoWork : public QObject
{
    Q_OBJECT
public:
    explicit DoWork(QObject *parent = nullptr);


signals:
    void workFinished(QVector<double> &ydata,QVector<double> &xdata);

public slots:
    void myworkerfunction(const  QVector<double> &message);
private:

    int res;
};

#endif // DOWORK_H
