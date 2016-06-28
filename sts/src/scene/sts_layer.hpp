#pragma once

#include "sts_object_group.hpp"
#include "sts_layered_object.hpp"

namespace sts {

class SceneManager;

class Layer: public ObjectGroup<LayeredObject>
{
public:
	Layer(SceneManager* sceneMgr, unsigned int lIndex);
	~Layer();

	void addObject(LayeredObject* object);
	std::list<LayeredObject*> objects();
	void removeObject(LayeredObject* object);

	float z() const;

	unsigned char opacity() const;
	void setOpacity(unsigned char value);
	int speed() const;
	void setSpeed(int value);
	SceneManager* sceneManager();

	void processLayer(unsigned int msec);

private:
	SceneManager* _scene;
	unsigned int _layerIndex;
	int _speed;
	unsigned char _opacity;
	std::list<LayeredObject*> _objects;

	Layer(const Layer&);
};

} // namespace sts
