#include "linear_alg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Transformation Functions */

vec2 v2(float x, float y)
{
    vec2 result = {x, y};
    return result;
}

vec4 v4(float x, float y, float z, float w)
{
    vec4 result = {x, y, z, w};
    return result;
}

vec4* v4_a(float x, float y, float z, float w)
{
	vec4 *point = malloc(sizeof(vec4));
	if(!point) return NULL;
	
	point->x = x;
	point->y = y;
	point->z = z;
	point->w = w;
	
	return point;
}

vec4* transform(mat4* a, vec4* p)
{
	vec4 *point = malloc(sizeof(vec4));
	if(!point) return NULL;
	
	point->x = a->x.x + a->y.x + a->z.x + a->w.x;
	point->y = a->x.y + a->y.y + a->z.y + a->w.y;
	point->z = a->x.z + a->y.z + a->z.z + a->w.z;
	point->w = 1;
	
	return point;
}

mat4* translate(float a, float b, float c)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = 1;
	matrix->x.y = 0;
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = 1;
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = 0;
	matrix->z.y = 0;
	matrix->z.z = 1;
	matrix->z.w = 0;
	
	matrix->w.x = a;
	matrix->w.y = b;
	matrix->w.z = c;
	matrix->w.w = 1;
	
	return matrix;
}

mat4* scale(float a, float b, float c)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = a;
	matrix->x.y = 0;
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = b;
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = 0;
	matrix->z.y = 0;
	matrix->z.z = c;
	matrix->z.w = 0;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = 0;
	matrix->w.w = 1;
	
	return matrix;
}

mat4* rotate_z(float t)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = cos(t);
	matrix->x.y = sin(t);
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = -sin(t);
	matrix->y.y = cos(t);
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = 0;
	matrix->z.y = 0;
	matrix->z.z = 1;
	matrix->z.w = 0;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = 0;
	matrix->w.w = 1;
	
	return matrix;
}

mat4* rotate_x(float t)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = 1;
	matrix->x.y = 0;
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = cos(t);
	matrix->y.z = sin(t);
	matrix->y.w = 0;
	
	matrix->z.x = 0;
	matrix->z.y = -sin(t);
	matrix->z.z = cos(t);
	matrix->z.w = 0;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = 0;
	matrix->w.w = 1;
	
	return matrix;
}

mat4* rotate_y(float t)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = cos(t);
	matrix->x.y = 0;
	matrix->x.z = -sin(t);
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = 1;
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = sin(t);
	matrix->z.y = 0;
	matrix->z.z = cos(t);
	matrix->z.w = 0;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = 0;
	matrix->w.w = 1;
	
	return matrix;
}

mat4* identity_matrix()
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = 1;
	matrix->x.y = 0;
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = 1;
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = 0;
	matrix->z.y = 0;
	matrix->z.z = 1;
	matrix->z.w = 0;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = 0;
	matrix->w.w = 1;
	
	return matrix;
}


/* Vector Functions */

void print_vector(vec4* v)
{
	printf("{%.2f %.2f %.2f %.2f}\n", v->x, v->y, v->z, v->w);
}

vec4* mult_scalar_vector(vec4* v, float a)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = v->x * a;
	vector->y = v->y * a;
	vector->z = v->z * a;
	vector->w = v->w * a;
	
	return vector;
}

vec4* vector_sum(vec4* v, vec4* w)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = v->x + w->x;
	vector->y = v->y + w->y;
	vector->z = v->z + w->z;
	vector->w = v->w + w->w;
	
	return vector;
}

vec4* vector_diff(vec4* v, vec4* w)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = v->x - w->x;
	vector->y = v->y - w->y;
	vector->z = v->z - w->z;
	vector->w = v->w - w->w;
	
	return vector;
}

float magnitude(vec4* v)
{
	float sum = v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w;
	return (float) sqrt((double) sum);
}

vec4 *normalize(vec4 *v)
{
	float scale = 1/(magnitude(v));
	return mult_scalar_vector(v, scale);
}

float dot_product(vec4* v, vec4* w)
{
	float sum = v->x*w->x + v->y*w->y + v->z*w->z + v->w*w->w;
	return sum;
}

vec4* cross_product(vec4* v, vec4* w)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = v->y*w->z - v->z*w->y;
	vector->y = v->z*w->x - v->x*w->z;
	vector->z = v->x*w->y - v->y*w->x;
	vector->w = 0;
	
	return vector;
}

/* Matrix Functions */

