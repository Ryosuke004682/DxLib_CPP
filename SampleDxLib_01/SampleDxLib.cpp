#include "DxLib.h"
#include<cmath>

const float DEGTORAD = 0.017453293f;

int WINAPI WinMain(_In_ HINSTANCE , _In_opt_ HINSTANCE , _In_ LPSTR , _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("斜め方向に移動するプレイヤー"), SetGraphMode(640, 480, 32),
		SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---

	float PlayerX = 360.0f , PlayerY = 240.0f;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		PlayerX += cos(-30.0f * DEGTORAD);
		PlayerY += sinf(-30.0f * DEGTORAD);

		DrawCircle(PlayerX ,PlayerY , 10.0f , GetColor(255 , 0 , 0));
	}

	DxLib_End();
	return 0;

}