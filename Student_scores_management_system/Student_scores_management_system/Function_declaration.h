#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<fstream>
#include<iostream>
#include <iomanip>
#include <cstring>
using namespace std;

enum Option//菜单选项序号设置
{
	EXIT,
	RECORD,
	CAL_COURSE,
	CAL_STU,
	SORT_DES_SCORE,
	SORT_ASC_SCORE,
	SORT_ASC_NUM,
	SORT_DIC_NAME,
	SEA_NUM,
	SEA_NAME,
	STA_ANA,
	LIST_RECORD
};

struct stu_scores//学生个人成绩信息构造体
{
	char stu_num[20] = { 0 };//学生学号
	char stu_name[10] = { 0 };//学生姓名
	int stu_score_list[6];//学生每门科目的成绩
	int stu_sum = -1;//学生成绩总分
	int stu_average = -1;//学生成绩平均分
	int rank = 0;//学生成绩名次
};

struct the_class//
{
	int class_num = 0;//设置的学生人数
	int real_num = 0;//真实的学生人数
	int class_average_list[6];//班级每门科目的平均分
	int class_sum_list[6];//班级每门科目的总分
	struct stu_scores** list;//学生个人成绩构造体数组
};

//函数声明

//初始化函数
int Initlist(struct the_class* ps);

//加载函数
int Loadlist(struct the_class* ps);

//录入学生成绩函数
void Record_score(struct the_class* ps);

//计算班级每门科目汇总函数
void Cal_total_average_score_course(struct the_class* ps, int mark);

//计算班级所有学生成绩的函数
void Cal_total_average_score_stu(struct the_class* ps);

//通过学生总分由高到低排序函数
int Sort_des_score(struct the_class* ps, int mark);

//通过学生总分由低到高排序函数
void Sort_asc_score(struct the_class* ps);

//通过学生学号由低到高排序函数
void Sort_asc_num(struct the_class* ps);

//通过学生名字在ASCII码中由低到高排序函数
void Sort_dic_name(struct the_class* ps);

//通过学生学号查找学生成绩的函数
void Sea_num(struct the_class* ps);

//通过学生姓名查找学生成绩的函数
void Sea_name(struct the_class* ps);

//分析每门科目学生的成绩评价以及总结的函数
void Stat_analysis(struct the_class* ps);

//打印出学生个人信息和班级信息的函数
void List_record(struct the_class* ps);

//数据保存函数
void Savedata(struct the_class* ps);