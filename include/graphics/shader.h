#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "maths/maths.h"
#include "utils/fileutils.h"
#include <map>

namespace sparky { namespace graphics {

  class Shader
  {
  private:
    std::map<GLchar, GLint> locations;
  public:
      GLuint m_ShaderID;
      GLint  m_Location;
      const char *m_VertPath;
      const char *m_FragPath;

    public:
      Shader(const char* vertPath, const char* fragPath);
      ~Shader();


      void setUniform1i(const GLchar* name, const int value);
      void setUniform1f(const GLchar* name, const float value);
      void setUniform2f(const GLchar* name, const maths::vec2& vector);
      void setUniform3f(const GLchar* name, const maths::vec3& vector);
      void setUniform4f(const GLchar* name, const maths::vec4& vector);
      void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

      void enable() const;
      void disable() const;

    private:
      GLuint load();
      GLint getUniformLocation(const GLchar* name);
  };

}}
