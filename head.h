#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxsize 100//ջ����

//��������ת����˳�����
typedef struct{
	char value[3][3];//��ǰ��ֵ�״̬
	int test;//��ǰ��ֵľ�̬��ֵ:A_win-B_win
	int A_win;//A_win�ľ�̬��ֵ
	int B_win;//B_win�ľ�̬��ֵ
	int location[2];//A������λ��
}datatype;

//˳��ջ����
typedef struct{ 
	datatype data[maxsize+1];//ջ����
	int top; 				 //ջ��ָ��
}Seqstack;

//ȫ�ֱ���
datatype data,temp;//��ʱ���ݴ����
datatype data_init;//�������̵ĳ�ʼ��
datatype data_temp[maxsize+1];//���ݹ��ۺ�����ֵ����չ�ĸ�ֽ������򣬽������ڴ�
int length;//data_temp�ļ�����
datatype reserve;//���浱ǰ���
datatype reserve1;//���浱ǰ���

Seqstack *Open_head;//open��
Seqstack *Closed_head;//closed��

/*********************��������*********************/
Seqstack *InitStack();//�ÿ�ջ
void Stackempty(Seqstack *S);//�ж�ջ�Ƿ�Ϊ��
void Push(Seqstack *S,datatype x);//��ջ
void Pop(Seqstack *S,datatype &x);//��ջ
void Show(Seqstack *S);//���ջ��Ԫ��
void Caculate_Yzq();//һ������Ϸ���ܿس���
/*********************��������*********************/
/***********************************************������������***********************************************/
//Ԫ�����
void Show_table(datatype value){
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			printf(" %c ",value.value[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

//С�˵���������
bool select(){
	char select;
	char ch;//���ո����ַ�
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
//��ʼ�˵�����
void Menu(){
	printf("******************һ������Ϸ******************\n");
	printf("*����Ϸ����                                *\n");
	printf("*1.���Է�ִ��Ϊ'#',�û���ִ��Ϊ'*'.          *\n");
	printf("*2.��ʼ����ʱ���Է���������.                 *\n");
	printf("*3.�û������ʽΪa b(0=<a/b<=2).             *\n");
	printf("**********************************************\n");
}
/***********************************************������������***********************************************/

/***********************************************������������***********************************************/
//�ÿ�ջ
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//�ж�ջ�Ƿ�Ϊ��
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("��ջΪ�գ�\n");
	}
	else{
		printf("��ջ�ǿգ�\n");
	}
}

//��ջ
void Push(Seqstack *S,datatype x){ 
	int i,j,p;//ѭ������
	if (S->top==maxsize){
		printf("�Բ���Open�������������ɵĸ���޷�������һ�����������ⱻ����ֹ��\n");
		exit(0);
	}
	S->top++; 		
	S->data[S->top]=x;
}

//��ջ
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("������˼��Open���ѿգ���һ��������ļ���С�����޽�!\n");
		exit(0);
	}
	x=S->data[S->top];
	S->top--;
}

//��������Ƿ���ȷ
void Check_input(int value){
	if(value<0||value>2){
		printf("Warning:your input is wrong!(0-8)\n");
		exit(0);
	}
}
//ð������
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
/***********************************************������������***********************************************/

/***********************************************��Ҫ��������***********************************************/
//�������λ���Ƿ�Ϸ�
bool test_location(int h,int l){
	if(data.value[h][l]=='0') return true;
	else return false;
}
//˫����ʤ�������
void test_value_A(){
	//ִ"*"(�û�)��ʤ���
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
	//ִ"#"(����)��ʤ���
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
//�������Ӻ���
void C_action(){
	int h_n=0,l_n=0;
	int h,l;//�������ӵ����к�
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
	data.value[h][l]='#';//��������λ��
}

//�����û���ʤ����ֵ
void Caculate_value(int h,int l){
	int i,j;//ѭ������
	int temp_A;
	reserve=data;//����Ԥ��ǰ�ĵ�ǰ���
	data.location[0]=h;
	data.location[1]=l;
	data.value[h][l]='*';
	reserve1=data;
	//�û����Ӻ󣬼������ʤ��ֵ̬
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
	//�û����Ӻ󣬼�����ʧ�ܾ�ֵ̬
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

//��������Ƿ�ɹ�
int test_win(){
	//ִ"*"(�û�)��ʤ���
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
	//ִ"#"(�û�)��ʤ���
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

//һ��������ľ������
void Caculate_Yzq(){
	int i,j;//ѭ������
	//Open���closed��ĳ�ʼ��
	Open_head=InitStack();
	Closed_head=InitStack();
	//һ��������ľ������
	while(!test_win()){		
		printf("��Computer��\n");
		C_action();
		test_win();
		//���û��Ƕȸ��ݵ�ǰ���Ԥ����û���������һ��֣��������������ѡ��������һ��֣�����������λ��
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
		printf("��Your action��(Best action:<%d,%d>)\n",temp.location[0],temp.location[1]);
		do{
			scanf("%d",&data.location[0]);
			Check_input(data.location[0]);
			scanf("%d",&data.location[1]);
			Check_input(data.location[1]);
		}while(!test_location(data.location[0],data.location[1]));
		data.value[data.location[0]][data.location[1]]='*';
	}
}
/***********************************************��Ҫ��������***********************************************/