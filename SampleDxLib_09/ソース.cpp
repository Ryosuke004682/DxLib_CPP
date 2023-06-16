#include"DxLib.h"
#include <cmath>

/*�΂߂̕�*/

float PlayerX = 320, PlayerY = 400;
bool OnUpKey, OnDownKey, OnRightKey, OnLeftKey = false;

void SetLine();
int Create1DimensionLineToY(int x);
int Create1DimensionLineToX(int y);


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---�ݒ�---
	ChangeWindowMode(TRUE), SetMainWindowText("�΂߂̕�"), SetGraphMode(640, 640
		, 32), SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---�ݒ�---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		/*�㉺���E�ɓ�����*/
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
//1���֐������B(y = 2x)
int Create1DimensionLineToY(int x)
{
	//�X�N���[���n���W�Ȃ̂ŁAx�͂��̂܂܎g���Ȃ��B
	return 2 * (640 - x);
}

//1���֐������B(x = y / 2)
int Create1DimensionLineToX(int y)
{
	return 640 - (y / 2);
}

//�΂߂̐���`�悷��B�����蔻������B
void SetLine()
{
	//���]��
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