#include "DxLib.h"
#include <cmath>

float PlayerX = 200, PlayerY = 300;

//加速ベクトル[1 , 1]の作成
float vi_x = 1;
float vi_y = 1;


void SetLine();
int Create1DimensionLineToY(int x);
int Create1DimensionLineToX(int y);


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("1次関数"), SetGraphMode(640, 640
, 32), SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---設定---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		DrawCircle(PlayerX , PlayerY , 10 , GetColor(255 , 0 ,0));
		PlayerX += vi_x * 2;
		PlayerY += vi_y * 2;

		SetLine();
	}

	DxLib_End();
	return 0;
}
	//1次関数を作る。(y = 2x)
	int Create1DimensionLineToY(int x)
	{
		//スクリーン系座標なので、xはそのまま使えない。
		return 1 * (640 - x);
		return 2 * (640 - x);
	}

	//1次関数を作る。(x = y / 2)
	int Create1DimensionLineToX(int y)
	{
		return 640 - (y / 1);
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
		
		if (nowLineY < PlayerY && nowLineX < PlayerX)
		{
			//斜め線を表すベクトルを作る。
			float line_X =  1;
			float line_Y = -2;//スクリーン座標系なのでマイナスをつけて上方向にしとく

			//lineの垂直ベクトル
			float vertical_X = -line_Y;
			float vertical_Y =  line_X;

			//verticalの大きさを求める a^2 + b^2 = c^2
			//pow : （x , y）として、xのy乗を求めてくれる関数。
			float normalization = sqrt(pow(vertical_X, 2) + pow(vertical_Y, 2));

			//ベクトルの正規化
			float normal_X = vertical_X / normalization;
			float normal_Y = vertical_Y / normalization;

			//viを反転したベクトル・normalの内積
			float reflectEnergy = ((-vi_x) * normal_X + (-vi_y) * normal_Y);

			//normalへ、reflectEnergyをかける。　これで反射方向とエネルギーが分かった
			float P_X = normal_X * reflectEnergy;
			float P_Y = normal_Y * reflectEnergy;

			//Pベクトルを2倍して、加速ベクトルを足して反射ベクトルを作る。
			float reflect_X = P_X * 2 + vi_x;
			float reflect_Y = P_Y * 2 + vi_y;

			vi_x = reflect_X;
			vi_y = reflect_Y;
		}
	}