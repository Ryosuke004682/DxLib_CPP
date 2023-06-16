#include "DxLib.h"
#include <cmath>

/*ジャンプを作る。*/

float PlayerX = 320, PlayerY = 400;

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("ジャンプ"), SetGraphMode(640, 480, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---

	float JumpPower  = -30;
	float FrameCount = 0;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		//ジャンプをさせたいので、ニュートンの運動方程式を使う。
		PlayerY    += JumpPower + (1.25 * FrameCount);
		FrameCount += 1.0f;

		DrawCircle(PlayerX , PlayerY , 15 , GetColor(255 , 0 , 0));
	}


	DxLib_End();
	return 0;
}