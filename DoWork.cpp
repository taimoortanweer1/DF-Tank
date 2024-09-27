#include "DoWork.h"
#include <QDebug>
#include <QRandomGenerator>


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
    random_data.reserve(data_size);
    // Generate random double values less than 5
    for (int i = 0; i < data_size; ++i) {
        double random_value = QRandomGenerator::global()->bounded(5.0);
        random_data.append(random_value);
    }

    qDebug() << "Received Data Size:" << message.size();
    yyDataz=message;

    for (int i=8; i< yyDataz.size();i+=2){
        dB_list.append(yyDataz[i]);
        index_list.append(yyDataz[i+1]);
    }

    for(int i=0; i<index_list.size();++i){
        random_data[index_list[i]]=dB_list[i];
    }

    float x_freq=(f2-f1)/5760;
    //int pkt_nbr= yyDataz[1];

    //if(pkt_nbr <=89){
        for (int d = 8; d < random_data.size(); ++d) {

            float xfreq=f1+(x_freq*x_itr);
            xxDataz.append(xfreq);
            //xxDataz.append(x_itr);
            yyDataz2.append(random_data[d]);
            //qDebug() << " Y Value after Process :  "<< qAbs(yyDataz[d]);
            x_itr=x_itr+1;

            xxDataz.reserve(numSamples);
            yyDataz.reserve(numSamples);
            yyDataz2.reserve(numSamples);


        //}
        //if(pkt_nbr ==89){
            //do_plotting();
            emit workFinished(yyDataz2,xxDataz);

        //}
    }

}
