#include "DoWork.h"
#include <QDebug>


DoWork::DoWork(QObject *parent)
    : QObject{parent}
{

   f1=400000000;
   f2=5900000000;
   x_itr=1;
   numSamples = 1000000;    // 1 million samples

}

void DoWork::myworkerfunction(const  QVector<double> &message)
{
    //res = 2;
    qDebug() << "Received Data Size:" << message.size();
    yyDataz=message;


    float x_freq=(f2-f1)/5760;
    int pkt_nbr= yyDataz[1];

    if(pkt_nbr <=89){
        for (int d = 8; d < yyDataz.size(); ++d) {

            float xfreq=f1+(x_freq*x_itr);
            xxDataz.append(xfreq);
            //xxDataz.append(x_itr);
            yyDataz2.append(yyDataz[d]);
            //qDebug() << " Y Value after Process :  "<< qAbs(yyDataz[d]);
            x_itr=x_itr+1;

            xxDataz.reserve(numSamples);
            yyDataz.reserve(numSamples);
            yyDataz2.reserve(numSamples);


        }
        if(pkt_nbr ==89){
            //do_plotting();
            emit workFinished(yyDataz2,xxDataz);

        }
    }

}
