#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


// ** ������ ������ �����ӿ�ũ ����鼭 �������� �ּ�ó�� �ϸ鼭 �����


const int PLAYER = 0;
const int ENEMY	 = 1;
const int Max	 = 2;

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

typedef struct tagObject
{
	INFO Info;

}OBJECT;

void InitializeObject(OBJECT* _Obj, int ObjectType);
char* SetName();

int main()
{
	OBJECT Player;
	OBJECT Enemy;

	OBJECT* Objects[Max];

	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);


	while (true)
	{
		// ** �ܼ�â�� ��� ����.
		system("cls");

		printf_s("\n[%s]\n", Objects[PLAYER]->Info.Name);
		printf_s("HP : %d\n", Objects[PLAYER]->Info.HP);
		printf_s("MP : %d\n", Objects[PLAYER]->Info.MP);
		printf_s("���ݷ� : %.2f\n", Objects[PLAYER]->Info.Att);
		printf_s("���� : %.2f\n", Objects[PLAYER]->Info.Def);
		printf_s("EXP : %d\n", Objects[PLAYER]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[PLAYER]->Info.Level);

		Sleep(500);

		printf_s("[%s]\n", Objects[ENEMY]->Info.Name);
		printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
		printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
		printf_s("���ݷ� : %.2f\n", Objects[ENEMY]->Info.Att);
		printf_s("���� : %.2f\n", Objects[ENEMY]->Info.Def);
		printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);

		Sleep(500);

		int iChoice = 0;
		int run = 0;
		printf_s("���Ϳ� �������ϴ�. �����Ͻðڽ��ϱ� ?\n1. ����\n2. ����\n�Է� : ");
		scanf_s("%d", &iChoice);

		switch (iChoice)
		{
		case 1:
			printf("[%s]�� ����\n", Objects[PLAYER]->Info.Name);
			if (Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def)
			{
				Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def;
			}
			else
				Objects[ENEMY]->Info.HP -= 1;

			Sleep(500);

			printf("[%s]�� ����\n", Objects[ENEMY]->Info.Name);
			if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def)
			{
				Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
			}
			else
				Objects[PLAYER]->Info.HP -= 1;

			break;
		case 2:
			srand(time(NULL));
			run = rand();
			if (Objects[ENEMY]->Info.Level> Objects[PLAYER]->Info.Level)
			{
				if (run % (Objects[ENEMY]->Info.Level - Objects[PLAYER]->Info.Level) +1 == 1)
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					iChoice++;
				}
				else
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					Sleep(500);
				}
			}
			else
				if (run % 2 == 1)
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					iChoice++;
				}
				else
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					Sleep(500);
				}			
			break;
		}

		if (iChoice == 3)
			break;
	}
	return 0;
}

void InitializeObject(OBJECT* _Obj, int ObjectType)
{
	switch (ObjectType)
	{
	case PLAYER:
		_Obj->Info.Name = SetName();

		_Obj->Info.Att = 10;
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
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

char* SetName()
{
	char Buffer[128] = "";

	printf_s("�̸� �Է� : ");
	scanf("%s", Buffer);

	char* pName = (char*)malloc(strlen(Buffer) + 1);
	strcpy(pName, Buffer);

	return pName;
}