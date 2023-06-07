
#include"DxLib.h"
#include<cmath>

const float DEGTORAD = 0.017453293f;
float PlayerX = 320.0f, PlayerY = 240.0f;

void PlayerMoveAndDraw();
void SetSlope(int slopeStart_X, int slopeEnd_X, int slopeAngle, int slopePosition_Y);

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---�ݒ�---
	ChangeWindowMode(TRUE), SetMainWindowText("�⓹���ړ�����v���C���["), SetGraphMode(1000, 600, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---�ݒ�---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		PlayerMoveAndDraw();//Player�̈ړ���Player�̕`��
		SetSlope(400, 600, -30, 240);//�⓹���쐬�B
	}

	DxLib_End();
	return 0;
}



//Player���ړ������Ă��APlayer��`�悷��֐������B
void PlayerMoveAndDraw()
{
	//���ֈړ�������B
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		PlayerX -= 3.0f;
	}

	//�E�Ɉړ�������B
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		PlayerX += 3.0f;
	}

	DrawCircle(PlayerX, PlayerY, 15.0f, GetColor(255, 0, 0));

	/*DrawCircle(x, y, radius, color)
	(x,y)�͕`�悷�钆�S���W�Aradius�͕`�悷��~�̔��a�Acolor�͐F*/
}


//�⓹���쐬
//void SetSlope(�⓹�̊J�n�ʒu�iX���W�j�A�⓹�̏I���ʒu�iX���W�j�A�⓹�̊p�x�A�⓹�̈ʒu);
void SetSlope(int slopeStart_X, int slopeEnd_X, int slopeAngle, int slopePosition_Y)
{
	//PlayerX���⓹�̌����ɂ��邩�ǂ����̔���
	if (slopeStart_X <= PlayerX && PlayerX <= slopeEnd_X)
	{

		//Player��Y���W��X���W�ɉ����ĕϓ�������B
		PlayerY = tanf(slopeAngle * DEGTORAD) * (PlayerX - slopeStart_X) + slopePosition_Y;
	}

	//�⓹��`��
	DrawLine(slopeStart_X, slopePosition_Y, slopeEnd_X,
		tanf(slopeAngle * DEGTORAD) * (slopeEnd_X - slopeStart_X)
		+ slopePosition_Y, GetColor(255, 255, 255));

}