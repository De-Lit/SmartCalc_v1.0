#include "plot.h"

#include "ui_plot.h"

Plot::Plot(QWidget *parent) : QWidget(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window | Qt::WindowTitleHint |
                       Qt::CustomizeWindowHint);

  connect(ui->bin_plot, SIGNAL(released()), this, SLOT(plotPressed()));
  connect(ui->bin_plot_clear, SIGNAL(released()), this,
          SLOT(plotClearPressed()));

  wGraphic = new QCustomPlot();
  ui->gridLayout->addWidget(wGraphic, 0, 0, 1, 1);
  wGraphic->xAxis->setLabel("x");
  wGraphic->yAxis->setLabel("y");

  setDefaultPlot();
}

Plot::~Plot() { delete ui; }

void Plot::setDefaultPlot() {
  wGraphic->xAxis->setRange(-10, 10);
  wGraphic->yAxis->setRange(-10, 10);
  wGraphic->replot();
}

void Plot::removePlot() {
  wGraphic->removeGraph(0);
  wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
  setDefaultPlot();
}

void Plot::plotPressed() {
  int x_min = ui->spinBox_x_min->value();
  int x_max = ui->spinBox_x_max->value();
  int y_min = ui->spinBox_y_min->value();
  int y_max = ui->spinBox_y_max->value();
  if (x_max > x_min && y_max > y_min) {
    char c[256] = {'\0'};
    emit signal(c);
    double val = smart_calc(c, x_min);
    if (strcmp(c, "Error\0") && val != INFINITY && val == val && val != -NAN) {
      float h = 0.05;
      int N = (x_max - x_min) / h + 1;
      QVector<double> x(N), y(N);
      double x_value = x_min;
      for (int i = 0; i < N; i++, x_value += h) {
        x[i] = x_value;
        y[i] = smart_calc(c, x[i]);
      }
      makePlot(x, y);
    } else {
      removePlot();
    }
  }
}

void Plot::plotClearPressed() { removePlot(); }

void Plot::makePlot(QVector<double> x, QVector<double> y) {
  wGraphic->xAxis->setRange(ui->spinBox_x_min->value(),
                            ui->spinBox_x_max->value());
  wGraphic->yAxis->setRange(ui->spinBox_y_min->value(),
                            ui->spinBox_y_max->value());

  wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
  wGraphic->graph(0)->setData(x, y);
  wGraphic->graph(0)->setLineStyle(QCPGraph::lsNone);
  wGraphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

  wGraphic->replot();
  wGraphic->setInteraction(QCP::iRangeZoom, true);
  wGraphic->setInteraction(QCP::iRangeDrag, true);
}

void Plot::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    Plot::plotPressed();
  }
}

void Plot::sgnClose() {
  this->close();
  ui->~Plot();
}
