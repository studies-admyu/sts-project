#pragma once

#include <string>

namespace sts {

struct Entity {
	// This is just a stub, actually we will load a model here. We will also need to separate models from colormap.
	Entity(const std::string &_id, const std::string &_model_name, const std::string &_colormap_hue)
			: id(_id), modelName(_model_name), colormapHue(_colormap_hue) { }

	std::string id;
	/* convert to hex immediately? */
	std::string colormapHue;
	std::string modelName;
};

}


