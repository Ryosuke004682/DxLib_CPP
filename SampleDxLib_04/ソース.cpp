#include "DxLib.h"
#include <cmath>

const float DEGTORAD = 0.017453293f;

int WINAPI WinMain(_In_ HINSTANCE , _In_opt_ HINSTANCE , _In_ LPSTR , _In_ int)
{
	//---ê›íË----
	ChangeWindowMode(TRUE), SetMainWindowText("ÉxÉNÉgÉãîΩéÀÇ…ÇÊÇÈîΩéÀî¬"), SetGraphMode(640, 480, 32),
		SetDoubleStartValidFlag(TRUE);

	DxLib_Init() , SetDrawScreen(DX_SCREEN_BACK);
	//---ê›íË----

	int PlayerX    = 320, PlayerY    = 240;
	int AddVectorX = 3  , AddVectorY = 1;

	int color      = GetColor(255, 0, 0);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		int object = DrawCircle(PlayerX, PlayerY, 10, color);

		PlayerX += AddVectorX;
		PlayerY += AddVectorY;

		if (640 < PlayerX || PlayerX < 0)
		{
			AddVectorX *= -1;
		}

		if (480 < PlayerY || PlayerY < 0)
		{
			AddVectorY *= -1;
		}

	}

	DxLib_End();
	return 0;
}