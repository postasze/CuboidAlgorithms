#include "randomdatainsertform.h"
#include "ui_randomdatainsertform.h"

RandomDataInsertForm::RandomDataInsertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomDataInsertForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
}

void RandomCuboidsGeneration(CuboidSerie& cuboidSerie, unsigned int numberOfCuboids)
{
    Cuboid *newCuboidPointer;
    unsigned int summaryVolume = 0;
    unsigned short length = 0, width = 0, height = 0, maximalSide = 0;

    maximalSide = max(cuboidSerie.getSphereLength(), cuboidSerie.getSphereWidth());

    srand (time(NULL));

    for(unsigned int i = 0; i < numberOfCuboids; i++)
    {


        length = rand() % maximalSide + 1;
        width = rand() % maximalSide + 1;
        height = rand() % maximalSide + 1;

        newCuboidPointer = new Cuboid(length, width, height);
        cuboidSerie.cuboidListForAlgorithm1->push_front(*newCuboidPointer);

        summaryVolume += length * width * height;
    }

    cuboidSerie.cuboidListForAlgorithm2->assign(cuboidSerie.cuboidListForAlgorithm1->begin(),
                                                 cuboidSerie.cuboidListForAlgorithm1->end());

    cuboidSerie.setInitialSphereHeight(ceil((float)summaryVolume /
        ((float)cuboidSerie.getSphereLength() * (float)cuboidSerie.getSphereWidth())));
    cuboidSerie.setInitialSphereVolume(cuboidSerie.getSphereLength() * cuboidSerie.getSphereWidth()
        * cuboidSerie.getInitialSphereHeight());
}

RandomDataInsertForm::~RandomDataInsertForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

void RandomDataInsertForm::on_buttonBox_accepted()
{
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    CuboidSerie *cuboidSerie = new CuboidSerie();
    unsigned short sphereLength, sphereWidth;
    unsigned int numberOfCuboids;

    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty())
        return ;

    sphereLength = ui->lineEdit_3->text().toUShort();
    sphereWidth = ui->lineEdit_2->text().toUShort();
    numberOfCuboids = ui->lineEdit->text().toUInt();

    cuboidSerie->setSphereLength(sphereLength);
    cuboidSerie->setSphereWidth(sphereWidth);

    RandomCuboidsGeneration(*cuboidSerie, numberOfCuboids);

    cuboidSeries->push_back(*cuboidSerie);

    this->~RandomDataInsertForm();
    this->parentMdi->removeSubWindow();
}

void RandomDataInsertForm::on_buttonBox_rejected()
{
    this->~RandomDataInsertForm();
    this->parentMdi->removeSubWindow();
}

