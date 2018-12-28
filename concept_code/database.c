
#include"sinon_database_fuction.h"
#pragma warning(disable:4996)

int main()
{
	//执行登陆操作
	int a;
	while (1)
	{
		a = login();
		if (a == 1)
			break;
		else if (a == 0)
			return 0;
	}
	//检测数据文件
	detect();
	//用于存放控制指令
	int control = 0, result = 0;
	//死循环确保程序运行
	while (1)
	{
		//登陆后菜单界面
		control = menu();
		switch (control)
		{
		default:
			puts("无效的输入！");
			break;
		case 1:
			result = search();
			break;
		case 2:
			result = edit();
			break;
		case 3:
			result = del();
			break;
		case 4:
			result = add();
			break;
		case 5:
			result = sort();
			break;
		case 6:
			puts("感谢使用！");
			Sleep(1000);
			return 0;
		}
	}
}
