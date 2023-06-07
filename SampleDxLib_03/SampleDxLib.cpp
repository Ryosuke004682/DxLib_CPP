#include"DxLib.h"
#include<cmath>

const float DEGTORAD = 0.017453293f;

int WINAPI WinMain(_In_ HINSTANCE , _In_opt_ HINSTANCE , _In_ LPSTR , _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE) , SetMainWindowText("sin波") , SetGraphMode(640, 480, 32) , 
		SetDoubleStartValidFlag(TRUE);

	DxLib_Init() , SetDrawScreen(DX_SCREEN_BACK);
	//---設定---

	//滑らかな画面遷移
	float Fade  = 0.0f;
	float red   = 0.0f;
	float green = 0.0f;
	float blue  = 0.0f;


	//フェードインフェードアウト
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		if (Fade < 180)
		{
			Fade += 1.0f;
		}

		red   = sin(Fade * DEGTORAD) * 255;
		green = sin(Fade * DEGTORAD) * 255;
		blue  = sin(Fade * DEGTORAD) * 255;

		DrawBox(0, 0 , 640 , 480 , GetColor(red , green ,blue) , true);
		DrawFormatString(0 , 0 , GetColor(255 , 0 , 0) , "%f" , Fade);
	}
	

	
	
	/*
	//playerの座標
	float PlayerX = 0.0f , PlayerY = 240.0f;
	float PlayerA = 0.0f , PlayerB = 120.0f;
	int   count = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		PlayerX += 1;
		PlayerY += sinf(count++ * DEGTORAD);
		
		PlayerA += 1;
		PlayerB += cosf(count++ * DEGTORAD);

		DrawCircle(PlayerX , PlayerY , 10.0f , GetColor(255 , 0 ,0));
		DrawCircle(PlayerA , PlayerB , 10.0f , GetColor(0, 0 , 255));
	}
	*/


	DxLib_End();
	return 0;
}
