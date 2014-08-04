#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include <QDebug>
#include <QMainWindow>
#include "Highlighter.h"
#include <QFileSystemModel>
#include <QMenu>





namespace Ui {
class notebook;
}
class LineNumberArea;
class notebook : public QMainWindow
{
    Q_OBJECT

public:
    explicit notebook(QWidget *parent = 0);
    ~notebook();
    //
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();


private slots:
    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionNew_triggered();
    //代码高亮
    void initContentEditor();
    //文件树形图
    void setupFileTree();
     //初始化文件树形图的右键菜单
    void initMenu();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void open();

private:
    Ui::notebook *ui;
    QMap<QString,QString> contacts;
    QString title;
    QString content;

    Highlighter *highlighter;
    //
    QWidget *lineNumberArea;

    QString path;

    QFileSystemModel *model;
    //右键展开的menu
    QMenu *itemMenu;
    //记录右键文件的位置
    QString itemPath;

};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(notebook *note) : QWidget(note) {
        this->note = note;
    }
//意义不明
//    QSize sizeHint() const {
//        return QSize(codeEditor->lineNumberAreaWidth(), 0);
//    }

protected:
//显示行数
    void paintEvent(QPaintEvent *event) {
        note->lineNumberAreaPaintEvent(event);
    }

private:
    notebook *note;
};

#endif // NOTEBOOK_H
