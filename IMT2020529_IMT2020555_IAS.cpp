#include<bits/stdc++.h>
using namespace std;
long int memory[1000];
long long int MBR;
int JUMP=0;
int JUMPK = 0;
int pc;
int halt;
int MAR;
int IR;
int IBR;
long int AC;
long int MQ;
void optimise(long long int C[])
{
	for(long long int i = 1 ;i<=80;i++)
	{
		if(C[80-i] == 2)
		{
			C[80 - i] = 0;
			C[80-i-1] += 1;
		}
		if(C[80-i] == 3)
		{
			C[80 - i] = 1;
			C[80 - i -1] += 1;
		}
	}
	return ;
}
void Multiplication(long long int a,long long int b,int ok)
{
	long long int A[40];
	long long int B[40];
	long long int C[80];
	long long int i = 0;
	for(i=0;i<80;i++)
	{
		C[i] = 0;
	}
	//
	//1100 = 12
	//0011 = 3
	//
	//   1100
	//  11000
	// 000000
	//0000000
	//
	//100100 = 36
	long long int p=a,q=b,t,y;
	for(long long int i = 1;i<=40;i++)
	{
		t = p%2;
		y = q%2;
		A[40-i] = t;
		B[40-i] = y;
		p = p/2;
		q = q/2;
	}
	long long int j = 0;
	for(long long int i = 1;i<=40;i++)
	{
		if(B[40-i] == 1){
		for(j=1;j<i;j++)
		{
			C[80-j] += 0;
		}
		for(j=1;j<=40;j++)
		{
			C[80-i-j+1] += A[40-j];
		}
		}
		optimise(C);
	}
	if(ok == 1)
	{
		for(i = 0 ; i< 80 ; i++)
		{
			if(C[i] == 0)
			{
				C[i] = 1;
			}
			else if(C[i] == 1)
			{
				C[i] = 0;
			}
		}
		C[79] += 1;
		optimise(C);
	}
	MQ = 0;
	AC = 0;
	for(j=1;j<=40;j++)
	{
		MQ += C[80-j]*pow(2,j-1);
	}
	for(j=41;j<=80;j++)
	{
		AC += C[80-j]*pow(2,j-41);
	}
	//cout << MQ << endl;
	return ;
}
void decodeandexecute(int IR, int MAR)
{
	switch(IR)
	{
		case 10: //Load MQ
			{
				AC = MQ;
				break;
			}
		case 9: //Load MQ , M(X)
			{
				MBR = memory[MAR];
				MQ = MBR;
				break;
			}
		case 33://Stor M(x)
			{
				MBR = AC;
				memory[MAR] = MBR;	
				printf("memory[%d] = %llX\n",MAR,MBR);
				break;
			}
		case 1: //Load M(x)
			{
				MBR = memory[MAR];
				AC = MBR;
				break;
			}
			//0011 = 3
			//0110
			//1001
			//1010
			//0101 = -3
			//0101   only allocate last 3 bits to data  
			//0101 = -3 true
			//1010 
			//0101
			//0001
			//0110
			//0011 = 3
		case 2: // Load -M(x)
			{
				MBR = memory[MAR];
				MBR = (MBR << 24);
				MBR = ~MBR;
				MBR += 1;
				MBR = MBR >> 24; 
				AC = MBR;
				break;
			}
		case 3: // Load |M(x)|
			{
				if(((memory[MAR])<<24) < 0)
				{
					MBR = memory[MAR];
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					AC = MBR;
				}
				else
				{
					MBR = memory[MAR];
					AC = MBR;
				}
				break;
			}
		case 4: //load -|M(x)|
			{
				if((memory[MAR] << 24) <0)
				{
					MBR = memory[MAR];
					AC = MBR;  
				}
				else
				{
					MBR = memory[MAR];
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					AC = MBR;
				}
				break;
			}
		case 13: //JUMP M(X,0:19)
			{
				JUMP = 1;
				break;
			}
		case 14://JUMP M(X,20:39)
			{
				JUMP = 2;
				JUMPK = 1;
				break;
			}
		case 15://JUMP +M(X,0:19)
			{
				long long int y = (AC << 24) >> 24;
				if((y) >= 0)
				{
					//cout << (y) << "so";
					JUMP = 1;
				}
				break;
			}
		case 16://JUMP +M(X,20:39)
			{
				long long int y = (AC << 24) >> 24;
				if((y) >= 0)
				{
					//cout << (AC << 24) << "so";
					JUMP = 2;
					JUMPK = 1;
				}
				break;
			}
		case 5: //ADD M(X)
			{
				MBR = memory[MAR];
				AC += MBR;
				break;
			}
		case 7: //ADD |M(X)|
			{
				MBR = memory[MAR];
				if((MBR << 24) <0)
				{
					//MBR = memory[MAR];
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					AC = AC + MBR;
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
				}
				else
				{
					AC = AC + MBR;
				}
				break;
			}
		case 6: //SUB M(X)
			{
				MBR = memory[MAR];
				MBR = (MBR << 24);
				MBR = ~MBR;
				MBR += 1;
				MBR = MBR >> 24;
				AC = AC + MBR;
				MBR = (MBR << 24);
				MBR = ~MBR;
				MBR += 1;
				MBR = MBR >> 24;
				break;
			}
		case 8: // Sub |M(x)|
			{
				MBR = memory[MAR];
				if((MBR << 24)<0)
				{
					AC = AC + MBR;
				}
				else
				{
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					AC = AC + MBR;
					MBR = (MBR << 24);
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
				}
				break;
			}
		case 11: // MUL M(x)
			{
				//cout << "fine till now";
				long long int a;
				MBR = memory[MAR];
				//MQ = MQ * MBR;
				int ok=0; //flag
				if((MQ << 24) < 0 && (MBR << 24) >= 0)
				{
					MQ = MQ << 24;
					MQ = ~MQ;
					MQ += 1;
					MQ = MQ >> 24;
					ok = 1;
				}
				else if((MQ << 24) >= 0 && ( MBR << 24) < 0)
				{
					MBR = MBR << 24;
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					ok = 1;
				}
				else if(( MQ << 24) < 0 && ( MBR << 24 ) < 0)
				{
					MQ = MQ << 24;
					MQ = ~MQ;
					MQ += 1;
					MQ = MQ >> 24;
					MBR = MBR << 24;
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
				}
				//
				Multiplication(MBR,MQ,ok);
				ok = 0;
				//a = MQ*MBR;
				//AC = a >> 40;
				//MQ = a - ( a << 40) ;
				// 
				break;
			}
		case 12: //DIV M(X)
			{
				int ok = 0; // flag
				MBR = memory[MAR];
				if((AC << 24) < 0 && (MBR << 24) > 0)
				{
					AC = AC << 24;
					AC = ~AC;
					AC += 1;
					AC = AC >> 24;
					ok = 1;
				}
				else if((AC << 24) > 0 && (MBR << 24) < 0)
				{
					MBR = MBR << 24;
					MBR = ~MBR;
					MBR += 1;
					MBR = MBR >> 24;
					ok = 1;
				}
				else if((AC << 24) < 0 && (MBR << 24) < 0)
				{
					AC = AC << 24;
					AC = ~AC;
					AC += 1;
					AC = AC >> 24;
					MBR = MBR << 24;
					MBR = ~ MBR;
					MBR += 1;
					MBR = MBR >> 24;
				}
				MQ = AC/MBR;
				if(ok == 1)
				{
					MQ = MQ << 24;
					MQ = ~MQ;
					MQ += 1;
					MQ = MQ >> 24;
				}
				ok = 0;
				AC = AC%MBR;
				break;
			}
		case 20: // LSH 
			{
				AC = AC << 1;
				break;
			}
		case 21: // RSH
			{
				AC = AC >> 1;
				break;
			}
		case 18: //STOR M(X,8:19)
			{
				long int t,a;
				//long int k = AC - ((AC >> 12) << 12);
				long int k = (AC << 52) >> 52 ;
				MBR = memory[MAR];
				a = MBR;
				//t = a - ( (a>>20) <<20);
				t = (a << 44) >> 44;
				a = a >> 32;
				a = a<<12;
				a = a+k;
				a = a << 20;
				a = a + t;
				MBR = a;
				memory[MAR] = MBR;

				break;
			}
		case 19: //STOR M(X,28:39)
			{
				long int a;
				//long int k = AC - ((AC >>12) << 12);
				long int k = (AC << 52) >> 52;
				MBR = memory[MAR];
				a = MBR;
				a = a >> 12 ;
				a = a << 12;
				a = a + k;
				MBR = a;
				memory[MAR] = MBR;
			}
	}
}


