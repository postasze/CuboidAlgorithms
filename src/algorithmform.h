#ifndef ALGORITHMFORM_H
#define ALGORITHMFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "cuboids.h"
#include <sys/time.h>

namespace Ui {
class AlgorithmForm;
}

class AlgorithmForm : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmForm(QWidget *parent = 0);
    ~AlgorithmForm();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_AlgorithmLaunchButton_clicked();

    void on_AcceptButton_clicked();

    void on_CancelButton_clicked();

private:
    MainWindow *parentMdi;
    Ui::AlgorithmForm *ui;
    Algorithm currentAlgorithm;
};

#endif // ALGORITHMFORM_H
