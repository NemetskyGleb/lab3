#include <iostream>
#include "Explorer.h"
#include "GroupByFolders.h"
#include "GroupByTypes.h"
#include "filemanager.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileManager f;
    f.show();

    return a.exec();
}
