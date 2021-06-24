#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QItemSelection>
#include "Data.h"
#include "FileBrowserModel.h"
#include "FileBrowserObserver.h"
#include "Explorer.h"
#include <memory>


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
    void displayTableModel();
    ~FileManager();


protected slots:
    void selectionGroup(int index);
    void selectionDisplay(int index);
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    Ui::FileManager *ui;
    QFileSystemModel* dirModel;
    std::shared_ptr<FileBrowserModel> fmodel;


    // стратегии
    IExplore* FolderGrouping;
    IExplore* TypesGrouping;
    IExplore* groupingStrategy;

      // адаптеры
    FileBrowserObserver* FileBrowserView;
    FileBrowserObserver* list_view_adapter;
    FileBrowserObserver* pie_chart;
    FileBrowserObserver* bar_chart;

    QString path;
};

#endif // FILEMANAGER_H
