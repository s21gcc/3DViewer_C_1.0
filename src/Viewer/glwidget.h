#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include <QOpenGLWidget>
#include <QWidget>

extern "C" {
#include "viewer.h"
}

class GLwidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit GLwidget(QWidget *parent = nullptr);
  ObjData obj = {0, 0, NULL, NULL};

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void parse();
  void stipple();
  void verticleMode();
  void readSettings();
  void saveSettings();

  float x_offset, y_offset, z_offset;
  char *fileName = NULL;
  float x_coord = 0, y_coord = 0, z_coord = -10;
  float x_coord_rotate = 0, y_coord_rotate = 0, z_coord_rotate = 0;
  float scale_x = 1, scale_y = 1;
  int projection_type = 0, mode = 0, verticle_mode = 0;
  float line_width = 1;
  float verticle_width = 1;
  float c_red = 0.0, c_blue = 0.0, c_green = 0.0;
  float v_red = 1.0, v_blue = 0.0, v_green = 0.0;
  float l_red = 0.0, l_blue = 0.0, l_green = 1.0;

 signals:
};

#endif  // GLWIDGET_H
