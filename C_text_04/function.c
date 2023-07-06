#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"statement.h"
#include<string.h>
#include<time.h>

struct hhh* phead = NULL;
count = 0;

//延迟函数  头文件tiem.h
void Delay(int time)//time*1000为秒数 
{
	clock_t now = clock();

	while (clock() - now < time);
}

void save(struct hhh* person)
{
	struct hhh* head = person->text;
	FILE* f = fopen("人头库.txt", "wb");
	if (f == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	while (head != NULL)//fscanf函数可读取文件的输入输出流
	{
		fprintf(f, "%s\n%d\n%g\n", head->data.name, head->data.numb, head->data.wages);
		head = head->text;
	}
	fclose(f);
}

struct hhh* load(const char* file)
{
	FILE* p = fopen(file, "rb");
	if (p == NULL)
	{
		return NULL;
	}
	struct hhh* loadcc = (struct hhh*)malloc(sizeof(struct hhh));
	if (loadcc == NULL)
	{
		printf("内存分配失败！");
		fclose(p);
		return NULL;
	}
	struct hhh* temp = (struct hhh*)malloc(sizeof(struct hhh));
	loadcc->text = temp;
	if (temp == NULL)
		return NULL;
	struct hhh* m = NULL;
	while ((temp != NULL && fscanf(p, "%s", temp->data.name) != EOF && fscanf(p, "%d", &temp->data.numb) != EOF && fscanf(p, "%g", &temp->data.wages) != EOF))
	{
		temp->text = (struct hhh*)malloc(sizeof(struct hhh));//为下个节点分配内存，同时这样的赋值方式也不会报错
		if (temp->text != NULL)
		{
			m = temp;
			temp = temp->text;
			temp->text = NULL;//必须加if进行限制，否则系统会考虑内存分配失败提示取消对NULL的引用
			count++;
		}
	}
	if (m != NULL)
		m->text = NULL;//拿到上一个节点进行置空，因为循环多判断了一次
	if (count == 0)
		loadcc->text = NULL;
	fclose(p);
	return loadcc;
}

//创建新空间
struct hhh* Creatspace(Data data)
{
	struct hhh* new = (struct hhh*)malloc(sizeof(struct hhh));
	if (new == NULL)
	{
		printf("空间分配失败!");
		return NULL;
	}
	new->data = data;
	new->text = NULL;
	return new;
}

//姓名、工号、工资筛选
struct hhh* search(struct hhh* person, int num)
{
	struct hhh* cur = (struct hhh*)malloc(sizeof(struct hhh));
	if (cur == NULL)
	{
		return NULL;
	}
	struct hhh* c = cur;
	if (num == 1)
	{
		struct hhh* p = person;
		char name[value] = {0};
		scanf_s("%s", name, (unsigned int)sizeof(name));
		while (person != NULL)
		{
			person = person->text;
			while (person != NULL && strcmp(person->data.name, name) == 0)
			{
				p = person->text;
				cur->text = (struct hhh*)malloc(sizeof(struct hhh));
				cur = cur->text;
				if (cur == NULL)
				{
					return NULL;
				}
				cur->data = person->data;
				person = p;
			}
		}
		cur->text = NULL;
		cur = c;
		return cur;
	}
	else if (num == 2)
	{
		scanf_s("%d", &num);
		struct hhh* p = person;
		while (person != NULL)
		{
			person = person->text;
			if(person != NULL && person->data.numb == num)
			{
				cur->text = (struct hhh*)malloc(sizeof(struct hhh));
				cur = cur->text;
				if (cur != NULL)
				{
					cur->data = person->data;
					cur->text = NULL;
				}
				c->text = cur;
				cur = c;
				return cur;
			}
		}
		if (cur != NULL)
			cur->text = NULL;
		cur = c;
		person = p;
		return cur;
	}
	else if (num == 3)
	{
		struct hhh* p = person;
		float a, b;
		scanf_s("%f", &a);
		scanf_s("%f", &b);
		if (a > b)
		{
			float temp = a;
			a = b;
			b = temp;
		}
		while (person != NULL)
		{
			person = person->text;
			if (person != NULL && person->data.wages >= a && person->data.wages <= b)
			{
				cur->text = (struct hhh*)malloc(sizeof(struct hhh));
				cur = cur->text;
				if (cur == NULL)
				{
					return NULL;
				}
				cur->data = person->data;
			}
		}
		if(cur != NULL)
			cur->text = NULL;
		cur = c;
		person = p;
		return cur;
	}
	else
	{
		cur->text = NULL;
		printf("无效输入！");
		return cur;
	}
}

//工号唯一判断
int X(struct hhh* person, int data)
{
	while (person->text != NULL)
	{
		person = person->text;
		if (person->data.numb == data)
			return 1;
	}
	return 0;
}

//头插
void Headadd(struct hhh* person)
{
	if (count == Max)
		printf("人员已满%d/%d!\n", count,Max);
	struct hhh* new = Creatspace(person->data);
	printf("请输入以下添加信息\n");
	printf("姓名：");
	scanf_s("%s",new->data.name,(unsigned int)sizeof(new->data.name));
	cc:
	printf("工号：");
	scanf_s("%d", &new->data.numb);
	if (X(person, new->data.numb) == 1)
	{
		printf("已存在该工号人员，禁止重复！\n");
		goto cc;
	}
	printf("工资：");
	scanf_s("%f", &new->data.wages);
	if (person->text == NULL)
	{
		person->text = new;
	}
	else
	{
		struct hhh* s = new;
		new->text = person->text;
		person->text = new;
	}
	count++;
	printf("\t添加成功！\n");
	printf("当前数据%d/%d\n", count, Max);
	save(person);
}

//尾插
void Tailadd(struct hhh* person)
{
	if (count == Max)
		printf("人员已满%d/%d!\n",count,Max);
	struct hhh* new = Creatspace(person->data);
	printf("请输入以下提示信息\n");
	printf("姓名：");
	scanf_s("%s", new->data.name, (unsigned int)sizeof(struct hhh));
	cc:
	printf("工号：");
	scanf_s("%d", &new->data.numb);
	if (X(person, new->data.numb) == 1)
	{
		printf("已存在该工号人员，禁止重复！\n");
		goto cc;
	}
	printf("工资：");
	scanf_s("%g", &new->data.wages);
	struct hhh* cur = person;
	while (person->text != NULL)
	{
		person = person->text;
	}
	new->text = NULL;
	person->text = new;
	person = cur;
	count++;
	printf("\t添加成功！\n");
	printf("当前数据%d/%d\n", count, Max);
	save(person);
}

//打印
void Print(struct hhh* person)
{
	struct hhh* print = person->text;
	printf("\t姓名\t\t工号\t\t工资\n");
	while (print != NULL)
	{
		printf("\t%-8s\t%-8d\t%-8g\n", print->data.name, print->data.numb, print->data.wages);
		print = print->text;
	}
	puts("");
	if(count == 0)
		printf("\t当前数据为0！\n");
}

//删除
int Remove(struct hhh* person)
{
	struct hhh* pp = person;
	int num;
	char p;
	scanf_s("%d", &num);
	if (num == 1)
	{
		printf("请输入删除人姓名：");
		struct hhh* cur = search(person,num);
		if (cur->text == NULL)
		{
			printf("\t未发现有该角色！\n");
			system("pause");
			return 0;
		}
		struct hhh* ar = (struct hhh*)sizeof(struct hhh);
		ar = cur->text;
		struct hhh* te;
		struct hhh* tr;
		while (person->text != NULL)
		{
			te = person;
			person = person->text;
			while (person != NULL && ar != NULL && strcmp(person->data.name, ar->data.name)== 0)
			{
				tr = person->text;
				person->text = NULL;
				Print(te);
				puts("");
				printf("    是否删除该角色？\ty(Y)/n(N)\t请选择：");
				scanf_s(" %c", &p,(unsigned int)sizeof(p));
				if (p == 'y' || p == 'Y')
				{
					free(person);
					te->text = tr;
					person = tr;
					count--;
					printf("\t删除成功！\n");
					break;
				}
				te->text = person;
				person->text = tr;
				person = tr;
				printf("\t已取消删除！\n");
			}
			if (person == NULL)
				break;
		}
		Delay(8*100);//延迟0.8秒
		person = pp;
		save(person);
		printf("\t已筛查完毕，保存文件成功！\n");
		system("pause");
	}
	else if (num == 2)
	{
		printf("请输入删除人工号：");
		struct hhh* cur = search(person,num);
		if (cur->text == NULL)
		{
			printf("\t未发现有该角色！\n");
			system("pause");
			return 0;
		}
		struct hhh* te;
		struct hhh* tr;
		cur = cur->text;
		while (person != NULL && cur != NULL)
		{
			te = person;
			person = person->text;
			if (person->data.numb == cur->data.numb)
			{
				tr = person->text;
				person->text = NULL;
				Print(te);
				puts("");
				printf("    是否删除该角色？\ty(Y)/n(N)\t请选择：");
				scanf_s(" %c", &p, (unsigned int)sizeof(p));
				if (p == 'y' || p == 'Y')
				{
					free(person);
					te->text = tr;
					count--;
					printf("\t删除成功！\n");
					break;
				}
				printf("\t已取消删除！\n");
				break;
			}
		}
		person = pp;
		save(person);
		system("pause");
	}
	else if(num == 3)
	{
		printf("请输入删除的工资段区间\n");
		struct hhh* pp = person;
		struct hhh* cur = search(person, num);
		if (cur->text == NULL)
		{
			printf("\t未发现匹配角色！");
			system("pause");
			return 0;
		}
		struct hhh* te = person;
		struct hhh* tr = person;
		struct hhh* ar = cur;
		printf("\t姓名\t\t工号\t\t工资\n");
		while (cur != NULL)
		{
			cur = cur->text;
			while (person != NULL && cur != NULL && person->data.wages != cur->data.wages)
			{
				te = person;
				person = person->text;
				if (person == NULL)
					break;
				tr = person->text;
			}
			if (person != NULL && cur != NULL && person->data.wages == cur->data.wages)
			{
				printf("\t%-8s\t%-8d\t%-8g\n", cur->data.name, cur->data.numb, cur->data.wages);
			}
			person = pp;
		}
		cur = ar;
		printf("    是否删除以上数据？\ty(Y)/n(N)\t请选择：");
		scanf_s(" %c", &p, (unsigned int) sizeof(p));
		if (p == 'y' || p == 'Y')
		{
			while (person != NULL && cur != NULL)
			{
				cur = cur->text;
				while (cur != NULL && person != NULL && person->data.numb != cur->data.numb)
				{
					te = person;
					person = person->text;
					if (person == NULL)
						break;
				}
				if (person != NULL && cur != NULL && person->data.numb == cur->data.numb)
				{
					tr = person->text;
					if (person->text == NULL)
						tr = NULL;
					free(person);
					te->text = tr;
				}
				person = tr;
			}
			person = pp;
			Delay(8 * 100);
			printf("\t删除成功！\n");
			system("pause");
			save(person);
			return 0;
		}
		printf("\t已取消删除！\n");
		system("pause");
	}
	else
	{
		printf("\t\t  无效输入!\n");
		system("pause");
	}
	return 0;
}

//清空
void Empty(struct hhh* person)
{
	struct hhh* cur= person->text;
	struct hhh* n = NULL;
	while (cur != NULL)
	{
		n = cur->text;
		free(cur);
		cur = n;
	}
	person->text = NULL;
	count = 0;
	printf("数据已清空！\n");
	save(person);
	system("pause");
}

//修改
void modify(struct hhh* person)
{
	struct hhh* pp = person;
	printf("请输入修改人的工号：");
	struct hhh* cur = search(person, 2);
	if (cur->text == NULL)
	{
		printf("\t未发现对应角色！\n");
		system("pause");
		return;
	}
	char p;
	while (person != NULL)
	{
		person = person->text;
		if (person != NULL && cur != NULL && person->data.numb == cur->text->data.numb)
		{
			Print(cur);
			printf("\t是否修改信息？\ty(Y)/n(N)\t请选择：");
			scanf_s(" %c", &p, (unsigned int)sizeof(p));
			if (p == 'y' || p == 'Y')
			{
				printf("请输入以下提示信息\n");
				printf("姓名：");
				scanf_s("%s", person->data.name,(unsigned int)sizeof(person->data.name));
				int t2,t = person->data.numb;
				cc:
				printf("工号：");
				scanf_s("%d", &t2);
				if (X(pp, t2) == 1 && person->data.numb != t)
				{
					printf("工号重复重新输入\n");
					goto cc;
				}
				person->data.numb = t2;
				printf("工资：");
				scanf_s("%g", &person->data.wages);
				person = pp;
				save(person);
				printf("\t修改成功!\n");
				free(cur);
				system("pause");
				return;
			}
		}
	}
	person = pp;
	printf("\t已取消修改!\n");
	system("pause");
}

//查看
void view(struct hhh* person)
{
	Print(person);
	printf("当前数据为%d/%d\n", count, Max);
}

//排序查找
void sort(struct hhh* person)
{
	printf("    1、姓名排序    2、工号排序    3、工资排序    4、查找\t请选择:");
	int num = 0;
	scanf_s(" %d", &num);
	struct hhh* cur = (struct hhh*)malloc(sizeof(struct hhh));
	struct hhh* s = person;
	struct hhh* pp = person;
	if(cur != NULL)
		cur->text = NULL;
	if (num == 1)
	{
		struct hhh* te = pp;
		struct hhh* tr = person;
		while (te != NULL)
		{
			te = te->text;
			tr = te;
			while (tr != NULL)
			{
				/*strcmp的判断小于返回负数(不一定就是 - 1)，等于返回0，
					大于返回正数(不一定就是1)，所以不能直接判断等于1还是等于-1*/
				tr = tr->text;
				if (tr != NULL && strcmp(te->data.name, tr->data.name) > 0)
				{
					cur->data = te->data;
					te->data = tr->data;
					tr->data = cur->data;
				}
			}
		}
		person = s;
		Print(person);
		save(person);
		return;
	}
	if (num == 2)
	{
		while (pp->text != NULL)
		{
			pp = pp->text;
			person = pp;
			while (person != NULL && person->text != NULL)
			{
				person = person->text;
				if (person != NULL && (pp->data.numb > person->data.numb))
				{
					cur->data = pp->data;
					pp->data = person->data;
					person->data = cur->data;
				}
			}
		}
		person = s;
		save(person);
		Print(person);
		return;
	}
	if (num == 3)
	{
		while (pp->text != NULL)
		{
			pp = pp->text;
			person = pp;
			while (person->text != NULL)
			{
				person = person->text;
				if (person != NULL && (pp->data.wages > person->data.wages))
				{
					cur->data = pp->data;
					pp->data = person->data;
					person->data = cur->data;
				}
			}
		}
		person = s;
		save(person);
		Print(person);
		return;
	}
	if (num == 4)
	{
		printf("\n    1、姓名    2、工号    3、工资    请选择查找方式:");
		int n;
		scanf_s("%d", &n);
		n == 1 ? printf("请输入查找人姓名：") :
			(n == 2 ? printf("请输入查找人工号：") :
				(n == 3 ? printf("请输入查找人工资段\n") : putchar(0)));
		cur = search(person, n);
		if (cur->text != NULL)
			Print(cur);
		return;
	}
	else
	{
		printf("错误输入！\n");
		return;
	}
}


void menu()
{
	printf("\t\t*********************************\n");
	printf("\t\t*\t\t\t\t*\n");
	printf("\t\t*\t 管理系统-链表式  \t*\n");
	printf("\t\t*\t   1、添加人员\t\t*\n");
	printf("\t\t*\t   2、删除信息\t\t*\n");
	printf("\t\t*\t   3、修改信息\t\t*\n");
	printf("\t\t*\t   4、浏览信息\t\t*\n");
	printf("\t\t*\t   5、排序查找\t\t*\n");
	printf("\t\t*\t   6、清空数据\t\t*\n");
	printf("\t\t*\t   0、退出系统 \t\t*\n");
	printf("\t\t*********************************\n");
	printf("\t\t请选择以上功能：");
}





