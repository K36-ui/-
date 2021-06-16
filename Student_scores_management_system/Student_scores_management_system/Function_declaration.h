#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<fstream>
#include<iostream>
#include <iomanip>
#include <cstring>
using namespace std;

enum Option//�˵�ѡ���������
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

struct stu_scores//ѧ�����˳ɼ���Ϣ������
{
	char stu_num[20] = { 0 };//ѧ��ѧ��
	char stu_name[10] = { 0 };//ѧ������
	int stu_score_list[6];//ѧ��ÿ�ſ�Ŀ�ĳɼ�
	int stu_sum = -1;//ѧ���ɼ��ܷ�
	int stu_average = -1;//ѧ���ɼ�ƽ����
	int rank = 0;//ѧ���ɼ�����
};

struct the_class//
{
	int class_num = 0;//���õ�ѧ������
	int real_num = 0;//��ʵ��ѧ������
	int class_average_list[6];//�༶ÿ�ſ�Ŀ��ƽ����
	int class_sum_list[6];//�༶ÿ�ſ�Ŀ���ܷ�
	struct stu_scores** list;//ѧ�����˳ɼ�����������
};

//��������

//��ʼ������
int Initlist(struct the_class* ps);

//���غ���
int Loadlist(struct the_class* ps);

//¼��ѧ���ɼ�����
void Record_score(struct the_class* ps);

//����༶ÿ�ſ�Ŀ���ܺ���
void Cal_total_average_score_course(struct the_class* ps, int mark);

//����༶����ѧ���ɼ��ĺ���
void Cal_total_average_score_stu(struct the_class* ps);

//ͨ��ѧ���ܷ��ɸߵ���������
int Sort_des_score(struct the_class* ps, int mark);

//ͨ��ѧ���ܷ��ɵ͵���������
void Sort_asc_score(struct the_class* ps);

//ͨ��ѧ��ѧ���ɵ͵���������
void Sort_asc_num(struct the_class* ps);

//ͨ��ѧ��������ASCII�����ɵ͵���������
void Sort_dic_name(struct the_class* ps);

//ͨ��ѧ��ѧ�Ų���ѧ���ɼ��ĺ���
void Sea_num(struct the_class* ps);

//ͨ��ѧ����������ѧ���ɼ��ĺ���
void Sea_name(struct the_class* ps);

//����ÿ�ſ�Ŀѧ���ĳɼ������Լ��ܽ�ĺ���
void Stat_analysis(struct the_class* ps);

//��ӡ��ѧ��������Ϣ�Ͱ༶��Ϣ�ĺ���
void List_record(struct the_class* ps);

//���ݱ��溯��
void Savedata(struct the_class* ps);