//
// sueda
// October, 2014
//
// Adapted from:
//   GLSL_helper.h
//   CSC473
//
//    Many useful helper functions for GLSL shaders - gleaned from various sources including orange book
//    Created by zwood on 2/21/10.

#include <GLSL.hpp>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cassert>

#include <log.hpp>

static std::string errorStringGL(GLenum err) {
   switch (err) {
   case GL_NO_ERROR: return "GL_NO_ERROR";
   case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
   case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
   case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
   case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
   case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
   case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
   case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
   default: return "DEFAULT ERROR STRING SHOULD NOT HAPPEN!";
   }
}

namespace GLSL {

   int printError()
   {
      // Returns 1 if an OpenGL error occurred, 0 otherwise.
      GLenum glErr;
      int retCode = 0;
	
      glErr = glGetError();
      while(glErr != GL_NO_ERROR) {
         printf("glError in file %s @ line %d: %s\n", __FILE__, __LINE__, errorStringGL(glErr).c_str());
         retCode = 1;
         glErr = glGetError();
      }
      return retCode;
   }

   void printShaderInfoLog(GLuint shader)
   {
      GLint infologLength = 0;
      GLint charsWritten  = 0;
      GLchar *infoLog;
	
      printError();
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);
      printError();
	
      if(infologLength > 0) {
         infoLog = (GLchar *)malloc(infologLength);
         if(infoLog == NULL) {
            puts("ERROR: Could not allocate InfoLog buffer");
            exit(1);
         }
         glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
         printf("Shader InfoLog:\n%s\n\n", infoLog);
         free(infoLog);
      }
      printError();
   }

   void printProgramInfoLog(GLuint program)
   {
      GLint infologLength = 0;
      GLint charsWritten  = 0;
      GLchar *infoLog;
	
      printError();
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);
      printError();
	
      if(infologLength > 0) {
         infoLog = (GLchar *)malloc(infologLength);
         if(infoLog == NULL) {
            puts("ERROR: Could not allocate InfoLog buffer");
            exit(1);
         }
         glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
         printf("Program InfoLog:\n%s\n\n", infoLog);
         free(infoLog);
      }
      printError();
   }

   void checkVersion()
   {
      int major, minor;
      major = minor = 0;
      const char *verstr = (const char *)glGetString(GL_VERSION);
	
      if((verstr == NULL) || (sscanf(verstr, "%d.%d", &major, &minor) != 2)) {
         printf("Invalid GL_VERSION format %d %d\n", major, minor);
      }
      if(major < 2) {
         printf("This shader example will not work due to opengl version, which is %d %d\n", major, minor);
         exit(0);
      }
   }

   char *textFileRead(const char *fn)
   {
      FILE *fp;
      char *content = NULL;
      int count = 0;
      if(fn != NULL) {
         fp = fopen(fn,"rt");
         if(fp != NULL) {
            fseek(fp, 0, SEEK_END);
            count = (int)ftell(fp);
            rewind(fp);
            if(count > 0) {
               content = (char *)malloc(sizeof(char) * (count+1));
               count = (int)fread(content,sizeof(char),count,fp);
               content[count] = '\0';
            }
            fclose(fp);
         } else {
            printf("error loading %s\n", fn);
         }
      }
      return content;
   }

   int textFileWrite(const char *fn, char *s)
   {
      FILE *fp;
      int status = 0;
      if(fn != NULL) {
         fp = fopen(fn,"w");
         if(fp != NULL) {
            if(fwrite(s,sizeof(char),strlen(s),fp) == strlen(s)) {
               status = 1;
            }
            fclose(fp);
         }
      }
      return(status);
   }

   GLint getAttribLocation(const GLuint program, const char varname[])
   {
      GLint r = glGetAttribLocation(program, varname);

      if (r < 0)
         std::cerr << "WARN: "<< varname << " cannot be bound (it either doesn't exist or has been optimized away). safe_glAttrib calls will silently ignore it.\n" << std::endl;
      LOG("program " << program << " varname " << varname << " location " << r);
      return r;
   }


   GLint getUniformLocation(const GLuint program, const char varname[])
   {
      GLint r = glGetUniformLocation(program, varname);
      if(r < 0) {
         std::cerr << "WARN: "<< varname << " cannot be bound (it either doesn't exist or has been optimized away). safe_glUniform calls will silently ignore it.\n" << std::endl;
      }
      return r;
   }


   void enableVertexAttribArray(const GLint handle)
   {
      if(handle >= 0) {
         glEnableVertexAttribArray(handle);
      }
   }

   void disableVertexAttribArray(const GLint handle)
   {
      if(handle >= 0) {
         glDisableVertexAttribArray(handle);
      }
   }

   void vertexAttribPointer(const GLint handle, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
   {
      if(handle >= 0) {
         glVertexAttribPointer(handle, size, type, normalized, stride, pointer);
      }
   }

}
