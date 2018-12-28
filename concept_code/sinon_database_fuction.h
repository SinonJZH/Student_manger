#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#define PASSWORD "sinon"

//定义数据结构体
struct Student
{
	char ID[20];
	char name[30];
	int age;
	double score;
};

int cmp(struct Student *a, struct Student *b);

//登陆函数
int login()
{
	char password[30] = "00000000000000000000000000000", ch = 0;
	puts("欢迎使用Sinon的学生信息管理系统！");
	puts("请先登录,或输入exit退出：");
	scanf("%s", password);
	if (strcmp(password, PASSWORD) == 0)
	{
		puts("登陆成功！");
		return 1;
	}
	else if (strcmp(password, "exit") == 0)
	{
		return 0;
	}
	else
	{
		puts("密码错误,请重试！");
		Sleep(1000);
		return -1;
	}
}

//数据库检测函数
void detect()
{
	FILE *fp;
	fp = fopen("Info.dat", "r");
	int control = 0;
	if (!fp)
	{
		int i = 1;
		while (i)
		{
			puts("数据库文件还未创建，需要创建一个吗？(是：1，否：2)");
			scanf("%1d", &control);
			switch (control)
			{
			default:
				puts("你输的啥玩意？请输1或2");
				break;
			case 1:
				fp = fopen("Info.dat","w+");
				puts("文件创建成功！");
				fprintf(fp, "%lf,%d,%s\n%s\n", 100.0,19,"test","B0000000000");
				i = 0;
				break;
			case 2:
				puts("不创建你运行这程序干啥？回去选1。");
				break;
			}
		}
	}
	else
	{
		puts("数据库已被成功读取。");
	}
	fclose(fp);
}

//菜单函数
int menu()
{
	while (1)
	{
		int control = 0;
		puts("*******************MENU***********************");
		puts("*1.数据查询                                  *");
		puts("*2.数据修改                                  *");
		puts("*3.数据删除                                  *");
		puts("*4.数据添加                                  *");
		puts("*5.排名查询                                  *");
		puts("*6.系统退出                                  *");
		puts("*请输入菜单前的数字来执行指令                *");
		puts("**********************************************");
		scanf("%1d", &control);
		if ((control > 0) & (control < 7))
		{
			return control;
		}
		else
		{
			puts("无效的命令，请重试！");
			Sleep(1000);
			system("cls");
		}
	}
}

//数据查询函数
int search()
{
	system("cls");
	FILE *fp;
	struct Student read[1000];
	int count = 0;
	fp = fopen("Info.dat", "rt");
	for (int i = 0; i <= 999; i++)
	{
		if (feof(fp))
		{
			count--;
			break;
		}
		fscanf(fp, "%lf,%d,%s%s",&read[i].score, &read[i].age, read[i].name, read[i].ID);
		count++;
	}
	if (count == 0)
	{
		puts("当前暂无数据！");
		fclose(fp);
		return 0;
	}
	puts("|--------------------------------------------------------------------------|");
	puts("|   序号          ID                            name   age        score    |");
	for (int i = 0; i <= (count-1); i++)
	{
		printf("| %4d  %20s    %20s   %2d       %.3f    |\n",i,read[i].ID , read[i].name, read[i].age, read[i].score);
	}
	puts("|--------------------------------------------------------------------------|");
	fclose(fp);
	return 0;
}

//数据修改函数
int edit()
{
	system("cls");
	FILE *fp;
	struct Student read[1000],edit;
	int count = 0, target = -1;
	fp = fopen("Info.dat", "rt");
	for (int i = 0; i <= 999; i++)
	{
		if (feof(fp))
		{
			count--;
			break;
		}
		fscanf(fp, "%lf,%d,%s%s", &read[i].score, &read[i].age, read[i].name, read[i].ID);
		count++;
	}
	puts("请输入你需要修改的条目序号：");
	scanf("%5d", &target);
	if (target < 0 || target >= count)
	{
		puts("没有查询到此序号的条目，请重试！");
		fclose(fp);
		return 0;
	}
	puts("请输入该学生的名字：");
	scanf("%20s", &edit.name);
	puts("请输入该学生的年龄：");
	scanf("%2d", &edit.age);
	puts("请输入该学生的ID:");
	scanf("%s", &edit.ID);
	puts("请输入该学生的成绩：");
	scanf("%lf", &edit.score);
	strcpy(read[target].name, edit.name);
	strcpy(read[target].ID, edit.ID);
	read[target].age = edit.age;
	read[target].score = edit.score;
	fclose(fp);
	fp = fopen("Info.dat", "w");
	for (int i = 0; i <= (count - 1); i++)
	{
		fprintf(fp, "%lf,%d,%s\n%s\n", read[i].score, read[i].age, read[i].name, read[i].ID);
	}
	puts("数据修改成功！");
	fclose(fp);
	Sleep(1000);
	return 0;
}

//数据删除函数
int del()
{
	system("cls");
	FILE *fp;
	struct Student read[1000];
	int count = 0, target = -1;
	fp = fopen("Info.dat", "rt");
	for (int i = 0; i <= 999; i++)
	{
		if (feof(fp))
		{
			count--;
			break;
		}
		fscanf(fp, "%lf,%d,%s%s", &read[i].score, &read[i].age, read[i].name, read[i].ID);
		count++;
	}
	puts("请输入你需要删除的条目ID：");
	scanf("%100d", &target);
	if (target < 0 || target >= count)
	{
		puts("没有查询到此ID的条目，请重试！");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	fp = fopen("Info.dat", "w");
	for (int i = 0; i <= (count - 1); i++)
	{
		if (i == target)
			continue;
		fprintf(fp, "%lf,%d,%s\n%s\n", read[i].score, read[i].age, read[i].name, read[i].ID);
	}
	puts("数据删除成功！");
	fclose(fp);
	return 0;
}

//数据增加函数
int add()
{
	system("cls");
	FILE *fp;
	struct Student edit;
	fp = fopen("Info.dat", "a+");
	puts("请输入该学生的名字：");
	scanf("%20s", &edit.name);
	puts("请输入该学生的年龄：");
	scanf("%2d", &edit.age);
	puts("请输入该学生的ID:");
	scanf("%s", &edit.ID);
	puts("请输入该学生的成绩：");
	scanf("%lf", &edit.score);
	fprintf(fp, "%lf,%d,%s\n%s\n", edit.score, edit.age, edit.name, edit.ID);
	puts("数据增加成功！");
	fclose(fp);
	return 0;
}

//成绩排名函数
int sort()
{
	system("cls");
	FILE *fp;
	struct Student read[1000];
	int count = 0;
	fp = fopen("Info.dat", "rt");
	for (int i = 0; i <= 999; i++)
	{
		if (feof(fp))
		{
			count--;
			break;
		}
		fscanf(fp, "%lf,%d,%s%s", &read[i].score, &read[i].age, read[i].name, read[i].ID);
		count++;
	}
	qsort(read, count, sizeof(read[0]), cmp);
	puts("|--------------------------------------------------------------------------|");
	puts("|   排名          ID                            name   age        score    |");
	for (int i = 0; i <= (count - 1); i++)
	{
		printf("| %4d  %20s    %20s   %2d       %.3f    |\n", i+1, read[i].ID, read[i].name, read[i].age, read[i].score);
	}
	puts("|--------------------------------------------------------------------------|");
	fclose(fp);
	return 0;
}

//比较函数
int cmp(struct Student *a, struct Student *b)
{
	return (a->score) < (b->score) ? 1 : -1;
}
