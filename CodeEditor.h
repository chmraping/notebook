#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = 0);
};

#endif // CODEEDITOR_H
