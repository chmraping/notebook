#ifndef NOTE_H
#define NOTE_H

class note
{
public:
    note();
    setTitle();
    setDate();
    setContent();
    getTitle();
    getDate();
    getContent();
    setNote(QString title,QString date,QString content);
private:
    QString title;
    QString date;
    QString content;
};

#endif // NOTE_H
