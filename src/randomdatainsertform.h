#ifndef RANDOMDATAINSERTFORM_H
#define RANDOMDATAINSERTFORM_H

#include <QWidget>
#include "mainwindow.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>

namespace Ui {
class RandomDataInsertForm;
}

class RandomDataInsertForm : public QWidget
{
    Q_OBJECT

public:
    explicit RandomDataInsertForm(QWidget *parent = 0);
    ~RandomDataInsertForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    MainWindow *parentMdi;
    Ui::RandomDataInsertForm *ui;
};

#endif // RANDOMDATAINSERTFORM_H
