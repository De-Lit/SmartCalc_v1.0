#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <cstring>

#include "qcustomplot.h"

extern "C" {
#include "smart_calc.h"
}

namespace Ui {
class Plot;
}

class Plot : public QWidget {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();

 private:
  Ui::Plot *ui;
  QCustomPlot *wGraphic;
  void setDefaultPlot();
  void removePlot();

 private slots:
  void plotPressed();
  void plotClearPressed();
  void makePlot(QVector<double>, QVector<double>);
  void keyPressEvent(QKeyEvent *e) override;

 signals:
  void signal(char *);

 public slots:
  void sgnClose();
};

#endif  // PLOT_H
