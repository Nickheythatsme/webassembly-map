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
#endif
#include <assert.h>

static void sdlError(const char *str) 
{
    fprintf(stderr, "Error at %s: %s\n", str, SDL_GetError());
#ifdef __EMSCRIPTEN__
    emscripten_force_exit(1);
#endif
}

void setShaders() {
    GLuint v, f, p;
    GLint ok;

    const char *vv = "void main()                   \n"
        "{                             \n"
        "  gl_Position = ftransform() + vec4(0.1, -0.25, 0, 0); \n"
        "}";
    const char *ff = "void main()                \n"
        "{	                         \n"
        "  gl_FragColor = vec4(gl_FragCoord.y/480.0, gl_FragCoord.x/640.0, 0.66, 1.0); \n"
        "}";

    v = (unsigned long long) glCreateShaderObject_(GL_VERTEX_SHADER);
    f = (unsigned long long) glCreateShaderObject_(GL_FRAGMENT_SHADER);

    glShaderSource_((void *)v, 1, &vv,NULL);
    glShaderSource_((void *)f, 1, &ff,NULL);

    glCompileShader_((void *)v);
    glGetObjectParameteriv_((void *)v, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
    if (!ok) {
        char msg[512];
        glGetInfoLog_((void *)v, sizeof msg, NULL, msg);
        printf("shader compilation issue: %s\n", msg);
    }
    assert(ok);

    glCompileShader_((void *)f);
    glGetObjectParameteriv_((void *)f, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
    assert(ok);

    p = (unsigned long long) glCreateProgramObject_();
    glAttachObject_((void *)p, (void *)f);
    glAttachObject_((void *)p, (void *)v);

    glLinkProgram_((void *)p);
    glGetObjectParameteriv_((void *)p, GL_OBJECT_LINK_STATUS_ARB, &ok);
    assert(ok);

    glUseProgramObject_((void *)p);
}


void draw(SDL_Window *window, SDL_Surface *surface) {
    int x, y;

    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) != 0) sdlError("SDL_LockSurface");
    }

    for (y = 0; y < 256; y++) {
        Uint32 *p = (Uint32 *)(((Uint8 *)surface->pixels) +
                               surface->pitch * y);
        for (x = 0; x < 256; x++) {
            *(p++) = SDL_MapRGB(surface->format, x, x ^ y, y);
        }
    }

    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    if (SDL_UpdateWindowSurface(window) != 0)
        sdlError("SDL_UpdateWindowSurface");
}

int main(void) {
    SDL_Window *window;
    SDL_GLContext context;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) sdlError("SDL_Init");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow("sdlglshader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

    if (window == NULL) sdlError("SDL_CreateWindow");
    context = SDL_GL_CreateContext(window);
    if (context == NULL) sdlError("SDL_CreateContext");

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
    glBegin( GL_TRIANGLES );
    glTexCoord2i(0, 0); glVertex3f( 10,  10,  0);
    glTexCoord2i(1, 0); glVertex3f( 300, 10,  0);
    glTexCoord2i(1, 1); glVertex3f( 300, 328, 0);
    glEnd();

    glColor3f(1, 1, 0); // is overridden by the shader, useful for debugging native builds
    glBegin( GL_TRIANGLES );
    glTexCoord2f(0, 0.5); glVertex3f(410, 10,  0);
    glTexCoord2f(1, 0.5); glVertex3f(600, 10,  0);
    glTexCoord2f(1, 1  ); glVertex3f(630, 400, 0);
    glEnd();

    SDL_GL_SwapWindow(window);
    // draw(window, surface);

#ifndef __EMSCRIPTEN__
    SDL_Delay(3000);
#endif

#ifdef __EMSCRIPTEN__
    int result = 1;
    REPORT_RESULT(result);
#endif
}

