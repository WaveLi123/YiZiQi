#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxsize 100//栈长度

//数据类型转换及顺序表构建
typedef struct{
	char value[3][3];//当前格局的状态
	int test;//当前格局的静态估值:A_win-B_win
	int A_win;//A_win的静态估值
	int B_win;//B_win的静态估值
	int location[2];//A的落子位置
}datatype;

//顺序栈定义
typedef struct{ 
	datatype data[maxsize+1];//栈数组
	int top; 				 //栈顶指针
}Seqstack;

//全局变量
datatype data,temp;//临时数据存放器
datatype data_init;//用于棋盘的初始化
datatype data_temp[maxsize+1];//根据估价函数的值对扩展的格局进行排序，结果存放于此
int length;//data_temp的计数器
datatype reserve;//保存当前格局
datatype reserve1;//保存当前格局

Seqstack *Open_head;//open表
Seqstack *Closed_head;//closed表

/*********************函数声明*********************/
Seqstack *InitStack();//置空栈
void Stackempty(Seqstack *S);//判断栈是否为空
void Push(Seqstack *S,datatype x);//入栈
void Pop(Seqstack *S,datatype &x);//出栈
void Show(Seqstack *S);//输出栈内元素
void Caculate_Yzq();//一字棋游戏的总控程序
/*********************函数声明*********************/
/***********************************************附属函数构建***********************************************/
//元素输出
void Show_table(datatype value){
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			printf(" %c ",value.value[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

//小菜单函数构建
bool select(){
	char select;
	char ch;//吸收干扰字符
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
//初始菜单构建
void Menu(){
	printf("******************一字棋游戏******************\n");
	printf("*【游戏规则】                                *\n");
	printf("*1.电脑方执子为'#',用户方执子为'*'.          *\n");
	printf("*2.开始比赛时电脑方率先走棋.                 *\n");
	printf("*3.用户出棋格式为a b(0=<a/b<=2).             *\n");
	printf("**********************************************\n");
}
/***********************************************附属函数构建***********************************************/

/***********************************************基本函数构建***********************************************/
//置空栈
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//判断栈是否为空
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("该栈为空！\n");
	}
	else{
		printf("该栈非空！\n");
	}
}

//入栈
void Push(Seqstack *S,datatype x){ 
	int i,j,p;//循环变量
	if (S->top==maxsize){
		printf("对不起，Open表已满，新生成的格局无法进表，该一字棋问题的求解被迫终止！\n");
		exit(0);
	}
	S->top++; 		
	S->data[S->top]=x;
}

//出栈
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("不好意思，Open表已空，该一字棋问题的极大极小分析无解!\n");
		exit(0);
	}
	x=S->data[S->top];
	S->top--;
}

//检查输入是否正确
void Check_input(int value){
	if(value<0||value>2){
		printf("Warning:your input is wrong!(0-8)\n");
		exit(0);
	}
}
//冒泡排序
void MpSort(datatype array[],int N){  
	datatype p;
	for(int i=0;i<=N-1;i++)
	{
		for(int j=0;j<N-1;j++)
		{
			if(array[j].test>array[j+1].test)
			{
				p=array[j];
				array[j]=array[j+1];
				array[j+1]=p;
			}
		}
	}
}
/***********************************************基本函数构建***********************************************/

/***********************************************主要函数构建***********************************************/
//检测落子位置是否合法
bool test_location(int h,int l){
	if(data.value[h][l]=='0') return true;
	else return false;
}
//双方获胜检测条件
void test_value_A(){
	//执"*"(用户)获胜检测
	data.A_win=0;
	if(data.value[0][0]=='*'&&data.value[0][1]=='*'&&data.value[0][2]=='*'){
		data.A_win++;
	}
	if(data.value[1][0]=='*'&&data.value[1][1]=='*'&&data.value[1][2]=='*'){
		data.A_win++;
	}
	if(data.value[2][0]=='*'&&data.value[2][1]=='*'&&data.value[2][2]=='*'){
		data.A_win++;
	}
	if(data.value[0][0]=='*'&&data.value[1][0]=='*'&&data.value[2][0]=='*'){
		data.A_win++;
	}
	if(data.value[0][1]=='*'&&data.value[1][1]=='*'&&data.value[2][1]=='*'){
		data.A_win++;
	}
	if(data.value[0][2]=='*'&&data.value[1][2]=='*'&&data.value[2][2]=='*'){
		data.A_win++;
	}
	if(data.value[0][0]=='*'&&data.value[1][1]=='*'&&data.value[2][2]=='*'){
		data.A_win++;
	}
	if(data.value[0][2]=='*'&&data.value[1][1]=='*'&&data.value[2][0]=='*'){
		data.A_win++;
	}
}
void test_value_B(){
	//执"#"(电脑)获胜检测
	data.B_win=0;
	if(data.value[0][0]=='#'&&data.value[0][1]=='#'&&data.value[0][2]=='#'){
		data.B_win++;
	}
	if(data.value[1][0]=='#'&&data.value[1][1]=='#'&&data.value[1][2]=='#'){
		data.B_win++;
	}
	if(data.value[2][0]=='#'&&data.value[2][1]=='#'&&data.value[2][2]=='#'){
		data.B_win++;
	}
	if(data.value[0][0]=='#'&&data.value[1][0]=='#'&&data.value[2][0]=='#'){
		data.A_win++;
	}
	if(data.value[0][1]=='#'&&data.value[1][1]=='#'&&data.value[2][1]=='#'){
		data.A_win++;
	}
	if(data.value[0][2]=='#'&&data.value[1][2]=='#'&&data.value[2][2]=='#'){
		data.A_win++;
	}
	if(data.value[0][0]=='#'&&data.value[1][1]=='#'&&data.value[2][2]=='#'){
		data.B_win++;
	}
	if(data.value[0][2]=='#'&&data.value[1][1]=='#'&&data.value[2][0]=='#'){
		data.B_win++;
	}
}
//电脑落子函数
void C_action(){
	int h_n=0,l_n=0;
	int h,l;//电脑落子的行列号
	time_t t;
	srand((int)time(&t));
	h=rand()%3;
	l=rand()%2+1;
	while(!test_location(h,l)){
		h=h_n%3;
		l_n++;
		l=l_n%3;
		if(l==2){
			h_n++;
		}
	}
	data.value[h][l]='#';//电脑落子位置
}

