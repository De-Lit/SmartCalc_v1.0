#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  plot = new Plot;
  connect(plot, &Plot::signal, this, &MainWindow::slot);
  connect(this, &MainWindow::sgnClose, plot, &Plot::sgnClose);

  ui->setupUi(this);

  connect(ui->bin_0, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_1, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_2, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_3, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_4, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_5, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_6, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_7, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_8, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_9, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_add, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_sub, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_mul, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_div, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_dec, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_open_bracket, SIGNAL(released()), this,
          SLOT(button_pressed()));
  connect(ui->bin_close_bracket, SIGNAL(released()), this,
          SLOT(button_pressed()));
  connect(ui->bin_mod, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_pow, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_x, SIGNAL(released()), this, SLOT(button_pressed()));
  connect(ui->bin_ln, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_log, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_sin, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_cos, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_tan, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_asin, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_acos, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_atan, SIGNAL(released()), this, SLOT(button_unar_pressed()));
  connect(ui->bin_sqrt, SIGNAL(released()), this, SLOT(button_unar_pressed()));

  connect(ui->bin_clear, SIGNAL(released()), this, SLOT(clear()));
  connect(ui->bin_all_clear, SIGNAL(released()), this, SLOT(all_clear()));
  connect(ui->bin_equal, SIGNAL(released()), this, SLOT(calculation()));
}

MainWindow::~MainWindow() {
  delete plot;
  delete ui;
}

void MainWindow::button_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString newLable;
  newLable = ui->lineEdit->text() + button->text();
  ui->lineEdit->setText(newLable);
}

void MainWindow::button_unar_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString newLable;
  newLable = ui->lineEdit->text() + button->text() + "(";
  ui->lineEdit->setText(newLable);
}

void MainWindow::calculation() {
  setlocale(LC_NUMERIC, "C");
  double result = 0;
  char str[256] = {'\0'};
  int lineLen = strlen(ui->lineEdit->text().toStdString().c_str());
  if (lineLen < 256) {
    strncpy(str, ui->lineEdit->text().toStdString().c_str(), lineLen);
    result = smart_calc(str, ui->double_x_input->value());
  }
  if (strcmp(str, "Error\0")) {
    memset(str, '\0', strlen(str));
    snprintf(str, sizeof(str), "%.10g", result);
  }
  ui->outputLabel->setText(str);
}

void MainWindow::clear() { ui->lineEdit->backspace(); }

void MainWindow::all_clear() {
  ui->lineEdit->clear();
  ui->outputLabel->setText("0");
  ui->double_x_input->setValue(0);
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    MainWindow::calculation();
  }
}

void MainWindow::slot(char *c) {
  int lineLen = strlen(ui->lineEdit->text().toStdString().c_str());
  if (lineLen < 256) {
    strncpy(c, ui->lineEdit->text().toStdString().c_str(), lineLen);
  }
}

void MainWindow::on_checkBox_stateChanged(int arg1) {
  if (arg1) {
    plot->show();
  } else {
    plot->close();
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  emit sgnClose();
  event->accept();
}
