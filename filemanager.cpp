#include "filemanager.h"
#include "ui_filemanager.h"
#include <QFileSystemModel>
#include "Explorer.h"
#include "GroupByTypes.h"
#include "GroupByFolders.h"
#include <QDebug>
#include <memory>

FileManager::FileManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManager)
{
    ui->setupUi(this);
    modelDir = new QFileSystemModel(this);
    IExplore* gtype = new GroupByFolders;
    explorer = new Explorer(gtype);

    this->setMinimumSize(1200, 500);

    modelDir->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    modelDir->setRootPath(QDir::currentPath());
    ui->treeView->setModel(modelDir);
}

FileManager::~FileManager()
{
    delete ui;
    delete modelDir;
    delete explorer;
}
