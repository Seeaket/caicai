#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"statement.h"
#include<string.h>
#include<time.h>
#include<ctype.h>

#define EPS 1e-6

struct hhh* phead = NULL;
count = 0;
//bbb
//�ӳٺ���  ͷ�ļ�tiem.h
void Delay(int time)//time*1000Ϊ���� 
{
	clock_t now = clock();

	while (clock() - now < time);
}

void save(struct hhh* person)
{
	struct hhh* head = person->text;
	FILE* f = fopen("��ͷ��.txt", "wb");
	if (f == NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		return;
	}
	while (head != NULL)//fscanf�����ɶ�ȡ�ļ������������
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
		printf("�ڴ����ʧ�ܣ�");
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
		temp->text = (struct hhh*)malloc(sizeof(struct hhh));//Ϊ�¸��ڵ�����ڴ棬ͬʱ�����ĸ�ֵ��ʽҲ���ᱨ��
		if (temp->text != NULL)
		{
			m = temp;
			temp = temp->text;
			temp->text = NULL;//�����if�������ƣ�����ϵͳ�ῼ���ڴ����ʧ����ʾȡ����NULL������
			count++;
		}
	}
	if (m != NULL)
		m->text = NULL;//�õ���һ���ڵ�����ÿգ���Ϊѭ�����ж���һ��
	if (count == 0)
		loadcc->text = NULL;
	fclose(p);
	return loadcc;
}

//�����¿ռ�
struct hhh* Creatspace(Data data)
{
	struct hhh* new = (struct hhh*)malloc(sizeof(struct hhh));
	if (new == NULL)
	{
		printf("�ռ����ʧ��!");
		return NULL;
	}
	new->data = data;
	new->text = NULL;
	return new;
}

//���������š�����ɸѡ
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
			while (person != NULL && samesearch(person->data.name, name) == 0)
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
		printf("��Ч���룡");
		return cur;
	}
}

//����Ψһ�ж�
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

//ͷ��
void Headadd(struct hhh* person)
{
	if (count == Max)
		printf("��Ա����%d/%d!\n", count,Max);
	struct hhh* new = Creatspace(person->data);
	printf("���������������Ϣ\n");
	printf("������");
	scanf_s("%s",new->data.name,(unsigned int)sizeof(new->data.name));
	cc:
	printf("���ţ�");
	scanf_s("%d", &new->data.numb);
	if (X(person, new->data.numb) == 1)
	{
		printf("�Ѵ��ڸù�����Ա����ֹ�ظ���\n");
		goto cc;
	}
	printf("���ʣ�");
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
	printf("\t��ӳɹ���\n");
	printf("��ǰ����%d/%d\n", count, Max);
	save(person);
}

//β��
void Tailadd(struct hhh* person)
{
	if (count == Max)
		printf("��Ա����%d/%d!\n",count,Max);
	struct hhh* new = Creatspace(person->data);
	printf("������������ʾ��Ϣ\n");
	printf("������");
	scanf_s("%s", new->data.name, (unsigned int)sizeof(struct hhh));
	cc:
	printf("���ţ�");
	scanf_s("%d", &new->data.numb);
	if (X(person, new->data.numb) == 1)
	{
		printf("�Ѵ��ڸù�����Ա����ֹ�ظ���\n");
		goto cc;
	}
	printf("���ʣ�");
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
	printf("\t��ӳɹ���\n");
	printf("��ǰ����%d/%d\n", count, Max);
	save(person);
}

//��ӡ
void Print(struct hhh* person)
{
	struct hhh* print = person->text;
	printf("\t����\t\t����\t\t����\n");
	while (print != NULL)
	{
		printf("\t%-8s\t%-8d\t%-8g\n", print->data.name, print->data.numb, print->data.wages);
		print = print->text;
	}
	puts("");
}

