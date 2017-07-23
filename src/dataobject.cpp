#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

DataObject::DataObject(QString x, QString y, QString length, QString width, QString hashColor, QObject *parent)
    : QObject(parent), x(x), y(y), length(length), width(width), hashColor(hashColor)
{
}

QString DataObject::getX() const
{
    return x;
}
void DataObject::setX(const QString x)
{
    this->x = x;
}

QString DataObject::getY() const
{
    return y;
}
void DataObject::setY(const QString y)
{
    this->y = y;
}

QString DataObject::getLength() const
{
    return length;
}
void DataObject::setLength(const QString length)
{
    this->length = length;
}

QString DataObject::getWidth() const
{
    return width;
}
void DataObject::setWidth(const QString width)
{
    this->width = width;
}

QString DataObject::getColor() const
{
    return hashColor;
}

void DataObject::setColor(const QString &hashColor)
{
    this->hashColor = hashColor;
}
