
#include"DxLib.h"
#include<cmath>

const float DEGTORAD = 0.017453293f;
float PlayerX = 320.0f, PlayerY = 240.0f;

void PlayerMoveAndDraw();
void SetSlope(int slopeStart_X, int slopeEnd_X, int slopeAngle, int slopePosition_Y);

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("坂道を移動するプレイヤー"), SetGraphMode(1000, 600, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		PlayerMoveAndDraw();//Playerの移動とPlayerの描画
		SetSlope(400, 600, -30, 240);//坂道を作成。
	}

	DxLib_End();
	return 0;
}



//Playerを移動させてかつ、Playerを描画する関数を作る。
void PlayerMoveAndDraw()
{
	//左へ移動させる。
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		PlayerX -= 3.0f;
	}

	//右に移動させる。
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		PlayerX += 3.0f;
	}

	DrawCircle(PlayerX, PlayerY, 15.0f, GetColor(255, 0, 0));

	/*DrawCircle(x, y, radius, color)
	(x,y)は描画する中心座標、radiusは描画する円の半径、colorは色*/
}


//坂道を作成
//void SetSlope(坂道の開始位置（X座標）、坂道の終了位置（X座標）、坂道の角度、坂道の位置);
void SetSlope(int slopeStart_X, int slopeEnd_X, int slopeAngle, int slopePosition_Y)
{
	//PlayerXが坂道の圏内にいるかどうかの判定
	if (slopeStart_X <= PlayerX && PlayerX <= slopeEnd_X)
	{

		//PlayerのY座標をX座標に応じて変動させる。
		PlayerY = tanf(slopeAngle * DEGTORAD) * (PlayerX - slopeStart_X) + slopePosition_Y;
	}

	//坂道を描画
	DrawLine(slopeStart_X, slopePosition_Y, slopeEnd_X,
		tanf(slopeAngle * DEGTORAD) * (slopeEnd_X - slopeStart_X)
		+ slopePosition_Y, GetColor(255, 255, 255));

}