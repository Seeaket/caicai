#pragma once
#include<stdio.h>
#include<stdlib.h>

#define Max 100
#define value 30

int count;

typedef struct wdfk
{
	char name[value];
	int numb;
	float wages;
}Data;

struct hhh
{
	Data data;
	struct hhh* text;
};

void Delay(int time);
void save(struct hhh* person);
struct hhh* load(const char* file);
int X(struct hhh* person, int data);

void Headadd(struct hhh* person);
void Tailadd(struct hhh* person);
void Print(struct hhh* person);
int Remove(struct hhh* person);
void Empty(struct hhh* person);
struct hhh* search(struct hhh* person, int num);
void modify(struct hhh* person);
void sort(struct hhh* person);
void view(struct hhh* person);
void timeshell();
int samesearch(char* str1,char* str2);

void alladd(struct hhh* person);
typedef void (*functionpointer)(struct hhh* person);
void exits(struct hhh* person);


void menu();


