#include "graphics/window.h"
#include "graphics/shader.h"

#include "graphics/buffer.h"
#include "graphics/indexbuffer.h"
#include "graphics/vertexarray.h"

#include "graphics/renderer2d.h"
#include "graphics/simple2drenderer.h"
#include "graphics/BatchRenderer2D.h"

#include "graphics/sprite.h"
#include "graphics/static_sprite.h"

#include <vector>
#include <time.h>


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

#define BATCH_RENDER 1
  std::vector<Renderable2D*> sprites;
  srand(time(NULL));

  for (float y =0; y < 9.0f; y += 0.05)
  {
    for (float x = 0; x < 16.0f; x += 0.05)
    {
      sprites.push_back(new
#if BATCH_RENDER          
          Sprite
#else
          StaticSprite
#endif
          (x, y, 0.04f, 0.04f, maths::vec4(rand() %1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDER                      
          ,shader
#endif
          ));
    }
  }


#if BATCH_RENDER
  Sprite sprite1(5, 5, 4, 4, maths::vec4(1,0,1,1));
  Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f,0,1,1));
  BatchRenderer2D renderer;
#else
  StaticSprite sprite1(5, 5, 4, 4, maths::vec4(1,0,1,1), shader);
  StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f,0,1,1), shader);
  Simple2DRenderer renderer;
#endif

  shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
  shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

  while (!window.closed()) {

//std::cout << window.getWidth() << "x" << window.getHeight() << std::endl;
    window.clear();
    double x,y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

#if BATCH_RENDER
    renderer.begin();
#endif

    for (unsigned int i = 0; i < sprites.size(); i++)
    {
      renderer.submit(sprites[i]);
    }

#if BATCH_RENDER
    renderer.end();
#endif

    renderer.flush();
//    printf("Sprites: %d\n", sprites.size());
    window.update();
  }

  return 0;
}


