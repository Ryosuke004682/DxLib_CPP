#include"DxLib.h"
#include <cmath>

/*斜めの壁*/

float PlayerX = 320, PlayerY = 400;
bool OnUpKey, OnDownKey, OnRightKey, OnLeftKey = false;

void SetLine();
int Create1DimensionLineToY(int x);
int Create1DimensionLineToX(int y);


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("斜めの壁"), SetGraphMode(640, 640
		, 32), SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		/*上下左右に動かす*/
		OnUpKey    = CheckHitKey(KEY_INPUT_UP)   ;
		OnDownKey  = CheckHitKey(KEY_INPUT_DOWN) ;
		OnRightKey = CheckHitKey(KEY_INPUT_RIGHT);
		OnLeftKey  = CheckHitKey(KEY_INPUT_LEFT) ;

		if (OnUpKey    == true) PlayerY -= 7;
		if (OnDownKey  == true) PlayerY += 7;
		if (OnLeftKey  == true) PlayerX -= 7;
		if (OnRightKey == true) PlayerX += 7;



		SetLine();

		DrawCircle(PlayerX, PlayerY, 10, GetColor(255, 0, 0));
	}

	DxLib_End();
	return 0;
}
//1次関数を作る。(y = 2x)
int Create1DimensionLineToY(int x)
{
	//スクリーン系座標なので、xはそのまま使えない。
	return 2 * (640 - x);
}

//1次関数を作る。(x = y / 2)
int Create1DimensionLineToX(int y)
{
	return 640 - (y / 2);
}

//斜めの線を描画する。当たり判定も作る。
void SetLine()
{
	//反転後
	DrawLine(0, Create1DimensionLineToY(0),
		640, Create1DimensionLineToY(640),
		GetColor(0, 244, 0));


	int nowLineX = Create1DimensionLineToX(PlayerY);
	int nowLineY = Create1DimensionLineToY(PlayerX);

	if (nowLineX < PlayerX && nowLineY < PlayerY)
	{
		PlayerX = nowLineX - 0.1;
	}
}