void print_matrix(mat4 *m)
{
	printf("{%.2f %.2f %.2f %.2f}\n", m->x.x, m->x.y, m->x.z, m->x.w);
	printf("{%.2f %.2f %.2f %.2f}\n", m->y.x, m->y.y, m->y.z, m->y.w);
	printf("{%.2f %.2f %.2f %.2f}\n", m->z.x, m->z.y, m->z.z, m->z.w);
	printf("{%.2f %.2f %.2f %.2f}\n", m->w.x, m->w.y, m->w.z, m->w.w);
}

mat4 *mult_scalar_matrix(mat4* m, float a)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->x.x*a;
	matrix->x.y = m->x.y*a;
	matrix->x.z = m->x.z*a;
	matrix->x.w = m->x.w*a;
	
	matrix->y.x = m->y.x*a;
	matrix->y.y = m->y.y*a;
	matrix->y.z = m->y.z*a;
	matrix->y.w = m->y.w*a;
	
	matrix->z.x = m->z.x*a;
	matrix->z.y = m->z.y*a;
	matrix->z.z = m->z.z*a;
	matrix->z.w = m->z.w*a;
	
	matrix->w.x = m->w.x*a;
	matrix->w.y = m->w.y*a;
	matrix->w.z = m->w.z*a;
	matrix->w.w = m->w.w*a;
	
	return matrix;
}

mat4 *matrix_sum(mat4* m, mat4* n)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->x.x + n->x.x;
	matrix->x.y = m->x.y + n->x.y;
	matrix->x.z = m->x.z + n->x.z;
	matrix->x.w = m->x.w + n->x.w;
	
	matrix->y.x = m->y.x + n->y.x;
	matrix->y.y = m->y.y + n->y.y;
	matrix->y.z = m->y.z + n->y.z;
	matrix->y.w = m->y.w + n->y.w;
	
	matrix->z.x = m->z.x + n->z.x;
	matrix->z.y = m->z.y + n->z.y;
	matrix->z.z = m->z.z + n->z.z;
	matrix->z.w = m->z.w + n->z.w;
	
	matrix->w.x = m->w.x + n->w.x;
	matrix->w.y = m->w.y + n->w.y;
	matrix->w.z = m->w.z + n->w.z;
	matrix->w.w = m->w.w + n->w.w;
	
	return matrix;
}

mat4 *matrix_diff(mat4* m, mat4* n)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->x.x - n->x.x;
	matrix->x.y = m->x.y - n->x.y;
	matrix->x.z = m->x.z - n->x.z;
	matrix->x.w = m->x.w - n->x.w;
	
	matrix->y.x = m->y.x - n->y.x;
	matrix->y.y = m->y.y - n->y.y;
	matrix->y.z = m->y.z - n->y.z;
	matrix->y.w = m->y.w - n->y.w;
	
	matrix->z.x = m->z.x - n->z.x;
	matrix->z.y = m->z.y - n->z.y;
	matrix->z.z = m->z.z - n->z.z;
	matrix->z.w = m->z.w - n->z.w;
	
	matrix->w.x = m->w.x - n->w.x;
	matrix->w.y = m->w.y - n->w.y;
	matrix->w.z = m->w.z - n->w.z;
	matrix->w.w = m->w.w - n->w.w;
	
	return matrix;
}