//ɾ��
int Remove(struct hhh* person)
{
	printf("    1������ɾ��   2������ɾ��   3�����ʶ�ɾ��   ��ѡ��:");
	struct hhh* pp = person;
	int num;
	char p;
	scanf_s("%d", &num);
	if (num == 1)
	{
		printf("������ɾ����������");
		struct hhh* cur = search(person,num);
		if (cur->text == NULL)
		{
			printf("\tδ�����иý�ɫ��\n");
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
				printf("    �Ƿ�ɾ���ý�ɫ��\ty(Y)/n(N)\t��ѡ��");
				scanf_s(" %c", &p,(unsigned int)sizeof(p));
				if (p == 'y' || p == 'Y')
				{
					free(person);
					te->text = tr;
					person = tr;
					count--;
					printf("\tɾ���ɹ���\n");
					break;
				}
				te->text = person;
				person->text = tr;
				person = tr;
				printf("\t��ȡ��ɾ����\n");
			}
			if (person == NULL)
				break;
		}
		Delay(8*100);//�ӳ�0.8��
		person = pp;
		save(person);
		printf("\t��ɸ����ϣ������ļ��ɹ���\n");
		return 0;
	}
	else if (num == 2)
	{
		printf("������ɾ���˹��ţ�");
		struct hhh* cur = search(person,num);
		if (cur->text == NULL)
		{
			printf("\tδ�����иý�ɫ��\n");
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
				printf("    �Ƿ�ɾ���ý�ɫ��\ty(Y)/n(N)\t��ѡ��");
				scanf_s(" %c", &p, (unsigned int)sizeof(p));
				if (p == 'y' || p == 'Y')
				{
					free(person);
					te->text = tr;
					count--;
					printf("\tɾ���ɹ���\n");
					break;
				}
				printf("\t��ȡ��ɾ����\n");
				break;
			}
		}
		person = pp;
		save(person);
		return 0;
	}
	else if(num == 3)
	{
		printf("������ɾ���Ĺ��ʶ�����\n");
		struct hhh* pp = person;
		struct hhh* cur = search(person, num);
		if (cur->text == NULL)
		{
			printf("\tδ����ƥ���ɫ��");
			system("pause");
			return 0;
		}
		struct hhh* te = person;
		struct hhh* tr = person;
		struct hhh* ar = cur;
		printf("\t����\t\t����\t\t����\n");
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
		printf("    �Ƿ�ɾ���������ݣ�\ty(Y)/n(N)\t��ѡ��");
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
			printf("\tɾ���ɹ���\n");
			save(person);
			return 0;
		}
		printf("\t��ȡ��ɾ����\n");
	}
	else
	{
		printf("\t\t  ��Ч����!\n");
	}
	return 0;
}

//���
void Empty(struct hhh* person)
{
	printf("\tȷ���������������  y(Y)/n(N)\t��ѡ��");
	char Y;
	scanf_s(" %c", &Y,(unsigned int)sizeof(Y));
	if (Y == 'Y' || Y == 'y')
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
		printf("��������գ�\n");
		save(person);
		
	}
	else if(Y == 'n' || Y == 'N')
	{
		printf("��ȡ��������ݣ�\n");
	}
	else
	{
		printf("����������ȡ�����\n");
	}
}

//�޸�
void modify(struct hhh* person)
{
	struct hhh* pp = person;
	printf("�������޸��˵Ĺ��ţ�");
	struct hhh* cur = search(person, 2);
	if (cur->text == NULL)
	{
		printf("\tδ���ֶ�Ӧ��ɫ��\n");
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
			printf("\t�Ƿ��޸���Ϣ��\ty(Y)/n(N)\t��ѡ��");
			scanf_s(" %c", &p, (unsigned int)sizeof(p));
			if (p == 'y' || p == 'Y')
			{
				printf("������������ʾ��Ϣ\n");
				printf("������");
				scanf_s("%s", person->data.name,(unsigned int)sizeof(person->data.name));
				int t2,t = person->data.numb;
				cc:
				printf("���ţ�");
				scanf_s("%d", &t2);
				if (X(pp, t2) == 1 && person->data.numb != t)
				{
					printf("�����ظ���������\n");
					goto cc;
				}
				person->data.numb = t2;
				printf("���ʣ�");
				scanf_s("%g", &person->data.wages);
				person = pp;
				save(person);
				printf("\t�޸ĳɹ�!\n");
				free(cur);
				return;
			}
		}
	}
	person = pp;
	printf("\t��ȡ���޸�!\n");
}

//�鿴
void view(struct hhh* person)
{
	Print(person);
	printf("��ǰ����Ϊ%d/%d\n", count, Max);
}

