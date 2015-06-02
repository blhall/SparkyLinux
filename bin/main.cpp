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

#include "graphics/layers/tilelayer.h"

#include <vector>
#include "utils/timer.h"


int main() {

  using namespace sparky;
  using namespace graphics;
  using namespace maths;

  Window window("Sparky!", 960,540);

//  mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

  Shader shader("shaders/basic.vert", "shaders/basic.frag");

  shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

  TileLayer layer(&shader);
  layer.add(new Sprite(0, 0, 2, 2, maths::vec4(0.8f, 0.2f, 0.8f, 1.0f)));

//FPS calculations
  Timer time;
  float timer(0);
  unsigned int frames(0);

  while (!window.closed()) 
  {

    window.clear();
    double x,y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

    layer.render();

    window.update();
    frames++;
    if (time.elapsed() - timer > 1.0f)
    {
      timer += 1.0f;
      printf("FPS: %d\n", frames);
      frames=0;
    }
  }

  return 0;
}


