#include "Function_declaration.h"

int Initlist(struct the_class* ps)//初始化函数
{
	int Class_num, i = 0;
	cout << "请设置班级人数:";
	cin >> Class_num;

	struct stu_scores** list_tmp = new struct stu_scores* [Class_num];/*使用设置好的班级初始人数来开辟动态数组用于储存学生个人信息构造体*/

	/*为每个学生个人信息构造体数组元素分配空间*/
	for (i = 0; i < Class_num; i++)
	{
		*(list_tmp + i) = new struct stu_scores;
	}

	/*初始化班级构造体*/
	ps->class_num = Class_num;
	ps->list = list_tmp;
	ps->class_average_list[0] = -1;
	ps->class_sum_list[0] = -1;

	/*检测文件是否存在，若否则创建文件*/
	ifstream file1;
	file1.open("data.txt", ifstream::in);
	if (!file1)
	{
		cout << "未检测到存储文件存在\n";
		ofstream file2;
		file2.open("data.txt", ifstream::out);
		if (file2.is_open())
		{
			cout << "创建新文件成功\n";
			file2.close();
			return 1;
		}
		else
		{
			cout << "创建新文件失败\n";
			return 0;
		}
	}
	return 1;
}

int Loadlist(struct the_class* ps)//加载函数
{
	ifstream file1;
	file1.open("data.txt");

	if (!file1)/*检测文件是否打开成功*/
	{
		cout << "ERROR Program Closed\n";
		cout << "打开文件失败\n";
		return 1;
	}
	if (file1.peek() == EOF)/*检测文件是否为空*/
		return 0;
	for (int i = 0;!file1.eof();i++)/*检测是否文件读取到尾的同时读取文件数据*/
	{
		if (i>=ps->class_num)/*检测是否会实际班级人数溢出*/
		{
			cout << "ERROR Program Closed\n";
			cout << "请输入一个不小于班级实际学生人数和已经储存学生人数的数字\n";
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

//空间扩容函数
void List_Expansion(struct the_class* ps)
{
	cout << "初始设置的人数小于实际人数，将扩容储存空间\n";
	int i;

	/*删除已开辟的空间*/
	for (i = 0; i < ps->class_num; i++)
		delete(ps->list[i]);

	/*重新开辟一个更大空间*/
	struct stu_scores** list_tmp = new struct stu_scores* [++(ps->class_num)];

	/*初始化班级构造体*/
	for (i = 0; i < ps->class_num+1; i++)
	{
		*(list_tmp + i) = new struct stu_scores;
	}
	ps->list = list_tmp;
	ps->class_average_list[0] = -1;
	ps->class_sum_list[0] = -1;
	ps->real_num = 0;

	/*重新读取文件数据*/
	Loadlist(ps);
	cout << "扩容成功\n";
}

//检查是否存在学生成绩的函数，作为某些函数使用前提
int check_emt(struct the_class* ps)
{
	if (ps->real_num == 0)
	{
		cout << "系统未检测到学生成绩，请先录入学生成绩\n";
		return 1;
	}
	else
		return 0;
}

void Savedata(struct the_class* ps)//数据保存函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	fstream f;
	f.open("data.txt");
	if (!f)/*检测文件打开成功与否*/
	{
		cout << "打开文件失败\n";
		return;
	}
	for (int i = 0; i < ps->real_num; i++)/*将程序数据保存至文件*/
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
	cout << "程序退出\n";
}

//打印菜单函数
void show_menu()
{
	cout << "名次   学号             姓名     语文   数学   英语   物理   化学   生物   总分     \n";//因题目未指明科目，故自设六门科目
}

//打印学生个人成绩函数
void show_stu_scores(struct stu_scores* ps, struct the_class* ps1)
{
	if (check_emt(ps1))/*检测数据是否为空函数*/
		return;
	for (int i = 0; i < ps1->real_num; i++)
	{
		if (ps1->list[i]->stu_sum == -1)/*检测学生成绩总分存在与否，是某些函数使用前提*/
		{
			cout << "请先执行项目3来计算每个学生的总分和平均分" << endl;
			return;
		}
	}
	int j;

	/*打印学生成绩*/
	cout << setiosflags(ios::left) << setw(7) << ps->rank;
	cout << setiosflags(ios::left) << setw(17) << ps->stu_num;
	cout << setiosflags(ios::left) << setw(9) << ps->stu_name;
	for (j = 0; j < 6; j++)
	{
		if (ps->stu_score_list[j] != -1)
			cout << setiosflags(ios::left) << setw(7) << ps->stu_score_list[j];
		else
		{
			cout << setiosflags(ios::left) << setw(7) << "无";
		}
	}
	cout << setiosflags(ios::left) << setw(5) << ps->stu_sum;
	cout << endl;
}

// 打印班级所有学生成绩的函数
void show_all_stu_scores(struct the_class* ps)
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	int i, j, mark = 0;
	if (Sort_des_score(ps, mark))/*使用项目4来排序的同时得到学生名次*/
		return;
	show_menu();
	for (i = 0; i < ps->real_num; i++)/*打印每个学生成绩*/
	{
		show_stu_scores(ps->list[i], ps);
	}
}

//打印班级每门科目汇总函数
void show_class_scores(struct the_class* ps)
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	int i, j;
	/*打印各科成绩数据*/
	cout << "科目   语文   数学   英语   物理   化学   生物   \n";
	cout << "总分   ";
	for (i = 0; i < 6; i++)
	{
		cout << setiosflags(ios::left) << setw(7) << ps->class_sum_list[i];
	}
	cout << endl;
	cout << "平均分 ";
	for (i = 0; i < 6; i++)
	{
		cout << setiosflags(ios::left) << setw(7) << ps->class_average_list[i];
	}
	cout << endl;
}

