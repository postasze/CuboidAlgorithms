#ifndef MANUALDATAINSERTFORM_H
#define MANUALDATAINSERTFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "cuboids.h"

namespace Ui {
class ManualDataInsertForm;
}

class ManualDataInsertForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManualDataInsertForm(QWidget *parent = 0);
    ~ManualDataInsertForm();

private slots:

    void on_sphereButton_clicked();

    void on_cuboidButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    MainWindow *parentMdi;
    CuboidSerie *cuboidSerie;
    unsigned int summaryVolume;
    bool sphereEntered, cuboidsEntered, dataEntered;
    Ui::ManualDataInsertForm *ui;
};

#endif // MANUALDATAINSERTFORM_H
