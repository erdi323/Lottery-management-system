#ifndef PUNTER_H
#define PUNTER_H
typedef struct punters{
	char name[20];//姓名（要求全局唯一）
	char password[20];//密码
	float balance;//账户余额
	char registTime[50];
	struct punters *next;
}Punters;

void puntersLoginMenu();//彩民登录菜单
void puntersMenu(Punters *s);//彩民菜单

int judgePuntersName(Punters *s);//判断用户名是否重复
void inputPuntersMessage(Punters *s);//输入帐号密码
void addpunters(Punters *s);//添加用户到链表
void registTime(char *len);//调用系统时间
void registerPunters();//注册

Punters* findLast(Punters *s);//查找上一个
void deletePunters(Punters *s);//注销用户

void insert(Punters *a,Punters *b);//交换
void bubbPuntersForbalance();//排序通过余额
void bubbPuntersForRegistTime();//排序通过注册时间

void displayAPunters(Punters *s);//显示指定彩民信息
void displayAllPunters();//显示所有彩民信息
void displayPuntersAllBuyLotter(Punters *s);//显示彩民的购买记录


Punters* findPunters(char *name);//查找用户
Punters* PuntersLongin();//彩民登录


void topupBalance(Punters *s);//充值余额
void changePassword(Punters *s);//修改密码

void saveAllPunters();//保存用户到硬盘
void readPuntersFromFile();//读取用户
#endif