int main()
{
	int n,i,address;
	long int t;
	cin >> n;
	for(i=0;i<n;i++)
	{
		scanf("%d %lX",&address,&t);
		memory[address] = t;
		if(i==0)
		{
			pc = address;
		}
	}
	halt = 1;
	while(halt)
	{
		long long int q;
		MAR = pc;
		MBR = memory[MAR];
		IBR = (MBR << 44) >> 44;
		//
		printf("MBR = %llX IBR = %X MAR = %d\n",MBR,IBR,MAR);
		//
		if(JUMP != 2)
		{
			if(JUMP==1)
			{
				JUMP==0;
			}
			halt = MBR >> 20;
			if(halt == 0)
			{
				exit(0);
			}
			//IBR = MBR - ((MBR >> 20) << 20) ;
			//IBR = (MBR << 44) >> 44;
			IR = MBR >> 32;
			//
			printf("IR1 = %X\n",IR);
			//
			//MAR = (MBR >> 20) - (IR << 12);
			//MAR = (MBR << 20) >> 42;
			MAR = MBR >> 20;
			MAR = (MAR <<20) >> 20;
			//
			printf("MAR1 = %X\n",MAR);
			//
			decodeandexecute(IR,MAR);
		}
		pc += 1;
		//
		printf("AC = %lX MQ = %lX MBR = %llX\n",AC,MQ,MBR);
		//
		if(JUMP!=1 && JUMPK != 1)
		{
			if(JUMP == 2)
			{
				JUMP = 0;
			}
			halt = IBR;
			if(halt == 0)
			{
				exit(0);
			}
			IR = IBR >> 12;
			//
			printf("IR2 = %X\n",IR); 
			//
			//MAR = IBR - (IR << 12);
			MAR = (IBR << 20)>>20;
			//
			printf("MAR2 = %X\n",MAR);
			//
			decodeandexecute(IR,MAR);
		}
		//
		printf("AC2 = %lX MQ2 = %lX MBR2 = %llX\n",AC,MQ,MBR);
		//
		if(JUMP == 1 || JUMP == 2)
		{
			//JUMP = 0;
			JUMPK = 0;
			pc = MAR;
		}
	}
	return 0;
}
