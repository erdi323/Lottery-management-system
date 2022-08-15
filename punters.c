#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"admin.h"
#include"punters.h"
#include"lottely.h"

extern int agde;
Punters *head=NULL;
Punters	*current=NULL;

void saveAllPunters(){//保存用户到硬盘
	FILE *fp=fopen("Punters.bat","wb");
	Punters *temp=head;
	while(temp!=NULL){
		fwrite(temp,sizeof(Punters),1,fp);
		temp=temp->next;
	}
	fclose(fp);
}
void readPuntersFromFile(){//读取用户
	FILE *fp=fopen("Punters.bat","rb");//文件不存在，返回NULL;
	int len=0;
	if(fp==NULL){
		return;
	}
	Punters *temp=malloc(sizeof(Punters));
	len=fread(temp,sizeof(Punters),1,fp);
	temp->next=NULL;
	while(len>0){
		//写入链表
		addpunters(temp);
		temp=malloc(sizeof(Punters));
		len=fread(temp,sizeof(Punters),1,fp);
		temp->next=NULL;
	}
	fclose(fp);
	free(temp);
}
void displayAPunters(Punters *s){//显示指定彩民信息
	printf("%s\t%0.2f\t%s\n",s->name,s->balance,s->registTime);
}
void displayAllPunters(){//显示所有彩民信息
	Punters *temp=head;
	if(head==NULL){
		printf("当前没有彩民信息存在！\n");
		return;
	}
	while(temp!=NULL){
		displayAPunters(temp);
		temp=temp->next;
	}
}

