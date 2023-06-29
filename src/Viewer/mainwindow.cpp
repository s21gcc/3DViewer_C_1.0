#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(gifWithScreenCast()));
  ui->widget->readSettings();
  setSettings();
}

MainWindow::~MainWindow() {
  ui->widget->saveSettings();
  if (ui->widget->obj.vertexes != NULL) {
    free(ui->widget->obj.vertexes);
  }
  if (ui->widget->obj.vertexes != NULL) {
    free(ui->widget->obj.face);
  }
  delete timer;
  delete ui;
}

void MainWindow::setSettings() {
  // Установка цветов
  ui->spinBox_red->setValue(ui->widget->c_red);
  ui->spinBox_green->setValue(ui->widget->c_green);
  ui->spinBox_blue->setValue(ui->widget->c_blue);
  ui->spinBox_red_line->setValue(ui->widget->l_red);
  ui->spinBox_green_line->setValue(ui->widget->l_green);
  ui->spinBox_blue_line->setValue(ui->widget->l_blue);
  ui->spinBox_red_verticle->setValue(ui->widget->v_red);
  ui->spinBox_green_verticle->setValue(ui->widget->v_green);
  ui->spinBox_blue_verticle->setValue(ui->widget->v_blue);
  // Ширина линий
  ui->spinBox_lineWidth->setValue(ui->widget->line_width);
  // Размер вершин
  ui->spinBox_verticle_Size->setValue(ui->widget->verticle_width);
  // Тип проекции
  if (ui->widget->projection_type == 0)
    ui->radioButton->toggle();
  else
    ui->radioButton_2->toggle();
  // Тип линии
  if (ui->widget->mode == 0)
    ui->radioButton_3->toggle();
  else
    ui->radioButton_4->toggle();
  // Отображение вершин
  if (ui->widget->verticle_mode == 0)
    ui->radioButton_5->toggle();
  else if (ui->widget->verticle_mode == 1)
    ui->radioButton_6->toggle();
  else
    ui->radioButton_7->toggle();
}

