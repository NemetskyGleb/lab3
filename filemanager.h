#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include "Data.h"

namespace Ui {
    class FileManager;
}

class QFileSystemModel;
class Explorer;

class FileManager : public QWidget
{
    Q_OBJECT

public:
    explicit FileManager(QWidget *parent = nullptr);
    ~FileManager();
enum class GroupedBy {
    Folders = 1,
    Types
};

private:
    Ui::FileManager *ui;
    QFileSystemModel* modelDir;
    Explorer* explorer;
    QList<Data> data;
    GroupedBy grouping = GroupedBy::Folders;
};

#endif // FILEMANAGER_H
