#include <iostream>
#include <cstdlib> // include rand()
#include <Windows.h>
#include <conio.h>
#include "GameObject.h"
#include "Utils.h"
#include "InputManager.h"


/*
RegularPolygonMgr contain polygons that use vector and use addPolygon pushback vector;

Selector is use mouseposition. If click left-mouse buttom that position restored Start_position
If left_mouse states is Dragging and Stay that position restored End_postion
StartPos,EndPos used to drawRactangle and check boundary.
Inside check Polygon-center.
If centerpos inside boundry that change states Selected

If the state of RegularPolygon is Idle, do nothing.
If the state of RegularPolygon is Selected, blinking and update work.

*/
int main()
{
	GameObject::Initialize();
    InputManager input;
	bool exit_flag = false;
    
	while (exit_flag == false)
	{
		GameObject::ClearFrame();
		input.readEveryFrame();

		GameObject::ProcessInput(exit_flag, input);

		GameObject::ExamineCollision();

		GameObject::UpdateAll(input);
		
		GameObject::DrawAll();

		GameObject::RenderFrame();
	}

    GameObject::Deinitialize();

	return 0;
}

