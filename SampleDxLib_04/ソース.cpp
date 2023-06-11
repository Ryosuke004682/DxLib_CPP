#include "DxLib.h"
#include <cmath>
#include <ctime>

const float DEGTORAD = 0.017453293f;

int WINAPI WinMain(_In_ HINSTANCE , _In_opt_ HINSTANCE , _In_ LPSTR , _In_ int)
{
	//---設定----
	ChangeWindowMode(TRUE), SetMainWindowText("ベクトル反射による反射板"), SetGraphMode(640, 480, 32),
		SetDoubleStartValidFlag(TRUE);

	DxLib_Init() , SetDrawScreen(DX_SCREEN_BACK);
	//---設定----

	int PlayerX    = 320, PlayerY    = 240;
	int AddVectorX = 3  , AddVectorY = 1;

	int color      = GetColor(255, 0, 0);

	bool colorChange = false;

	
	//srand関数を使ってランダムな値を初期化する。
	srand(static_cast<unsigned int>(time(nullptr)));


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		if (!colorChange)
		{
			int object = DrawCircle(PlayerX, PlayerY, 10, color);
		}
		else
		{
			int object = DrawCircle(PlayerX, PlayerY, 10, GetColor(255 , 0 , 0));
		}

		

		PlayerX += AddVectorX;
		PlayerY += AddVectorY;

		if (640 < PlayerX || PlayerX < 0)
		{
			//画面の端（640地点）に到達したら、Xベクトルを反転させる。
			AddVectorX *= -1;

			if (!colorChange)
			{
				int red   = rand() % 256;
				int green = rand() % 256;
				int blue  = rand() % 256;

				int color = GetColor(red, green, blue);

				colorChange = true;
			}
		}

		if (480 < PlayerY || PlayerY < 0)
		{
			AddVectorY *= -1;

			if (!colorChange)
			{
				int red   = rand() % 256;
				int green = rand() % 256;
				int blue  = rand() % 256;

				int color = GetColor(red, green, blue);

				colorChange = true;
			}
		}

		if (colorChange)
		{
			colorChange = false;
		}

	}

	DxLib_End();
	return 0;
}