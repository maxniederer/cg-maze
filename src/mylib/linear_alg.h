#ifndef _MYLIB_H_
#define _MYLIB_H_

typedef struct
{
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef struct
{
	vec4 x;
	vec4 y;
	vec4 z;
	vec4 w;
} mat4;

typedef struct
{
    float x;
    float y;
} vec2;

/* Transformation Functions */

vec2 v2(float x, float y);
vec4 v4(float x, float y, float z, float w);
vec4* v4_a(float x, float y, float z, float w);
vec4* transform(mat4* a, vec4* p);
mat4* translate(float a, float b, float c);
mat4* scale(float a, float b, float c);
mat4* rotate_z(float t);
mat4* rotate_x(float t);
mat4* rotate_y(float t);
mat4* identity_matrix();

/* Vector Functions */

void print_vector(vec4* v);
vec4* mult_scalar_vector(vec4* v, float a);
vec4* vector_sum(vec4* v, vec4* w);
vec4* vector_diff(vec4* v, vec4* w);
float magnitude(vec4* v);
vec4* normalize(vec4* v);
float dot_product(vec4* v, vec4* w);
vec4* cross_product(vec4* v, vec4* w);

/* Matrix Functions */

void print_matrix(mat4* m);
mat4* mult_scalar_matrix(mat4* m, float a);
mat4* matrix_sum(mat4* m, mat4* n);
mat4* matrix_diff(mat4* m, mat4* n);
mat4* matrix_prod(mat4* m, mat4* n);
mat4* inverse(mat4 *m);
mat4* transpose(mat4 *m);
vec4* mult_matrix_vector(mat4 *m, vec4 *v);

mat4 *minor(mat4* m);
mat4 *cofactor(mat4* m);
float determinant(mat4* m, mat4* minor);

/* Camera Functions */

mat4* look_at(vec4* eye, vec4* at, vec4* up);
mat4* look_at_coord(float eyex, float eyey, float eyez, float atx, float aty, float atz, float upx, float upy, float upz);
mat4* ortho(float left, float right, float bottom, float top, float near, float far);
mat4* frustum(float left, float right, float bottom, float top, float near, float far);

vec4* changing_vector(float alpha, vec4* end, vec4* start);
vec4* changing_vector_pi(float alpha, float r);

#endif