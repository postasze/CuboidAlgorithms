#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QString y READ getY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString length READ getLength WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(QString width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QString hashColor READ getColor WRITE setColor NOTIFY colorChanged)

public:
    DataObject(QObject *parent=0);
    DataObject(QString x, QString y, QString length,
               QString width, QString hashColor, QObject *parent=0);

    QString getX() const;
    void setX(const QString x);

    QString getY() const;
    void setY(const QString y);

    QString getLength() const;
    void setLength(const QString length);

    QString getWidth() const;
    void setWidth(const QString width);

    QString getColor() const;
    void setColor(const QString &color);

signals:
    void xChanged();
    void yChanged();
    void lengthChanged();
    void widthChanged();
    void colorChanged();

private:
    QString x, y, length, width;
    QString hashColor;
};

#endif // DATAOBJECT_H
