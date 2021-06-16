#include "Function_declaration.h"
//本版本为题目指定的V5.0版本，并在此之上加入了文件储存读取功能
//为确保程序的稳定性，请使用vs2019调试此程序

void menu()/*菜单函数*/
{
	cout << "----------------------------------------------------\n";
	cout << "     ---------系统项目菜单--------\n";
	cout << "（1）录入每个学生的学号、姓名和各科考试成绩\n";
	cout << "（2）计算每门课程的总分和平均分\n";
	cout << "（3）计算每个学生的总分和平均分\n";
	cout << "（4）按每个学生的总分由高到低排出名次表\n";
	cout << "（5）按每个学生的总分由低到高排出名次表\n";
	cout << "（6）按学号由小到大排出成绩表\n";
	cout << "（7）按姓名的字典顺序排出成绩表\n";
	cout << "（8）按学号查询学生排名及其考试成绩\n";
	cout << "（9）按姓名查询学生排名及其考试成绩\n";
	cout << "（10）按优秀（90~100）、良好（80~89）、中等（70~79）、及格（60~69）、不及格（0~59）5个类别，对每门课程分别统计每个类别的人数以及所占的百分比\n";
	cout << "（11）输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分\n";
	cout << "0.Exit\n";
	cout << "请输入数字来使用对应项目来系统管理学生成绩:";
}

int main()
{
	int mark = 1;
	struct the_class Class;/*定义班级构造体，具体内容看头文件*/
	cout << "欢迎使用学生管理系统\n";

	if (Initlist(&Class))/*使用初始化函数初始化班级构造体，并得到返回值来确定成功与否*/
	{
		int input = 0;
		if (Loadlist(&Class))/*使用加载函数来读取储存文件中的学生数据，并通过返回值确定成功与否*/
			return 0;

		do
		{
			menu();
			cin >> input;
			cout << "--------------------------------\n";
			switch (input)
			{
			case EXIT:
				Savedata(&Class);
				break;
			case RECORD:
				Record_score(&Class);
				break;
			case CAL_COURSE:
				Cal_total_average_score_course(&Class, mark);
				break;
			case CAL_STU:
				Cal_total_average_score_stu(&Class);
				break;
			case SORT_DES_SCORE:
				Sort_des_score(&Class, mark);
				break;
			case SORT_ASC_SCORE:
				Sort_asc_score(&Class);
				break;
			case SORT_ASC_NUM:
				Sort_asc_num(&Class);
				break;
			case SORT_DIC_NAME:
				Sort_dic_name(&Class);
				break;
			case SEA_NUM:
				Sea_num(&Class);
				break;
			case SEA_NAME:
				Sea_name(&Class);
				break;
			case STA_ANA:
				Stat_analysis(&Class);
				break;
			case LIST_RECORD:
				List_record(&Class);
				break;
			default:
				printf("选择错误\n");
				break;
			}
		} while (input);
	}

	return 0;
}