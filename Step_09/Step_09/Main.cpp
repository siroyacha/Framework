#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>

typedef struct tagInfo
{
	char Name[7];
	int Number;

	int iKor;
	int iEng;
	int IMath;
}INFO;

int main()
{
	/*
	tagInfo StudentA;
	tagInfo StudentB;

	printf_s("StudentA : \n");
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.IMath);
	printf_s("�� : %d, �� : %d, �� : %d\n", StudentA.iKor, StudentA.iEng, StudentA.IMath);


	printf_s("StudentB : \n");
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.IMath);
	printf_s("�� : %d, �� : %d, �� : %d\n", StudentB.iKor, StudentB.iEng, StudentB.IMath);
	*/
	
	/*
	INFO info;

	strcpy(info.Name, "ȫ�浿");

	info.iKor = 10;
	info.iEng = 20;
	info.IMath = 30;

	printf_s("%s : \n", info.Name);
	printf_s("%d, %d, %d", info.iKor, info.iEng, info.IMath);
	*/

	/*
	INFO info;
	int iIndex = 0;

	printf_s("����� ������ �����Դϱ�??\n");
	printf_s("**************************\n");
	printf_s("*     1. ��       ��     *\n");
	printf_s("*     2. ��   ��  ��     *\n");
	printf_s("*     3. ��       ��     *\n");
	printf_s("**************************\n");
	scanf_s("%d",&iIndex);


	switch (iIndex)
	{
	case 1:
		break;
	case 2:
		strcpy(info.Name, "������");
		break;
	case 3:
		strcpy(info.Name, "����");
		break;
	default:
		printf_s("�߸��� �Է��Դϴ�.\n");
	}

	printf_s("%s\n", info.Name);
	*/

	INFO info[3];
	char name[7];
	printf_s("�л��� ������ �Է��ϼ���.\n");

	/*
	for (int i = 0; i < 3; i++)
	{
		printf_s("�̸� �Է� : \n");
		scanf_s("%s", name);
		strcpy(info[i].Name, name);
	}
	*/
	
	strcpy(info[0].Name, "ȫ�浿");
	strcpy(info[1].Name, "��ö��");
	strcpy(info[2].Name, "�̿���");
	/*
	*/

	for (int i = 0; i < 3; i++)
	{
		printf_s("���� ���� ����: \n");
		scanf_s(" %d %d %d", &info[i].iKor, &info[i].iEng, &info[i].IMath);
	}

	for (int i = 0; i < 3; i++)
	{
		printf_s("%s : %d, %d, %d", info[i].Name, info[i].iKor, info[i].iEng, info[i].IMath);
	}

	return 0;
}