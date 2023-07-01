#include <Novice.h>

const char kWindowTitle[] = "LE2B_ヨシダ_タケル";
const int MAX = 50;//パーティクルの最大
    int posx[MAX];
	int posy[MAX];
	int speedx[MAX];
	int speedy[MAX];
	int flag [MAX];
	int bloodEffect[MAX];
	int gravity[MAX];
	
	int minX = 8;
	int maxX = 16;
	int minY = 8;
	int maxY = 16;
	

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	int swingSword = Novice::LoadAudio("./swingasword.mp3");
	int background =  Novice::LoadTexture("./background.png");
	int enemyTexture[3];
	enemyTexture[0] = Novice::LoadTexture("./enemy1.png");
	enemyTexture[1] = Novice::LoadTexture("./enemy2.png");
	enemyTexture[2] = Novice::LoadTexture("./enemy3.png");
	int damegTexture[4];
	 damegTexture[0] = Novice::LoadTexture("./damage.png");
	 damegTexture[1] = Novice::LoadTexture("./damage2.png");
	 damegTexture[2] = Novice::LoadTexture("./damage3.png");
	 damegTexture[3] = Novice::LoadTexture("./damage4.png");
	 int attackTexture[4];
	 attackTexture[0] = Novice::LoadTexture("./ataku2.png");
	 attackTexture[1] = Novice::LoadTexture("./ataku3.png");
	 attackTexture[2] = Novice::LoadTexture("./ataku4.png");
	 attackTexture[3] = Novice::LoadTexture("./ataku5.png");
	int damageAnimation = 0;
	int attackAnimation = 0;
	int attackReset = 0;
	int attackDamage = 0;
	int enemyAnimation = 0;
	int effectSutāto = 0;
	int enemyposx = 600;
	int enemyposy = 400;
	int bloodposx = 620;
	int bloodSplatter = 0;
	

	for (int i = 0; i < MAX; i++)
	{
		posx[i] = enemyposx;
		posy[i] = enemyposy;
		speedx[i] = 3;
		speedy[i]=10;
		flag[i] = 0;
		gravity[i] = 1;
		bloodEffect[i] = 0;
	}
	
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		//演出リセット
		if (keys[DIK_R])
		{
			//初期化
			damageAnimation = 0;
			attackAnimation = 0;
			attackReset = 0;
			attackDamage = 0;
			enemyAnimation = 0;
			effectSutāto = 0;
		}
		if (keys[DIK_SPACE])
		{
			effectSutāto = 1;
		}
		if (attackReset == 0) 
		{
			attackAnimation++;
		}

	
		
		if (bloodSplatter)
		{
			for (int i = 0; i < MAX; i++)
			{
				if (flag[i] == 0)
				{
					flag[i] = 1;
					posx[i] = bloodposx + rand() % maxX - minX;
					posy[i] = enemyposy + rand() % maxY - minY;
					speedx[i] = rand() % 6 - 3;
					break;
				}
				posx[i] -= speedx[i];
				posy[i] -= speedy[i];
				speedy[i] -= gravity[i];
			}
			for (int i = 0; i < MAX; i++)
			{
				if (posy[i] >= 500)
				{
					flag[i] = 0;
					posy[i] = enemyposy;
					posx[i] = bloodposx;
					speedy[i] = 10;
				}
			}

		}
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//背景
		
		Novice::DrawSprite(0, 0, background, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		//敵
		Novice::DrawSprite(enemyposx, enemyposy, enemyTexture[0], 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		//エフェクト開始
		if (effectSutāto == 1)
		{

			enemyAnimation++;
			if (enemyAnimation >= 3)
			{
				enemyAnimation++;
				Novice::DrawSprite(600, 400, enemyTexture[0], 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

			}
			if (enemyAnimation <= 3 || enemyAnimation >= 5)
			{
				enemyAnimation++;
				Novice::DrawSprite(600, 400, enemyTexture[1], 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

			}
			if (enemyAnimation <= 3 || enemyAnimation >= 5)
			{
				enemyAnimation++;
				Novice::DrawSprite(600, 400, enemyTexture[2], 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

			}

			//ダメージエフェクト
			if (attackDamage == 1)
			{
				damageAnimation++;
				if (damageAnimation <= 2)
				{
					Novice::DrawSprite(530, 320, damegTexture[3], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
				}
				if (damageAnimation <= 4)
				{
					Novice::DrawSprite(530, 320, damegTexture[2], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
				}
				if (damageAnimation <= 6)
				{
					Novice::DrawSprite(530, 320, damegTexture[1], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
				}
				if (damageAnimation >= 8)
				{
					Novice::DrawSprite(530, 320, damegTexture[0], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
				}
				if (damageAnimation >= 50)
				{
					attackDamage = 0;
				}
			}

			//敵に攻撃
			if (attackAnimation > 2)
			{
				Novice::DrawSprite(590, 400, attackTexture[0], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
			}
			if (attackAnimation > 5)
			{
				Novice::DrawSprite(590, 400, attackTexture[1], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
			}
			if (attackAnimation > 8)
			{
				Novice::DrawSprite(590, 400, attackTexture[2], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
				Novice::PlayAudio(swingSword, false, 0.5f);
			}
			if (attackAnimation > 11)
			{
				Novice::DrawSprite(590, 400, attackTexture[3], 0.15f, 0.15f, 0.0f, 0xFFFFFFFF);
			}
			if (attackAnimation > 13)
			{
				attackAnimation = 0;
				attackReset = 1;
				attackDamage = 1;
				//出血
				bloodSplatter = 1;

			}
		}
		if (bloodSplatter == 1)
		{
			for (int i = 0; i < MAX; i++)
			{
				if (flag[i] == 1)
				{
					Novice::DrawEllipse(posx[i], posy[i], 3, 3, 0.0f, 0xFF0000FF, kFillModeSolid);
				}

			}
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