mat4* matrix_prod(mat4* m, mat4* n)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = (m->x.x * n->x.x) + (m->y.x * n->x.y) + (m->z.x * n->x.z) +(m->w.x * n->x.w);
	matrix->x.y = (m->x.y * n->x.x) + (m->y.y * n->x.y) + (m->z.y * n->x.z) +(m->w.y * n->x.w);
	matrix->x.z = (m->x.z * n->x.x) + (m->y.z * n->x.y) + (m->z.z * n->x.z) +(m->w.z * n->x.w);
	matrix->x.w = (m->x.w * n->x.x) + (m->y.w * n->x.y) + (m->z.w * n->x.z) +(m->w.w * n->x.w);
	
	matrix->y.x = (m->x.x * n->y.x) + (m->y.x * n->y.y) + (m->z.x * n->y.z) +(m->w.x * n->y.w);
	matrix->y.y = (m->x.y * n->y.x) + (m->y.y * n->y.y) + (m->z.y * n->y.z) +(m->w.y * n->y.w);
	matrix->y.z = (m->x.z * n->y.x) + (m->y.z * n->y.y) + (m->z.z * n->y.z) +(m->w.z * n->y.w);
	matrix->y.w = (m->x.w * n->y.x) + (m->y.w * n->y.y) + (m->z.w * n->y.z) +(m->w.w * n->y.w);
	
	matrix->z.x = (m->x.x * n->z.x) + (m->y.x * n->z.y) + (m->z.x * n->z.z) +(m->w.x * n->z.w);
	matrix->z.y = (m->x.y * n->z.x) + (m->y.y * n->z.y) + (m->z.y * n->z.z) +(m->w.y * n->z.w);
	matrix->z.z = (m->x.z * n->z.x) + (m->y.z * n->z.y) + (m->z.z * n->z.z) +(m->w.z * n->z.w);
	matrix->z.w = (m->x.w * n->z.x) + (m->y.w * n->z.y) + (m->z.w * n->z.z) +(m->w.w * n->z.w);
	
	matrix->w.x = (m->x.x * n->w.x) + (m->y.x * n->w.y) + (m->z.x * n->w.z) +(m->w.x * n->w.w);
	matrix->w.y = (m->x.y * n->w.x) + (m->y.y * n->w.y) + (m->z.y * n->w.z) +(m->w.y * n->w.w);
	matrix->w.z = (m->x.z * n->w.x) + (m->y.z * n->w.y) + (m->z.z * n->w.z) +(m->w.z * n->w.w);
	matrix->w.w = (m->x.w * n->w.x) + (m->y.w * n->w.y) + (m->z.w * n->w.z) +(m->w.w * n->w.w);
	
	return matrix;
}

mat4* inverse(mat4* m)
{
	mat4* matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	mat4* s1 = minor(m);
	mat4* s2 = cofactor(s1);
	mat4* s3 = transpose(s2);
	float s4 = determinant(m, s1);
	
	matrix =  mult_scalar_matrix(s3, 1/s4);
	
	return matrix;
}

float determinant(mat4* m, mat4* minor)
{
	float det = m->x.x*minor->x.x - m->y.x*minor->y.x + m->z.x*minor->z.x - m->w.x*minor->w.x;
	return det;
}

mat4* minor(mat4* m)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->y.y*m->z.z*m->w.w + m->z.y*m->w.z*m->y.w + m->w.y*m->y.z*m->z.w - m->y.w*m->z.z*m->w.y - m->z.w*m->w.z*m->y.y - m->w.w*m->y.z*m->z.y;
	matrix->x.y = m->y.x*m->z.z*m->w.w + m->z.x*m->w.z*m->y.w + m->w.x*m->y.z*m->z.w - m->y.w*m->z.z*m->w.x - m->z.w*m->w.z*m->y.x - m->w.w*m->y.z*m->z.x;
	matrix->x.z = m->y.x*m->z.y*m->w.w + m->z.x*m->w.y*m->y.w + m->w.x*m->y.y*m->z.w - m->y.w*m->z.y*m->w.x - m->z.w*m->w.y*m->y.x - m->w.w*m->y.y*m->z.x;
	matrix->x.w = m->y.x*m->z.y*m->w.z + m->z.x*m->w.y*m->y.z + m->w.x*m->y.y*m->z.z - m->y.z*m->z.y*m->w.x - m->z.z*m->w.y*m->y.x - m->w.z*m->y.y*m->z.x;
	
	matrix->y.x = m->x.y*m->z.z*m->w.w + m->z.y*m->w.z*m->x.w + m->w.y*m->x.z*m->z.w - m->x.w*m->z.z*m->w.y - m->z.w*m->w.z*m->x.y - m->w.w*m->x.z*m->z.y;
	matrix->y.y = m->x.x*m->z.z*m->w.w + m->z.x*m->w.z*m->x.w + m->w.x*m->x.z*m->z.w - m->x.w*m->z.z*m->w.x - m->z.w*m->w.z*m->x.x - m->w.w*m->x.z*m->z.x;
	matrix->y.z = m->x.x*m->z.y*m->w.w + m->z.x*m->w.y*m->x.w + m->w.x*m->x.y*m->z.w - m->x.w*m->z.y*m->w.x - m->z.w*m->w.y*m->x.x - m->w.w*m->x.y*m->z.x;
	matrix->y.w = m->x.x*m->z.y*m->w.z + m->z.x*m->w.y*m->x.z + m->w.x*m->x.y*m->z.z - m->x.z*m->z.y*m->w.x - m->z.z*m->w.y*m->x.x - m->w.z*m->x.y*m->z.x;
	
	matrix->z.x = m->x.y*m->y.z*m->w.w + m->y.y*m->w.z*m->x.w + m->w.y*m->x.z*m->y.w - m->x.w*m->y.z*m->w.y - m->y.w*m->w.z*m->x.y - m->w.w*m->x.z*m->y.y;
	matrix->z.y = m->x.x*m->y.z*m->w.w + m->y.x*m->w.z*m->x.w + m->w.x*m->x.z*m->y.w - m->x.w*m->y.z*m->w.x - m->y.w*m->w.z*m->x.x - m->w.w*m->x.z*m->y.x;
	matrix->z.z = m->x.x*m->y.y*m->w.w + m->y.x*m->w.y*m->x.w + m->w.x*m->x.y*m->y.w - m->x.w*m->y.y*m->w.x - m->y.w*m->w.y*m->x.x - m->w.w*m->x.y*m->y.x;
	matrix->z.w = m->x.x*m->y.y*m->w.z + m->y.x*m->w.y*m->x.z + m->w.x*m->x.y*m->y.z - m->x.w*m->y.y*m->w.x - m->y.w*m->w.y*m->w.x - m->w.w*m->x.y*m->y.x;
	
	matrix->w.x = m->x.y*m->y.z*m->z.w + m->y.y*m->z.z*m->x.w + m->z.y*m->x.z*m->y.w - m->x.w*m->y.z*m->z.y - m->y.w*m->z.z*m->x.y - m->z.w*m->x.z*m->y.y;
	matrix->w.y = m->x.x*m->y.z*m->z.w + m->y.x*m->z.z*m->x.w + m->z.x*m->x.z*m->y.w - m->x.w*m->y.z*m->z.x - m->y.w*m->z.z*m->x.x - m->z.w*m->x.z*m->y.x;
	matrix->w.z = m->x.x*m->y.y*m->z.w + m->y.x*m->z.y*m->x.w + m->z.x*m->x.y*m->y.w - m->x.w*m->y.y*m->z.x - m->y.w*m->z.y*m->x.x - m->z.w*m->x.y*m->y.x;
	matrix->w.w = m->x.x*m->y.y*m->z.z + m->y.x*m->z.y*m->x.z + m->z.x*m->x.y*m->y.z - m->x.z*m->y.y*m->z.x - m->y.z*m->z.y*m->x.x - m->z.z*m->x.y*m->y.x;
	
	return matrix;
}

