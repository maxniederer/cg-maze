#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../mylib/initShader.h"
#include "../mylib/linear_alg.h"
#include "../mylib/maze.h"

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

#define TOTALVERTICES 36*(79+81+1)

vec4 vertices[TOTALVERTICES];
vec4 colors[TOTALVERTICES]; // Colors (not really use this but send it into the pipeline anyway)
int num_vertices = TOTALVERTICES;
vec2 tex_coords[TOTALVERTICES];

/**/

GLuint ctm_location;
mat4 ctm_a = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4* ctm = &ctm_a;

GLuint model_view_location; // Global variable
mat4 model_view_a = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4* model_view = &model_view_a; // Global variable initialized to the identity matrix

GLuint projection_location; // Global variable
mat4 projection_a = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4* projection = &projection_a; // Global variable initialized to the identity matrix

extern cell maze[8][8];
extern state solution[200];

/**/

void makeCube(float x, float y, float z, float xl, float yl, float zl, int curr) {
    // BOTTOM FACE
    vertices[curr]   = v4(x-xl/2, y   , z+zl/2, 1.0);
    vertices[curr+1] = v4(x+xl/2, y   , z-zl/2, 1.0);
    vertices[curr+2] = v4(x+xl/2, y   , z+zl/2, 1.0);
    vertices[curr+3] = v4(x-xl/2, y   , z+zl/2, 1.0);
    vertices[curr+4] = v4(x-xl/2, y   , z-zl/2, 1.0);
    vertices[curr+5] = v4(x+xl/2, y   , z-zl/2, 1.0);
    // TOP FACE
    vertices[curr+6]   = v4(x-xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+1+6] = v4(x+xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+2+6] = v4(x+xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+3+6] = v4(x-xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+4+6] = v4(x+xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+5+6] = v4(x-xl/2, y+yl, z-zl/2, 1.0);
    // RIGHT FACE
    vertices[curr+12]   = v4(x+xl/2, y   , z+zl/2, 1.0);
    vertices[curr+1+12] = v4(x+xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+2+12] = v4(x-xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+3+12] = v4(x+xl/2, y   , z+zl/2, 1.0);
    vertices[curr+4+12] = v4(x-xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+5+12] = v4(x-xl/2, y   , z+zl/2, 1.0);
    // LEFT FACE
    vertices[curr+18]   = v4(x+xl/2, y   , z-zl/2, 1.0);
    vertices[curr+1+18] = v4(x-xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+2+18] = v4(x+xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+3+18] = v4(x+xl/2, y   , z-zl/2, 1.0);
    vertices[curr+4+18] = v4(x-xl/2, y   , z-zl/2, 1.0);
    vertices[curr+5+18] = v4(x-xl/2, y+yl, z-zl/2, 1.0);
    // FRONT FACE
    vertices[curr+24]   = v4(x-xl/2, y   , z+zl/2, 1.0);
    vertices[curr+1+24] = v4(x-xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+2+24] = v4(x-xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+3+24] = v4(x-xl/2, y   , z+zl/2, 1.0);
    vertices[curr+4+24] = v4(x-xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+5+24] = v4(x-xl/2, y   , z-zl/2, 1.0);
    // BACK FACE
    vertices[curr+30]   = v4(x+xl/2, y   , z+zl/2, 1.0);
    vertices[curr+1+30] = v4(x+xl/2, y+yl, z-zl/2, 1.0);
    vertices[curr+2+30] = v4(x+xl/2, y+yl, z+zl/2, 1.0);
    vertices[curr+3+30] = v4(x+xl/2, y   , z+zl/2, 1.0);
    vertices[curr+4+30] = v4(x+xl/2, y   , z-zl/2, 1.0);
    vertices[curr+5+30] = v4(x+xl/2, y+yl, z-zl/2, 1.0);

    // colors array
    for (int i = 0; i < 36; i++) {
        colors[curr+i] = v4(1.0, 0.0, 0.0, 1.0);
    }
}

