#ifndef VECTOR_LIB_GUARD

#define VECTOR_LIB_GUARD

typedef struct {
  double x;
  double y;
} vector_t;

typedef struct {
  double x;
  double y;
} point_t;

typedef struct {
  point_t p;
  vector_t v;
} line_t;

typedef union {
  vector_t v;
  point_t p;
  struct {
    double x;
    double y;
  };
} tuple_t;

#define X_BASIS                                                                \
  (vector_t) { 1, 0 }
#define Y_BASIS                                                                \
  (vector_t) { 0, 1 }

struct __vector_namespace {
  /*
   * Returns a point resulting from moving $1 along $2.
   */
  point_t (*move)(point_t, vector_t);

  /*
   * Returns a point whose cordinates are the average
   * of $1 and $2.
   */
  point_t (*midpoint)(point_t, vector_t);
  /*
   * Returns a vector that represents the motion needed
   * to go from $1 to $2.
   */
  vector_t (*motion_between)(point_t, point_t);
  /*
   * Returns a vector whose components are the sum
   * of the components of $1 and $2.
   */
  vector_t (*add)(vector_t, vector_t);
  /*
   * Returns a vector whose components are those of
   * $1 each scaled by $2.
   */
  vector_t (*scale)(vector_t, double);
  /*
   * Returns, in radians, the angle formed by 2 vectors.
   */
  double (*angle_between)(vector_t, vector_t);
  /*
   * Rotates the vector $1 by the angle between it and $2.
   */
  vector_t (*rotate_by_angle_between)(vector_t to_rotate, vector_t reference);
  /*
   * Rotates $1 by the angle $2 in radians.
   */
  vector_t (*rotate_by_angle)(vector_t to_rotate, double theta);
  /*
   * Returns a vector corresponding to the projection of $1 onto
   * the direction of $2.
   */
  vector_t (*projection_onto)(vector_t to_project, vector_t onto);
  /*
   * Returns a vector corresponding to $1 reflected along the direction
   * of $2.
   */
  vector_t (*reflection_along)(vector_t to_reflect, vector_t along);
  /*
   * Returns the inner product of vectors $1 and $2
   */
  double (*dot)(vector_t, vector_t);
  /*
   * Returns the slope of vector $1 with respect to $2
   */
  double (*slope_between)(vector_t, vector_t);
  /*
   * Returns the norm of the vector $1.
   */
  double (*magnitude)(vector_t);
  /*
   * Returns a vector in the direction of $1 but whose
   * magnitude is 1.
   */
  vector_t (*normalized)(vector_t);
  /*
   * Pretty prints a vector.
   */
  vector_t (*debug)(vector_t);
  /*
   * Returns the line that passes through both points.
   */
  line_t (*line_through)(point_t, point_t);
  /*
   * Finds point on line with give x coordinate for non
   * vertical lines.
   */
  point_t (*point_on_line_with_x)(line_t, double);
  /*
   * Finds point on line with give y coordinate for non
   * vertical lines.
   */
  point_t (*point_on_line_with_y)(line_t, double);
};

/**
 * Loads all public procedures concerning the library
 **/
struct __vector_namespace
load_vector_library(void);
#endif
