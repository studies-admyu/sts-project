#pragma once

#include <memory>

#include <rendering/sts_renderable.hpp>

namespace sts {

class SceneObject
{
friend class SceneManager;

public:
	struct Position
	{
		Position(int i_x = 0, int i_y = 0):
			x(i_x), y(i_y) { }

		int x;
		int y;
	};

	virtual ~SceneObject();

	bool isVisible() const;
	void setVisible(bool value);
	virtual void setPosition(const Position& pos);
	virtual Position position() const;
	void setPlanarRotation(float radians);
	float planarRotation() const;
	void setAxisRotation(float radians);
	float axisRotation() const;
	virtual void processObject();

protected:
	SceneObject(Renderable* renderable);
	SceneObject(std::string renderableName);
	IAttachable* attachable();
	const IAttachable* attachable() const;

private:
	std::unique_ptr<IAttachable> _attachable;

	SceneObject(const SceneObject&);
};

} // namespace sts
