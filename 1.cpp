#include<bits/stdc++.h>
using namespace std;
long int memory[1000];
long int MBR;
int JUMP=0;
int pc;
int halt;
int MAR;
int IR;
int IBR;
long int AC;
long int MQ;
void decodeandexecute(int IR, int MAR)
{
	switch(IR)
	{
		case 10:
			{
				AC = MQ;
				break;
			}
		case 9:
			{
				MQ = memory[MAR];
				break;
			}
		case 17:
			{
				memory[MAR] = AC;
				break;
			}
		case 1:
			{
				AC = memory[MAR];
				break;
			}
		case 2:
			{
				AC = -memory[MAR];
				break;
			}
		case 3:
			{
				if(memory[MAR] < 0)
				{
					AC = -memory[MAR];
				}
				else
				{
					AC = memory[MAR];
				}
				break;
			}
		case 4:
			{
				if(memory[MAR] <0)
				{
					AC = memory[MAR];
				}
				else
				{
					AC = -memory[MAR];
				}
				break;
			}
		case 13:
			{
				JUMP = 1;
				break;
			}
		case 14:
			{
				JUMP = 2;
				break;
			}
		case 15:
			{
				if(AC >= 0)
				{
					JUMP = 1;
				}
				break;
			}
		case 16:
			{
				if(AC >=0)
				{
					JUMP = 2;
				}
				break;
			}
		case 5:
			{
				MBR = memory[MAR];
				AC += MBR;
				break;
			}
		case 7:
			{
				MBR = memory[MAR];
				if(MBR<0)
				{
					AC = AC - MBR;
				}
				else
				{
					AC = AC + MBR;
				}
				break;
			}
		case 6:
			{
				MBR = memory[MAR];
				AC = AC - MBR;
				break;
			}
		case 8:
			{
				MBR = memory[MAR];
				if(MBR<0)
				{
					AC = AC + MBR;
				}
				else
				{
					AC = AC - MBR;
				}
				break;
			}
		case 11:
			{
				long long int a;
				MBR = memory[MAR];
				a = MQ*MBR;
				AC = a >> 40;
				MQ = a - ( a << 40) ;
				break;
			}
		case 12:
			{
				MBR = memory[MAR];
				MQ = AC/MBR;
				AC = AC%MBR;
				break;
			}
		case 20:
			{
				AC = AC <<1;
				break;
			}
		case 21:
			{
				AC = AC >> 1;
				break;
			}
		case 18:
			{
				long int t,a,k = AC - ((AC >> 12) << 12);
				a = memory[MAR];
				t = a - ( (a>>20) <<20) ;
				a = a >> 32;
				a = a<<12;
				a = a+k;
				a = a << 20;
				a = a + t;
				memory[MAR] = a;
				break;
			}
		case 19:
			{
				long int a,k = AC - ((AC >>12) << 12) ;
				a = memory[MAR];
				a = a>> 12 ;
				a = a << 12;
				a = a + k;
				memory[MBR] = a;
			}


int main()
{
	int n,i,address;
	long int t;
	for(i=0;i<n;i++)
	{
		scanf("%d %X",address,t);
		memory[address] = t;
		if(i==0)
		{
			pc = address;
		}
	}
	halt = 1;
	while(halt)
	{
		MAR = pc;
		MBR = memory[MAR];
		halt = MBR >> 20;
		if(halt == 0)
		{
			exit(0);
		}
		IBR = MBR - (MBR >> 20) ;
		IR = MBR >> 32;
		MAR = (MBR >> 20) - (IR << 12);
		pc += 1;
		decodeandexecute(IR,MAR);
		halt = IBR;
		if(halt == 0)
		{
			exit(0);
		}
		IR = IBR >> 12;
		MAR = IBR - (IR << 12) ;
		decodeandexecute(IR,MAR);
	}
	return 0;
}

	

