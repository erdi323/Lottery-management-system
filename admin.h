#ifndef ADMIN_H
#define ADMIN_H
typedef struct admin{
	char name[20];
	char password[20];
}Admin;

int adminLogin();//管理员/公证员登录
void adminMenu();//管理员菜单
void notaryMenu();//公证员菜单

#endif
