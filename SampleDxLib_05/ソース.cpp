#include "DxLib.h"
#include <cmath>

float PlayerX = 200, PlayerY = 300;

//�����x�N�g��[1 , 1]�̍쐬
float vi_x = 1;
float vi_y = 1;


void SetLine();
int Create1DimensionLineToY(int x);
int Create1DimensionLineToX(int y);


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//---�ݒ�---
	ChangeWindowMode(TRUE), SetMainWindowText("1���֐�"), SetGraphMode(640, 640
, 32), SetDoubleStartValidFlag(TRUE);

	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//---�ݒ�---


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
	//1���֐������B(y = 2x)
	int Create1DimensionLineToY(int x)
	{
		//�X�N���[���n���W�Ȃ̂ŁAx�͂��̂܂܎g���Ȃ��B
		return 1 * (640 - x);
		return 2 * (640 - x);
	}

	//1���֐������B(x = y / 2)
	int Create1DimensionLineToX(int y)
	{
		return 640 - (y / 1);
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
		
		if (nowLineY < PlayerY && nowLineX < PlayerX)
		{
			//�΂ߐ���\���x�N�g�������B
			float line_X =  1;
			float line_Y = -2;//�X�N���[�����W�n�Ȃ̂Ń}�C�i�X�����ď�����ɂ��Ƃ�

			//line�̐����x�N�g��
			float vertical_X = -line_Y;
			float vertical_Y =  line_X;

			//vertical�̑傫�������߂� a^2 + b^2 = c^2
			//pow : �ix , y�j�Ƃ��āAx��y������߂Ă����֐��B
			float normalization = sqrt(pow(vertical_X, 2) + pow(vertical_Y, 2));

			//�x�N�g���̐��K��
			float normal_X = vertical_X / normalization;
			float normal_Y = vertical_Y / normalization;

			//vi�𔽓]�����x�N�g���Enormal�̓���
			float reflectEnergy = ((-vi_x) * normal_X + (-vi_y) * normal_Y);

			//normal�ցAreflectEnergy��������B�@����Ŕ��˕����ƃG�l���M�[����������
			float P_X = normal_X * reflectEnergy;
			float P_Y = normal_Y * reflectEnergy;

			//P�x�N�g����2�{���āA�����x�N�g���𑫂��Ĕ��˃x�N�g�������B
			float reflect_X = P_X * 2 + vi_x;
			float reflect_Y = P_Y * 2 + vi_y;

			vi_x = reflect_X;
			vi_y = reflect_Y;
		}
	}