#include "Function_declaration.h"

int Initlist(struct the_class* ps)//��ʼ������
{
	int Class_num, i = 0;
	cout << "�����ð༶����:";
	cin >> Class_num;

	struct stu_scores** list_tmp = new struct stu_scores* [Class_num];/*ʹ�����úõİ༶��ʼ���������ٶ�̬�������ڴ���ѧ��������Ϣ������*/

	/*Ϊÿ��ѧ��������Ϣ����������Ԫ�ط���ռ�*/
	for (i = 0; i < Class_num; i++)
	{
		*(list_tmp + i) = new struct stu_scores;
	}

	/*��ʼ���༶������*/
	ps->class_num = Class_num;
	ps->list = list_tmp;
	ps->class_average_list[0] = -1;
	ps->class_sum_list[0] = -1;

	/*����ļ��Ƿ���ڣ������򴴽��ļ�*/
	ifstream file1;
	file1.open("data.txt", ifstream::in);
	if (!file1)
	{
		cout << "δ��⵽�洢�ļ�����\n";
		ofstream file2;
		file2.open("data.txt", ifstream::out);
		if (file2.is_open())
		{
			cout << "�������ļ��ɹ�\n";
			file2.close();
			return 1;
		}
		else
		{
			cout << "�������ļ�ʧ��\n";
			return 0;
		}
	}
	return 1;
}

int Loadlist(struct the_class* ps)//���غ���
{
	ifstream file1;
	file1.open("data.txt");

	if (!file1)/*����ļ��Ƿ�򿪳ɹ�*/
	{
		cout << "ERROR Program Closed\n";
		cout << "���ļ�ʧ��\n";
		return 1;
	}
	if (file1.peek() == EOF)/*����ļ��Ƿ�Ϊ��*/
		return 0;
	for (int i = 0;!file1.eof();i++)/*����Ƿ��ļ���ȡ��β��ͬʱ��ȡ�ļ�����*/
	{
		if (i>=ps->class_num)/*����Ƿ��ʵ�ʰ༶�������*/
		{
			cout << "ERROR Program Closed\n";
			cout << "������һ����С�ڰ༶ʵ��ѧ���������Ѿ�����ѧ������������\n";
			return 1;
		}
		file1 >> ps->list[i]->stu_num;
		file1 >> ps->list[i]->stu_name;
		for(int j=0;j<6;j++)
			file1 >> ps->list[i]->stu_score_list[j];
		ps->real_num++;
	}
	file1.close();
	return 0;
}

//�ռ����ݺ���
void List_Expansion(struct the_class* ps)
{
	cout << "��ʼ���õ�����С��ʵ�������������ݴ���ռ�\n";
	int i;

	/*ɾ���ѿ��ٵĿռ�*/
	for (i = 0; i < ps->class_num; i++)
		delete(ps->list[i]);

	/*���¿���һ������ռ�*/
	struct stu_scores** list_tmp = new struct stu_scores* [++(ps->class_num)];

	/*��ʼ���༶������*/
	for (i = 0; i < ps->class_num+1; i++)
	{
		*(list_tmp + i) = new struct stu_scores;
	}
	ps->list = list_tmp;
	ps->class_average_list[0] = -1;
	ps->class_sum_list[0] = -1;
	ps->real_num = 0;

	/*���¶�ȡ�ļ�����*/
	Loadlist(ps);
	cout << "���ݳɹ�\n";
}

//����Ƿ����ѧ���ɼ��ĺ�������ΪĳЩ����ʹ��ǰ��
int check_emt(struct the_class* ps)
{
	if (ps->real_num == 0)
	{
		cout << "ϵͳδ��⵽ѧ���ɼ�������¼��ѧ���ɼ�\n";
		return 1;
	}
	else
		return 0;
}

void Savedata(struct the_class* ps)//���ݱ��溯��
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	fstream f;
	f.open("data.txt");
	if (!f)/*����ļ��򿪳ɹ����*/
	{
		cout << "���ļ�ʧ��\n";
		return;
	}
	for (int i = 0; i < ps->real_num; i++)/*���������ݱ������ļ�*/
	{
		int j = 0;
		f << ps->list[i]->stu_num << endl;
		f << ps->list[i]->stu_name << endl;
		for (j = 0; j < 5; j++)
			f << ps->list[i]->stu_score_list[j] << endl;
		f << ps->list[i]->stu_score_list[j];
		if (i + 1 != ps->real_num)
			f << endl;
		ps->list[i]++;
	}
	f.close();
	cout << "�����˳�\n";
}