//计算用户获胜概率值
void Caculate_value(int h,int l){
	int i,j;//循环变量
	int temp_A;
	reserve=data;//保存预测前的当前格局
	data.location[0]=h;
	data.location[1]=l;
	data.value[h][l]='*';
	reserve1=data;
	//用户落子后，计算其获胜静态值
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(data.value[i][j]=='0'){
				data.value[i][j]='*';
			}
		}
	}
	test_value_A();
	temp_A=data.A_win;
	data=reserve1;
	data.A_win=temp_A;
	//用户落子后，计算其失败静态值
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(data.value[i][j]=='0'){
				data.value[i][j]='#';
			}
		}
	}
	test_value_B();
	data.test=data.A_win-data.B_win;
	length++;
	data_temp[length]=data;
	data=reserve;
}

//检测搜索是否成功
int test_win(){
	//执"*"(用户)获胜检测
	if((data.value[0][0]=='*'&&data.value[0][1]=='*'&&data.value[0][2]=='*')
	||(data.value[1][0]=='*'&&data.value[1][1]=='*'&&data.value[1][2]=='*')
	||(data.value[2][0]=='*'&&data.value[2][1]=='*'&&data.value[2][2]=='*')
	||(data.value[0][0]=='*'&&data.value[1][0]=='*'&&data.value[2][0]=='*')
	||(data.value[0][1]=='*'&&data.value[1][1]=='*'&&data.value[2][1]=='*')
	||(data.value[0][2]=='*'&&data.value[1][2]=='*'&&data.value[2][2]=='*')
	||(data.value[0][0]=='*'&&data.value[1][1]=='*'&&data.value[2][2]=='*')
	||(data.value[0][2]=='*'&&data.value[1][1]=='*'&&data.value[2][0]=='*')){
		Show_table(data);
		printf("Congratulatios,you win!\n");
		if(select()){
			system("cls");	
			data=data_init;
			Menu();
			Caculate_Yzq();
		}
		else exit(0);
	}
	//执"#"(用户)获胜检测
	if((data.value[0][0]=='#'&&data.value[0][1]=='#'&&data.value[0][2]=='#')
	||(data.value[1][0]=='#'&&data.value[1][1]=='#'&&data.value[1][2]=='#')
	||(data.value[2][0]=='#'&&data.value[2][1]=='#'&&data.value[2][2]=='#')
	||(data.value[0][0]=='#'&&data.value[1][0]=='#'&&data.value[2][0]=='#')
	||(data.value[0][1]=='#'&&data.value[1][1]=='#'&&data.value[2][1]=='#')
	||(data.value[0][2]=='#'&&data.value[1][2]=='#'&&data.value[2][2]=='#')
	||(data.value[0][0]=='#'&&data.value[1][1]=='#'&&data.value[2][2]=='#')
	||(data.value[0][2]=='#'&&data.value[1][1]=='#'&&data.value[2][0]=='#')){
		Show_table(data);
		printf("Pardon,you lose!\n");
		if(select()){
			system("cls");
			data=data_init;
			Menu();
			Caculate_Yzq();
		}
		else exit(0);
	}
	else{
		if((data.value[0][0]!='0'&&data.value[0][1]!='0'&&data.value[0][2]!='0')
			&&(data.value[1][0]!='0'&&data.value[1][1]!='0'&&data.value[1][2]!='0')
			&&(data.value[2][0]!='0'&&data.value[2][1]!='0'&&data.value[2][2]!='0')
			&&(data.value[0][0]!='0'&&data.value[1][1]!='0'&&data.value[2][2]!='0')
			&&(data.value[0][2]!='0'&&data.value[1][1]!='0'&&data.value[2][0]!='0')){
			Show_table(data);
			printf("Pardon,no winner!\n");
			if(select()){
				system("cls");
				data=data_init;
				Caculate_Yzq();
			}
			else exit(0);
		}
		else{
			Show_table(data);
			return 0;
		}
	}
	return 1;
}

//一字棋问题的具体求解
void Caculate_Yzq(){
	int i,j;//循环变量
	//Open表和closed表的初始化
	Open_head=InitStack();
	Closed_head=InitStack();
	//一字棋问题的具体操作
	while(!test_win()){		
		printf("【Computer】\n");
		C_action();
		test_win();
		//在用户角度根据当前格局预测对用户有利的下一格局，并将其进行排序，选出最优下一格局，即最优落子位置
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(test_location(i,j)){
					Caculate_value(i,j);
				}
			}
		}
		MpSort(data_temp,length);
		for(i=0;i<length;i++){
			Push(Open_head,data_temp[i]);
		}
		length=0;

		Pop(Open_head,temp);
		Push(Closed_head,temp);
		printf("【Your action】(Best action:<%d,%d>)\n",temp.location[0],temp.location[1]);
		do{
			scanf("%d",&data.location[0]);
			Check_input(data.location[0]);
			scanf("%d",&data.location[1]);
			Check_input(data.location[1]);
		}while(!test_location(data.location[0],data.location[1]));
		data.value[data.location[0]][data.location[1]]='*';
	}
}
/***********************************************主要函数构建***********************************************/