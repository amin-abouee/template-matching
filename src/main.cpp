#include "templatematchingui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TemplateMatchingUI w;
    w.show();

    return a.exec();
}
