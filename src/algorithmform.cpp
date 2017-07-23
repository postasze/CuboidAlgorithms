#include "algorithmform.h"
#include "ui_algorithmform.h"

AlgorithmForm::AlgorithmForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
    currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY;
    ui->progressBar->setValue(0);
    ui->AcceptButton->setDisabled(true);
    ui->comboBox->addItem("Algorytm \"Jak największy w jak najmniejszym obszarze\" z tablicą zajętości");
    ui->comboBox->addItem("Algorytm \"Jak największy w jak najmniejszym obszarze\" bez tablicy zajętości");
    ui->comboBox->addItem("Algorytm \"Jak najbardziej płaski w jak najbardziej zewnętrznej części\"");
}

AlgorithmForm::~AlgorithmForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

void AlgorithmForm::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
         currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY;
         break;
        case 1:
         currentAlgorithm = LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY;
         break;
        case 2:
         currentAlgorithm = MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS;
         break;
    }
}

void AlgorithmForm::on_AlgorithmLaunchButton_clicked()
{
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    CuboidalSphere *cuboidalSphere = nullptr;
    Layer *layer = nullptr;
    unsigned short resultHeight = 0;
    unsigned long computationTimeStart = 0, computationTimeEnd = 0, timeDuration = 0;
    struct timeval timeValue;

    ui->progressBar->setValue(0);

    switch(currentAlgorithm)
    {
       case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
        for(unsigned int i = 0; i < cuboidSeries->size(); i++)
        {
            if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY) == true)
                continue;

            (*cuboidSeries)[i].setComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY, true);
            cuboidalSphere = new CuboidalSphere((*cuboidSeries)[i].getSphereLength(),
                 (*cuboidSeries)[i].getSphereWidth(), (*cuboidSeries)[i].getInitialSphereHeight(), true);
            clearCuboids(*(*cuboidSeries)[i].cuboidListForAlgorithm1);

            gettimeofday(&timeValue, NULL);
            computationTimeStart = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            resultHeight = Algorithm_1(*(*cuboidSeries)[i].cuboidListForAlgorithm1, cuboidalSphere);
            gettimeofday(&timeValue, NULL);
            computationTimeEnd = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            timeDuration = computationTimeEnd - computationTimeStart;
            (*cuboidSeries)[i].setComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY, timeDuration);

            (*cuboidSeries)[i].setFinalSphereHeight(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY, resultHeight);
            (*cuboidSeries)[i].setFinalSphereVolume(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY,
                (*cuboidSeries)[i].getSphereLength() * (*cuboidSeries)[i].getSphereWidth() * resultHeight);
            //cuboidalSphere->~CuboidalSphere();
            //free(cuboidalSphere);
            ui->progressBar->setValue(100*(i+1)/cuboidSeries->size());
        }
        ui->progressBar->setValue(100);
        ui->AcceptButton->setEnabled(true);
        break;
       case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
        for(unsigned int i = 0; i < cuboidSeries->size(); i++)
        {
            if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY) == true)
                continue;

            (*cuboidSeries)[i].setComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY, true);
            cuboidalSphere = new CuboidalSphere((*cuboidSeries)[i].getSphereLength(),
                 (*cuboidSeries)[i].getSphereWidth(), (*cuboidSeries)[i].getInitialSphereHeight(), false);
            clearCuboids(*(*cuboidSeries)[i].cuboidListForAlgorithm1);

            gettimeofday(&timeValue, NULL);
            computationTimeStart = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            resultHeight = Algorithm_1(*(*cuboidSeries)[i].cuboidListForAlgorithm1, cuboidalSphere);
            gettimeofday(&timeValue, NULL);
            computationTimeEnd = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            timeDuration = computationTimeEnd - computationTimeStart;
            (*cuboidSeries)[i].setComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY, timeDuration);

            (*cuboidSeries)[i].setFinalSphereHeight(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY, resultHeight);
            (*cuboidSeries)[i].setFinalSphereVolume(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY,
                (*cuboidSeries)[i].getSphereLength() * (*cuboidSeries)[i].getSphereWidth() * resultHeight);
            cuboidalSphere->~CuboidalSphere();
            free(cuboidalSphere);
            ui->progressBar->setValue(100*(i+1)/cuboidSeries->size());
        }
        ui->progressBar->setValue(100);
        ui->AcceptButton->setEnabled(true);
        break;
       case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
        for(unsigned int i = 0; i < cuboidSeries->size(); i++)
        {
            if((*cuboidSeries)[i].getComputedBy(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS) == true)
                continue;

            (*cuboidSeries)[i].setComputedBy(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS, true);
            layer = new Layer((*cuboidSeries)[i].getSphereLength(), (*cuboidSeries)[i].getSphereWidth());

            gettimeofday(&timeValue, NULL);
            computationTimeStart = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            resultHeight = Algorithm_2(*(*cuboidSeries)[i].cuboidListForAlgorithm2, *layer);
            gettimeofday(&timeValue, NULL);
            computationTimeEnd = 1000000*timeValue.tv_sec + timeValue.tv_usec;
            timeDuration = computationTimeEnd - computationTimeStart;
            (*cuboidSeries)[i].setComputationTime(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS, timeDuration);

            (*cuboidSeries)[i].setFinalSphereHeight(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS, resultHeight);
            (*cuboidSeries)[i].setFinalSphereVolume(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS,
                (*cuboidSeries)[i].getSphereLength() * (*cuboidSeries)[i].getSphereWidth() * resultHeight);
            layer->~Layer();
            free(layer);
            ui->progressBar->setValue(100*(i+1)/cuboidSeries->size());
        }
        ui->progressBar->setValue(100);
        ui->AcceptButton->setEnabled(true);
        break;
    }
}

void AlgorithmForm::on_AcceptButton_clicked()
{
    this->~AlgorithmForm();
    this->parentMdi->removeSubWindow();
}

void AlgorithmForm::on_CancelButton_clicked()
{
    this->~AlgorithmForm();
    this->parentMdi->removeSubWindow();
}
