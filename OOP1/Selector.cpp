#include "Selector.h"
#include "InputManager.h"
#include "Utils.h"
#include "Canvas.h"
void Selector::update(InputManager& input)
{
	/*Position v1;
	Position v2;
	*/
	if (input.getMouseButtonDown(0))//ó�������� ���
	{
		setVisible();
		startPos = input.getMousePosition();
		Debug::Log("startPos:%d %d", startPos.x, startPos.y);
	}
	if (input.getMouseButtonStay(0))//�巡�� ���� ���� ���� �ٲܷ��� ������
	{
		endPos = input.getMousePosition();
		//Debug::Log("endPos:%d %d", endPos.x, endPos.y);
	}
	if (input.getMouseButtonUp(0))//��ư�� ���� ���
	{
		setVisible(false);
		endPos = input.getMousePosition();
		Debug::Log("endPos:%d %d", endPos.x, endPos.y);
		/*End.x = Borland::WhereX();
		End.y = Borland::WhereY();*/
	}
	for_each(polyMgr)



	//if (startPos.x > endPos.x)
	//{
	//	int temp_x = startPos.x;
	//	startPos.x = endPos.x;
	//	endPos.x = temp_x;
	//}
	//if (startPos.y > endPos.y)
	//{
	//	int temp_y = startPos.y;
	//	startPos.y = endPos.y;
	//	endPos.y = temp_y;
	//}
	//Debug::Log("startPos:%d %d", startPos.x, startPos.y);
	//Debug::Log("endPos:%d %d", endPos.x, endPos.y);
}

void Selector::draw()
{
	if (startPos.x == endPos.x&&startPos.y==endPos.y)
		return;
	if (!isVisible())
		return;
	canvas.drawLine(196, startPos, Position{ endPos.x , startPos.y });//+�� ó������ �˾Ҵµ� +�� �ڼ��� ���� Vector�� ������ �ѱ�� �Ǿ��־ ������ x�� ���� ���Ϸ��� x�� �������� �̻��� ����� �����⿡ �ӽú����� �־ ��Ȯ�� ������
	canvas.drawLine(179, Position{ endPos.x ,startPos.y }, endPos);
	canvas.drawLine(196, Position{ startPos.x , endPos.y }, endPos );
	canvas.drawLine(179,  startPos, Position{ startPos.x , endPos.y });
}
