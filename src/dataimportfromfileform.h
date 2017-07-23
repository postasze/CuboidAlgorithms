#ifndef DATAIMPORTFROMFILEFORM_H
#define DATAIMPORTFROMFILEFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "cuboids.h"

namespace Ui {
class DataImportFromFileForm;
}

class DataImportFromFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataImportFromFileForm(QWidget *parent = 0);
    ~DataImportFromFileForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    MainWindow *parentMdi;
    Ui::DataImportFromFileForm *ui;
};

#endif // DATAIMPORTFROMFILEFORM_H
