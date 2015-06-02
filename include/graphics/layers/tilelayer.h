#pragma once

#include "graphics/layers/layer.h"
#include "graphics/BatchRenderer2D.h"

namespace sparky { namespace graphics {
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};
}}