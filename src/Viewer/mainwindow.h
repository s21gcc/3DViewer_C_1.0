#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>

#include <QFileDialog>
#include <QMainWindow>

#include "QtWidgets"
#include "qgifimage.h"

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
  void setSettings();

 private:
  Ui::MainWindow *ui;
  QString gifFileName;
  QGifImage *imageForGif;
  QTimer *timer;
  int fps = 0;

 private slots:

  void on_spinBox_X_valueChanged(double arg1);
  void on_spinBox_Y_valueChanged(double arg1);
  void on_spinBox_Z_valueChanged(double arg1);
  void on_rotate_spinBox_X_valueChanged(double arg1);
  void on_rotate_spinBox_Y_2_valueChanged(double arg1);
  void on_rotate_spinBox_Z_2_valueChanged(double arg1);
  void on_spinBox_scale_X_valueChanged(double arg1);
  void on_spinBox_scale_Y_valueChanged(double arg1);
  void on_radioButton_toggled(bool checked);
  void on_radioButton_2_toggled(bool checked);
  void on_spinBox_red_valueChanged(double arg1);
  void on_spinBox_green_valueChanged(double arg1);
  void on_spinBox_blue_valueChanged(double arg1);
  void on_toolButton_clicked();
  void on_loadButton_pressed();
  void on_radioButton_3_toggled(bool checked);
  void on_radioButton_4_toggled(bool checked);
  void on_spinBox_lineWidth_valueChanged(double arg1);
  void on_spinBox_verticle_Size_valueChanged(double arg1);
  void on_spinBox_red_verticle_valueChanged(double arg1);
  void on_spinBox_blue_verticle_valueChanged(double arg1);
  void on_spinBox_green_verticle_valueChanged(double arg1);
  void on_spinBox_green_line_valueChanged(double arg1);
  void on_spinBox_red_line_valueChanged(double arg1);
  void on_spinBox_blue_line_valueChanged(double arg1);
  void on_radioButton_5_toggled(bool checked);
  void on_radioButton_6_toggled(bool checked);
  void on_radioButton_7_toggled(bool checked);
  void on_resetButton_pressed();
  void on_lineEdit_textChanged(const QString &arg1);
  void on_screen_clicked();
  void on_gif_clicked();
  void gifWithScreenCast();
};

#endif  // MAINWINDOW_H
