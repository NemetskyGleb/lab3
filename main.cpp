#include <iostream>
#include "Explorer.h"
#include "GroupByFolders.h"
#include "GroupByTypes.h"

int main()
{
    IExplore* gpf = new GroupByFolders();
    IExplore* gpt = new GroupByTypes();
    Explorer* e = new Explorer(gpf);
    e->explore("C:/QtProjects/lab3/testFolder/");
    e->setStrategy(gpt);
    e->explore("C:/QtProjects/lab3/testFolder/");
    delete gpf;
    delete gpt;
    delete e;
    return 0;
}
