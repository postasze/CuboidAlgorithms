#ifndef DISPLAYINPUTDATAFORM_H
#define DISPLAYINPUTDATAFORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class DisplayInputDataForm;
}

class DisplayInputDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayInputDataForm(QWidget *parent = 0);
    ~DisplayInputDataForm();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    MainWindow *parentMdi;
    Ui::DisplayInputDataForm *ui;

    enum Column
    {
        LENGTH, WIDTH, HEIGHT
    };
};

#endif // DISPLAYINPUTDATAFORM_H
