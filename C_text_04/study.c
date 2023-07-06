#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"statement.h"


struct data
{
	//一个字节占8个bit;所以一个int类型就是32个bit
	unsigned int year : 20;//年份12个bit也够了
	unsigned int month : 4;//12个月份那么二进制下12=1100就是四个bit
	unsigned int day : 5;//每个月的天数不会超过32天,5个bit就够了：32 = 10 0000
};

void Input(struct data* p)
{
	//定义几个无符号的整型输入数据
	unsigned int yearcc, monthcc, daycc;
	printf("输入年月日，我给你算算是当年的第几天：");
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
	printf("这是%d年的第%d天", p->year, daynum);
}



int main()
{
	//位结构体的年月日输入，内存位的分配
	/*struct data p;
	Input(&p);
	counter(&p);*/
	//不管头插尾插都要重新定义分配空间
	struct hhh* _t = load("人头库.txt");
	if (_t == NULL)
	{
		/*struct hhh**/ _t = (struct hhh*)malloc(sizeof(struct hhh));
		if (_t == NULL)
		{
			printf("空间分配失败！");
			return 0;
		}
		_t->text = NULL;
	}
	while (1)
	{
		menu();
		int num;
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			printf("    1、头部添加\t2、尾部添加\t\t请选择:");
			scanf_s("%d", &num);
			num == 1 ? Headadd(_t) : (num == 2 ? Tailadd(_t) : printf("错误输入！"));
			system("pause");
			break;
		case 2:
			printf("    1、姓名删除   2、工号删除   3、工资段删除   请选择:");
			Remove(_t);
			break;
		case 3:
			modify(_t);
			break;
		case 4:
			view(_t);
			system("pause");
			break;
		case 5:
			sort(_t);
			system("pause");
			break;
		case 6:
			Empty(_t);
			break;
		case 0:
			printf("欢迎下次使用！\n");
			free(_t);
			system("pause");
			return 0;
		default:
			printf("\t\t  错误输入\n");
			system("pause");
			break;
		}
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}//清楚缓冲区
		system("cls");
	}








	return 0;
}