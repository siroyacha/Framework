#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


//�÷��̾�� ���͸� ���� �ϴ� �뵵�� ���� ����
const int PLAYER = 0;
const int ENEMY	 = 1;
const int Max	 = 2;

const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;

int SceneState = 0;

int Check = 1;

//�÷��̾�� ���� �� ĳ���͵��� ������ �����ϴ� ����ü
typedef struct tagInfo
{
	// ** ���� Ÿ���� �緮(int, float ��� ����)
	char* Name;
	int HP;
	int MP;
	
	int EXP;

	float Att;
	float Def;
	
	int Level;

}INFO;

// ** ������Ʈ ������ ���� ���� ����ü
typedef struct tagObject
{
	char* Name;
	INFO Info;

}OBJECT;

//�ʿ��� �Լ����� ���漱��

void SceneManager(OBJECT* _Player, OBJECT* _Enemy);
char* SetName();

void LogoScene();
void MenuScene();
void StageScene(OBJECT* _Player, OBJECT* _Enemy);

void InitializePlayer(OBJECT* _Player);
void PlayerScene(OBJECT* _Player);

void InitializeEnemy(OBJECT* _Enemy);
void EnemyScene(OBJECT* _Enemy);

void SetPosition(int _x, int _y, char* _str, int _Color=15);
void SetColor(int _Color);
void HideCursor();

int main()
{
	/*
	//�÷��̾�� ������ ���� ����ü�� ����
	OBJECT Player;
	OBJECT Enemy;

	//����ü �迭�� ����
	OBJECT* Objects[Max];

	//�÷��̾�� ���͸� ���� �Ҵ�
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);
	
	//�������� �� ���(�� �Ŵ����� ���� �ӽ������� ���� ���)
	StageScene(Objects[PLAYER], Objects[ENEMY]);
	*/


	// ** Ŀ���� �Ⱥ��̰� ��
	HideCursor();

	// ** �ܼ�â ������ ����
	system("mode con:cols=120 lines=30");

	//**�ܼ�â �̸� ����
	system("title ������ Framework v0.6");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);

	DWORD dwTime = GetTickCount(); // 1/1000 (1000���� 1��)
	int Delay = 1000;

	int UpCount = 0;

	while (true)
	{
		if (dwTime + Delay < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

			printf_s("%s\n", Player->Name);

			// ** ���� ����
			SceneManager(Player, Monster);
		}
	}

	return 0;
}

void SceneManager(OBJECT* _Player, OBJECT* _Enemy)
{
	switch (SceneState)
	{
	case Scene_Logo:
		LogoScene();
		break;
	case Scene_Menu:
		MenuScene();
		break;
	case Scene_Stage:
		StageScene(_Player, _Enemy);
		break;
	case Scene_Exit:

		exit(NULL);// ** ���α׷� ����
		break;
	}
}

