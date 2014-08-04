#ifndef BLOG_H
#define BLOG_H
#include <QTextDocument>
class blog
{
public:
    blog();
    blog(QString title,QDate date,QTextDocument content);
    QString getTile();
    QDate getDate();
    QTextDocument getContent();

private:
    QString title;
    QDate *date;
    QTextDocument content;
};

#endif // BLOG_H
