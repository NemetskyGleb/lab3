#include <iostream>
#include "Explorer.h"
#include "GroupByFolders.h"
#include "GroupByTypes.h"

int main()
{
    IExplore* gpf = new GroupByFolders();
    Explorer* e = new Explorer(gpf);
    e->explore("C:/QtProjects/lab3/testFolder/");
    delete gpf;
    delete e;
    return 0;
}