void Record_score(struct the_class* ps)//录入学生成绩函数
{
	if (ps->real_num == ps->class_num)/*检测实际学生人数是否溢出，若是则扩容空间*/
		List_Expansion(ps);
	cout << "输入学生学号：";
	cin >> ps->list[ps->real_num]->stu_num;
	cout << "输入学生姓名：";
	cin >> ps->list[ps->real_num]->stu_name;
	cout << "输入学生成绩（若学生未参加某项考试请输入-1）\n";
	cout << "输入语文成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[0];
	cout << "输入数学成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[1];
	cout << "输入英语成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[2];
	cout << "输入物理成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[3];
	cout << "输入化学成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[4];
	cout << "输入生物成绩\n";
	cin >> ps->list[ps->real_num]->stu_score_list[5];
	ps->real_num++;
}

void Cal_total_average_score_course(struct the_class* ps, int mark)//计算班级每门科目汇总函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	int sum_list[6] = { 0 }, average_list[6] = { 0 }, test_num = 0;
	
	/*初始化班级成绩总分数组*/
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
		cout << "计算完成\n";
}

void Cal_total_average_score_stu(struct the_class* ps)//计算班级所有学生成绩的函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	int i, j, test_num = 0, sum_tmp = 0;;
	
	/*计算学生个人成绩汇总*/
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
	cout << "计算完成\n";
}

int Sort_des_score(struct the_class* ps, int mark)//通过学生总分由高到低排序函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return 0;
	
	struct stu_scores* tmp = NULL;
	int i, j;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*检测学生成绩总分存在与否，是某些函数使用前提*/
		{
			cout << "请先执行项目3来计算每个学生的总分和平均分" << endl;
			return 1;
		}
	}
	/*排序*/
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
	/*录入学生名次*/
	for (int i = 0, j = 0; j < ps->real_num; i++, j++)
	{
		ps->list[j]->rank = i + 1;
		if (ps->list[i]->stu_sum == ps->list[i + 1]->stu_sum)
			i--;
	}
	/*打印所有学生成绩*/
	if (mark)
		show_all_stu_scores(ps);
	return 0;
}

