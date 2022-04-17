#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


// ** ������ ������ �����ӿ�ũ ����鼭 �������� �ּ�ó�� �ϸ鼭 �����

//�÷��̾�� ���͸� ���� �ϴ� �뵵�� ���� ����
const int PLAYER = 0;
const int ENEMY	 = 1;
const int Max	 = 2;

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

typedef struct tagObject
{
	INFO Info;

}OBJECT;

//�ʿ��� �Լ����� ���漱��
void InitializeObject(OBJECT* _Obj, int ObjectType);
char* SetName();
void StageScene(OBJECT* _Obj);

int main()
{
	//�÷��̾�� ������ ���� ����ü�� ����
	OBJECT Player;
	OBJECT Enemy;

	OBJECT* Objects[Max];

	//�÷��̾�� ���͸� ���� �Ҵ�
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);
	
	//�������� �� ���(�� �Ŵ����� ���� �ӽ������� ���� ���)
	StageScene();


	return 0;
}

//ĳ���͵��� ������ �ʱ�ȭ�ϴ� �Լ�
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
void StageScene(OBJECT* Player, OBJECT* Enemy)
{
	//������ üũ�� �� ����
	int LoopCheck = 1;
	//����â ����� �ϴ� �ݺ���
	while (LoopCheck)
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

		printf_s("[%s]\n", Objects[ENEMY]->Info.Name);
		printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
		printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
		printf_s("���ݷ� : %.2f\n", Objects[ENEMY]->Info.Att);
		printf_s("���� : %.2f\n", Objects[ENEMY]->Info.Def);
		printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);

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
			printf("[%s]�� ����\n", Objects[PLAYER]->Info.Name);
			//�÷��̾��� ���ݷ��� ������ ���º��� �������
			if (Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def)
			{
				Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def;
			}
			//�÷��̾��� ���ݷ��� ������ ���º��� ���� ���
			else
				Objects[ENEMY]->Info.HP -= 1;

			//������ ������ �����ϴ� �κ�
			printf("[%s]�� ����\n", Objects[ENEMY]->Info.Name);
			//������ ���ݷ��� �÷��̾��� ���º��� ���� ���
			if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def)
			{
				Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
			}
			//������ ���ݷ��� �÷��̾��� ���º��� ���� ���
			else
				Objects[PLAYER]->Info.HP -= 1;

			break;

			//���� �ൿ�� �����ϴ� �κ�
		case 2:
			//���� �õ� �ʱ�ȭ
			srand(time(NULL));
			//�����Լ��� ���� Ȯ�� ����
			run = rand() % 100;
			//������ ������ �÷��̾�� ���� ��� �÷��̾�� �г�Ƽ�� �־� ���� Ȯ���� ���ߴ� ����
			if (Objects[ENEMY]->Info.Level > Objects[PLAYER]->Info.Level)
			{
				//�г�Ƽ�� �����Ͽ� ���� Ȯ���� �����ϰ� ������ ���
				if (run - (Objects[ENEMY]->Info.Level - Objects[PLAYER]->Info.Level) * 5 > 30)
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

}
