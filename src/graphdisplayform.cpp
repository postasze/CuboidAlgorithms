#include "graphdisplayform.h"
#include "ui_graphdisplayform.h"

bool LargerCoordinateX(QPoint& firstPoint, QPoint& secondPoint)
{
  return firstPoint.x() < secondPoint.x();
}

GraphDisplayForm::GraphDisplayForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphDisplayForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);

    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    list<QPoint> algorithm1PointsList, algorithm2PointsList, algorithm3PointsList;
    list<QPoint>::iterator iter;
    unsigned long minValue = ULLONG_MAX, maxValue = 0;

    QChart *chart = new QChart();
    QLineSeries *algorithm1series = new QLineSeries(), *algorithm2series = new QLineSeries(), *algorithm3series = new QLineSeries();
    QValueAxis *axisX = new QValueAxis;
    axisX->setLinePenColor(QColor(0, 0, 150));
    axisX->setTickCount(10);
    axisX->setTitleText("Ilość prostopadłościanów (rozmiar danych)");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLinePenColor(QColor(0, 0, 150));
    axisY->setTickCount(10);
    axisY->setTitleText("Czas obliczeń w mikrosekundach");
    chart->addAxis(axisY, Qt::AlignLeft);

    algorithm1series->setName("Jak największy prostopadłościan z tablicą zajętości");
    algorithm2series->setName("Jak największy prostopadłościan bez tablicy zajętości");
    algorithm3series->setName("Jak najbardziej płaski prostopadłościan");

    for(unsigned int i = 0; i < cuboidSeries->size(); i++)
    {
        if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY) == true)
            algorithm1PointsList.push_front(QPoint((*cuboidSeries)[i].cuboidListForAlgorithm1->size(),
                (*cuboidSeries)[i].getComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY)));

        if((*cuboidSeries)[i].getComputedBy(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY) == true)
            algorithm2PointsList.push_front(QPoint((*cuboidSeries)[i].cuboidListForAlgorithm1->size(),
                (*cuboidSeries)[i].getComputationTime(LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY)));

        if((*cuboidSeries)[i].getComputedBy(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS) == true)
            algorithm3PointsList.push_front(QPoint((*cuboidSeries)[i].cuboidListForAlgorithm1->size(),
                (*cuboidSeries)[i].getComputationTime(MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS)));
    }
    algorithm1PointsList.sort(LargerCoordinateX);
    algorithm2PointsList.sort(LargerCoordinateX);
    algorithm3PointsList.sort(LargerCoordinateX);

    iter = algorithm1PointsList.begin();
    while (iter != algorithm1PointsList.end())
    {
      *algorithm1series << *iter;
      if(iter->y() > maxValue)
          maxValue = iter->y();
      if(iter->y() < minValue)
          minValue = iter->y();
      ++iter;
    }

    iter = algorithm2PointsList.begin();
    while (iter != algorithm2PointsList.end())
    {
      *algorithm2series << *iter;
      if(iter->y() > maxValue)
          maxValue = iter->y();
      if(iter->y() < minValue)
          minValue = iter->y();
      ++iter;
    }

    iter = algorithm3PointsList.begin();
    while (iter != algorithm3PointsList.end())
    {
      *algorithm3series << *iter;
      if(iter->y() > maxValue)
          maxValue = iter->y();
      if(iter->y() < minValue)
          minValue = iter->y();
      ++iter;
    }

    axisY->setRange(minValue, maxValue);

    if(!algorithm1PointsList.empty())
    {
        chart->addSeries(algorithm1series);
        algorithm1series->attachAxis(axisX);
        algorithm1series->attachAxis(axisY);
    }

    if(!algorithm2PointsList.empty())
    {
        chart->addSeries(algorithm2series);
        algorithm2series->attachAxis(axisX);
        algorithm3series->attachAxis(axisY);
    }

    if(!algorithm3PointsList.empty())
    {
        chart->addSeries(algorithm3series);
        algorithm3series->attachAxis(axisX);
        algorithm3series->attachAxis(axisY);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);
    this->resize(800, 600);
    this->show();
}

GraphDisplayForm::~GraphDisplayForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}
