#ifndef GRAPHDISPLAYFORM_H
#define GRAPHDISPLAYFORM_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include "mainwindow.h"
#include <climits>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class GraphDisplayForm;
}

class GraphDisplayForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphDisplayForm(QWidget *parent = 0);
    ~GraphDisplayForm();

private:
    MainWindow *parentMdi;
    Ui::GraphDisplayForm *ui;
};

#endif // GRAPHDISPLAYFORM_H
