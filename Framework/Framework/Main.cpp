#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>

// ��Ʈ������ ���� 30�� �ȳѱ��

// ** ���� : https://www.youtube.com/watch?v=_nuS86ITjIM
// ** �ƽ�Ű ��Ʈ : http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20

// ** ����	 0
// ** ��ο� �Ķ�	 1
// ** ��ο� �ʷ�	 2
// ** ��ο� �ϴ�	 3
// ** ��ο� ����	 4
// ** ��ο� ����	 5
// ** ��ο� ���	 6
// ** ȸ��	 7
// ** ��ο� ȸ��	 8
// ** �Ķ�	 9
// ** �ʷ�	 10
// ** �ϴ�	 11
// ** ����	 12
// ** ����	 13
// ** ���	 14
// ** �Ͼ�	 15

const int Warrior = 1;
const int Hunter = 2;
const int Wizard = 3;

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
	int Type;
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

int SetPlayerJob();
void LevelUp(OBJECT* _Player);
void PrintStatus(OBJECT* _Object);
void Move(int* Encounter);
int EnCounter();


int main()
{

	// ** Ŀ���� �Ⱥ��̰� ��
	HideCursor();

	// ** �ܼ�â ������ ����
	system("mode con:cols=120 lines=30");

	//**�ܼ�â �̸� ����
	system("title ������ Framework v0.6");

	// ** ��ü ������ ������.
	//system("color 70");

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
	int Width = (120 / 2) - (strlen("   __        _____    ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"   __         _____    ");
	SetPosition(Width, Height + 2, (char*)"  / /  ___   / ___/__  ");
	SetPosition(Width, Height + 3, (char*)" / /__/ _ \\/ (_ / _ \\ ");
	SetPosition(Width, Height + 4, (char*)"/____/\___/\\___/\\___/ ");

	Sleep(5000);
	SceneState++;
}

void MenuScene()
{
	printf_s("MenuScene\n");

	printf_s("������ ���� �Ͻðڽ��ϱ�?\n1. ����\n2. ����\n�Է� : ");

	int i = 0;
	scanf("%d", &i);


	if (i == 1)
		SceneState++;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.Att = 10;
	_Player->Info.Def = 10;
	_Player->Info.EXP = 0;
	_Player->Info.HP = 100;
	_Player->Info.MP = 10;
	_Player->Info.Level = 1;
	_Player->Info.Type = SetPlayerJob();
}


void PlayerScene(OBJECT* _Player)
{

	PrintStatus(_Player);
	/*
	DWORD SetnameTime = 0;
	if (SetnameTime + 10000 < GetTickCount())
		Check = 1;

	if (Check)
	{
		SetnameTime = GetTickCount();

		_Player->Info.EXP += 100;
		Check = 0;
	}
	*/
	

	if (_Player->Info.EXP >= 100)
	{
		LevelUp(_Player);
		_Player->Info.EXP = 0;
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
	_Enemy->Info.Type = 0;
}

void EnemyScene(OBJECT* _Enemy)
{
	PrintStatus(_Enemy);
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
	int Encounter = 0;
	//�̵�
	Move(&Encounter);
	
	// ** ����
	if (Encounter)
	{
		PlayerScene(_Player);
		EnemyScene(_Enemy);
	}
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x,_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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

int SetPlayerJob()
{
	int type = 0;
	system("cls");
	printf_s("����� ������ �����Դϱ�?\n");
	printf_s("1.����\t 2.�ü�\t 3.������\n�Է� : ");
	
	scanf_s("%d", &type);

	return type;
}

void LevelUp(OBJECT* _Player)
{
	_Player->Info.Level++;
	switch (_Player->Info.Type)
	{
	case Warrior:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	case Hunter:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	case Wizard:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	}
}

void PrintStatus(OBJECT* _Object)
{
	printf_s("%s\n", _Object->Name);
	printf_s("���� : %02d\n���� : %d\nü�� : %d\n���� : %d\n���ݷ� : %0.2f\n���� : %0.2f\n����ġ : %03d\n",
		_Object->Info.Level,_Object->Info.Type, _Object->Info.HP, _Object->Info.MP, _Object->Info.Att, _Object->Info.Def, _Object->Info.EXP);
}

void Move(int* Encounter)
{
	int MoveHelper = 0;
	printf_s("�̵� �Ͻðڽ��ϱ�?\n1. �̵�\n0. ����\n�Է� : ");
	scanf("%d", &MoveHelper);
	switch (MoveHelper)
	{
	case 1:
		*Encounter = EnCounter();
		break;
	case 0:
		exit(NULL);
		break;
	}
	if (*Encounter)
		printf_s("���� ����!\n");
	else
		printf_s("�̵� ����\n");
	DWORD SetMoveTime = 0;
	if (SetMoveTime + 3000 < GetTickCount())
		Check = 1;

	if (Check)
	{
		SetMoveTime = GetTickCount();

		Check = 0;
	}
}

int EnCounter()
{
	int _Encounter = 0;
	srand(GetTickCount());

	_Encounter = (rand() % 100) + 1;

	if (_Encounter <= 80)
		return 0;
	if (_Encounter <= 5)
		return 2;
	else
		return 1;
}

void MapScene(OBJECT* _Player)
{
	int P_x = 0;
	int P_y = 0;
	/*
	SetPosition()
	*/
}

void TownScene()
{

}

void BattelScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter)
{
	int runcounter = 0;
	int runchance = 0;
	int battelhelper = 0;

	srand(GetTickCount());

	runchance = (rand() - (_Enemy->Info.Level - _Player->Info.Level) * 2) % 100;

	if (*Encounter == 1)
	{
		printf_s("�����Ͻðڽ��ϱ�?\n1. �� 2. �ƴϿ�\n");
		scanf("%d", &runcounter);

		if (runcounter==1)
		{
			if (runchance>=70)
			{
				printf_s("���� ����!\n");
				*Encounter = 0;
			}
			else
			{
				printf("���� ����\n������ �����մϴ�\n");
				Sleep(500);
			}
		}
		printf_s("������ ���۵˴ϴ�!");
		Sleep(500);

		PlayerScene(_Player);
		EnemyScene(_Enemy);

		printf_s("1. ���� 2. ���� 3. ������ ���\n");
		switch (battelhelper)
		{
		case 1:
			break;
		default:
			break;
		}
	}
}