#pragma once

#include <memory>

#include <rendering/sts_renderable.hpp>

namespace sts {

class IMotionState;

class SceneObject
{
friend class SceneManager;

public:
	struct Position
	{
		Position(int i_x = 0, int i_y = 0):
			x(i_x), y(i_y) { }
		Position operator+(const Position& p) const
			{ return Position(this->x + p.x, this->y + p.y); }
		Position operator-(const Position& p) const
			{ return Position(this->x - p.x, this->y - p.y); }

		int x;
		int y;
	};

	virtual ~SceneObject();

	void _setMotionState(IMotionState* newState);

	bool isVisible() const;
	void setVisible(bool value);
	virtual void setPosition(const Position& pos);
	virtual Position position() const;
	void setPlanarRotation(float radians);
	float planarRotation() const;
	void setAxisRotation(float radians);
	float axisRotation() const;

	IMotionState* motionState();
	const IMotionState* motionState() const;

	virtual void processObject(unsigned int msec);

protected:
	SceneObject(Renderable* renderable);
	SceneObject(std::string renderableName);
	IAttachable* attachable();
	const IAttachable* attachable() const;

private:
	std::unique_ptr<IAttachable> _attachable;
	std::unique_ptr<IMotionState> _motionState;

	SceneObject(const SceneObject&);
	void initObject(Renderable* renderable);
};

} // namespace sts
