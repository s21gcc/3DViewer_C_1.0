#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) : QOpenGLWidget{parent} {}

void GLwidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LINE_STIPPLE);
}

void GLwidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
}

void GLwidget::paintGL() {
  // Base
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, obj.vertexes);
  glClearColor(c_red, c_green, c_blue, 1.0f);
  glEnableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);

  // Projection
  if (projection_type == 0)
    glOrtho(-5, 5, -5, 5, 0.1f, 2000);
  else
    gluPerspective(90.0f, width() / height(), 0.1f, 1000.0f);

  glTranslated(x_coord, y_coord, z_coord);
  glScaled(scale_x, scale_y, 1);

  // Rotation
  glRotatef(x_coord_rotate, 1, 0, 0);
  glRotatef(y_coord_rotate, 0, 1, 0);
  glRotatef(z_coord_rotate, 0, 0, 1);

  // Цвет, толщина и пунктир линий
  glLineWidth(line_width);
  glColor3f(l_red, l_green, l_blue);
  stipple();

  glDrawElements(GL_LINES, obj.num_facets * 2, GL_UNSIGNED_INT, obj.face);
  glColor3f(v_red, v_green, v_blue);
  glPointSize(verticle_width);
  verticleMode();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLwidget::parse() {
  if (parse_obj_file(fileName, &obj)) {
    obj.num_facets = 0;
    obj.num_vertexes = 0;
    obj.vertexes = NULL;
    obj.face = NULL;
  }
  free(fileName);
  update();
}

void GLwidget::stipple() {
  if (mode == 0) {
    if (glIsEnabled(GL_LINE_STIPPLE)) glDisable(GL_LINE_STIPPLE);
  } else {
    if (!glIsEnabled(GL_LINE_STIPPLE)) {
      glEnable(GL_LINE_STIPPLE);
    }
    glLineStipple(1, 1);
  }
  update();
}

void GLwidget::verticleMode() {
  if (verticle_mode == 1) {
    if (!glIsEnabled(GL_POINT_SMOOTH)) glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.num_vertexes);
  } else if (verticle_mode == 2) {
    if (glIsEnabled(GL_POINT_SMOOTH)) glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.num_vertexes);
  }
  update();
}

void GLwidget::readSettings() {
  FILE *f = fopen(".SuperViewerSettings.ini", "r");
  if (f) {
    fscanf(f, "%d %d %d %f %f %f %f %f %f %f %f %f %f %f", &projection_type,
           &mode, &verticle_mode, &line_width, &verticle_width, &c_red, &c_blue,
           &c_green, &v_red, &v_blue, &v_green, &l_red, &l_blue, &l_green);
  }
  fclose(f);
}

void GLwidget::saveSettings() {
  FILE *f = fopen(".SuperViewerSettings.ini", "w");
  fprintf(f, "%d %d %d %f %f %f %f %f %f %f %f %f %f %f", projection_type, mode,
          verticle_mode, line_width, verticle_width, c_red, c_blue, c_green,
          v_red, v_blue, v_green, l_red, l_blue, l_green);
  fclose(f);
}