//��ӡ�˵�����
void show_menu()
{
	cout << "����   ѧ��             ����     ����   ��ѧ   Ӣ��   ����   ��ѧ   ����   �ܷ�     \n";//����Ŀδָ����Ŀ�����������ſ�Ŀ
}

//��ӡѧ�����˳ɼ�����
void show_stu_scores(struct stu_scores* ps, struct the_class* ps1)
{
	if (check_emt(ps1))/*��������Ƿ�Ϊ�պ���*/
		return;
	for (int i = 0; i < ps1->real_num; i++)
	{
		if (ps1->list[i]->stu_sum == -1)/*���ѧ���ɼ��ִܷ��������ĳЩ����ʹ��ǰ��*/
		{
			cout << "����ִ����Ŀ3������ÿ��ѧ�����ֺܷ�ƽ����" << endl;
			return;
		}
	}
	int j;

	/*��ӡѧ���ɼ�*/
	cout << setiosflags(ios::left) << setw(7) << ps->rank;
	cout << setiosflags(ios::left) << setw(17) << ps->stu_num;
	cout << setiosflags(ios::left) << setw(9) << ps->stu_name;
	for (j = 0; j < 6; j++)
	{
		if (ps->stu_score_list[j] != -1)
			cout << setiosflags(ios::left) << setw(7) << ps->stu_score_list[j];
		else
		{
			cout << setiosflags(ios::left) << setw(7) << "��";
		}
	}
	cout << setiosflags(ios::left) << setw(5) << ps->stu_sum;
	cout << endl;
}

// ��ӡ�༶����ѧ���ɼ��ĺ���
void show_all_stu_scores(struct the_class* ps)
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	int i, j, mark = 0;
	if (Sort_des_score(ps, mark))/*ʹ����Ŀ4�������ͬʱ�õ�ѧ������*/
		return;
	show_menu();
	for (i = 0; i < ps->real_num; i++)/*��ӡÿ��ѧ���ɼ�*/
	{
		show_stu_scores(ps->list[i], ps);
	}
}

//��ӡ�༶ÿ�ſ�Ŀ���ܺ���
void show_class_scores(struct the_class* ps)
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	int i, j;
	/*��ӡ���Ƴɼ�����*/
	cout << "��Ŀ   ����   ��ѧ   Ӣ��   ����   ��ѧ   ����   \n";
	cout << "�ܷ�   ";
	for (i = 0; i < 6; i++)
	{
		cout << setiosflags(ios::left) << setw(7) << ps->class_sum_list[i];
	}
	cout << endl;
	cout << "ƽ���� ";
	for (i = 0; i < 6; i++)
	{
		cout << setiosflags(ios::left) << setw(7) << ps->class_average_list[i];
	}
	cout << endl;
}

void Record_score(struct the_class* ps)//¼��ѧ���ɼ�����
{
	if (ps->real_num == ps->class_num)/*���ʵ��ѧ�������Ƿ���������������ݿռ�*/
		List_Expansion(ps);
	cout << "����ѧ��ѧ�ţ�";
	cin >> ps->list[ps->real_num]->stu_num;
	cout << "����ѧ��������";
	cin >> ps->list[ps->real_num]->stu_name;
	cout << "����ѧ���ɼ�����ѧ��δ�μ�ĳ���������-1��\n";
	cout << "�������ĳɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[0];
	cout << "������ѧ�ɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[1];
	cout << "����Ӣ��ɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[2];
	cout << "��������ɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[3];
	cout << "���뻯ѧ�ɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[4];
	cout << "��������ɼ�\n";
	cin >> ps->list[ps->real_num]->stu_score_list[5];
	ps->real_num++;
}

void Cal_total_average_score_course(struct the_class* ps, int mark)//����༶ÿ�ſ�Ŀ���ܺ���
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	int sum_list[6] = { 0 }, average_list[6] = { 0 }, test_num = 0;
	
	/*��ʼ���༶�ɼ��ܷ�����*/
	for (int i = 0; i < 6; i++)
		ps->class_sum_list[i] = 0;

	for (int i = 0; i < 6; i++)
	{
		test_num = 0;
		for (int j = 0; j < ps->real_num; j++)
		{
			if (ps->list[j]->stu_score_list[i] != -1)
			{
				ps->class_sum_list[i] += ps->list[j]->stu_score_list[i];
				test_num++;
			}
		}
		ps->class_average_list[i] = ps->class_sum_list[i] / test_num;
	}
	if(mark)
		cout << "�������\n";
}

