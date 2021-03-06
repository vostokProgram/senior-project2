#ifndef _GBUFFER_H
#define _GBUFFER_H

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <types.h>

class Gbuffer {
    // attachment points
    static const int num_attachments = 7;
    GLuint attachments[7]; // initialized in init
public:
    // handle to Frame Buffer Object
    GLuint fbo; 
    // handle to individual buffers
    GLuint gpos;
    GLuint gnor;
    GLuint gcol;
    GLuint gspc;
    GLuint zbuf;
    GLuint gfinal;
    GLuint gvposd; // view space position and depth
    GLuint gvnor;
    GLuint gid;

    bool init(uint width, uint height);
    void bind();
    void bindTextures();
    void unbindTextures();
    void copyDepthBuffer(uint width, uint height);
    void startFrame();
    void bindFinalBuffer();
    void unbindFinalBuffer();
    void copyFinalBuffer(uint width, uint height);
};

#endif
