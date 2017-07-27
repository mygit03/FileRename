#include "filerename.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRename w;
    w.show();

    return a.exec();
}