mat4 *cofactor(mat4* m)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->x.x;
	matrix->x.y = -m->x.y;
	matrix->x.z = m->x.z;
	matrix->x.w = -m->x.w;
	
	matrix->y.x = -m->y.x;
	matrix->y.y = m->y.y;
	matrix->y.z = -m->y.z;
	matrix->y.w = m->y.w;
	
	matrix->z.x = m->z.x;
	matrix->z.y = -m->z.y;
	matrix->z.z = m->z.z;
	matrix->z.w = -m->z.w;
	
	matrix->w.x = -m->w.x;
	matrix->w.y = m->w.y;
	matrix->w.z = -m->w.z;
	matrix->w.w = m->w.w;
	
	return matrix;
}

mat4 *transpose(mat4* m)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	matrix->x.x = m->x.x;
	matrix->x.y = m->y.x;
	matrix->x.z = m->z.x;
	matrix->x.w = m->w.x;
	
	matrix->y.x = m->x.y;
	matrix->y.y = m->y.y;
	matrix->y.z = m->z.y;
	matrix->y.w = m->w.y;
	
	matrix->z.x = m->x.z;
	matrix->z.y = m->y.z;
	matrix->z.z = m->z.z;
	matrix->z.w = m->w.z;
	
	matrix->w.x = m->x.w;
	matrix->w.y = m->y.w;
	matrix->w.z = m->z.w;
	matrix->w.w = m->w.w;
	
	return matrix;
}

vec4 *mult_matrix_vector(mat4 *m, vec4 *v)
{
	vec4 *matrix = malloc(sizeof(vec4));
	if(!matrix) return NULL;
	
	matrix->x = m->x.x*v->x + m->x.y*v->x + m->x.z*v->x + m->x.w*v->x;
	matrix->y = m->y.x*v->y + m->y.y*v->y + m->y.z*v->y + m->y.w*v->y;
	matrix->z = m->z.x*v->z + m->z.y*v->z + m->z.z*v->z + m->z.w*v->z;
	matrix->w = m->w.x*v->w + m->w.y*v->w + m->w.z*v->w + m->w.w*v->w;
	
	return matrix;
}

/* Camera Functions */