void Sort_asc_score(struct the_class* ps)//通过学生总分由低到高排序函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*检测学生成绩总分存在与否，是某些函数使用前提*/
		{
			cout << "请先执行项目3来计算每个学生的总分和平均分" << endl;
			return;
		}
	}
	/*排序*/
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
	/*打印所有学生成绩，不使用all函数为避免重排序*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i],ps);
}

void Sort_asc_num(struct the_class* ps)//通过学生学号由低到高排序函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j, k;
	/*排序*/
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
	/*打印所有学生成绩*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i], ps);
}

void Sort_dic_name(struct the_class* ps)//通过学生名字在ASCII码中由低到高排序函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	
	struct stu_scores* tmp = NULL;
	int i, j, k;
	/*排序*/
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
	/*打印所有学生成绩*/
	for (i = 0; i < ps->real_num; i++)
		show_stu_scores(ps->list[i], ps);
}

void Sea_num(struct the_class* ps)//通过学生学号查找学生成绩的函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	int mark = 0, i, j;
	char sea_num[20] = { 0 };
	/*为避免使用者在使用计算所有学生成绩函数前直接使用该函数，排序得到名次*/
	Sort_des_score(ps, mark);
	
	cout << "请输入要查找学生的学号：";
	cin >> sea_num;

	/*查找学生*/
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
			show_stu_scores(ps->list[i], ps);/*打印该学生成绩*/
			return;
		}
	}
	cout << "未查找到该学号的学生\n";
}

void Sea_name(struct the_class* ps)//通过学生姓名查找学生成绩的函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	int mark = 0, i, j;
	char sea_name[20] = { 0 };
	/*为避免使用者在使用计算所有学生成绩函数前直接使用该函数，排序得到名次*/
	Sort_des_score(ps, mark);
	
	cout << "请输入要查找学生的姓名：";
	cin >> sea_name;

	/*查找学生*/
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
			show_stu_scores(ps->list[i], ps);/*打印该学生成绩*/
			return;
		}
	}
	cout << "未查找到该学号的学生\n";
}

void Stat_analysis(struct the_class* ps)//分析每门科目学生的成绩评价以及总结的函数
{
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	int i, j;
	const char* courses_list = "语文数学英语物理化学生物";
	
	for (i = 0; i < 6; i++)
	{
		int rank_list[5] = { 0 }, test_num = 0;
		double rank_aver_list[5] = { 0 };
		for (j = 0; j < ps->real_num; j++)
		{
			if (ps->list[j]->stu_score_list[i] == -1)/*若学生未参与考试则跳过本次循环，不作评价*/
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
		for (int k = 0; k < 5; k++)/*计算所占比*/
			rank_aver_list[k] = double(rank_list[k]) / double(test_num);

		/*打印计算数据*/
		cout << "               ----";
		for (int k = 0; k < 4; k++)
			cout << *(courses_list + k);
		courses_list += 4;
		cout << "----       ";
		cout << endl << "       优秀   良好   中等   及格   不及格 " << endl;
		cout << setiosflags(ios::left) << setw(7) << "人数   ";
		for (int k = 0; k < 5; k++)
			cout << setiosflags(ios::left) << setw(7) << rank_list[k];
		cout << endl;
		
		cout << setiosflags(ios::left) << setw(7) << "所占比 ";
		for (int k = 0; k < 5; k++)
			cout << setiosflags(ios::left) << setw(7) << setiosflags(ios::showpoint) << setprecision(2) << rank_aver_list[k];
		cout << endl << endl;
	}
}

void List_record(struct the_class* ps)//打印出学生个人信息和班级信息的函数
{
	int mark = 0;
	if (check_emt(ps))/*检测数据是否为空函数*/
		return;
	for (int i = 0; i < ps->real_num; i++)
	{
		if (ps->list[i]->stu_sum == -1)/*检测学生成绩总分存在与否，是某些函数使用前提*/
		{
			cout << "请先执行项目3来计算每个学生的总分和平均分" << endl;
			return;
		}
	}

	/*打印所有学生成绩*/
	cout << "学生个人成绩表\n";
	show_all_stu_scores(ps);
	cout << endl;
	cout << "班级各科成绩汇总\n";

	/*为避免使用者在使用计算班级数据函数前直接使用该函数，计算得到班级数据*/
	Cal_total_average_score_course(ps, mark);

	/*打印班级数据*/
	show_class_scores(ps);
}