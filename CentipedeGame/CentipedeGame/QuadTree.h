#pragma once
#include "CentipedeGameApp.h"
#include "Sprite.h"
#include <glm\vec2.hpp>

using namespace glm;

class AABB
{
public:
	vec2 center;
	vec2 halfSize;

	AABB() {}
	AABB(vec2 _center, vec2 _halfSize) 
	{
		center = _center;
		halfSize = _halfSize;
	}
	~AABB() {}

	bool Contains(vec2 point)
	{
		return (point.x < center.x + halfSize.x &&
			point.x > center.x - halfSize.x &&
			point.y < center.y + halfSize.y &&
			point.y > center.y - halfSize.y);
	}

	bool Contains(Point2D point)
	{
		return (point.x < center.x + halfSize.x &&
			point.x > center.x - halfSize.x &&
			point.y < center.y + halfSize.y &&
			point.y > center.y - halfSize.y);
	}

	bool Intersects(AABB other)
	{
		return !(center.x + halfSize.x < other.center.x - other.halfSize.x ||
			center.x - halfSize.x > other.center.x + other.halfSize.x ||
			center.y + halfSize.y < other.center.y - other.halfSize.y ||
			center.y - halfSize.y > other.center.y + other.halfSize.y);
	}
};

class QuadTree
{
private:
	QuadTree** children;
	AABB boundary;
	Sprite** objects;

public:
	static const int CAPACITY = 2;

	enum SUBTREE { TOP_LEFT = 0, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

	QuadTree()
	{
		children = nullptr;
		objects = nullptr;
		boundary.halfSize.x = CentipedeGameApp::instance->getWindowWidth() / 2;
		boundary.halfSize.y = CentipedeGameApp::instance->getWindowHeight() / 2;
		boundary.center = boundary.halfSize;
	}

	QuadTree(AABB _boundary)
	{
		children = nullptr;
		objects = nullptr;
		boundary = _boundary;
	}

	~QuadTree()
	{
		if (children != nullptr)
		{
			for (int i = 0; i < 4; ++i)
				if (children[i] != nullptr)
					delete children[i];
			delete children;
			children = nullptr;
		}

		if (objects != nullptr)
			delete objects;
	}

	bool Insert(Sprite* sprite)
	{
		if (!boundary.Contains(sprite->position))
			return false;

		if (children == nullptr)
		{
			if (objects == nullptr)
			{
				objects = new Sprite*[CAPACITY];
				memset(objects, 0, sizeof(Sprite*) * CAPACITY);
			}

			if (objects[CAPACITY - 1] == nullptr)
			{
				for (int i = 0; i < CAPACITY; ++i)
					if (objects[i] == nullptr)
					{
						objects[i] = sprite;
						return true;
					}
			}

			SubDivide();
		}

		for (int i = 0; i < 4; ++i)
			if (children[i]->Insert(sprite))
				return true;

		return false;
	}

	void SubDivide()
	{
		children = new QuadTree*[4];

		vec2 qSize = vec2(boundary.halfSize.x / 2, boundary.halfSize.y / 2);

		vec2 qCenter = vec2(boundary.center.x - qSize.x, boundary.center.y - qSize.y);
		children[TOP_LEFT] = new QuadTree(AABB(qCenter, qSize));

		qCenter = vec2(boundary.center.x + qSize.x, boundary.center.y - qSize.y);
		children[TOP_RIGHT] = new QuadTree(AABB(qCenter, qSize));

		qCenter = vec2(boundary.center.x - qSize.x, boundary.center.y + qSize.y);
		children[BOTTOM_LEFT] = new QuadTree(AABB(qCenter, qSize));

		qCenter = vec2(boundary.center.x + qSize.x, boundary.center.y + qSize.y);
		children[BOTTOM_RIGHT] = new QuadTree(AABB(qCenter, qSize));

		if (objects != nullptr)
		{
			for (int i = 0; i < CAPACITY; ++i)
			{
				if (objects[i] == nullptr)
					continue;

				for (int j = 0; j < 4; ++j)
					if (children[j]->Insert(objects[i]))
						break;

				objects[i] = nullptr;
			}

			delete objects;
			objects = nullptr;
		}
	}

	void Clear()
	{
		*this = QuadTree();
	}

	void Draw(Renderer2D* renderer)
	{
		renderer->setRenderColour(1, 0, 0);
		renderer->drawLine
		(
			boundary.center.x - boundary.halfSize.x,
			boundary.center.y - boundary.halfSize.y,
			boundary.center.x + boundary.halfSize.x,
			boundary.center.y - boundary.halfSize.y
		);
		renderer->drawLine
		(
			boundary.center.x - boundary.halfSize.x,
			boundary.center.y + boundary.halfSize.y - 1,
			boundary.center.x + boundary.halfSize.x,
			boundary.center.y + boundary.halfSize.y - 1
		);
		renderer->drawLine
		(
			boundary.center.x - boundary.halfSize.x + 1,
			boundary.center.y + boundary.halfSize.y,
			boundary.center.x - boundary.halfSize.x + 1,
			boundary.center.y - boundary.halfSize.y
		);
		renderer->drawLine
		(
			boundary.center.x + boundary.halfSize.x,
			boundary.center.y + boundary.halfSize.y,
			boundary.center.x + boundary.halfSize.x,
			boundary.center.y - boundary.halfSize.y
		);

		if (children != nullptr)
			for (int i = 0; i < 4; ++i)
				children[i]->Draw(renderer);
	}
};