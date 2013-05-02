#include <QApplication>
#include <QTextCodec>
#include "Marco.h"

using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    Marco *m = new Marco;
    m->show();

    return app.exec();
}
