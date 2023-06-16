#include"DxLib.h"
#include <cmath>

/*簡単な2Dアクションゲーム*/

//Playerの座標
int PlayerX = 320, PlayerY = 240;

//地面
int GroundLineY = 240;


//移動
bool OnUpKey ,OnRightKey, OnLeftKey = false;
void PlayerMoveControl();

//ジャンプ
bool  JumpNowSwitch = false;
float JumpPower     = -20;
float FrameCount    = 0;
void PlayerJumpControl();

//空中床
bool FallSwitch = false;
void SetAerialFloor(float x1, float x2, float h);



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("アクションゲーム"), SetGraphMode(640, 480, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		PlayerMoveControl();
		PlayerJumpControl();
		SetAerialFloor(340, 500 , 100);

		DrawCircle(PlayerX, PlayerY, 15, GetColor(255 , 0 , 0));
		DrawLine(0 , 240 , 1280 , 240 , GetColor(0 , 255 , 0));
	}


	DxLib_End();
	return 0;
}

//Playerの左右移動
void PlayerMoveControl()
{
	OnRightKey = CheckHitKey(KEY_INPUT_RIGHT);
	OnLeftKey  = CheckHitKey(KEY_INPUT_LEFT) ;

	if (OnRightKey == true) PlayerX += 5;
	if (OnLeftKey  == true) PlayerX -= 5;

	DrawFormatString(0, 0 , GetColor(0 , 255 , 0) , "PlayerX : %d" , PlayerX);
	DrawFormatString(0, 24, GetColor(0 , 255 , 0) , "PlayerY : %d" , PlayerY);
}

//ジャンプを作る。
void PlayerJumpControl()
{
	OnUpKey = CheckHitKey(KEY_INPUT_UP);

	//上キーを押したらジャンプにシフトする。
	if (OnUpKey == true) JumpNowSwitch = true;

	if (JumpNowSwitch == true) {
		
		//Playerが地面よりも上にいるときにジャンプにシフトする。
		if (PlayerY <= GroundLineY)
		{
			//運動方程式を使ってジャンプさせる。
			PlayerY    += JumpPower + (1.0 * FrameCount);
			FrameCount += 1.0f;
		}
	}

	//地面に落下したときの処理を書く。
	
	//Playerを地面に固定する。（Playerが地面よりも下に行った場合、地面に戻す。）
	if (GroundLineY <= PlayerY)
	{
		JumpNowSwitch = false;//Playerが地面より下にいるときにジャンプが終了したと検知させる。
		FrameCount    = 0.0f; //FrameCountをリセット。（ジャンプし始めたら、またカウントする。）
		PlayerY       = GroundLineY; //Playerの座標を地面に合わせる。
	}
}


//指定した座標に空中床を接地する。
void SetAerialFloor(float x1, float x2, float h)
{
	/*指定した範囲内でかつ、PlayerのY座標が空中床の座標を超えた時に、GroundLineの高さを変える。*/

	if (x1 <= PlayerX && PlayerX <= x2)
	{
		if (PlayerY < h)
		{
			GroundLineY = h;
		}
	}
	//空中床から落ちた時の処理を作る。
	else
	{
		GroundLineY = 240;
	}


	//地面より上に居つつ、ジャンプ中ではないとき
	if (PlayerY < GroundLineY && JumpNowSwitch == false)
	{
		FallSwitch = true;
			
	}
		
	//TODO　落下しない。
	//落下中の処理
	if (FallSwitch == true)
	{
		GroundLineY = 240;
		PlayerY    += (1 * FrameCount);
		FrameCount += 1.0f;
	}

	//Playerを地面に固定しとく。
	if (GroundLineY <= PlayerY)
	{
		FallSwitch = false;
		FrameCount = 0.0f;
		PlayerY    = GroundLineY;
	}

	DrawLine(x1 , h , x2 , h , GetColor(0 , 255 , 0));

}