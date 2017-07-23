#include "displayinputdataform.h"
#include "ui_displayinputdataform.h"
#include "cuboids.h"

DisplayInputDataForm::DisplayInputDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayInputDataForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
    QStringList headers;
    QString comboBoxItem;
    unsigned short sphereLength, sphereWidth;
    headers << "Długość prostopadłościanu" << "Szerokość prostopadłościanu"
           << "Wysokość prostopadłościanu";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 210);
    ui->tableWidget->setColumnWidth(2, 210);

    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    cout << "rozmiar " << cuboidSeries->size() << endl;
    for(unsigned int i = 0; i < cuboidSeries->size(); i++)
    {
        sphereLength = (*cuboidSeries)[i].getSphereLength();
        sphereWidth = (*cuboidSeries)[i].getSphereWidth();

        comboBoxItem += "Seria: " + QString::number(i+1) + ", ilość prostopadłościanów: " +
            QString::number((*cuboidSeries)[i].cuboidListForAlgorithm1->size()) + ", długość obszaru: " +
            QString::number(sphereLength) + ", szerokość obszaru: " + QString::number(sphereWidth);
        ui->comboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
}

DisplayInputDataForm::~DisplayInputDataForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

void DisplayInputDataForm::on_comboBox_currentIndexChanged(int i)
{
    ui->tableWidget->clear();
    int number = 1;
    QStringList headers;
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    unsigned short sphereLength, sphereWidth, initialSphereHeight;
    unsigned short finalSphereHeightForAlgorithm1, finalSphereHeightForAlgorithm2, finalSphereHeightForAlgorithm3;
    unsigned int initialSphereVolume;
    unsigned long computationTimeforAlgorithm1, computationTimeforAlgorithm2, computationTimeforAlgorithm3;

    sphereLength = (*cuboidSeries)[i].getSphereLength();
    sphereWidth = (*cuboidSeries)[i].getSphereWidth();
    initialSphereHeight = (*cuboidSeries)[i].getInitialSphereHeight();
    initialSphereVolume = (*cuboidSeries)[i].getInitialSphereVolume();
    finalSphereHeightForAlgorithm1 = (*cuboidSeries)[i].getFinalSphereHeight(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY);
    finalSphereHeightForAlgorithm2 = (*cuboidSeries)[i].getFinalSphereHeight(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY);
    finalSphereHeightForAlgorithm3 = (*cuboidSeries)[i].getFinalSphereHeight(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS);
    computationTimeforAlgorithm1 = (*cuboidSeries)[i].getComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY);
    computationTimeforAlgorithm2 = (*cuboidSeries)[i].getComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY);
    computationTimeforAlgorithm3 = (*cuboidSeries)[i].getComputationTime(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS);

    ui->lineEdit->setText(QString::number(sphereLength));
    ui->lineEdit_2->setText(QString::number(sphereWidth));
    ui->lineEdit_3->setText(QString::number(initialSphereHeight));
    ui->lineEdit_4->setText(QString::number(initialSphereVolume));

    if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY) == true)
        ui->finalSphereHeightForAlgorithm1LineEdit->setText("");
    else
        ui->finalSphereHeightForAlgorithm1LineEdit->setText(QString::number(finalSphereHeightForAlgorithm1));
    if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY) == true)
        ui->finalSphereHeightForAlgorithm2LineEdit->setText("");
    else
        ui->finalSphereHeightForAlgorithm2LineEdit->setText(QString::number(finalSphereHeightForAlgorithm2));
    if((*cuboidSeries)[i].getComputedBy(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS) == true)
        ui->finalSphereHeightForAlgorithm3LineEdit->setText("");
    else
        ui->finalSphereHeightForAlgorithm3LineEdit->setText(QString::number(finalSphereHeightForAlgorithm3));

    if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY) == true)
        ui->timeForAlgorithm1LineEdit->setText(QString::number(computationTimeforAlgorithm1));
    else
        ui->timeForAlgorithm1LineEdit->setText("");
    if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY) == true)
        ui->timeForAlgorithm2LineEdit->setText(QString::number(computationTimeforAlgorithm2));
    else
        ui->timeForAlgorithm2LineEdit->setText("");
    if((*cuboidSeries)[i].getComputedBy(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS) == true)
        ui->timeForAlgorithm3LineEdit->setText(QString::number(computationTimeforAlgorithm3));
    else
        ui->timeForAlgorithm3LineEdit->setText("");

    headers << "Długość prostopadłościanu" << "Szerokość prostopadłościanu"
           << "Wysokość prostopadłościanu";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    list<Cuboid>::iterator iter = (*cuboidSeries)[i].cuboidListForAlgorithm1->begin();
    while (iter != (*cuboidSeries)[i].cuboidListForAlgorithm1->end())
    {
        cout << iter->getX() << endl;
        cout << iter->getY() << endl;
        cout << iter->getZ() << endl;
        cout << endl;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(number - 1, LENGTH, new QTableWidgetItem(QString::number(iter->getLength())));
        ui->tableWidget->setItem(number - 1, WIDTH, new QTableWidgetItem(QString::number(iter->getWidth())));
        ui->tableWidget->setItem(number - 1, HEIGHT, new QTableWidgetItem(QString::number(iter->getHeight())));
        number++;
        iter++;
    }
}
