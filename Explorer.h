#ifndef EXPLORER_H
#define EXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>


class IExplore {
public:
    virtual void explore(const QString& path) = 0;
    virtual ~IExplore() {}
};

class Explorer
{
private:
    IExplore *p;
public:
    explicit Explorer(IExplore* l) : p(l) {}
    void explore(const QString& path) {
        p->explore(path);
    }
};


#endif //EXPLORER_H