void LogoScene()
{
	int Width = (120 / 2) - (strlen("      ,gggg,     _,gggggg,_        ,gg,         _,gggggg,_      ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"      ,gggg,     _,gggggg,_        ,gg,         _,gggggg,_      ");
	SetPosition(Width, Height + 2, (char*)"      d8` `8I   ,d8P``d8P`Y8b,     i8``8i      ,d8P``d8P`Y8b,   ");
	SetPosition(Width, Height + 3, (char*)"      88  ,dP  ,d8'   Y8   `8b,dP  `8,,8'     ,d8'   Y8   `8b,dP");
	SetPosition(Width, Height + 4, (char*)"   8888888P`   d8'    `Ybaaad88P'   `Y88aaad8 d8'    `Ybaaad88P'");
	SetPosition(Width, Height + 5, (char*)"      88       8P       `````Y8      d8````Y8,8P       `````Y8  ");
	SetPosition(Width, Height + 6, (char*)"      88       8b            d8     ,8P     8b8b            d8  ");
	SetPosition(Width, Height + 7, (char*)" ,aa,_88       Y8,          ,8P     dP      Y8Y8,          ,8P  ");
	SetPosition(Width, Height + 8, (char*)"dP` `88P       `Y8,        ,8P' _ ,dP'      I8`Y8,        ,8P'  ");
	SetPosition(Width, Height + 9, (char*)"Yb,_,d88b,,_    `Y8b,,__,,d8P'  `888,,_____,dP `Y8b,,__,,d8P'   ");
	SetPosition(Width, Height + 10, (char*)" `Y8P`  `Y88888   ``Y8888P`'    a8P`Y888888P`    ``Y8888P`'     ");

	Sleep(5000);
	SceneState++;
}

void MenuScene()
{
	printf_s("MenuScene\n");

	printf_s("���� �� ����??\n1. �̵�\n2. ����\n�Ϸ� : ");

	int i = 0;
	scanf("%d", &i);


	if (i == 1)
		SceneState++;
	else if (i == 2)
		SceneState = Scene_Exit;
}

//ĳ���͵��� ������ �ʱ�ȭ�ϴ� �Լ�
/*
void InitializeObject(OBJECT* _Obj, int ObjectType)
{
	//����ġ���� ���� ĳ���� Ÿ�Ժ��� �ٸ� ������ �ʱ�ȭ
	switch (ObjectType)
	{
		//�÷��̾�� ���� �ʱ�ȭ
	case PLAYER:
		_Obj->Info.Name = SetName();

		_Obj->Info.Att = 10;
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
		//���ͷ� ���� �ʱ�ȭ
	case ENEMY:
		_Obj->Info.Name = (char*)"Enemy";

		_Obj->Info.Att = 5;
		_Obj->Info.Def = 15;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 30;
		_Obj->Info.MP = 5;
		_Obj->Info.Level = 7;
		break;
	}
}
*/



void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.Att = 10;
	_Player->Info.Def = 10;
	_Player->Info.EXP = 0;
	_Player->Info.HP = 100;
	_Player->Info.MP = 10;
	_Player->Info.Level = 1;
}

DWORD SetnameTime = 0;

void PlayerScene(OBJECT* _Player)
{
	if (SetnameTime + 10000 < GetTickCount())
		Check = 1;

	if (Check)
	{
		SetnameTime = GetTickCount();

		_Player->Name = SetName();
		Check = 0;
	}
}

void InitializeEnemy(OBJECT* _Enemy)
{
	_Enemy->Name = (char*)"Enemy";

	_Enemy->Info.Att = 5;
	_Enemy->Info.Def = 15;
	_Enemy->Info.EXP = 0;
	_Enemy->Info.HP = 30;
	_Enemy->Info.MP = 5;
	_Enemy->Info.Level = 1;
}

void EnemyScene(OBJECT* _Enemy)
{

}


//�̸��� �Է¹޴� �Լ�
char* SetName()
{
	//�̸��� �Է¹��� ����
	char Buffer[128] = "";

	printf_s("�̸� �Է� : ");
	scanf("%s", Buffer);

	//�Է¹��� �̸��� �����Ҵ����� ������ ����(null���� �����ϱ� ������ ũ�Ⱑ 1�� �� ũ��)
	char* pName = (char*)malloc(strlen(Buffer) + 1);
	//���ڿ� ����� �̸��� ����
	strcpy(pName, Buffer);

	//�̸� ��ȯ
	return pName;
}

//�������� ���� ����ϴ� �Լ�
void StageScene(OBJECT* _Player, OBJECT* _Enemy)
{
	// ** ����

	PlayerScene(_Player);
	EnemyScene(_Enemy);

	/*
	//������ üũ�� �� ����
	int LoopCheck = 1;

	//����â ����� �ϴ� �ݺ���
	while (LoopCheck)
	{
		// ** �ܼ�â�� ��� ����.
		system("cls");

		printf_s("\n[%s]\n", Player->Info.Name);
		printf_s("HP : %d\n", Player->Info.HP);
		printf_s("MP : %d\n", Player->Info.MP);
		printf_s("���ݷ� : %.2f\n", Player->Info.Att);
		printf_s("���� : %.2f\n", Player->Info.Def);
		printf_s("EXP : %d\n", Player->Info.EXP);
		printf_s("Level : %d\n\n", Player->Info.Level);

		printf_s("[%s]\n", Enemy->Info.Name);
		printf_s("HP : %d\n", Enemy->Info.HP);
		printf_s("MP : %d\n", Enemy->Info.MP);
		printf_s("���ݷ� : %.2f\n", Enemy->Info.Att);
		printf_s("���� : %.2f\n", Enemy->Info.Def);
		printf_s("EXP : %d\n", Enemy->Info.EXP);
		printf_s("Level : %d\n\n", Enemy->Info.Level);

		//����� ������Ű�� �Լ�
		Sleep(500);

		//���ݰ� ������ �����ϴ� �������� ���� ����
		int iChoice = 0;

		//���� üũ�� ���� ���� �Է¹��� ����
		int run = 0;

		printf_s("���Ϳ� �������ϴ�. �����Ͻðڽ��ϱ� ?\n1. ����\n2. ����\n�Է� : ");
		scanf_s("%d", &iChoice);

		//�÷��̾��� �������� ���ݰ� ������ �����ϴ� ����ġ��
		switch (iChoice)
		{
			//���� �ൿ�� �����ϴ� �κ�
		case 1:
			//�÷��̾��� ������ �����ϴ� �κ�
			printf("[%s]�� ����\n", Player->Info.Name);
			//�÷��̾��� ���ݷ��� ������ ���º��� �������
			if (Player->Info.Att > Enemy->Info.Def)
			{
				Enemy->Info.HP -= Player->Info.Att - Enemy->Info.Def;
			}
			//�÷��̾��� ���ݷ��� ������ ���º��� ���� ���
			else
				Enemy->Info.HP -= 1;

			//������ ������ �����ϴ� �κ�
			printf("[%s]�� ����\n", Enemy->Info.Name);
			//������ ���ݷ��� �÷��̾��� ���º��� ���� ���
			if (Enemy->Info.Att > Player->Info.Def)
			{
				Player->Info.HP -= Enemy->Info.Att - Player->Info.Def;
			}
			//������ ���ݷ��� �÷��̾��� ���º��� ���� ���
			else			
				Player->Info.HP -= 1;

			//���� ����
			break;

			//���� �ൿ�� �����ϴ� �κ�
		case 2:
			//���� �õ� �ʱ�ȭ
			srand(time(NULL));
			//�����Լ��� ���� Ȯ�� ����
			run = rand() % 100;

			//������ ������ �÷��̾�� ���� ��� �÷��̾�� �г�Ƽ�� �־� ���� Ȯ���� ���ߴ� ����
			if (Enemy->Info.Level > Player->Info.Level)
			{
				//�г�Ƽ�� �����Ͽ� ���� Ȯ���� �����ϰ� ������ ���
				if (run - (Enemy->Info.Level - Player->Info.Level) * 5 > 30)
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					//����ġ�µ� �����Ͽ� ���� ������ �κ�
					LoopCheck = 0;
					break;
				}
				//������ �������� ���
				else
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					//���� �� ����� ������ �ִ� �κ�
					Sleep(500);
				}
			}

			//�÷��̾��� ������ ���ͺ��� ���� ���
			else
				//70������ Ȯ���� ������ ����
				if (run > 30)
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					//����ġ�µ� �����Ͽ� ���� ������ �κ�
					LoopCheck = 0;
					break;
				}
			//������ �������� ���
				else
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					//���� �� ����� ������ �ִ� �κ�
					Sleep(500);
				}
			//���� �κ��� ������ ���ư��� �κ�
			break;
		}
	}
	*/
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x,_y };

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

/*
	__             ______
   / /     ____   / ____ / ___
  / /     / __ \ / /   __ / __ \
 / /___  / /_/  / /  _/ //_/ /  |
/_____ / \____ / \____ / \____ /


*/
