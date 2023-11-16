#pragma once
#include "GameObject.h"
#include <algorithm>
#include "RegularPolygon.h"
class RegularPolygonMgr : public GameObject
{
public:
	vector<RegularPolygon*> polygons;

	RegularPolygonMgr():GameObject(" ",0,true),polygons()
	{

	}
	vector<RegularPolygon*>& getPolys() { return polygons; }
	void addPolygon(RegularPolygon* polygon) 
	{
		polygons.push_back(polygon);
	}
	~RegularPolygonMgr()
	{
		for_each(polygons.begin(), polygons.end(), [&](auto it) {delete* it; });
	}
};

