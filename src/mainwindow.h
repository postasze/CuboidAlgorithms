#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cuboids.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setNumberOfSubWindows(int number);
    int getNumberOfSubWindows();
    CuboidManager& getCuboidManager();
    void removeSubWindow();

private slots:

    void on_actionManualDataInsert_triggered();

    void on_actionDataImportFromFile_triggered();

    void on_actionRandomDataInsert_triggered();

    void on_actionAlgorithmForm_triggered();

    void on_actionInputDataDisplay_triggered();

    void on_actionGraphDisplay_triggered();

    void on_actionCuboidsDisplay_triggered();

private:
    Ui::MainWindow *ui;
    CuboidManager cuboidManager;
    int numberOfSubWindows;
    void loadSubWindow(QWidget *widget);
};

#endif // MAINWINDOW_H
