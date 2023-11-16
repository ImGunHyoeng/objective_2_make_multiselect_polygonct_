#include <cstdlib> // include rand()
#include <Windows.h>
#include <conio.h>
#include "GameObject.h"
#include "Canvas.h"
#include "Cards.h"
#include "Enemy.h"
#include "Bullet.h"
#include "InputManager.h"
#include <algorithm>
#include "RegularPolygon.h"
#include "Selector.h"
#include "RegularPolygonMgr.h"

using namespace std;

Canvas GameObject::canvas(5*9, 7*7);
vector<GameObject*> GameObject::objs;


void GameObject::draw() { if (alive == true) canvas.draw(shape, position, dimension, visible); }

void GameObject::Initialize()
{
	objs.clear();
	vector<RegularPolygon*> polygonvec;
	auto dim = canvas.getDimension();/*
	auto polygon = new RegularPolygon(2, { dim.x / 2, dim.y / 2 }, 10.0f);
	auto polygon1 = new RegularPolygon(2, { dim.x / 2, dim.y / 2 }, 10.0f);
	auto polygon2 = new RegularPolygon(2, { dim.x / 2, dim.y / 2 }, 10.0f);
	auto polygon3 = new RegularPolygon(2, { dim.x / 2, dim.y / 2 }, 10.0f);
	auto polygon4 = new RegularPolygon(2, { dim.x / 2, dim.y / 2 }, 10.0f);*/
	for (int i = 0; i < 5; i++)
	{
		polygonvec.push_back(new RegularPolygon(2+i, { rand() % (dim.x / 2),rand() % (dim.y / 2)}, 10.0-i));
	}
	auto polymgr = new RegularPolygonMgr();
	for_each(polygonvec.begin(), polygonvec.end(), [&](auto it) {polymgr->addPolygon(it);});
	
	auto selector = new Selector(Position{0,0},Position{0,0},*polymgr);
	GameObject::Add(selector);
	GameObject::Add(polymgr);
	for_each(polygonvec.begin(), polygonvec.end(), [](auto it) {GameObject::Add(it); });
	
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;

	objs.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;

	auto it = find(objs.begin(), objs.end(), obj);
	if (it == objs.end()) return;

	objs.erase(it);
	delete obj;
}

void GameObject::ClearFrame()
{
	canvas.clear();
}

void GameObject::ProcessInput(bool& exit_flag, InputManager& input)
{
	Bullet* bullet = nullptr;

	if (input.getKey('I')) {
		for (auto obj : objs)
		{
			auto pos = obj->getPosition();
			Debug::Log("[%s (%2d, %2d) %d %d] ", obj->getShape(), (int)pos.x, (int)pos.y, obj->isVisible(), obj->isAlive());
		}
		Bullet::printNumberOfCreatedBullets();
	}
	if (input.getKeyDown(VK_SPACE)) {
		auto canvasDim = canvas.getDimension();

		// pick any player closer to a randomized position.
		auto randPos = Vector2{ rand() % (canvasDim.x - 5), rand() % (canvasDim.y - 2)};
	}
	if (input.getKeyDown('Q')) {
		exit_flag = true;
	}
}

void GameObject::UpdateAll(InputManager& input)
{
	for (auto it = objs.begin(); it != objs.end(); it++)
	{
		auto obj = *it;
		if (obj->isAlive() == false) continue;
		obj->update(input);
	}
	RemoveDeadObjects();
}

void GameObject::DrawAll()
{
	for (auto obj : objs) obj->draw();
}

void GameObject::RenderFrame()
{
	canvas.render();
	Sleep(10);
}

void GameObject::ExamineCollision()
{
	for (auto it = objs.begin(); it != objs.end(); it++)
	{
		auto obj = *it;
		if (obj->isAlive() == false) continue;
		ICollidable* c_i = dynamic_cast<ICollidable*>(obj);
		for (auto jt = it + 1; jt != objs.end() && obj->isAlive() == true; jt++)
		{
			auto other = *jt;
			if (other->isAlive() == false) continue;
			ICollidable* c_j = dynamic_cast<ICollidable*>(other);
			if (c_j == nullptr) continue;
			if (obj->isColliding(other) == false)  continue;
			c_j->onCollision(obj);
			c_i->onCollision(other);
		}
	}
	RemoveDeadObjects();
}

void GameObject::RemoveDeadObjects()
{	
	auto FirstToRemove = stable_partition(objs.begin(), objs.end(), [](auto obj) { return obj->isAlive(); });
	for_each(FirstToRemove, objs.end(), [](auto obj) { delete obj; });
	objs.erase(FirstToRemove, objs.end());
}

void GameObject::Deinitialize()
{
	while (!objs.empty()) {
		auto obj = objs.back();
		objs.pop_back();
		delete obj;
	}
	objs.clear();
}