#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"lottely.h"
#include"punters.h"
#include"admin.h"

extern int agde;
float theBonus=500000.00;//奖池
int issue=0;//期号
int lotterID=0;//彩票id
BuyLotter *frist=NULL;//彩票链
BuyLotter *trail=NULL;
Lottery	*top=NULL;//彩票信息链
Lottery	*end=NULL;

void addBuyLotter(BuyLotter *w){//添加彩票链表
	if(frist==NULL){
		frist=w;
		trail=w;
	}else{
		trail->next=w;
		trail=w;
	}	
}
void maopao(int a[]){//排序
	for(int i=0;i<7-2;i++){
		for(int j=7-2;j>i;j--){
			if(a[j] < a[i]){
				int t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
}
void inputLottely(Punters *s){//购买彩票
	if (issue<1){
		printf("彩票未发布\n");
		return;
	}
	int a[7];
	char cc[]="未开奖";
	BuyLotter *w=malloc(sizeof(BuyLotter));
	w->next=NULL;
	w->issue=issue;//期号
	w->lotterID=++lotterID;//彩票id
	strcpy(w->punter,s->name);//彩票归属人
	strcpy(w->state,cc);//开奖状态
	w->bonus=0;//未开奖，中奖金额暂定为0
	printf("期号：%d 单价：￥2/注 彩票id：%d\n",w->issue,w->lotterID);
	for(int i=0;i<6;i++){//选红球
		printf("请选择第%d个红球的号码（1-33）：",i+1);
		scanf("%d",&a[i]);
		if(a[i]>33||a[i]<1){
			printf("红球没有这个号码，请重新选择\n");
			i--;
			continue;
		}
		for(int j=0;j<i;j++){
			if(a[j] == a[i]){
					printf("这个红球已被选择，请重新选择\n");
					i--;
					break;
			}
		}
	}
	do{//选蓝球
		printf("请选择篮球的号码（1-16）：");
		scanf("%d",&a[6]);
		if(a[6]>16 || a[6]<1){
			printf("红球没有这个号码，请重新选择\n");
		}else{
			break;
		}
	}while(1);
	maopao(a);//排序
	for(int i=0;i<7;i++){//拷贝
		w->chooseNum[i]=a[i];
	}
	do{//下注
		printf("输入你要买多少注：");
		scanf("%d",&w->buyNum);
		if(w->buyNum>5){
			printf("单张彩票注数不能大于5,请重新输入\n");
		}else if(w->buyNum<=0){
			printf("单张彩票注数不能小于0,请重新输入\n");
		}else{
			break;
		}
	}while(1);
	printf("彩票价格为2*%d=%0.2f元\n",w->buyNum,w->buyNum*2.0);//显示价格
	//调用系统时间
	char len[50]={0};
	registTime(len);//调用系统时间
	strcpy(w->buyTime,len);//购买时间	
	if(s->balance<2*w->buyNum){
		printf("余额不足!请充值余额\n");
		return;
	}
	s->balance-=2*w->buyNum;
	printf("感谢您的购买\n");
	agde++;
	theBonus=theBonus+2*w->buyNum*0.51;
	addBuyLotter(w);
}

void displayALottery(BuyLotter *w){//显示单张彩票信息
	printf("期号：%d  彩票id：%d  购买人：%s\n红球：",w->issue,w->lotterID,w->punter);
	for(int i=0;i<6;i++){
		printf("%d ",w->chooseNum[i]);
	}
	printf("蓝球：%d\n",w->chooseNum[6]);
	printf("注数：%d 中奖情况：%s\n购买时间：%s\n\n",w->buyNum,w->state,w->buyTime);
}
void displayAllLottery(){//显示所有彩票信息
	BuyLotter *temp=frist;
	while(temp!=NULL){
		displayALottery(temp);
		temp=temp->next;
	}
}
void displayNowAllBuyLotter(){//显示当期所有彩票
	BuyLotter *temp=frist;
	while(temp!=NULL){
		if(temp->issue==issue){
			printf("================================\n");
			displayALottery(temp);
		}	
		temp=temp->next;
	}
}
void displayPuntersAllBuyLotter(Punters *s){//显示彩民的购买记录
	BuyLotter *temp=frist;
	while(temp!=NULL){
		if(strcmp(temp->punter,s->name)==0){
			printf("================================\n");
			displayALottery(temp);
		}	
		temp=temp->next;
	}
}
int redNum(BuyLotter *temp,int a[]){//红球相同的个数
	int red=0;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			if(temp->chooseNum[j]==a[i]){
				red++;
			}						
		}			
	}
	return red;
}
int blueNum(BuyLotter *temp,int a[]){//蓝球相同的个数
	int blue=0;
	if(temp->chooseNum[6]==a[6]){
		blue++;
	}
	return blue;
}
void BuyLotterWhetherWin(int a[]){//判断是否中奖        
	int red,blue;
	char name[20];
	float currentTheBonus=theBonus;//独立奖池
	float single;//单注奖金
	Punters *s=NULL;//用户
	BuyLotter *temp=frist;
	for(;temp!=NULL;temp=temp->next){
		if(temp->issue==issue){//判断当前彩票
			red=redNum(temp,a);
			blue=blueNum(temp,a);
			strcpy(name,temp->punter);
			s=findPunters(name);//查找用户
			//判断中奖
			if(red==6 && blue==1){

				strcpy(temp->state,"一等奖");
				single=currentTheBonus*0.75;
				if(single >= 5000000){
					single = 5000000;
				}
				temp->bonus =single * temp->buyNum;//彩票金额
				theBonus = theBonus - single * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else if(red==6 && blue==0){

				strcpy(temp->state,"二等奖");
				single=currentTheBonus*0.25;
				if(single >= 5000000){
					single = 5000000;
				}
				temp->bonus =single * temp->buyNum;//彩票金额
				theBonus=theBonus-single * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else if(red==5 && blue==1){

				strcpy(temp->state,"三等奖");
				temp->bonus =3000 * temp->buyNum;//彩票金额
				theBonus = theBonus -  3000 * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else if((red==4 && blue==1)||(red==5 && blue==0)){

				strcpy(temp->state,"四等奖");
				temp->bonus =200 * temp->buyNum;//彩票金额
				theBonus = theBonus -  200 * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else if((red==3 && blue==1)||(red==4 && blue==0)){

				strcpy(temp->state,"五等奖");
				temp->bonus =10 * temp->buyNum;//彩票金额
				theBonus = theBonus -  10 * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else if((red==2 && blue==1)||(red==1 && blue==1)||(red==0 && blue==1)){

				strcpy(temp->state,"六等奖");
				temp->bonus =5 * temp->buyNum;//彩票金额
				theBonus = theBonus -  5 * temp->buyNum;//奖池
				s->balance+=temp->bonus;//用户余额

			}else{
				strcpy(temp->state,"未中奖");
			}
		}
	}	
}
void winNumRand(int *a){//随机生成
	srand(time(NULL));
	for(int i=0;i<6;i++){//中奖号码 红球
		a[i]=rand()%33+1;
		for(int j=0;j<i;j++){//不重复
			if(a[j] == a[i]){
				i--;
				break;
			}
		}
	}
	a[6]=rand()%16+1;//蓝球
}
void runALottery(){//开奖
	if(top==NULL){
		printf("还未发布彩票\n");
		return;
	}
	int a[7];
	winNumRand(a);
	maopao(a);//排序
	for(int i=0;i<7;i++){//拷贝
		end->winNum[i]=a[i];
	}
	printf("红球开奖号：");
	for(int i=0;i<6;i++){
		printf("%d ",end->winNum[i]);
	}
	printf("蓝球开奖号：%d\n",end->winNum[6]);
	end->buyAmount=lotterID;//本期售出总数；
	end->theBonus=theBonus;//本期奖池总额	
	if(frist!=NULL){
		BuyLotterWhetherWin(a);////判断是否中奖 
	}
	lotterID=0;
	agde++;
	lotteries();//自动发布下一期
}
void displaAllLotteries(){//显示已开奖彩票总体信息
	Lottery	*temp=top;
	if (top==NULL){
		printf("还未发布彩票\n");
		return;
	}
	
	if(top->next!=NULL){
		while(temp->next!=NULL){//已开奖
			printf("期号：%d 单价：￥2/注 状态：%s\n已售出：%d当期奖池金额：%0.2f\n红球：",temp->issue,temp->state,temp->buyAmount,temp->theBonus);
				for(int i=0;i<6;i++){
					printf("%d ",temp->winNum[i]);
				}
				printf("蓝球：%d\n",temp->winNum[6]);
				temp=temp->next;
		}
		return;
	}

}
void displayNowLotteries(){//显示当期彩票总体信息
	printf("期号：%d 单价：￥2/注 状态：未开奖\n已售出：%d 当期奖池金额：%0.2f\n",issue,lotterID,theBonus);//未开奖
	printf("红球：0 0 0 0 0 0 蓝球：0\n");
}
void addLotteries(Lottery *x){//添加彩票总体信息到链表
	if(top==NULL){
		top=x;
		end=x;
	}else{
		end->next=x;
		end=x;
	}
}
void lotteries(){//发布彩票
	if(strcmp(end->state,"未开奖")==0){
		printf("该期彩票未开奖，不能从新发布\n");
		return;
	}
	Lottery *x=malloc(sizeof(Lottery));
	x->issue=++issue;//发布期号
	x->price=2;//彩票单价
	strcpy(x->state,"未开奖");
	x->next=NULL;//下一个链表
	agde++;
	addLotteries(x);//添加彩票总体信息到链表
	printf("彩票发布成功\n");
}

void saveAllBuyLotter(){//保存所有彩票到硬盘
	FILE *fp=fopen("buyLotter.bat","wb");
	BuyLotter *temp=frist;
	while(temp!=NULL){
		fwrite(temp,sizeof(BuyLotter),1,fp);
		temp=temp->next;
	}
	fclose(fp);
}
void readBuyLotterFromFile(){//读取所有彩票
	FILE *fp=fopen("BuyLotter.bat","rb");//文件不存在，返回NULL;
	int len=0;
	if(fp==NULL){
		return;
	}
	BuyLotter *temp=malloc(sizeof(BuyLotter));
	len=fread(temp,sizeof(BuyLotter),1,fp);
	temp->next=NULL;
	while(len>0){
		//写入链表
		addBuyLotter(temp);
		temp=malloc(sizeof(BuyLotter));
		len=fread(temp,sizeof(BuyLotter),1,fp);
		temp->next=NULL;
	}
	fclose(fp);
	free(temp);
}

void saveAllLottery(){//保存彩票信息到硬盘
	FILE *fp=fopen("Lottery.bat","wb");
	Lottery *temp=top;
		while(temp!=NULL){
			if(temp==end){
				temp->theBonus=theBonus;
				temp->buyAmount=lotterID;
			}
			fwrite(temp,sizeof(Lottery),1,fp);
			temp=temp->next;
		}
		fclose(fp);
}
void readLotteryFromFile(){//读取彩票信息
	FILE *fp=fopen("Lottery.bat","rb");//文件不存在，返回NULL;
	int len=0;
	if(fp==NULL){
		return;
	}
	Lottery *temp=malloc(sizeof(Lottery));
	len=fread(temp,sizeof(Lottery),1,fp);
	temp->next=NULL;
	while(len>0){
		//写入链表
		addLotteries(temp);
		temp=malloc(sizeof(Lottery));
		len=fread(temp,sizeof(Lottery),1,fp);
		temp->next=NULL;
	}
	fclose(fp);
	free(temp);
}
void endLottery(){//找到最后的彩票信息
	if (end!=NULL){
		theBonus=end->theBonus;
		lotterID=end->buyAmount;
		issue=end->issue;	
	}
}