void Cal_total_average_score_stu(struct the_class* ps)//����༶����ѧ���ɼ��ĺ���
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	int i, j, test_num = 0, sum_tmp = 0;;
	
	/*����ѧ�����˳ɼ�����*/
	for (j = 0; j < ps->real_num; j++)
	{
		sum_tmp = 0;
		for (i = 0; i < 6; i++)
		{
			test_num = 0;
			if (ps->list[j]->stu_score_list[i] != -1)
			{
				sum_tmp += ps->list[j]->stu_score_list[i];
				test_num++;
			}
		}
		ps->list[j]->stu_sum = sum_tmp;
		for (i = 0; i < ps->real_num; i++)
			ps->list[i]->stu_average = ps->list[i]->stu_sum / test_num;
	}
	cout << "�������\n";
}

int Sort_des_score(struct the_class* ps, int mark)//ͨ��ѧ���ܷ��ɸߵ���������
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return 0;
	
	struct stu_scores* tmp = NULL;
	int i, j;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*���ѧ���ɼ��ִܷ��������ĳЩ����ʹ��ǰ��*/
		{
			cout << "����ִ����Ŀ3������ÿ��ѧ�����ֺܷ�ƽ����" << endl;
			return 1;
		}
	}
	/*����*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = i; j < ps->real_num; j++)
		{
			if (ps->list[i]->stu_sum < ps->list[j]->stu_sum)
			{
				tmp = ps->list[i];
				ps->list[i] = ps->list[j];
				ps->list[j] = tmp;
			}
		}
	}
	/*¼��ѧ������*/
	for (int i = 0, j = 0; j < ps->real_num; i++, j++)
	{
		ps->list[j]->rank = i + 1;
		if (ps->list[i]->stu_sum == ps->list[i + 1]->stu_sum)
			i--;
	}
	/*��ӡ����ѧ���ɼ�*/
	if (mark)
		show_all_stu_scores(ps);
	return 0;
}

void Sort_asc_score(struct the_class* ps)//ͨ��ѧ���ܷ��ɵ͵���������
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*���ѧ���ɼ��ִܷ��������ĳЩ����ʹ��ǰ��*/
		{
			cout << "����ִ����Ŀ3������ÿ��ѧ�����ֺܷ�ƽ����" << endl;
			return;
		}
	}
	/*����*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = i; j < ps->real_num; j++)
		{
			if (ps->list[i]->stu_sum > ps->list[j]->stu_sum)
			{
				tmp = ps->list[i];
				ps->list[i] = ps->list[j];
				ps->list[j] = tmp;
			}
		}
	}
	/*��ӡ����ѧ���ɼ�����ʹ��all����Ϊ����������*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i],ps);
}

void Sort_asc_num(struct the_class* ps)//ͨ��ѧ��ѧ���ɵ͵���������
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j, k;
	/*����*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = i; j < ps->real_num; j++)
		{
			for (k = 0; ps->list[i]->stu_num[k] != 0; k++)
			{
				if (ps->list[i]->stu_num[k] > ps->list[j]->stu_num[k])
				{
					tmp = ps->list[i];
					ps->list[i] = ps->list[j];
					ps->list[j] = tmp;
					break;
				}
			}
		}
	}
	/*��ӡ����ѧ���ɼ�*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i], ps);
}

void Sort_dic_name(struct the_class* ps)//ͨ��ѧ��������ASCII�����ɵ͵���������
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j, k;
	/*����*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = i; j < ps->real_num; j++)
		{
			for (k = 0; ps->list[i]->stu_name[k] != 0; k++)
			{
				if (ps->list[i]->stu_name[k] > ps->list[j]->stu_name[k])
				{
					tmp = ps->list[i];
					ps->list[i] = ps->list[j];
					ps->list[j] = tmp;
					break;
				}
			}
		}
	}
	/*��ӡ����ѧ���ɼ�*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i], ps);
}

void Sea_num(struct the_class* ps)//ͨ��ѧ��ѧ�Ų���ѧ���ɼ��ĺ���
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	int mark = 0, i, j;
	char sea_num[20] = { 0 };
	/*Ϊ����ʹ������ʹ�ü�������ѧ���ɼ�����ǰֱ��ʹ�øú���������õ�����*/
	Sort_des_score(ps, mark);
	
	cout << "������Ҫ����ѧ����ѧ�ţ�";
	cin >> sea_num;

	/*����ѧ��*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = i; ps->list[i]->stu_num[j] != '\0'; j++)
		{
			if (ps->list[i]->stu_num[j] != sea_num[j])
				break;
		}
		if (ps->list[i]->stu_num[j] == 0 && sea_num[j] == ps->list[i]->stu_num[j])
		{
			show_menu();
			show_stu_scores(ps->list[i], ps);/*��ӡ��ѧ���ɼ�*/
			return;
		}
	}
	cout << "δ���ҵ���ѧ�ŵ�ѧ��\n";
}

