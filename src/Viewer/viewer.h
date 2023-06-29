//
// Created by Oznak Banshee on 4/24/23.
//

#ifndef INC_3DVIEWER_VIEWER_H
#define INC_3DVIEWER_VIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  int num_vertexes;
  int num_facets;
  double *vertexes;
  int *face;
} ObjData;

// Parser
int parse_obj_file(char *filename, ObjData *obj);
int alloc_mem(FILE *f, ObjData *obj);
void fill_data(FILE *f, ObjData *obj);

// Affine
void translate(double x, double y, double z, ObjData *obj);
void scale(double x, double y, ObjData *obj);
void rotation(ObjData *obj, int angle, int axis);

#endif  // INC_3DVIEWER_VIEWER_H