mat4* look_at(vec4* eye, vec4* at, vec4* up)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;

	vec4* n = vector_diff(eye, at);
	n = normalize(n);
	// u = vup x n
	vec4* u = cross_product(up, n);//vec4* u = cross_product(up, n);
	u = normalize(u);
	// v = n x u
	vec4* v = cross_product(n, u); //vec4* v = cross_product(n, u);
	//v = normalize(v);
	
	mat4 R = {{u->x, v->x, n->x, 0}, {u->y, v->y, n->y, 0}, {u->z, v->z, n->z, 0}, {0, 0, 0, 1}};
	mat4 T = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {eye->x, eye->y, eye->z, 1}};
	matrix = matrix_prod(&R, &T);

	matrix->w.x = -dot_product(u, eye);
	matrix->w.y = -dot_product(v, eye);
	matrix->w.z = -dot_product(n, eye);
	matrix->w.w = 1;
	return matrix;
}

mat4* look_at_coord(float eyex, float eyey, float eyez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	vec4 eye = {eyex, eyey, eyez, 0};
	vec4 at = {atx, aty, atz, 0};
	vec4 up = {upx, upy, upz, 0};
	//vec4 neye = {-eyex, -eyey, -eyez, 0};
	
	// n = e - a
	vec4* n = vector_diff(&eye, &at);
	n = normalize(n);
	// u = vup x n
	vec4* u = cross_product(&up, n);
	u = normalize(u);
	// v = n x u
	vec4* v = cross_product(n, u);
	//v = normalize(v);
	
	mat4 R = {{u->x, v->x, n->x, 0}, {u->y, v->y, n->y, 0}, {u->z, v->z, n->z, 0}, {0, 0, 0, 1}};
	mat4 T = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {eye.x, eye.y, eye.z, 1}};
	matrix = matrix_prod(&R, &T);
	
	matrix->w.x = -dot_product(u, &eye);
	matrix->w.y = -dot_product(v, &eye);
	matrix->w.z = -dot_product(n, &eye);
	matrix->w.w = 1;

	return matrix;

	// ASSUMING P (VRP) IS EYE POINT E
	
	// V = RT
	// R = M
	// T = T(p.x, p.y, p.z, 1)
	// want to look at world from point Px, Py, Pz in -x direction
	// .. M = {0,0,-1,0},{0,1,0,0},{1,0,0,0},{Px,Py,Pz,1} ???
	// {x',y',z',P'} = M*{x,y,z,P}
}

mat4* ortho(float left, float right, float bottom, float top, float near, float far)
{
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;
	
	mat4 S = {{2/(right-left),0,0,0}, {0,2/(top-bottom),0,0}, {0,0,2/(near-far),0}, {0, 0, 0, 1}};
	mat4 T = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-(right+left)/2,-(top+bottom)/2,-(near+far)/2,1}};
	
	matrix = matrix_prod(&S, &T);
	return matrix;
}

mat4* frustum(float left, float right, float bottom, float top, float near, float far) {
	mat4 *matrix = malloc(sizeof(mat4));
	if(!matrix) return NULL;

	matrix->x.x = 2*near/(right-left);
	matrix->x.y = 0;
	matrix->x.z = 0;
	matrix->x.w = 0;
	
	matrix->y.x = 0;
	matrix->y.y = 2*near/(top-bottom);
	matrix->y.z = 0;
	matrix->y.w = 0;
	
	matrix->z.x = (right+left)/(right-left);
	matrix->z.y = (top+bottom)/(top-bottom);
	matrix->z.z = (far+near)/(far-near);
	matrix->z.w = -1;
	
	matrix->w.x = 0;
	matrix->w.y = 0;
	matrix->w.z = (-2*far*near)/(far-near);
	matrix->w.w = 0;

	return matrix;
}

vec4* changing_vector(float alpha, vec4* end, vec4* start)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = alpha*(end->x - start->x) + start->x;
	vector->y = alpha*(end->y - start->y) + start->y;
	vector->z = alpha*(end->z - start->z) + start->z;
	vector->w = alpha*(end->w - start->w) + start->w;
	
	return vector;
}

vec4* changing_vector_pi(float alpha, float r)
{
	vec4 *vector = malloc(sizeof(vec4));
	if(!vector) return NULL;
	
	vector->x = r*cos(2*M_PI*(alpha+.125+.5)) + 4.0;
	vector->y = 4.0;
	vector->z = r*sin(2*M_PI*(alpha+.125+.5)) + 4.0;
	vector->w = 0.0;
	
	return vector;
}