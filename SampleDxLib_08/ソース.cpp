#include"DxLib.h"
#include <cmath>

/*�ǂ����*/

float PlayerX   = 320  , PlayerY   = 400;
bool OnRightKey = false, OnLeftKey = false;

 void SetLeftWall (float x);
 void SetRightWall(float x);

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---�ݒ�---
	ChangeWindowMode(TRUE), SetMainWindowText("�ǂ���邺"), SetGraphMode(640, 480, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---�ݒ�---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		OnRightKey = CheckHitKey(KEY_INPUT_RIGHT);
		OnLeftKey  = CheckHitKey(KEY_INPUT_LEFT);

		/*���E�̈ړ�*/
		if (OnRightKey == true) PlayerX += 10;
		if (OnLeftKey  == true) PlayerX -= 10;


		SetLeftWall(620);
		SetRightWall(20);


		DrawCircle(PlayerX, PlayerY, 15, GetColor(255 , 0 , 0));
	}


	DxLib_End();
	return 0;
}

void SetLeftWall(float x)
{
	if (x - 3.0f <= PlayerX)
	{
		if (x - 0.1 <= PlayerX)
		{
			PlayerX = x - 0.1;
		}
	}
}

void SetRightWall(float x)
{
	if (x - 3.0f >= PlayerX)
	{
		if (x - 0.1 >= PlayerX)
		{
			PlayerX = x - 0.1;
		}
	}
}