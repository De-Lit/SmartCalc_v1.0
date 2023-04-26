#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <cstring>

#include "plot.h"

extern "C" {
#include "smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Plot *plot;
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void button_pressed();
  void button_unar_pressed();
  void calculation();
  void clear();
  void all_clear();

 protected slots:
  void on_checkBox_stateChanged(int arg1);
  void keyPressEvent(QKeyEvent *e) override;

 public slots:
  void slot(char *);

 signals:
  void sgnClose();
};

#endif  // MAINWINDOW_H