int judgePuntersName(Punters *s){//判断用户名是否重复
	Punters *temp=head;
	while(temp!=NULL){
		if(strcmp(temp->name,s->name)==0){
			return 0;
		}
		temp=temp->next;
	}
	return 1;
}
void inputPuntersMessage(Punters *s){//输入帐号密码
	int aged;
	char cn;
	do{
		for(int i=0;i<1;i++){
			getchar();
			printf("输入姓名：");
			scanf("%s",s->name);
			getchar();
			printf("输入密码：");
			scanf("%s",s->password);
			aged=judgePuntersName(s);
			if(aged==0){
				i--;
				printf("用户名重复，请重新输入！！！\n");
			}
		}
		printf("用户名:%s，密码:%s\n确定已此内容注册吗？(Y/N)\n",s->name,s->password);
		getchar();
		scanf("%c",&cn);
		if (cn=='y'||cn=='Y'){	
			return;
		}
		printf("请重新输入用户名和密码\n");
	}while(1);
}
void addpunters(Punters *s){//添加用户到链表
	if(head==NULL){//第一次
		head=s;
		current=s;
	}else{//之后
		current->next=s;
		current=s;
	}
}
void registTime(char *len){//调用系统时间
	time_t timp;
	time(&timp);
	struct tm *p;
	p=gmtime(&timp);
	snprintf(len,50,"%d年%d月%d日%d时%d分%d秒",
		1900+p->tm_year,1+p->tm_mon,p->tm_mday,
		8+p->tm_hour,p->tm_min,p->tm_sec);
}
void registerPunters(){//注册
	Punters *s=malloc(sizeof(Punters));
	s->next=NULL;
	s->balance=0;
	//注册时间
	char len[50]={0};
	registTime(len);//调用系统时间
	strcpy(s->registTime,len);
	agde++;
	inputPuntersMessage(s);
	addpunters(s);
}
Punters* PuntersLongin(){//彩民登录
	Punters *temp=head;
	Punters *t=NULL;
	char name[20];
	char password[20];
	int cnn=0;
	do{
		getchar();
		printf("输入姓名：");
		scanf("%s",name);
		getchar();
		printf("输入密码：");
		scanf("%s",password);
		while(temp!=NULL){
			if(strcmp(temp->name,name)==0){
				t=temp;
				break;
			}
			temp=temp->next;
		}
		if(t==NULL){
			printf("该用户未注册\n");
			return NULL;
		}else{
			if(strcmp(t->password,password)==0){
				return t;
			}
		}
		cnn++;
		if(cnn>=3){
			printf("密码输入错误三次！！退出系统\n");
			exit(0);
		}
		printf("密码错误！！请重新输入\n");
	}while(1);
}
Punters* findPunters(char *name){//查找用户
	Punters *temp=head;
	Punters *t=NULL;
	if (head==NULL){
		printf("还未有用户注册\n");
		return 0;
	}
	while(temp!=NULL){
			if(strcmp(temp->name,name)==0){
				t=temp;
				return t;
			}
			temp=temp->next;
	}
	if(t==NULL){
		printf("没有该用户\n");
		return NULL;
	}
}
void topupBalance(Punters *s){//充值余额
	float moeny;
	if(s!=NULL){
		do{
			printf("输入充值余额：");
			scanf("%f",&moeny);
			s->balance+=moeny;
			if (s->balance>0){
				agde++;
				printf("充值成功！！\n");
				return;
			}
			printf("充值金额错误\n");
		}while(1);
	}
}
void changePassword(Punters *s){//修改密码
	char oldPassword[20];
	char newPassword[20];
	char as;
	int cnn;
	Punters *temp=head;
	while(temp!=NULL){
		if(strcmp(temp->name,s->name)==0){
			do{
				getchar();
				printf("输入原密码：");
				scanf("%s",oldPassword);
				if(strcmp(s->password,oldPassword)!=0){
					cnn++;
					if(cnn>=3){
						printf("密码输入错误三次！！退出系统\n");
						exit(0);
					}
					printf("原密码错误！！请重新输入\n");
				}else{
					break;
				}
			}while(1);	
			do{
				getchar();
				printf("输入新密码：");
				scanf("%s",newPassword);
				if(strcmp(newPassword,oldPassword)==0){
					printf("新密码不能和原密码相同！！请重新输入\n");
				}else{
					break;
				}
			}while(1);
			getchar();
			printf("修改密码后无法还原\n是否修改密码？（Y/N）\n");
			scanf("%c",&as);
			if(as=='y'||as=='Y'){
				strcpy(s->password,newPassword);
				agde++;
				printf("密码修改成功\n");
				return;
			}else{
				printf("是否退出修改密码？（Y/N）\n");
				getchar();
				scanf("%c",&as);
				if(as=='y'||as=='Y'){
					return;
				}
			}
		}
	}
}
Punters* findLast(Punters *s){//查找上一个
	Punters *temp=head;
	if(head!=s){
		while(temp!=NULL){
			if (temp->next!=NULL){
				if(strcmp(temp->next->name,s->name)==0){
						return temp;
				}
				temp=temp->next;		
			}
		}
	}
	return NULL;
}
void deletePunters(Punters *s){//注销用户
	char as;
	Punters *last=findLast(s);
	printf("离开后你的数据将全部消失，确定要离开我了吗？\n");
	printf("按Y确认注销，其他键取消\n");
	getchar();
	scanf("%c",&as);				
	if(as=='y'||as=='Y'){
		agde++;
		if(last==NULL){//第一个
			head=head->next;
		}else{
			last->next=s->next;			
		}
		if(current==s){//最后一个	
			current=last;
		}
		printf("您的用户已删除成功，欢迎下次光临！！\n");
		free(s);
	}
	printf("退出注销\n");
}
void insert(Punters *a,Punters *s){//交换
	Punters *lasta=findLast(a);
	Punters *lasts=findLast(s);

	lasts->next=s->next;
	s->next=lasta->next;
	lasta->next=s;
}
void bubbPuntersForbalance(){//排序通过余额
	Punters *temp=head;
	Punters *s=head->next;
	if(s==NULL||head==NULL){//没有参数或一个参数
		return;
	}
	agde++;
	for(;s!=NULL;s=s->next){
		for(temp=head;temp!=s;temp=temp->next){
			if(temp==head){
				if(temp->balance < s->balance){
					Punters *lasts=findLast(s);
					lasts->next=s->next;
					s->next=head;
					head=s;
					break;
				}
			}
			if(temp->balance < s->balance){
				insert(temp,s);
				break;	
			}
		}
		if (temp->next==NULL)
		{
			current=temp;
		}
	}
}
void bubbPuntersForRegistTime(){//排序通过注册时间
	Punters *temp=head;
	Punters *s=head->next;
	if(s==NULL){//只有一个参数
		return;
	}
	agde++;
	for(;s!=NULL;s=s->next){
		for(temp=head;temp!=s;temp=temp->next){
			if(temp==head){
				if(strcmp(temp->registTime,s->registTime)>0){
					Punters *last=findLast(s);		
					last->next=s->next;
					s->next=head;
					head=s;
					break;
				}
			}
			if(strcmp(temp->registTime,s->registTime)>0){
				insert(temp,s);
				break;
			}
		}
		if (temp->next==NULL)
		{
			current=temp;
		}
	}
}
void puntersLoginMenu(){//彩民登录菜单
	int choose;
	Punters *user=NULL;
	do{	
		printf("\t1.注册\n");
		printf("\t2.登录\n");
		printf("输入你的选择：");
		getchar();
		scanf("%d",&choose);
		switch(choose){
					case 1:
						registerPunters();
						break;
					case 2:						
						user=PuntersLongin();
						if(user!=NULL){
							puntersMenu(user);
						}
						break;
					default:
						return;
		}
	}while(1);
}
void puntersMenu(Punters *s){//彩民菜单
	int choose;
	do{	
		printf("\t1.我的信息\n");
		printf("\t2.购买彩票\n");
		printf("\t3.购买记录\n");
		printf("\t4.充值余额\n");
		printf("\t5.修改密码\n");
		printf("\t6.注销账户\n");
		printf("输入你的选择：");
		scanf("%d",&choose);
		switch(choose){
					case 1:
						printf("用户名\t余额\t注册时间\n");
						displayAPunters(s);
						break;
					case 2:
						inputLottely(s);
						break;
					case 3:
						displayPuntersAllBuyLotter(s);
						break;
					case 4:
						printf("非常抱歉;暂不支持用户自行充值！\n请到站点进行充值!\n");
						break;
					case 5:
						changePassword(s);
						break;
					case 6:
						deletePunters(s);
						return;
					default:
						saveAllBuyLotter();
						saveAllPunters();
						return;
		}
	}while(1);
}
