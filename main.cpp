#include "df_tank_v1.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    df_tank_v1 w;
    w.show();
    return a.exec();
}
