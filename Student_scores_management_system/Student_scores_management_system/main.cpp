#include "Function_declaration.h"
//���汾Ϊ��Ŀָ����V5.0�汾�����ڴ�֮�ϼ������ļ������ȡ����
//Ϊȷ��������ȶ��ԣ���ʹ��vs2019���Դ˳���

void menu()/*�˵�����*/
{
	cout << "----------------------------------------------------\n";
	cout << "     ---------ϵͳ��Ŀ�˵�--------\n";
	cout << "��1��¼��ÿ��ѧ����ѧ�š������͸��ƿ��Գɼ�\n";
	cout << "��2������ÿ�ſγ̵��ֺܷ�ƽ����\n";
	cout << "��3������ÿ��ѧ�����ֺܷ�ƽ����\n";
	cout << "��4����ÿ��ѧ�����ܷ��ɸߵ����ų����α�\n";
	cout << "��5����ÿ��ѧ�����ܷ��ɵ͵����ų����α�\n";
	cout << "��6����ѧ����С�����ų��ɼ���\n";
	cout << "��7�����������ֵ�˳���ų��ɼ���\n";
	cout << "��8����ѧ�Ų�ѯѧ���������俼�Գɼ�\n";
	cout << "��9����������ѯѧ���������俼�Գɼ�\n";
	cout << "��10�������㣨90~100�������ã�80~89�����еȣ�70~79��������60~69����������0~59��5����𣬶�ÿ�ſγ̷ֱ�ͳ��ÿ�����������Լ���ռ�İٷֱ�\n";
	cout << "��11�����ÿ��ѧ����ѧ�š����������ƿ��Գɼ����Լ�ÿ�ſγ̵��ֺܷ�ƽ����\n";
	cout << "0.Exit\n";
	cout << "������������ʹ�ö�Ӧ��Ŀ��ϵͳ����ѧ���ɼ�:";
}

int main()
{
	int mark = 1;
	struct the_class Class;/*����༶�����壬�������ݿ�ͷ�ļ�*/
	cout << "��ӭʹ��ѧ������ϵͳ\n";

	if (Initlist(&Class))/*ʹ�ó�ʼ��������ʼ���༶�����壬���õ�����ֵ��ȷ���ɹ����*/
	{
		int input = 0;
		if (Loadlist(&Class))/*ʹ�ü��غ�������ȡ�����ļ��е�ѧ�����ݣ���ͨ������ֵȷ���ɹ����*/
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
				printf("ѡ�����\n");
				break;
			}
		} while (input);
	}

	return 0;
}