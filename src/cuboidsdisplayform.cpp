#include "cuboidsdisplayform.h"
#include "ui_cuboidsdisplayform.h"
#include <QQmlContext>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QObject>
#include <QDebug>

CuboidsDisplayForm::CuboidsDisplayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CuboidsDisplayForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
    QString comboBoxItem;
    unsigned short sphereLength, sphereWidth;
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY;

    ui->comboBox_2->addItem("Algorytm \"Jak największy w jak najmniejszym obszarze\" z tablicą zajętości");
    ui->comboBox_2->addItem("Algorytm \"Jak największy w jak najmniejszym obszarze\" bez tablicy zajętości");
    ui->comboBox_2->addItem("Algorytm \"Jak najbardziej płaski w jak najbardziej zewnętrznej części\"");

    ui->lineEdit->setText("0");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setText("0");
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setText("0");
    ui->lineEdit_3->setReadOnly(true);

    //ui->comboBox->clear();
    for(unsigned int i = 0; i < cuboidSeries->size(); i++)
    {
        //if((*cuboidSeries)[i].getComputedBy(currentAlgorithm) == false)
        //    continue;

        sphereLength = (*cuboidSeries)[i].getSphereLength();
        sphereWidth = (*cuboidSeries)[i].getSphereWidth();

        comboBoxItem += "Seria: " + QString::number(i+1) + ", ilość prostopadłościanów: " +
            QString::number((*cuboidSeries)[i].cuboidListForAlgorithm1->size()) + ", długość obszaru: " +
            QString::number(sphereLength) + ", szerokość obszaru: " + QString::number(sphereWidth);
        ui->comboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
}

CuboidsDisplayForm::~CuboidsDisplayForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

void CuboidsDisplayForm::on_comboBox_currentIndexChanged(int i)
{
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    this->cuboidSeriePointer = &(*cuboidSeries)[i];
    QQmlContext *context1 = ui->quickWidget->rootContext();
    QQmlContext *context2 = ui->quickWidget_2->rootContext();
    QQmlContext *context3 = ui->quickWidget_3->rootContext();
    unsigned short sphereLength = cuboidSeriePointer->getSphereLength();
    unsigned short sphereWidth = cuboidSeriePointer->getSphereWidth();
    unsigned short sphereHeight = cuboidSeriePointer->getFinalSphereHeight(currentAlgorithm);
    QList<QObject*> *layerDataList = new QList<QObject*>();
    QList<QObject*> *cuboidDataList = new QList<QObject*>();

    ui->lineEdit->setText(QString::number(0));
    ui->horizontalSlider->setValue(0);
    ui->lineEdit_2->setText(QString::number(0));
    ui->horizontalSlider_2->setValue(0);
    ui->lineEdit_3->setText(QString::number(0));
    ui->horizontalSlider_3->setValue(0);

    if(cuboidSeriePointer->getComputedBy(currentAlgorithm) == false)
    {
        context1->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context1->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        context2->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context2->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        context3->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context3->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        return;
    }

    for(int i = 0; i < sphereWidth; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context1->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context1->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
    layerDataList->clear();
    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context2->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context2->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
    layerDataList->clear();
    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereWidth; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context3->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context3->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
}

void CuboidsDisplayForm::on_horizontalSlider_valueChanged(int value)
{
    QQmlContext *context = ui->quickWidget->rootContext();
    unsigned short sphereLength = cuboidSeriePointer->getSphereLength();
    unsigned short sphereWidth = cuboidSeriePointer->getSphereWidth();
    unsigned short sphereHeight = cuboidSeriePointer->getFinalSphereHeight(currentAlgorithm);
    double degree = (double) sphereLength / 100.0;
    unsigned short x = floor(degree * value);
    list<Cuboid>::iterator iter, end;
    QList<QObject*> *cuboidDataList = new QList<QObject*>();
    QList<QObject*> *layerDataList = new QList<QObject*>();

    ui->lineEdit->setText(QString::number(x));

    if(currentAlgorithm == MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS)
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm2->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm2->end();
    }
    else
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm1->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm1->end();
    }

    while (iter != end)
    {        
        if(iter->getX() <= x && x < iter->getX() + iter->getLength())
        {
            cuboidDataList->append(new DataObject(QString::number(iter->getY()), QString::number(sphereHeight - iter->getZ() - iter->getHeight()),
                   QString::number(iter->getWidth()), QString::number(iter->getHeight()), QString::number(iter->getColor())));
        }
        iter++;
    }

    for(int i = 0; i < sphereWidth; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "transparent"));

    context->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
}