void getVertices(void) {
    
    // 1. poles
    int currV = 0, currT = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            makeCube((float) i, 0.0, (float) j, 0.25, 1.1, 0.25, currV);
            currV += 36;
        }
    }
    while (currT < currV) {
        tex_coords[currT] = v2(0.5, 0.5);
        tex_coords[currT+1] = v2(1.0, 0.5);
        tex_coords[currT+2] = v2(1.0, 0.0); //
        tex_coords[currT+3] = v2(0.5, 0.5);
        tex_coords[currT+4] = v2(1.0, 0.0); //
        tex_coords[currT+5] = v2(0.5, 0.0);
        currT += 6;
    }

    // 2. walls
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (maze[i][j].north == 1) { // NORTH WALLS
                makeCube((float)i, 0.0, (float)j+.5, 0.1, 1, 1, currV);
                currV += 36;
            }
            if (maze[i][j].west == 1) { // WEST WALLS
                makeCube((float)i+.5, 0.0, (float)j, 1, 1, 0.1, currV);
                currV += 36;
            }
        }
        if (maze[i][7].east == 1) {// LAST EAST WALL
            makeCube((float)i+.5, 0.0, (float)j, 1, 1, 0.1, currV);
            currV += 36;
        }
    }
    for (j = 0; j < 8; j++)
        if (maze[7][j].south == 1) { // LAST SOUTH WALLS
            makeCube((float)i, 0.0, (float)j+.5, 0.1, 1.0, 1, currV);/*
                print_vector(&vertices[currV]);
                print_vector(&vertices[currV+1]);
                print_vector(&vertices[currV+2]);
                print_vector(&vertices[currV+6]);
                print_vector(&vertices[currV+7]);
                print_vector(&vertices[currV+8]);*/
            currV += 36;
        }

    while (currT < currV) {
        tex_coords[currT] = v2(0.0, 0.0);
        tex_coords[currT+1] = v2(0.5, 0.5);
        tex_coords[currT+2] = v2(0.0, 0.5);
        tex_coords[currT+3] = v2(0.0, 0.0);
        tex_coords[currT+4] = v2(0.5, 0.0);
        tex_coords[currT+5] = v2(0.5, 0.5);
        currT += 6;
        tex_coords[currT] = v2(0.0, 0.0);
        tex_coords[currT+1] = v2(0.0, 0.5);
        tex_coords[currT+2] = v2(0.5, 0.5);
        tex_coords[currT+3] = v2(0.0, 0.0);
        tex_coords[currT+4] = v2(0.5, 0.5);
        tex_coords[currT+5] = v2(0.5, 0.0);
        currT += 6;
        //right
        tex_coords[currT] = v2(0.5, 0.5);
        tex_coords[currT+1] = v2(0.5, 0.0);
        tex_coords[currT+2] = v2(0.0, 0.0);
        tex_coords[currT+3] = v2(0.5, 0.5);
        tex_coords[currT+4] = v2(0.0, 0.0);
        tex_coords[currT+5] = v2(0.0, 0.5);
        currT += 6;
        //left
        tex_coords[currT] = v2(0.0, 0.5);
        tex_coords[currT+2] = v2(0.0, 0.0);
        tex_coords[currT+1] = v2(0.5, 0.0);
        tex_coords[currT+3] = v2(0.5, 0.5);
        tex_coords[currT+4] = v2(0.0, 0.5);
        tex_coords[currT+5] = v2(0.0, 0.0);
        currT += 6;
        //front
        tex_coords[currT] = v2(0.0, 0.5);
        tex_coords[currT+1] = v2(0.0, 0.0);
        tex_coords[currT+2] = v2(0.5, 0.0);
        tex_coords[currT+3] = v2(0.0, 0.5);
        tex_coords[currT+4] = v2(0.5, 0.0);
        tex_coords[currT+5] = v2(0.5, 0.5);
        currT += 6;
        //back
        tex_coords[currT] = v2(0.0, 0.5);
        tex_coords[currT+1] = v2(0.5, 0.0);
        tex_coords[currT+2] = v2(0.0, 0.0);
        tex_coords[currT+3] = v2(0.0, 0.5);
        tex_coords[currT+4] = v2(0.5, 0.5);
        tex_coords[currT+5] = v2(0.5, 0.0);
        currT += 6;
    }
    
    // 3. ground
    makeCube(4, -0.5, 4, 15, 0.5, 15, currV);
    currV += 36;

    while (currT < currV) {
        tex_coords[currT] = v2(0.0, 1.0); //
        tex_coords[currT+1] = v2(0.5, 1.0);
        tex_coords[currT+2] = v2(0.5, 0.5);
        tex_coords[currT+3] = v2(0.0, 1.0); //
        tex_coords[currT+4] = v2(0.5, 0.5);
        tex_coords[currT+5] = v2(0.0, 0.5);
        currT += 6;
    }

    // colors
    for (int i = 0; i < TOTALVERTICES; i++) {
        colors[i] = v4(1.0, 0.0, 0.0, 1.0);
    }
}

