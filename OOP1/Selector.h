#pragma once
#include "GameObject.h"
#include "RegularPolygonMgr.h"
class Selector :public GameObject
{
	Position startPos;
	Position endPos;
	RegularPolygonMgr polyMgr;
public:
	Selector(const Position& _start,const Position&_end,const RegularPolygonMgr& _mgr):startPos(_start),endPos(_end),GameObject(" ",0,true),polyMgr(_mgr)
	{}
	void update(InputManager& input) override;
	void draw() override;
};

