#pragma once

#include <GL/glew.h>
#include "maths/maths.h"
#include "graphics/renderable2d.h"


namespace sparky { namespace graphics {

  class Renderer2D
  {
  public:
  	virtual void begin() =0;
  	virtual void end() =0;
  	virtual void submit(const Renderable2D* renderable) =0;
  	virtual void flush() =0;
  };

}}
