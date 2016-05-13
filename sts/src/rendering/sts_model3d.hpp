#pragma once

#include "sts_renderable.hpp"

namespace sts {

class Model3D: public Renderable
{
public:
	/** Creates a 3D model from a *.mesh file. Use it instead of new operator.
	  * @arg name - renderable name (to obtain it from the GameRoot).
	  * @arg modelFilename - name of the *.mesh file.
	  * @arg scale - model scale.
	  * You don't need to destroy it by yourself. All the renderables will be destroyed
	  * during the scene cleaning.
	  */
	static Model3D* create(std::string name, std::string modelFilename, float scale = 1.0f);

	~Model3D();
	IAttachable* _spawnAttachable(Ogre::SceneNode* node) const;
	std::string modelFilename() const;
	float scale() const;

private:
	std::string _modelFilename;
	float _modelScale;

	/** Default constructor is private to prevent creation via new */
	Model3D(std::string name, std::string modelFilename, float scale);

	/** Duplicating is prohibited */
	Model3D(const Model3D&);
};

} // namespace sts
