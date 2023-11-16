#include "Selector.h"
#include "InputManager.h"
#include "Utils.h"
#include "Canvas.h"
#include "RegularPolygon.h"
#include <algorithm>
void Selector::update(InputManager& input)
{
	vector<RegularPolygon*>::iterator it;
	
	if (input.getMouseButtonDown(0))//ó�������� ���
	{
		setVisible();
		startPos = input.getMousePosition();
		Debug::Log("startPos:%d %d", startPos.x, startPos.y);
		for (it = polyMgr.polygons.begin(); it != polyMgr.polygons.end(); it++)
		{
			(*it)->setStatus(POLYGONSTATE::IDLE);
				(*it)->setVisible();
		}
	}
	if (input.getMouseButtonStay(0))//�巡�� ���� ���� ���� �ٲܷ��� ������
	{
		endPos = input.getMousePosition();
		for (it = polyMgr.polygons.begin(); it != polyMgr.polygons.end(); it++)
		{
			if (inside((*it)->getPosition(), startPos, endPos))
			{
				(*it)->setStatus(POLYGONSTATE::SELECTED);
			}
		}
		//Debug::Log("endPos:%d %d", endPos.x, endPos.y);
	}
	if (input.getMouseButtonUp(0))//��ư�� ���� ���
	{
		setVisible(false);
		endPos = input.getMousePosition();
		Debug::Log("endPos:%d %d", endPos.x, endPos.y);
		for (it = polyMgr.polygons.begin(); it != polyMgr.polygons.end(); it++)
		{
			if (inside((*it)->getPosition(), startPos, endPos))
			{
				(*it)->setStatus(POLYGONSTATE::SELECTED);
			}
		}
		//for_each(polyMgr.polygons.begin(), polyMgr.polygons.end(), [this](auto& it)
		//	{
		//		if (inside(it.getposition(), this.startpos, this.endpos))
		//		{
		//			it.setStatus(POLYGONSTATE::SELECTED);
		//		}
		//	}
		//);
		/*End.x = Borland::WhereX();
		End.y = Borland::WhereY();*/
	}

}

void Selector::draw()
{
	canvas.drawRectangle(startPos, endPos, isVisible());
	/*if (startPos.x == endPos.x&&startPos.y==endPos.y)
		return;
	if (!isVisible())
		return;
	canvas.drawLine(196, startPos, Position{ endPos.x , startPos.y });
	canvas.drawLine(179, Position{ endPos.x ,startPos.y }, endPos);
	canvas.drawLine(196, Position{ startPos.x , endPos.y }, endPos );
	canvas.drawLine(179,  startPos, Position{ startPos.x , endPos.y });*/
}

bool Selector::inside(const Position &pos,const Position&start,const Position&end)
{
	auto minX = start.x < end.x ? start.x : end.x;
	auto maxX = start.x >= end.x ? start.x : end.x;
	auto minY = start.y < end.y ? start.y : end.y;
	auto maxY = start.y >= end.y ? start.y : end.y;

	Vector2 topLeft{ minX, minY };
	Vector2 topRight{ maxX, minY };
	Vector2 bottomLeft{ minX, maxY };
	Vector2 bottomRight{ maxX, maxY };
	if (pos.x<minX || pos.x>maxX)
		return false;
	if (pos.y<minY || pos.y>maxY)
		return false;
	return true;
}
