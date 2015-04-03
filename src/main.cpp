#include "templatematching.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TemplateMatching w;
    w.show();

    return a.exec();
}
