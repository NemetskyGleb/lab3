#include <iostream>
#include "Explorer.h"
#include "GroupByFolders.h"
#include "GroupByTypes.h"
#include "filemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    IExplore* gpf = new GroupByFolders();
//    IExplore* gpt = new GroupByTypes();
//    Explorer* e = new Explorer(gpt);
//    e->setStrategy(gpt);
//    e->explore("C:/QtProjects/lab3/empty");
//    delete gpf;
//    delete gpt;
//    delete e;

    FileManager f;
    f.show();

    return a.exec();
}