//ʱ����ʾ
void timeshell()
{
	//while (1)
	//{
		putchar(10);
		time_t m;
		m = time(NULL);
		struct tm cm;
		int n = localtime_s(&cm, &m);
		char* week[] = { "����һ","���ڶ�","������","������","������","������","������" };
		printf("\t      ����ʱ�䣺%d��%d��%d�� %d:%d:%d %s\n", cm.tm_year+1900, cm.tm_mon+1, cm.tm_mday,
			cm.tm_hour, cm.tm_min, cm.tm_sec, week[cm.tm_wday]);
	//	Delay(1000);//�ӳ�һ���ӡ
	//	system("cls");
	//}
}


//�������
void sort(struct hhh* person)
{
	printf("    1����������    2����������    3����������    4������\t��ѡ��:");
	int num = 0;
	scanf_s(" %d", &num);
	struct hhh* cur = (struct hhh*)malloc(sizeof(struct hhh));
	struct hhh* s = person;
	struct hhh* pp = person;
	if(cur != NULL)
		cur->text = NULL;
	if (num > 0 && num < 4)
	{
		struct hhh* te = pp;
		struct hhh* tr = person;
		while (te != NULL)
		{
			te = te->text;
			tr = te;
			while (tr != NULL && te != NULL)
			{
				/*strcmp���ж�С�ڷ��ظ���(��һ������ - 1)�����ڷ���0��
					���ڷ�������(��һ������1)�����Բ���ֱ���жϵ���1���ǵ���-1*/
				tr = tr->text;
				if (tr != NULL && (num == 1 ? (strcmp(te->data.name, tr->data.name) > 0) : 
				(num == 2 ? te->data.numb > tr->data.numb : (num == 3 ? te->data.wages > tr->data.wages :putchar(0)))))
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
	if (num == 4)
	{
		printf("\n    1������    2������    3������    ��ѡ����ҷ�ʽ:");
		int n;
		scanf_s("%d", &n);
		n == 1 ? printf("�����������������") :
			(n == 2 ? printf("����������˹��ţ�") :
				(n == 3 ? printf("����������˹��ʶ�\n") : putchar(0)));
		cur = search(person, n);
		if (cur->text != NULL)
			Print(cur);
		else
		{
			printf("δ����������\n");
		}
		return;
	}
	else
	{
		printf("�������룡\n");
		return;
	}
}

//�������Դ�Сд��ĸ����
int samesearch(char* str1, char* str2)
{
	char* arr1 = _strdup(str1);
	char* arr2 = _strdup(str2);
	for (int i = 0; arr1[i]; i++)
	{
		if (arr1[i] >= 'A' && arr1[i] <= 'Z')
		{
			arr1[i] = tolower((unsigned char)arr1[i]);
		}
	}
	for (int i = 0; arr1[i]; i++)
	{
		if (arr2[i] >= 'A' && arr2[i] <= 'Z')
		{
			arr2[i] = tolower((unsigned int)arr2[i]);
		}
	}
	//if(arr1 != NULL && arr2!=NULL)
	int n = strcmp(arr1, arr2);
	free(arr1);
	free(arr2);
	return n;
}


void menu()
{
	printf("\t\t*********************************\n");
	printf("\t\t*\t\t\t\t*\n");
	printf("\t\t*\t ����ϵͳ-����ʽ  \t*\n");
	printf("\t\t*\t   1�������Ա\t\t*\n");
	printf("\t\t*\t   2��ɾ����Ϣ\t\t*\n");
	printf("\t\t*\t   3���޸���Ϣ\t\t*\n");
	printf("\t\t*\t   4�������Ϣ\t\t*\n");
	printf("\t\t*\t   5���������\t\t*\n");
	printf("\t\t*\t   6���������\t\t*\n");
	printf("\t\t*\t   0���˳�ϵͳ \t\t*\n");
	printf("\t\t*********************************\n");
	printf("\t\t��ѡ�����Ϲ��ܣ�");
}

void alladd(struct hhh* person)
{
	int num;
	printf("    1��ͷ�����\t2��β�����\t\t��ѡ��:");
	scanf_s("%d", &num);
	num == 1 ? Headadd(person) : (num == 2 ? Tailadd(person) : printf("�������룡"));
}

void exits(struct hhh* person)
{
	printf("��ӭ�´�ʹ�ã�\n");
	free(person);
	exit(0);
}



