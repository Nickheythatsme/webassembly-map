// Copyright 2015 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#ifndef __EMSCPRIPTEN__
    #include "SDL.h"
    #include "SDL_opengl.h"
    #include "sdl2_arb.h"
#else
    #include <emscripten.h>
    #include "SDL2/sdl.h"
    #include "SDL2/SDL_opengl.h"
#endif
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

static void sdlError(const char *str) 
{
    fprintf(stderr, "Error at %s: %s\n", str, SDL_GetError());
    exit(1);
}

void setShaders() {
#ifdef __EMSCRIPTEN__
    GLuint v, f, p;
#else
    void *v, *f, *p;
#endif
    GLint ok;

    const char *vv = "void main()                   \n"
        "{                             \n"
        "  gl_Position = ftransform() + vec4(0.1, -0.25, 0, 0); \n"
        "}";
    const char *ff = "void main()                \n"
        "{	                         \n"
        "  gl_FragColor = vec4(gl_FragCoord.y/480.0, gl_FragCoord.x/640.0, 0.66, 1.0); \n"
        "}";

    v = glCreateShaderObject_(GL_VERTEX_SHADER);
    f = glCreateShaderObject_(GL_FRAGMENT_SHADER);

    glShaderSource_(v, 1, &vv,NULL);
    glShaderSource_(f, 1, &ff,NULL);

    glCompileShader_(v);
    glGetObjectParameteriv_(v, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
    if (!ok) {
        char msg[512];
        glGetInfoLog_(v, sizeof msg, NULL, msg);
        printf("shader compilation issue: %s\n", msg);
    }
    assert(ok);

    glCompileShader_(f);
    glGetObjectParameteriv_(f, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
    assert(ok);

    p = glCreateProgramObject_();
    glAttachObject_(p, f);
    glAttachObject_(p, v);

    glLinkProgram_(p);
    glGetObjectParameteriv_(p, GL_OBJECT_LINK_STATUS_ARB, &ok);
    assert(ok);

    glUseProgramObject_(p);
}

int main(void) {
    SDL_Window *window;
    SDL_GLContext context;

    // Create SDL windows
    if (SDL_Init(SDL_INIT_VIDEO) != 0) sdlError("SDL_Init");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == nullptr) sdlError("SDL_CreateWindow");
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) sdlError("SDL_CreateContext");

    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    initARB();
    setShaders();

    glColor3f(0, 1, 1); // is overridden by the shader, useful for debugging native builds
    glBegin(GL_TRIANGLES);

    glTexCoord2i(0, 0); glVertex3f( 10,  10,  0);
    glTexCoord2i(1, 0); glVertex3f( 300, 10,  0);
    glTexCoord2i(1, 1); glVertex3f( 300, 328, 0);
    glEnd();

    SDL_GL_SwapWindow(window);
    // draw(window, surface);

#ifndef __EMSCRIPTEN__
    SDL_Event e;
bool quit = false;
while (!quit){
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            quit = true;
        }
        if (e.type == SDL_KEYDOWN){
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN){
            quit = true;
        }
    }
}
    SDL_DestroyWindow(window);
#endif

    SDL_Quit();
}

