#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"admin.h"
#include"punters.h"
#include"lottely.h"

Admin admin[2]={{"erdi","123"},{"admin","123"}};//公证员帐号 和 管理员帐号

int adminLogin(){
	char username[100];
	char password[20];
	int cnt=0;
	do{
		printf("用户名：");
		scanf("%s",username);
		printf("密码：");
		scanf("%s",password);
		//判断
		if(strcmp(admin[0].name,username)==0 && strcmp(admin[0].password,password)==0){
			printf("公证员登录成功！\n");
			return 1;
		}else if(strcmp(admin[1].name,username)==0 && strcmp(admin[1].password,password)==0){
			printf("管理员登录成功！\n");
			return 0;
		}else{
			cnt++;
			if(cnt==3){
				printf("输入三次错误，系统退出!\n");
				exit(0);
			}
			printf("用户名与密码不正确\n你还有%d次机会\n",3-cnt);
		}
	}while(1);
}
void adminMenu(){
	int choose;
	char name[20];
	Punters *s=NULL;
	do{	
		printf("\t1.发行彩票\n");
		printf("\t2.查询彩民信息\n");
		printf("\t3.按注册时间显示彩民信息\n");
		printf("\t4.按余额显示彩民信息\n");
		printf("\t5.为用户充值\n");
		printf("\t6.显示当前彩票的总体信息\n");
		printf("\t7.显示已开奖的彩票的总体信息\n");
		printf("\t8.显示当期已出售彩票\n");
		printf("\t9.显示全部已出售彩票\n");
		printf("输入你的选择：");
		scanf("%d",&choose);
		switch(choose){
					case 1:						
						lotteries();//发行彩票
						break;
					case 2:
						getchar();
						printf("输入姓名：");
						scanf("%s",name);
						s=findPunters(name);//查找用户
						printf("用户名\t余额\t注册时间\n");
						displayAPunters(s);//显示该用户
						break;
					case 3:
						bubbPuntersForRegistTime();//排序通过注册时间
						printf("用户名\t余额\t注册时间\n");
						displayAllPunters();//显示所有用户
						break;
					case 4:
						bubbPuntersForbalance();//排序通过余额
						printf("用户名\t余额\t注册时间\n");
						displayAllPunters();//显示所有用户
						break;
					case 5:
						getchar();
						printf("输入姓名：");
						scanf("%s",name);
						s=findPunters(name);//查找用户
						topupBalance(s);//为用户充值
						break;
					case 6:
						displayNowLotteries();//显示当期彩票总体信息
					case 7:
						displaAllLotteries();//彩票总体信息
						break;
					case 8:
						displayNowAllBuyLotter();//显示当期所有彩票
						break;
					case 9:
						displayAllLottery();//显示所有彩票信息
						break;
					default:
						return;
		}
	}while(1);
}
void notaryMenu(){
	int choose;
	do{	
		printf("\t1.开奖\n");
		printf("\t2.查询彩票信息\n");
		scanf("%d",&choose);
		switch(choose){
					case 1:
						runALottery();
						break;
					case 2:
						displaAllLotteries();//彩票总体信息
						break;
					default:
						saveAllLottery();//保存彩票总体信息
						return;
		}
	}while(1);
}

