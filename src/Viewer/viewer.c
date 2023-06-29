#include "viewer.h"

int parse_obj_file(char *filename, ObjData *obj) {
  int error = 0;
  FILE *f = fopen(filename, "r");
  if (!f) {
    error = 1;
  } else {
    if (alloc_mem(f, obj) == 0) {
      fill_data(f, obj);
    } else {
      error = 1;
    }
    fclose(f);
  }
  return error;
}

void fill_data(FILE *f, ObjData *obj) {
  char *pattern = NULL;
  size_t len = 1024;
  int vertex_in_massive = 0;
  int facets_in_massive = 0;
  int first_face = 0;
  int flag = 0;
  int now_vertex_count = 0;
  while (getline(&pattern, &len, f) != EOF) {
    if (strncmp(pattern, "v ", 2) == 0) {
      now_vertex_count++;
      double x, y, z;
      sscanf(pattern, "v %lf %lf %lf", &x, &y, &z);
      obj->vertexes[vertex_in_massive++] = x;
      obj->vertexes[vertex_in_massive++] = y;
      obj->vertexes[vertex_in_massive++] = z;
    } else if (strncmp(pattern, "f ", 2) == 0) {
      char *token = strtok(pattern + 2, " ");
      while (token != NULL) {
        int x = atoi(token);
        if (x != 0) {
          if (x < 0) x += now_vertex_count + 1;
          obj->face[facets_in_massive] = x - 1;
          if (flag == 0) {
            first_face = x - 1;
            flag = 1;
          } else {
            obj->face[++facets_in_massive] = x - 1;
          }
          facets_in_massive++;
        }
        token = strtok(NULL, " ");
      }
      obj->face[facets_in_massive] = first_face;
      facets_in_massive++;
      flag = 0;
    }
  }
  free(pattern);
}

int alloc_mem(FILE *f, ObjData *obj) {
  char *pattern = NULL;
  size_t len = 1024;
  int error = 0;
  while (getline(&pattern, &len, f) > 0) {
    if (pattern[0] == 'v' && pattern[1] == ' ') {
      obj->num_vertexes += 1;
    }
    if (pattern[0] == 'f' && pattern[1] == ' ') {
      char *token = strtok(pattern + 2, " ");
      while (token != NULL) {
        int x = atoi(token);
        if (x != 0) obj->num_facets++;
        token = strtok(NULL, " ");
      }
    }
  }
  if (pattern != NULL) free(pattern);
  if (obj->num_vertexes > 0)
    obj->vertexes = calloc(obj->num_vertexes * 3, sizeof(double));
  if (obj->num_facets > 0) obj->face = calloc(obj->num_facets * 2, sizeof(int));
  if (obj->face == NULL || obj->vertexes == NULL) error = 1;
  fseek(f, 0, SEEK_SET);
  return error;
}

void translate(double x, double y, double z, ObjData *obj) {
  // Смещение по x
  for (int i = 0; i < obj->num_vertexes * 3; i += 3) {
    obj->vertexes[i] += x;
  }
  // Смещение по y
  for (int i = 1; i < obj->num_vertexes * 3; i += 3) {
    obj->vertexes[i] += y;
  }
  // Смещение по z
  for (int i = 2; i < obj->num_vertexes * 3; i += 3) {
    obj->vertexes[i] += z;
  }
}

void scale(double x, double y, ObjData *obj) {
  // Масштаб x
  for (int i = 0; i < obj->num_vertexes * 3; i += 3) {
    obj->vertexes[i] *= x;
  }
  // Масштаб y
  for (int i = 1; i < obj->num_vertexes * 3; i += 3) {
    obj->vertexes[i] *= y;
  }
}

void rotation(ObjData *obj, int angle, int axis) {
  double new_angle = angle * M_PI / 180;
  for (int i = 0; i < obj->num_vertexes * 3; i += 3) {
    double x = obj->vertexes[i];
    double y = obj->vertexes[i + 1];
    double z = obj->vertexes[i + 2];
    // Поворот по X
    if (axis == 0) {
      obj->vertexes[i + 1] = y * cos(new_angle) - z * sin(new_angle);
      obj->vertexes[i + 2] = y * sin(new_angle) + z * cos(new_angle);
      // Поворот по Y
    } else if (axis == 1) {
      obj->vertexes[i] = x * cos(new_angle) + z * sin(new_angle);
      obj->vertexes[i + 2] = -x * sin(new_angle) + z * cos(new_angle);
      // Поворот по Z
    } else if (axis == 2) {
      obj->vertexes[i] = x * cos(new_angle) - y * sin(new_angle);
      obj->vertexes[i + 1] = x * sin(new_angle) + y * cos(new_angle);
    }
  }
}