void CuboidsDisplayForm::on_horizontalSlider_2_valueChanged(int value)
{
    QQmlContext *context = ui->quickWidget_2->rootContext();
    unsigned short sphereLength = cuboidSeriePointer->getSphereLength();
    unsigned short sphereWidth = cuboidSeriePointer->getSphereWidth();
    unsigned short sphereHeight = cuboidSeriePointer->getFinalSphereHeight(currentAlgorithm);
    double degree = (double) sphereWidth / 100.0;
    unsigned short y = floor(degree * value);
    list<Cuboid>::iterator iter, end;
    QList<QObject*> *cuboidDataList = new QList<QObject*>();
    QList<QObject*> *layerDataList = new QList<QObject*>();

    ui->lineEdit_2->setText(QString::number(y));

    if(currentAlgorithm == MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS)
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm2->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm2->end();
    }
    else
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm1->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm1->end();
    }

    while (iter != end)
    {
        if(iter->getY() <= y && y < iter->getY() + iter->getWidth())
        {
            cuboidDataList->append(new DataObject(QString::number(iter->getX()), QString::number(sphereHeight - iter->getZ() - iter->getHeight()),
                   QString::number(iter->getLength()), QString::number(iter->getHeight()), QString::number(iter->getColor())));
        }
        iter++;
    }

    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "transparent"));

    context->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
}

void CuboidsDisplayForm::on_horizontalSlider_3_valueChanged(int value)
{
    QQmlContext *context = ui->quickWidget_3->rootContext();
    unsigned short sphereLength = cuboidSeriePointer->getSphereLength();
    unsigned short sphereWidth = cuboidSeriePointer->getSphereWidth();
    unsigned short sphereHeight = cuboidSeriePointer->getFinalSphereHeight(currentAlgorithm);
    double degree = (double) sphereHeight / 100.0;
    unsigned short z = floor(degree * value);
    list<Cuboid>::iterator iter, end;
    QList<QObject*> *cuboidDataList = new QList<QObject*>();
    QList<QObject*> *layerDataList = new QList<QObject*>();

    ui->lineEdit_3->setText(QString::number(z));

    if(currentAlgorithm == MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS)
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm2->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm2->end();
    }
    else
    {
        iter = cuboidSeriePointer->cuboidListForAlgorithm1->begin();
        end = cuboidSeriePointer->cuboidListForAlgorithm1->end();
    }

    while (iter != end)
    {
        if(iter->getZ() <= z && z < iter->getZ() + iter->getHeight())
        {
            cuboidDataList->append(new DataObject(QString::number(iter->getX()), QString::number(sphereWidth - iter->getY() - iter->getWidth()),
                   QString::number(iter->getLength()), QString::number(iter->getWidth()), QString::number(iter->getColor())));
        }
        iter++;
    }

    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereWidth; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "transparent"));

    context->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
}

void CuboidsDisplayForm::on_comboBox_2_currentIndexChanged(int index)
{
    unsigned short sphereLength, sphereWidth, sphereHeight;
    QQmlContext *context1 = ui->quickWidget->rootContext();
    QQmlContext *context2 = ui->quickWidget_2->rootContext();
    QQmlContext *context3 = ui->quickWidget_3->rootContext();
    QList<QObject*> *layerDataList = new QList<QObject*>();
    QList<QObject*> *cuboidDataList = new QList<QObject*>();

    switch(index)
    {
        case 0:
            currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY;
            break;
        case 1:
            currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY;
            break;
        case 2:
            currentAlgorithm = MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS;
            break;
    }
    if(cuboidSeriePointer == nullptr)
        return ;

    sphereLength = cuboidSeriePointer->getSphereLength();
    sphereWidth = cuboidSeriePointer->getSphereWidth();
    sphereHeight = cuboidSeriePointer->getFinalSphereHeight(currentAlgorithm);

    ui->lineEdit->setText(QString::number(0));
    ui->horizontalSlider->setValue(0);
    ui->lineEdit_2->setText(QString::number(0));
    ui->horizontalSlider_2->setValue(0);
    ui->lineEdit_3->setText(QString::number(0));
    ui->horizontalSlider_3->setValue(0);

    if(cuboidSeriePointer->getComputedBy(currentAlgorithm) == false)
    {
        context1->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context1->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        context2->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context2->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        context3->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
        context3->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
        return;
    }
    for(int i = 0; i < sphereWidth; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context1->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context1->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
    layerDataList->clear();
    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereHeight; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context2->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context2->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
    layerDataList->clear();
    for(int i = 0; i < sphereLength; i++)
        for(int j = 0; j < sphereWidth; j++)
            layerDataList->append(new DataObject(QString::number(i), QString::number(j),
                                             QString::number(1), QString::number(1), "white"));
    context3->setContextProperty("layerModel", QVariant::fromValue(*layerDataList));
    context3->setContextProperty("cuboidModel", QVariant::fromValue(*cuboidDataList));
    layerDataList->clear();
}
