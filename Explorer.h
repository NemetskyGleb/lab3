#ifndef EXPLORER_H
#define EXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include "Data.h"
#include "FileBrowserObserver.h"

class IExplore {
public:
    virtual void explore(const QString& path) = 0;
    virtual ~IExplore() {}

    // привязка наблюдателя
    void Attach(FileBrowserObserver* observer) {
        if (observer)
            observer_ = observer;
    }

    // событие окончания формирования данных
    void OnFinish(const std::unique_ptr<QList<Data> >& data) const {
        observer_->UpdateDisplay(data);
    }

private:
    FileBrowserObserver* observer_;
};

class Explorer
{
private:
    IExplore *p = nullptr;
public:
    Explorer() = default;
    explicit Explorer(IExplore* l) : p(l) {}
    void explore(const QString& path) {
        p->explore(path);
    }
    void setStrategy(IExplore* strategy) {
        if (p)
            delete p;
        p = strategy;
    }

    ~Explorer() { if (p) delete p; }
};

namespace Common {
    inline qint64 getTotalSize(const QString& path)
    {
        qint64 totalSize = 0;
        QDir dir(path);
        for (const auto& it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type | QDir::Size))
                if (it.isDir() && !it.isSymLink()) {
                    totalSize += getTotalSize(it.absoluteFilePath());
                } else totalSize += it.size();
        return totalSize;
    }
    inline qint64 sumSizes(const QMap<QString, qint64> Sizes)
    {
        qint64 totalSize = 0;
        foreach(qint64 size, Sizes.values())
            totalSize += size;
        return totalSize;
    }
}

#endif //EXPLORER_H
