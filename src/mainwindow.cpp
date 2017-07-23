#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithmform.h"
#include "cuboidsdisplayform.h"
#include "dataimportfromfileform.h"
#include "displayinputdataform.h"
#include "graphdisplayform.h"
#include "manualdatainsertform.h"
#include "randomdatainsertform.h"
#include <QMdiSubWindow>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    this->numberOfSubWindows = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow(QWidget *widget)
{
    cout << this->numberOfSubWindows << endl;
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->resize(widget->width(), widget->height());
    window->setWindowModality(Qt::WindowModal);
    window->show();
}

void MainWindow::on_actionManualDataInsert_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new ManualDataInsertForm(this));
}

void MainWindow::on_actionDataImportFromFile_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new DataImportFromFileForm(this));
}

void MainWindow::on_actionRandomDataInsert_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new RandomDataInsertForm(this));
}


void MainWindow::on_actionAlgorithmForm_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    if(this->cuboidManager.getCuboidSeries()->empty())
        return;

    this->numberOfSubWindows = 1;
    loadSubWindow(new AlgorithmForm(this));
}


void MainWindow::on_actionInputDataDisplay_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new DisplayInputDataForm(this));
}

void MainWindow::on_actionGraphDisplay_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new GraphDisplayForm(this));
    ui->mdiArea->activeSubWindow()->showMaximized();
}

void MainWindow::on_actionCuboidsDisplay_triggered()
{
    if(this->numberOfSubWindows == 1)
        return ;

    this->numberOfSubWindows = 1;
    loadSubWindow(new CuboidsDisplayForm(this));
    ui->mdiArea->activeSubWindow()->showMaximized();
}

void MainWindow::setNumberOfSubWindows(int numberOfSubWindows)
{
    this->numberOfSubWindows = numberOfSubWindows;
}

int MainWindow::getNumberOfSubWindows()
{
    return this->numberOfSubWindows;
}

CuboidManager& MainWindow::getCuboidManager()
{
    return this->cuboidManager;
}

void MainWindow::removeSubWindow()
{
    this->ui->mdiArea->closeActiveSubWindow();
}
