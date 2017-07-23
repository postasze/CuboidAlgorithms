#include "manualdatainsertform.h"
#include "mainwindow.h"
#include "ui_manualdatainsertform.h"

using namespace std;

ManualDataInsertForm::ManualDataInsertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualDataInsertForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    sphereEntered = false;
    cuboidsEntered = false;
    dataEntered = false;
    cuboidSerie = new CuboidSerie();
    summaryVolume = 0;
    ui->setupUi(this);
}

ManualDataInsertForm::~ManualDataInsertForm()
{
    if(!dataEntered)
    {
        cuboidSerie->cuboidListForAlgorithm1->clear();
        cuboidSerie->cuboidListForAlgorithm2->clear();
        free(cuboidSerie);
    }
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

void ManualDataInsertForm::on_sphereButton_clicked()
{
    if(ui->sphereLengthLineEdit->text().isEmpty() || ui->sphereWidthLineEdit->text().isEmpty())
        return ;

    cuboidSerie->setSphereLength(ui->sphereLengthLineEdit->text().toUShort());
    cuboidSerie->setSphereWidth(ui->sphereWidthLineEdit->text().toUShort());

    sphereEntered = true;
    ui->sphereButton->setDisabled(true);
}

void ManualDataInsertForm::on_cuboidButton_clicked()
{
    unsigned short length = 0, width = 0, height = 0;
    Cuboid *newCuboidPointer;

    if(ui->cuboidLengthLineEdit->text().isEmpty() || ui->cuboidWidthLineEdit->text().isEmpty() ||
            ui->cuboidHeightLineEdit->text().isEmpty())
        return ;

    length = ui->cuboidLengthLineEdit->text().toUShort();
    width = ui->cuboidWidthLineEdit->text().toUShort();
    height = ui->cuboidHeightLineEdit->text().toUShort();
    newCuboidPointer = new Cuboid(length, width, height);
    cuboidSerie->cuboidListForAlgorithm1->push_front(*newCuboidPointer);

    summaryVolume += length * width * height;
    cuboidsEntered = true;
    ui->cuboidLengthLineEdit->setText("");
    ui->cuboidWidthLineEdit->setText("");
    ui->cuboidHeightLineEdit->setText("");
}

void ManualDataInsertForm::on_buttonBox_accepted()
{
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();

    if(!sphereEntered || !cuboidsEntered)
        return ;

    cuboidSerie->cuboidListForAlgorithm2->assign(cuboidSerie->cuboidListForAlgorithm1->begin(),
                                                 cuboidSerie->cuboidListForAlgorithm1->end());

    cuboidSerie->setInitialSphereHeight(ceil((float)summaryVolume /
        ((float)cuboidSerie->getSphereLength() * (float)cuboidSerie->getSphereWidth())));
    cuboidSerie->setInitialSphereVolume(cuboidSerie->getSphereLength() * cuboidSerie->getSphereWidth()
        * cuboidSerie->getInitialSphereHeight());

    cuboidSeries->push_back(*cuboidSerie);

    dataEntered = true;

    this->~ManualDataInsertForm();
    this->parentMdi->removeSubWindow();
}

void ManualDataInsertForm::on_buttonBox_rejected()
{
    this->~ManualDataInsertForm();
    this->parentMdi->removeSubWindow();
}