/**/

void init(void)
{
    int width = 800; // CHANGE
    int height = 800; // CHANGE
    GLubyte my_texels[width][height][3];

    FILE *fp = fopen("p2texture04.raw", "r");  // CHANGE
    fread(my_texels, width * height * 3, 1, fp);
    fclose(fp);

    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(tex_coords), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(tex_coords), tex_coords);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0 + sizeof(vertices));

    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0 + (sizeof(vertices) + sizeof(colors)));

    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    printf("texture_location: %i\n", texture_location);

    //projection = frustum(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    //   tans: -0.05, 0.05, -0.05, 0.05, -0.2, -4
    //   tans: -1.0, 1.0, -1.0, 1.0, -1.0, -10.0
    //model_view = look_at_coord(-4.0, 3.0, -4.0, -4.0, 0.0, -4.0, -1.0, 0.0, 0.0);
    //model_view = look_at_coord(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    /* // THIS ORTHO VIEW WORKS FOR LOOKING AT THE ENTRANCE 
    projection = ortho(-2, 2, -2, 2, 0, -8);
    model_view = look_at_coord(0.5, 2.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0);*/

    projection = frustum(-0.15, 0.15, -0.15, 0.15, -.15, 12.0);
    model_view = look_at_coord(4.0, 8.0, 4.0, 4.0, 0.0, 4.0, 1.0, 1.0, 0.0);

    ctm_location = glGetUniformLocation(program, "ctm");
    model_view_location = glGetUniformLocation(program, "model_view");
    projection_location = glGetUniformLocation(program, "projection_matrix");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) ctm);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) model_view);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) projection);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glutSwapBuffers();
}

vec4* start_eye;
vec4* end_eye;
vec4* curr_eye;
vec4* start_at;
vec4* end_at;
vec4* curr_at;
vec4* start_up;
vec4* end_up;
vec4* curr_up;

state currentState = IDLE; // CHANGE
int isAnimating = 0;
int current_step = 0;
int max_steps;
float alpha = 0.0;