void Sea_name(struct the_class* ps)//ͨ��ѧ����������ѧ���ɼ��ĺ���
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	int mark = 0, i, j;
	char sea_name[20] = { 0 };
	/*Ϊ����ʹ������ʹ�ü�������ѧ���ɼ�����ǰֱ��ʹ�øú���������õ�����*/
	Sort_des_score(ps, mark);
	
	cout << "������Ҫ����ѧ����������";
	cin >> sea_name;

	/*����ѧ��*/
	for (i = 0; i < ps->real_num; i++)
	{
		for (j = 0; ps->list[i]->stu_name[j] != 0; j++)
		{
			if (ps->list[i]->stu_name[j] != sea_name[j])
				break;
		}
		if (ps->list[i]->stu_name[j] == 0 && sea_name[j] == ps->list[i]->stu_name[j])
		{
			show_menu();
			show_stu_scores(ps->list[i], ps);/*��ӡ��ѧ���ɼ�*/
			return;
		}
	}
	cout << "δ���ҵ���ѧ�ŵ�ѧ��\n";
}

void Stat_analysis(struct the_class* ps)//����ÿ�ſ�Ŀѧ���ĳɼ������Լ��ܽ�ĺ���
{
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	int i, j;
	const char* courses_list = "������ѧӢ������ѧ����";
	
	for (i = 0; i < 6; i++)
	{
		int rank_list[5] = { 0 }, test_num = 0;
		double rank_aver_list[5] = { 0 };
		for (j = 0; j < ps->real_num; j++)
		{
			if (ps->list[j]->stu_score_list[i] == -1)/*��ѧ��δ���뿼������������ѭ������������*/
				continue;
			if (ps->list[j]->stu_score_list[i] >= 90)
				rank_list[0]++;
			else if (ps->list[j]->stu_score_list[i] < 90 && ps->list[j]->stu_score_list[i] >= 80)
				rank_list[1]++;
			else if (ps->list[j]->stu_score_list[i] < 80 && ps->list[j]->stu_score_list[i] >= 70)
				rank_list[2]++;
			else if (ps->list[j]->stu_score_list[i] < 70 && ps->list[j]->stu_score_list[i] >= 60)
				rank_list[3]++;
			else if (ps->list[j]->stu_score_list[i] < 60)
				rank_list[4]++;
			test_num++;
		}
		for (int k = 0; k < 5; k++)/*������ռ��*/
			rank_aver_list[k] = double(rank_list[k]) / double(test_num);

		/*��ӡ��������*/
		cout << "               ----";
		for (int k = 0; k < 4; k++)
			cout << *(courses_list + k);
		courses_list += 4;
		cout << "----       ";
		cout << endl << "       ����   ����   �е�   ����   ������ " << endl;
		cout << setiosflags(ios::left) << setw(7) << "����   ";
		for (int k = 0; k < 5; k++)
			cout << setiosflags(ios::left) << setw(7) << rank_list[k];
		cout << endl;
		
		cout << setiosflags(ios::left) << setw(7) << "��ռ�� ";
		for (int k = 0; k < 5; k++)
			cout << setiosflags(ios::left) << setw(7) << setiosflags(ios::showpoint) << setprecision(2) << rank_aver_list[k];
		cout << endl << endl;
	}
}

void List_record(struct the_class* ps)//��ӡ��ѧ��������Ϣ�Ͱ༶��Ϣ�ĺ���
{
	int mark = 0;
	if (check_emt(ps))/*��������Ƿ�Ϊ�պ���*/
		return;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*���ѧ���ɼ��ִܷ��������ĳЩ����ʹ��ǰ��*/
		{
			cout << "����ִ����Ŀ3������ÿ��ѧ�����ֺܷ�ƽ����" << endl;
			return;
		}
	}

	/*��ӡ����ѧ���ɼ�*/
	cout << "ѧ�����˳ɼ���\n";
	show_all_stu_scores(ps);
	cout << endl;
	cout << "�༶���Ƴɼ�����\n";

	/*Ϊ����ʹ������ʹ�ü���༶���ݺ���ǰֱ��ʹ�øú���������õ��༶����*/
	Cal_total_average_score_course(ps, mark);

	/*��ӡ�༶����*/
	show_class_scores(ps);
}