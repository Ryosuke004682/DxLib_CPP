#include "DxLib.h"
#include <cmath>

// Playerの移動制御
float PlayerX = 400;
float PlayerY = 200;
float Player_vi_X = 5;
float Player_vi_Y = 5;

// Enemyの移動制御
float EnemyX = 200;
float EnemyY = 200;
float Enemy_vi_X = 6;
float Enemy_vi_Y = -2;

// 反射用変数
float reflect_X;
float reflect_Y;
int reflectionFrameCount = 0;

float temp_reflect_X_Player;
float temp_reflect_Y_Player;
float temp_reflectX_Enemy;
float temp_reflectY_Enemy;

void CreateReflectionVector(float line_X, float line_Y, float P_vi_X, float P_vi_Y, float E_vi_X, float E_vi_Y);
void CreateReflectionWall();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// ---設定---
	ChangeWindowMode(TRUE), SetMainWindowText("ビリヤード"), SetGraphMode(640, 480, 32),
		SetDoubleStartValidFlag(TRUE); DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	// ---設定---


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		// Player
		PlayerX += Player_vi_X;
		PlayerY += Player_vi_Y;
		DrawCircle(PlayerX, PlayerY, 40, GetColor(255, 0, 0));

		// Enemy
		EnemyX += Enemy_vi_X;
		EnemyY += Enemy_vi_Y;
		DrawCircle(EnemyX, EnemyY, 40, GetColor(0, 255, 0));

		if (pow(EnemyX - PlayerX, 2) + pow(EnemyY - PlayerY, 2) < pow(80, 2)) {

			++reflectionFrameCount;
		}
		else {
			reflectionFrameCount = 0;
		}

		if (reflectionFrameCount == 1) {

			// 反射
			CreateReflectionVector(EnemyX - PlayerX, EnemyY - PlayerY,
				Player_vi_X, Player_vi_Y, Enemy_vi_X, Enemy_vi_Y);

			Player_vi_X = temp_reflect_X_Player;
			Player_vi_Y = temp_reflect_Y_Player;
			Enemy_vi_X = temp_reflectX_Enemy;
			Enemy_vi_Y = temp_reflectY_Enemy;
		}

		// 壁を作る
		CreateReflectionWall();
	}

	DxLib_End(); return 0;
}

// 反射ベクトルを作る
// line_X,Y:ボール2点間
// vi_X,Y:反射ベクトルを返す
void CreateReflectionVector(float line_X, float line_Y, float P_vi_X, float P_vi_Y, float E_vi_X, float E_vi_Y) {

	// 2点間の垂直の壁
	float vertical_X = -line_Y;
	float vertical_Y = line_X;

	// verticalの大きさを求める a² + b² = c²
	float c = sqrt(pow(vertical_X, 2) + pow(vertical_Y, 2));

	// verticalの正規化ベクトル
	float vertical_NX = vertical_X / c;
	float vertical_NY = vertical_Y / c;

	// verticalを垂直化＆正規化ベクトル
	float normal_X = (-vertical_Y) / c; // -line_X
	float normal_Y = vertical_X / c;    // -line_Y

	// Player側の力で、PlayerとEnemyを動かす
	float P_reflectEnergyFromPlayer = ((P_vi_X)*vertical_NX) + ((P_vi_Y)*vertical_NY);
	float E_reflectEnergyFromPlayer = ((P_vi_X)*normal_X) + ((P_vi_Y)*normal_Y);

	// Enemy側の力で、EnemyとPlayerを動かす
	float P_reflectEnergyFromEnemy = ((E_vi_X)*normal_X) + ((E_vi_Y)*normal_Y);
	float E_reflectEnergyFromEnemy = ((E_vi_X)*vertical_NX) + ((E_vi_Y)*vertical_NY);

	// Player側の力をPlayerとEnemyへ与える
	float P_X_FromPlayer = vertical_NX * P_reflectEnergyFromPlayer;
	float P_Y_FromPlayer = vertical_NY * P_reflectEnergyFromPlayer;
	float E_X_FromPlayer = normal_X * E_reflectEnergyFromPlayer;
	float E_Y_FromPlayer = normal_Y * E_reflectEnergyFromPlayer;

	// Enemy側の力をEnemyとPlayerへ与える
	float E_X_FromEnemy = vertical_NX * E_reflectEnergyFromEnemy;
	float E_Y_FromEnemy = vertical_NY * E_reflectEnergyFromEnemy;
	float P_X_FromEnemy = normal_X * P_reflectEnergyFromEnemy;
	float P_Y_FromEnemy = normal_Y * P_reflectEnergyFromEnemy;

	// 与えられたベクトルを2つとも加算される
	temp_reflect_X_Player = P_X_FromPlayer + P_X_FromEnemy;
	temp_reflect_Y_Player = P_Y_FromPlayer + P_Y_FromEnemy;
	temp_reflectX_Enemy = E_X_FromPlayer + E_X_FromEnemy;
	temp_reflectY_Enemy = E_Y_FromPlayer + E_Y_FromEnemy;
}

// 反射する壁を作る、画面からボールが出ないようにする
void CreateReflectionWall() {

	// Player用の反射壁
	if (PlayerX < 0 || 640 < PlayerX) {
		Player_vi_X = -Player_vi_X;
	}
	if (PlayerY < 0 || 480 < PlayerY) {
		Player_vi_Y = -Player_vi_Y;
	}

	// Enemy用の反射壁
	if (EnemyX < 0 || 640 < EnemyX) {
		Enemy_vi_X = -Enemy_vi_X;
	}
	if (EnemyY < 0 || 480 < EnemyY) {
		Enemy_vi_Y = -Enemy_vi_Y;
	}
}