#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"statement.h"


struct data
{
	//һ���ֽ�ռ8��bit;����һ��int���;���32��bit
	unsigned int year : 20;//���12��bitҲ����
	unsigned int month : 4;//12���·���ô��������12=1100�����ĸ�bit
	unsigned int day : 5;//ÿ���µ��������ᳬ��32��,5��bit�͹��ˣ�32 = 10 0000
};

void Input(struct data* p)
{
	//���弸���޷��ŵ�������������
	unsigned int yearcc, monthcc, daycc;
	printf("���������գ��Ҹ��������ǵ���ĵڼ��죺");
	int i = scanf("%d %d %d", &yearcc, &monthcc, &daycc);
	struct data m = { yearcc,monthcc,daycc };
	*p = m;
}

void counter(struct data* p)
{
	int arr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int daynum = p->day;
	unsigned int i = 0;
	while (++i < (p->month))
		daynum += arr[i - 1];
	if (p->month > 2)
		daynum += (int)(p->year % 4 == 0 && p->year % 100 || p->year % 400 == 0);
	printf("����%d��ĵ�%d��", p->year, daynum);
}


int main()
{
	//λ�ṹ������������룬�ڴ�λ�ķ���
	/*struct data p;
	Input(&p);
	counter(&p);*/
	//����ͷ��β�嶼Ҫ���¶������ռ�
	functionpointer funcs[] = { exits,alladd,Remove,modify,view,sort,Empty };
	struct hhh* _t = load("��ͷ��.txt");
	if (_t == NULL)
	{
		/*struct hhh**/ _t = (struct hhh*)malloc(sizeof(struct hhh));
		if (_t == NULL)
		{
			printf("�ռ����ʧ�ܣ�");
			return 0;
		}
		_t->text = NULL;
	}
	while (1)
	{
		system("cls");
		timeshell();
		menu();
		int num;
		scanf_s("%d", &num);
		if (num >= 0 && num <= 6)
			funcs[num](_t);
		else
		{
			printf("\t\t  ��������\n");
		}
		system("pause");
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}//���������
	}
	return 0;
}