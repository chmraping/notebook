#include "blog.h"

blog::blog()
{
}

blog::blog(QString title, QDate date, QTextDocument content)
{
    this->title = title;
    this->date = date;
    this->content = content;
}

QString blog::getTile()
{
    return this->title;
}

QDate blog::getDate()
{
    return this->date;
}

QTextDocument blog::getContent()
{
    return this->content;
}

