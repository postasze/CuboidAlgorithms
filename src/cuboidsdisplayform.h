#ifndef CUBOIDSDISPLAYFORM_H
#define CUBOIDSDISPLAYFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "dataobject.h"

namespace Ui {
class CuboidsDisplayForm;
}

class CuboidsDisplayForm : public QWidget
{
    Q_OBJECT

public:
    explicit CuboidsDisplayForm(QWidget *parent = 0);
    ~CuboidsDisplayForm();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    MainWindow *parentMdi;
    Ui::CuboidsDisplayForm *ui;
    QList<DataObject*> *dataList;
    CuboidSerie *cuboidSeriePointer;
    Algorithm currentAlgorithm;
};

#endif // CUBOIDSDISPLAYFORM_H
