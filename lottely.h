#ifndef LOTTERY_H
#define LOTTERY_H
typedef struct buyLotter{//彩票信息
	int issue;//发布期号；
	int lotterID;//单张彩票唯一标识ID；
	int chooseNum[7];//彩票上选中的号码；(开奖号)
	char punter[20];//购买者帐号；
	int buyNum; //已购买某一彩票号的注数（单张彩票不能超过5注）；倍数
	char state[10];//中奖状态；
	float bonus;//中奖金额
	char buyTime[50];//购买时间 年，月，日，时，分
	struct buyLotter *next;//下一个链表
}BuyLotter;

typedef struct lottery{//彩票总体信息
	int issue;//发布期号
	float price;//彩票单价
	char state[10];//开奖状态；
	int winNum[7];//中奖号码；
	int buyAmount;//本期售出总数；
	float theBonus;//本期奖池总额
	struct lottery *next;//下一个链表
}Lottery;

void addBuyLotter(BuyLotter *w);//添加彩票链表
void maopao(int a[]);//排序
void inputLottely();//购买彩票

void displayALottery(BuyLotter *w);//显示单张彩票信息
void displayNowAllBuyLotter();//显示当期所有彩票
void displayAllLottery();//显示所有彩票信息
void displaAllLotteries();//显示已开奖彩票总体信息
void displayNowLotteries();//显示当期彩票总体信息

void addLotteries(Lottery *x);//添加彩票总体信息到链表
void lotteries();//公布彩票
void BuyLotterWhetherWin(int a[]);//判断是否中奖
void winNumRand(int *a);//随机生成
int redNum(BuyLotter *temp,int a[]);//红球相同的个数
int blueNum(BuyLotter *temp,int a[]);//蓝球相同的个数
void runALottery();//开奖

void saveAllBuyLotter();//保存所有彩票到硬盘
void readBuyLotterFromFile();//读取所有彩票
void saveAllLottery();//保存彩票信息到硬盘
void readLotteryFromFile();//读取彩票信息
void endLottery();//找到最后的彩票信息

#endif
