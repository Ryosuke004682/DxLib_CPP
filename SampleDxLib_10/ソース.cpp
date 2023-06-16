#include"DxLib.h"
#include <cmath>

/*�ȒP��2D�A�N�V�����Q�[��*/

//Player�̍��W
int PlayerX = 320, PlayerY = 240;

//�n��
int GroundLineY = 240;


//�ړ�
bool OnUpKey ,OnRightKey, OnLeftKey = false;
void PlayerMoveControl();

//�W�����v
bool  JumpNowSwitch = false;
float JumpPower     = -20;
float FrameCount    = 0;
void PlayerJumpControl();

//�󒆏�
bool FallSwitch = false;
void SetAerialFloor(float x1, float x2, float h);



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---�ݒ�---
	ChangeWindowMode(TRUE), SetMainWindowText("�A�N�V�����Q�[��"), SetGraphMode(640, 480, 32)
		, SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---�ݒ�---


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

//Player�̍��E�ړ�
void PlayerMoveControl()
{
	OnRightKey = CheckHitKey(KEY_INPUT_RIGHT);
	OnLeftKey  = CheckHitKey(KEY_INPUT_LEFT) ;

	if (OnRightKey == true) PlayerX += 5;
	if (OnLeftKey  == true) PlayerX -= 5;

	DrawFormatString(0, 0 , GetColor(0 , 255 , 0) , "PlayerX : %d" , PlayerX);
	DrawFormatString(0, 24, GetColor(0 , 255 , 0) , "PlayerY : %d" , PlayerY);
}

//�W�����v�����B
void PlayerJumpControl()
{
	OnUpKey = CheckHitKey(KEY_INPUT_UP);

	//��L�[����������W�����v�ɃV�t�g����B
	if (OnUpKey == true) JumpNowSwitch = true;

	if (JumpNowSwitch == true) {
		
		//Player���n�ʂ�����ɂ���Ƃ��ɃW�����v�ɃV�t�g����B
		if (PlayerY <= GroundLineY)
		{
			//�^�����������g���ăW�����v������B
			PlayerY    += JumpPower + (1.0 * FrameCount);
			FrameCount += 1.0f;
		}
	}

	//�n�ʂɗ��������Ƃ��̏����������B
	
	//Player��n�ʂɌŒ肷��B�iPlayer���n�ʂ������ɍs�����ꍇ�A�n�ʂɖ߂��B�j
	if (GroundLineY <= PlayerY)
	{
		JumpNowSwitch = false;//Player���n�ʂ�艺�ɂ���Ƃ��ɃW�����v���I�������ƌ��m������B
		FrameCount    = 0.0f; //FrameCount�����Z�b�g�B�i�W�����v���n�߂���A�܂��J�E���g����B�j
		PlayerY       = GroundLineY; //Player�̍��W��n�ʂɍ��킹��B
	}
}


//�w�肵�����W�ɋ󒆏���ڒn����B
void SetAerialFloor(float x1, float x2, float h)
{
	/*�w�肵���͈͓��ł��APlayer��Y���W���󒆏��̍��W�𒴂������ɁAGroundLine�̍�����ς���B*/

	if (x1 <= PlayerX && PlayerX <= x2)
	{
		if (PlayerY < h)
		{
			GroundLineY = h;
		}
	}
	//�󒆏����痎�������̏��������B
	else
	{
		GroundLineY = 240;
	}


	//�n�ʂ���ɋ��A�W�����v���ł͂Ȃ��Ƃ�
	if (PlayerY < GroundLineY && JumpNowSwitch == false)
	{
		FallSwitch = true;
			
	}
		
	//TODO�@�������Ȃ��B
	//�������̏���
	if (FallSwitch == true)
	{
		GroundLineY = 240;
		PlayerY    += (1 * FrameCount);
		FrameCount += 1.0f;
	}

	//Player��n�ʂɌŒ肵�Ƃ��B
	if (GroundLineY <= PlayerY)
	{
		FallSwitch = false;
		FrameCount = 0.0f;
		PlayerY    = GroundLineY;
	}

	DrawLine(x1 , h , x2 , h , GetColor(0 , 255 , 0));

}