void MainWindow::on_spinBox_X_valueChanged(double arg1) {
  ui->widget->x_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_Y_valueChanged(double arg1) {
  ui->widget->y_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_Z_valueChanged(double arg1) {
  ui->widget->z_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_rotate_spinBox_X_valueChanged(double arg1) {
  ui->widget->x_coord_rotate = arg1;
  ui->widget->update();
}

void MainWindow::on_rotate_spinBox_Y_2_valueChanged(double arg1) {
  ui->widget->y_coord_rotate = arg1;
  ui->widget->update();
}

void MainWindow::on_rotate_spinBox_Z_2_valueChanged(double arg1) {
  ui->widget->z_coord_rotate = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_scale_X_valueChanged(double arg1) {
  ui->widget->scale_x = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_scale_Y_valueChanged(double arg1) {
  ui->widget->scale_y = arg1;
  ui->widget->update();
}

void MainWindow::on_radioButton_toggled(bool checked) {
  ui->widget->projection_type = 0;
  ui->widget->update();
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
  ui->widget->projection_type = 1;
  ui->widget->update();
}

void MainWindow::on_spinBox_red_valueChanged(double arg1) {
  ui->widget->c_red = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_green_valueChanged(double arg1) {
  ui->widget->c_green = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_blue_valueChanged(double arg1) {
  ui->widget->c_blue = arg1;
  ui->widget->update();
}

void MainWindow::on_toolButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home", tr("Object (*.obj)"));
  ui->lineEdit->setText(fileName);
}

void MainWindow::on_loadButton_pressed() {
  const char *str = ui->lineEdit->text().toStdString().c_str();
  ui->widget->fileName = (char *)malloc(256);
  if (ui->widget->fileName != NULL) {
    strncpy(ui->widget->fileName, str, 255);
  }
  ui->widget->parse();
  ui->loadButton->setDisabled(1);
  ui->toolButton->setDisabled(1);
  ui->resetButton->setDisabled(0);
  char nv[20] = "";
  sprintf(nv, "%d", ui->widget->obj.num_vertexes);
  ui->VerticesLabel->setText(nv);
  char ne[20] = "";
  sprintf(ne, "%d", ui->widget->obj.num_facets / 3);
  ui->EdgesLabel->setText(ne);
}

void MainWindow::on_radioButton_3_toggled(bool checked) {
  ui->widget->mode = 0;
}

void MainWindow::on_radioButton_4_toggled(bool checked) {
  ui->widget->mode = 1;
}

void MainWindow::on_spinBox_lineWidth_valueChanged(double arg1) {
  ui->widget->line_width = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_verticle_Size_valueChanged(double arg1) {
  ui->widget->verticle_width = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_red_verticle_valueChanged(double arg1) {
  ui->widget->v_red = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_green_verticle_valueChanged(double arg1) {
  ui->widget->v_green = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_blue_verticle_valueChanged(double arg1) {
  ui->widget->v_blue = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_red_line_valueChanged(double arg1) {
  ui->widget->l_red = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_green_line_valueChanged(double arg1) {
  ui->widget->l_green = arg1;
  ui->widget->update();
}

void MainWindow::on_spinBox_blue_line_valueChanged(double arg1) {
  ui->widget->l_blue = arg1;
  ui->widget->update();
}

void MainWindow::on_radioButton_5_toggled(bool checked) {
  ui->widget->verticle_mode = 0;
}

void MainWindow::on_radioButton_6_toggled(bool checked) {
  ui->widget->verticle_mode = 1;
}

void MainWindow::on_radioButton_7_toggled(bool checked) {
  ui->widget->verticle_mode = 2;
}

void MainWindow::on_resetButton_pressed() {
  // Позиции
  ui->spinBox_X->setValue(0);
  ui->spinBox_Y->setValue(0);
  ui->spinBox_Z->setValue(-10);
  // Ротация
  ui->rotate_spinBox_X->setValue(0);
  ui->rotate_spinBox_Y_2->setValue(0);
  ui->rotate_spinBox_Z_2->setValue(0);
  // Масштаб
  ui->spinBox_scale_X->setValue(1);
  ui->spinBox_scale_Y->setValue(1);
  // Установка цветов
  ui->spinBox_red->setValue(0);
  ui->spinBox_green->setValue(0);
  ui->spinBox_blue->setValue(0);
  ui->spinBox_red_line->setValue(0);
  ui->spinBox_green_line->setValue(1);
  ui->spinBox_blue_line->setValue(0);
  ui->spinBox_red_verticle->setValue(1);
  ui->spinBox_green_verticle->setValue(0);
  ui->spinBox_blue_verticle->setValue(0);
  // Ширина линий
  ui->spinBox_lineWidth->setValue(1);
  // Размер вершин
  ui->spinBox_verticle_Size->setValue(1);
  // Проекция
  ui->radioButton->toggle();
  // Тип линии
  ui->radioButton_3->toggle();
  // Вид вершин
  ui->radioButton_5->toggle();
  // Очистка пути
  ui->lineEdit->clear();
  // Очистка счетчика вершин и ребер
  ui->EdgesLabel->setText("0");
  ui->VerticesLabel->setText("0");
  // Запрет новых файлов
  ui->toolButton->setDisabled(0);
  free(ui->widget->obj.face);
  free(ui->widget->obj.vertexes);
  ui->widget->obj.face = NULL;
  ui->widget->obj.vertexes = NULL;
  ui->widget->obj.num_vertexes = 0;
  ui->widget->obj.num_facets = 0;
  ui->widget->update();
  ui->resetButton->setDisabled(1);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1) {
  if (!ui->resetButton->isEnabled()) ui->loadButton->setDisabled(0);
}

// Перемещение по файловой системе, захват пикселей виджета opengl и сохранение
// изображения

void MainWindow::on_screen_clicked() {
  QFileDialog dialogConnectImage(this);
  QString imageFileName = dialogConnectImage.getSaveFileName(
      this, tr("Make a screenshot"), ".jpeg", tr("image (*.bmp *.jpeg)"));
  QImage img = ui->widget->grabFramebuffer();
  img.save(imageFileName);
  QMessageBox messageBoxImage;
  messageBoxImage.information(0, "", "Screenshot saved");
}

// Перемещение по файловой системе, создание скринкастов, включение таймера

void MainWindow::on_gif_clicked() {
  gifFileName = QFileDialog::getSaveFileName(this, tr("Make a GIF"), ".gif",
                                             tr("gif (*.gif)"));
  if (gifFileName != "") {
    ui->gif->setDisabled(true);
    imageForGif = new QGifImage;
    imageForGif->setDefaultDelay(10);
    timer->setInterval(100);
    timer->start();
  }
}

// Добавляет кадры в imageforgif до fps != 50

void MainWindow::gifWithScreenCast() {
  QImage image = ui->widget->grabFramebuffer();
  QSize imageSize(640, 480);
  QImage scaledImage = image.scaled(imageSize);
  imageForGif->addFrame(scaledImage);
  if (fps == 50) {
    timer->stop();
    imageForGif->save(gifFileName);
    fps = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif saved");
    delete imageForGif;
    ui->gif->setText("Gif");
    ui->gif->setEnabled(true);
  }
  fps++;
  //сколько осталось до конца съемки
  if (!ui->gif->isEnabled()) {
    ui->gif->setText(QString::number(fps / 10));
  }
}
