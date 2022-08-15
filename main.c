#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"admin.h"
#include"punters.h"
#include"lottely.h"

int agde=0;

void mainMenu();

int main(){
	int choose;
	char as;
	readPuntersFromFile();//读取用户
	readBuyLotterFromFile();//读取所有彩票
	readLotteryFromFile();//读取彩票信息
	endLottery();
	do{
		mainMenu();
		printf("输入你的选择：");
		scanf("%d",&choose);
		switch(choose){
					case 1:
						as=adminLogin();
						if(as==1){
							notaryMenu();
						}else{
							adminMenu();
						}
						break;
					case 2:
							puntersLoginMenu();
						break;
					default:
							if (agde>0)
							{
								printf("数据已修改，是否保存\n");
								printf("输入你的选择(Y/N)：");
								getchar();
								scanf("%c",&as);
								if (as=='Y'||as=='y')
								{
									saveAllBuyLotter();
									saveAllLottery();
									saveAllPunters();
									printf("数据已保存\n");
								}
							}
						
						return 0;
		}
	}while(1);
  return 0;
}
void mainMenu(){//主菜单
	printf("====================================\n");
	printf("=             欢迎进入             =\n");
	printf("=           福利彩票系统           =\n");
	printf("====================================\n");
	printf("=   彩票规则：                     =\n");
	printf("=           红球1-33选5            =\n");
	printf("=           蓝球1-16选1            =\n");
	printf("====================================\n\n");

	printf("\t1.公证员/管理员登录\n");
	printf("\t2.彩民登录/注册\n");
}
