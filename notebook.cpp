#include "notebook.h"
#include "ui_notebook.h"
#include <QTime>
#include <QDate>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QFileSystemModel>

notebook::notebook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notebook)
{
    ui->setupUi(this);
    //文件树形图
    path = QDir::currentPath();
    setupFileTree();
    //初始化文件树形图的右键菜单
    initMenu();

    initContentEditor();

    QDate date = QDate::currentDate();
    qDebug()<<date;
    ui->dateEdit->setDate(date);



}

notebook::~notebook()
{
    delete ui;
}

void notebook::initMenu()
{

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);//设置这个才能添加右键菜单
    itemMenu = new QMenu(this);
    QAction *open;
    open = new QAction(tr("打开"),this);
    itemMenu->addAction(open);
    QAction *del;
    del = new QAction(tr("删除"),this);
    itemMenu->addAction(del);

    connect(open, SIGNAL(triggered()), this, SLOT(open()));

}
void notebook::open()
{
    QFile file(itemPath);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,tr("载入失败"),tr("该文件正被别的文件使用"));
        return;
    }
    QDataStream in(&file);
    in >> contacts;
    ui->titleEdit->setText(contacts["title"]);
    ui->contentEdit->setText(contacts["content"]);
    QDate date = QDate::fromString(contacts["date"],"yyyy/MM/dd");
    ui->dateEdit->setDate(date);

    path = itemPath;
    setupFileTree();


}
void notebook::setupFileTree()
{
    model = new QFileSystemModel();

    qDebug() << path;
    model->setRootPath(path);
    ui->treeView->setModel(model);
    QModelIndex index = model->index(path);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    //展开到当前目录
    ui->treeView->expand(index);

    //滚动到当前目录
    ui->treeView->scrollTo(index);
    //设置列宽
    ui->treeView->resizeColumnToContents(0);




}
void notebook::initContentEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->contentEdit->setFont(font);

    highlighter = new Highlighter(ui->contentEdit->document());

}



void notebook::on_actionSave_triggered()
{
       QString date = ui->dateEdit->text();
       title = ui->titleEdit->text();
       content = ui->contentEdit->toPlainText();

       if(title==""){
           QMessageBox::information(this,tr("保存失败"),tr("%1不能为空！").arg(title));
           return;
       }
       contacts.insert("title",title);
       contacts.insert("date",date);
       contacts.insert("content",content);
       QString fileName =QFileDialog::getSaveFileName(this,tr("保存文件"),"",tr("NB files (*.nb);;All Files(*)"));
       qDebug()<<fileName;
       if(fileName=="")return;
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly)){
           QMessageBox::information(this,tr("b保存失败"),tr("该文件正被别的文件使用"));
           return;
       }
       QDataStream out(&file);
       out << contacts;

       path = fileName;
       setupFileTree();


}

void notebook::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("载入文件"),"",tr("NB files (*.nb);;All Files(*)"));
    if(fileName=="")return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,tr("载入失败"),tr("该文件正被别的文件使用"));
//        QMessageBox::information(this,tr("Failed"),tr("File is under using by other process!"));
        return;
    }
    QDataStream in(&file);
    in >> contacts;
    ui->titleEdit->setText(contacts["title"]);
    ui->contentEdit->setText(contacts["content"]);
    QDate date = QDate::fromString(contacts["date"],"yyyy/MM/dd");
    ui->dateEdit->setDate(date);

    path = fileName;
    setupFileTree();
}

void notebook::on_actionCopy_triggered()
{
    ui->contentEdit->copy();
}

void notebook::on_actionPaste_triggered()
{
    ui->contentEdit->paste();
}

void notebook::on_actionRedo_triggered()
{
    ui->contentEdit->redo();
}

void notebook::on_actionUndo_triggered()
{
    ui->contentEdit->undo();
}

void notebook::on_actionNew_triggered()
{

}

void notebook::on_treeView_doubleClicked(const QModelIndex &index)
{
   QString fileName = model->filePath(index);
   QFile file(fileName);
   if(!file.open(QIODevice::ReadOnly)){
       return;
   }
   QDataStream in(&file);
   in >> contacts;

   ui->titleEdit->setText(contacts["title"]);
   ui->contentEdit->setText(contacts["content"]);
   QDate date = QDate::fromString(contacts["date"],"yyyy/MM/dd");

   ui->dateEdit->setDate(date);

   path = fileName;
   setupFileTree();

}

void notebook::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    itemPath = model->filePath(index);
    itemMenu->exec(QCursor::pos());
}
