#pragma once

namespace sts {

struct MuzzleFlashStyle
{
	MuzzleFlashStyle(const std::string& _id, const std::string& _colormap_hue, const std::string& _sound)
			:id(_id), colormap_hue(_colormap_hue), sound(_sound) {}
	std::string id;
	/* convert to hex immediately? */
	std::string colormap_hue;
	std::string sound;
};

} // namespace sts