void keyboard(unsigned char key, int mousex, int mousey)
{
    if (key == ' ') {
        if (isAnimating == 0) {
            currentState = FLYING_TO_START; // CHANGE
        }
    }
    else if (key == 'q')
        exit(0);
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

orientation currFacing = EAST;
int curr_step = 0;

void idle(void)
{
    if (isAnimating) {
        current_step++;

        if(currentState == FLYING_TO_START) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = FLYING_AROUND;
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector(alpha, end_eye, start_eye);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
        }
        else if(currentState == FLYING_AROUND) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = FLYING_DOWN;
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector_pi(alpha, 6.0);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
        }
        else if(currentState == FLYING_DOWN) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = BEGIN;
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector(alpha, end_eye, start_eye);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
        }
        else if(currentState == WALK_FORWARD) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = solution[curr_step];
                curr_step++;
                printf("walked.\n");
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector(alpha, end_eye, start_eye);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
            
        }
        else if(currentState == TURN_LEFT) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = solution[curr_step];
                curr_step++;
                printf("turned left.\n");
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector(alpha, end_eye, start_eye);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
            
        }
        else if(currentState == TURN_RIGHT) {
            if(current_step == max_steps) {
                isAnimating = 0;
                alpha = 1.0;
                currentState = solution[curr_step];
                curr_step++;
                printf("turned right.\n");
            }
            else {
                alpha = (float) current_step / max_steps;
            }
            curr_eye = changing_vector(alpha, end_eye, start_eye);
            curr_at = changing_vector(alpha, end_at, start_at);
            curr_up = changing_vector(alpha, end_up, start_up);
            model_view = look_at(curr_eye, curr_at, curr_up);
            
        }
        glutPostRedisplay();
    }

    else { // if not animating

        if(currentState == FLYING_TO_START)
        {
            max_steps = 250;
            current_step = 0;
            isAnimating = 1;

            start_eye = v4_a(4.0, 8.0, 4.0, 0.0);
            end_eye = changing_vector_pi(0.0, 6.0);
            //end_eye = v4_a(4.0, 4.0, 10.0, 0.0);

            start_at = v4_a(4.0, 0.0, 4.0, 0.0);
            end_at = v4_a(4.0, 1.0, 4.0, 0.0);

            start_up = v4_a(1.0, 0.0, 0.0, 0.0);
            end_up = v4_a(0.0, -1.0, 0.0, 0.0);
        }
        else if(currentState == FLYING_AROUND) {
            max_steps = 1000; //180
            current_step = 0;
            isAnimating = 1;

            start_eye = changing_vector_pi(0.0, 6.0);
            end_eye = changing_vector_pi(1.0, 6.0);
            //start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
            //end_eye = v4_a(10.0, 4.0, 4.0, 0.0);

            start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
            end_at = v4_a(4.0, 1.0, 4.0, 0.0);

            start_up = v4_a(end_up->x, end_up->y, end_up->z, 0.0);
            end_up = v4_a(0.0, -1.0, 0.0, 0.0);
        }
        else if(currentState == FLYING_DOWN) {
            max_steps = 250;
            current_step = 0;
            isAnimating = 1;

            start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
            end_eye = v4_a(0.5, 0.5, -0.5, 0.0);

            start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
            end_at = v4_a(0.5, 0.5, 0.5, 0.0);

            start_up = v4_a(end_up->x, end_up->y, end_up->z, 0.0);
            end_up = v4_a(0.0, -1.0, 0.0, 0.0);
        }
        else if(currentState == WALK_FORWARD) {
            max_steps = 100;
            current_step = 0;
            isAnimating = 1;

            // up vector does not change
            start_up = v4_a(end_up->x, end_up->y, end_up->z, 0.0);

            if (currFacing == EAST) {
                start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
                end_eye = v4_a(start_eye->x, start_eye->y, start_eye->z + 1, 0.0);

                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x, start_at->y, start_at->z + 1, 0.0);
            }
            else if (currFacing == WEST) {
                start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
                end_eye = v4_a(start_eye->x, start_eye->y, start_eye->z - 1, 0.0);

                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x, start_at->y, start_at->z - 1, 0.0);
            }
            else if (currFacing == NORTH) {
                start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
                end_eye = v4_a(start_eye->x + 1, start_eye->y, start_eye->z, 0.0);

                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x + 1, start_at->y, start_at->z, 0.0);
            }
            else if (currFacing == SOUTH) {
                start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
                end_eye = v4_a(start_eye->x - 1, start_eye->y, start_eye->z, 0.0);

                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x - 1, start_at->y, start_at->z, 0.0);
            }
        }
        else if(currentState == TURN_LEFT) {
            max_steps = 100;
            current_step = 0;
            isAnimating = 1;

            // eye and up vector does not change
            start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
            start_up = v4_a(end_up->x, end_up->y, end_up->z, 0.0);

            if (currFacing == EAST) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x + 1, start_at->y, start_at->z - 1, 0.0);
                currFacing = NORTH;
            }
            else if (currFacing == NORTH) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x - 1, start_at->y, start_at->z - 1, 0.0);
                currFacing = WEST;
            }
            else if (currFacing == WEST) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x - 1, start_at->y, start_at->z + 1, 0.0);
                currFacing = SOUTH;
            }
            else if (currFacing == SOUTH) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x + 1, start_at->y, start_at->z + 1, 0.0);
                currFacing = EAST;
            }
        }
        else if(currentState == TURN_RIGHT) {
            max_steps = 100;
            current_step = 0;
            isAnimating = 1;

            // eye and up vector does not change
            start_eye = v4_a(end_eye->x, end_eye->y, end_eye->z, 0.0);
            start_up = v4_a(end_up->x, end_up->y, end_up->z, 0.0);

            if (currFacing == NORTH) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x - 1, start_at->y, start_at->z + 1, 0.0);
                currFacing = EAST;
            }
            else if (currFacing == EAST) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x - 1, start_at->y, start_at->z - 1, 0.0);
                currFacing = SOUTH;
            }
            else if (currFacing == SOUTH) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x + 1, start_at->y, start_at->z - 1, 0.0);
                currFacing = WEST;
            }
            else if (currFacing == WEST) {
                start_at = v4_a(end_at->x, end_at->y, end_at->z, 0.0);
                end_at = v4_a(start_at->x + 1, start_at->y, start_at->z + 1, 0.0);
                currFacing = NORTH;
            }
        }
        else if(currentState == BEGIN) {
            currentState = solution[curr_step];
            curr_step++;
        }
    }
    
    //model_view = look_at(xxx,0.1,0, 0,0,0, 0,1,0);
}

int main(int argc, char **argv)
{
    getMaze();
    printmaze();
    printf("walls: %d\n", numOfWalls());
    solve();
    solveShort();
    //printsol();

    getVertices();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Maze");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();


    return 0;
}