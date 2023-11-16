#include "Selector.h"
#include "InputManager.h"
#include "Utils.h"
#include "Canvas.h"
void Selector::update(InputManager& input)
{
	/*Position v1;
	Position v2;
	*/
	if (input.getMouseButtonDown(0))//처음눌렀을 경우
	{
		setVisible();
		startPos = input.getMousePosition();
		Debug::Log("startPos:%d %d", startPos.x, startPos.y);
	}
	if (input.getMouseButtonStay(0))//드래그 중일 때도 값을 바꿀려고 설정함
	{
		endPos = input.getMousePosition();
		//Debug::Log("endPos:%d %d", endPos.x, endPos.y);
	}
	if (input.getMouseButtonUp(0))//버튼을 떼는 경우
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
	canvas.drawLine(196, startPos, Position{ endPos.x , startPos.y });//+로 처리될줄 알았는데 +를 자세히 보니 Vector의 값으로 넘기게 되어있어서 기존의 x와 내가 더하려는 x가 더해져서 이상한 결과가 나오기에 임시변수로 넣어서 정확히 전달함
	canvas.drawLine(179, Position{ endPos.x ,startPos.y }, endPos);
	canvas.drawLine(196, Position{ startPos.x , endPos.y }, endPos );
	canvas.drawLine(179,  startPos, Position{ startPos.x , endPos.y });
}
