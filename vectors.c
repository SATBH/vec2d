#include "vectors.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793

double
dot(vector_t a, vector_t b);
vector_t
normalized(vector_t v);

vector_t
debug(vector_t v)
{
  printf("vector_t { x: %.4f, y: %.4f }\n", v.x, v.y);
  return v;
}

vector_t
motion_between(point_t end, point_t start)
{
  return (vector_t){end.x - start.x, end.y - start.y};
}

point_t
midpoint(point_t a, vector_t b)
{
  return (point_t){a.x / 2 + b.x / 2, a.y / 2 + b.y / 2};
}

point_t
move(point_t a, vector_t b)
{
  return (point_t){a.x + b.x, a.y + b.y};
}

vector_t
add(vector_t a, vector_t b)
{
  return (vector_t){a.x + b.x, a.y + b.y};
}

vector_t
scale(vector_t v, double s)
{
  return (vector_t){v.x * s, v.y * s};
}

double
magnitude(vector_t v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}

double
angle_between(vector_t a, vector_t b)
{
  return acos(dot(normalized(a), normalized(b)));
}

vector_t
normalized(vector_t v)
{
  return scale(v, 1 / magnitude(v));
}

double
dot(vector_t a, vector_t b)
{
  return a.x * b.x + a.y * b.y;
}

vector_t
projection_onto(vector_t to_project, vector_t onto)
{
  onto = normalized(onto);
  return scale(onto, dot(to_project, onto));
}

vector_t
reflection_along(vector_t to_reflect, vector_t along)
{
  along = normalized(along);
  return add(scale(to_reflect, -1), scale(along, 2 * dot(to_reflect, along)));
}

vector_t
rotate_by_angle_between(vector_t to_rotate, vector_t reference)
{
  vector_t n_reference = normalized(reference);
  vector_t n_to_rotate = normalized(to_rotate);
  double sin = -(n_to_rotate.x * n_reference.y - n_reference.x * n_to_rotate.y);
  double cos = dot(n_to_rotate, n_reference);
  return (vector_t){
      .x = cos * to_rotate.x + -sin * to_rotate.y,
      .y = sin * to_rotate.x + cos * to_rotate.y,
  };
}

vector_t
rotate_by_angle(vector_t to_rotate, double theta)
{
  double t_sin = sin(theta);
  double t_cos = cos(theta);
  return (vector_t){
      .x = t_cos * to_rotate.x + -t_sin * to_rotate.y,
      .y = t_sin * to_rotate.x + t_cos * to_rotate.y,
  };
}

double
slope_between(vector_t v, vector_t reference)
{
  const vector_t x = projection_onto(v, reference);
  const vector_t y = add(v, scale(x, -1));
  return magnitude(y) / magnitude(x);
}

line_t
line_through(point_t a, point_t b)
{
  return (line_t){.p = a, .v = motion_between(a, b)};
}

point_t
point_on_line_with_x(line_t line, double x)
{
  const double scaling = (x - line.p.x) / line.v.x;
  return move(line.p, scale(line.v, scaling));
}

point_t
point_on_line_with_y(line_t line, double y)
{
  const double scaling = (y - line.p.y) / line.v.y;
  return move(line.p, scale(line.v, scaling));
}

struct __vector_namespace
load_vector_library(void)
{
  const struct __vector_namespace V = {
      .move = move,
      .add = add,
      .debug = debug,
      .scale = scale,
      .dot = dot,
      .magnitude = magnitude,
      .normalized = normalized,
      .angle_between = angle_between,
      .rotate_by_angle_between = rotate_by_angle_between,
      .projection_onto = projection_onto,
      .reflection_along = reflection_along,
      .rotate_by_angle = rotate_by_angle,
      .motion_between = motion_between,
      .slope_between = slope_between,
      .midpoint = midpoint,
      .line_through = line_through,
      .point_on_line_with_x = point_on_line_with_x,
      .point_on_line_with_y = point_on_line_with_y,
  };
  return V;
}
