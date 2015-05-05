#include "graphics/window.h"
#include "graphics/shader.h"

#include "graphics/buffer.h"
#include "graphics/indexbuffer.h"
#include "graphics/vertexarray.h"

#include "graphics/renderer2d.h"
#include "graphics/simple2drenderer.h"

int main() {

  using namespace sparky;
  using namespace graphics;
  using namespace maths;

  sparky::graphics::Window window("Sparky!", 960,540);
  //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#if 0
  std::cout << glGetString(GL_VERSION) << std::endl;

  GLfloat vertices[] = 
  {
    0, 0, 0,
    8, 0, 0,
    0, 3, 0,
    0, 3, 0,
    8, 3, 0,
    8, 0, 0,
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  GLfloat vertices[] = 
  {
    0, 0, 0,
    0, 3, 0,
    8, 3, 0,
    8, 0, 0,
  };

  GLushort indices[] = 
  {
    0, 1, 2,
    2, 3, 0
  };

  GLfloat colorsA[] =
  {
    1, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 1
  };

  GLfloat colorsB[] =
  {
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1
  };

  VertexArray sprite1, sprite2;
  IndexBuffer ibo(indices, 6);

  sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
  sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

  sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
  sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

#endif

  mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);



  Shader shader("shaders/basic.vert", "shaders/basic.frag");
  shader.enable();
  shader.setUniformMat4("pr_matrix", ortho);
  shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

  Renderable2D sprite1(maths::vec3(5, 5, 0), maths::vec2(4, 4), maths::vec4(1,0,1,1), shader);
  Renderable2D sprite2(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2f,0,1,1), shader);
  Simple2DRenderer renderer;


  shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
  shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

  while (!window.closed()) {

//std::cout << window.getWidth() << "x" << window.getHeight() << std::endl;
    window.clear();
    double x,y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
    renderer.submit(&sprite1);
    renderer.submit(&sprite2);
    renderer.flush();
    window.update();
  }

  return 0;
}


