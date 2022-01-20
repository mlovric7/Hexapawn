#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>


int board[9]={-1,-1,-1,0,0,0,1,1,1};
int win=0, crrs;

void empty_stdin(){

    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();

}



void boardreset(){

	int boardorg[9]={-1,-1,-1,0,0,0,1,1,1};
	memcpy(board, boardorg, 4*9);	

}

void printboard(){

	int i;
	printf("\t");
	for(i=0;i<9;i++)
	{
		if (i==3)
			printf("\t\t1 2 3");
		if (i==6)
			printf("\t\t4 5 6");
		if (i%3==0)
			printf("\n\t");
		if (board[i]==-1)
			printf("B ");
		else if (board[i]==0)
			printf("- ");
		else
			printf("W ");
		
	}
	printf("\t\t7 8 9\n\n");
}

int legalmovescheck(int e, int s){
		
	if ((s>9) || (s<1) || (e>9) || (e<1)){ 
		printf("That is not a valid coordinate\n\n");
		return false;
		}
	else if (board[s-1]!=1){ 
		printf("That is not a valid coordinate\n\n");
		return false;
		}
	
	else if (e>s || e-s==-1){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else if (s-e>4){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else if (s==7 && e==3){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else if (s-e==3 && board[e-1]!=0){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else if (board[e-1]==1){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else if (s-e != 3 && board[e-1]!=-1){
		printf("Move is not legal\n\n");
		return false;
		}
	
	else return true;	
}


int winnerplayer(){

	int j[4]={0,1,3,4};
	int k[4]={1,2,4,5};
	int i=0,b=0;
	
	for(i=0;i<3;i++)
	{
		if(board[i]==1)
		{
			printf("You win!\n\n");
			return 1;
		}
	}
	
	for(i=0;i<9;i++)
	{
		if(board[i]==-1)
		{
			b++;
		}
	}

	if(b==0)
	{
		printf("You win!\n\n");
		return 1;
	}
	
	for(i=0;i<6;i++)
	{
		if(board[i]==-1)
			if(board[i+3]==0)
				return 0;
	}
		
	for(i=0;i<4;i++)
	{
		if(board[j[i]]==-1)
			if(board[j[i]+4]==1)
				return 0;
		if(board[k[i]]==-1)
			if(board[k[i]+2]==1)
				return 0;
	}

	
	
	printf("You win!\n\n");
	return 1;		
}


int CPUwinner(){

	int j[4]={4,5,7,8};
	int k[4]={3,4,6,7};
	int i=0,b=0;
	
	for(i=6;i<9;i++)
	{
		if(board[i]==-1)
		{
			printf("I win!\n\n");
			return -1;
		}
	}
	
	for(i=0;i<9;i++)
	{
		if(board[i]==1)
		{
			b++;
		}
	}

	if(b==0)
	{
		printf("I win!\n\n");
		return -1;
	}
	
	for(i=3;i<9;i++)
	{
		if(board[i]==1)
			if(board[i-3]==0)
				return 0;
	}
	
	for(i=0;i<4;i++)
	{
		if(board[j[i]]==1)
			if(board[j[i]-4]==-1)
				return 0;
		if(board[k[i]]==1)
			if(board[k[i]-2]==-1)
				return 0;
	}


	
	printf("I win!\n\n");
	return -1;
}

void statistic(int wins, int loss){

	int played=wins + loss;
	printf("You've won %d times, and I've won %d out of %d matches played!\n\n", wins, loss, played);
}

void playermove(){

	start:
	int s, e, t;
	printf("\nWhat is your move?\n");
	scanf("%d, %d",&s, &e);
	bool valid = legalmovescheck(e,s);
	
	if(valid==true){
			board[e-1]=1;
			board[s-1]=0;
		printboard();
		empty_stdin();
	}
	else
	{
		empty_stdin();
		goto start;
	} 
	
	win = winnerplayer();
}

int moves[19][4]={
	{24,25,36,0},
	{14,15,35,36},
	{15,35,36,47},
	{36,58,59,24},
	{15,35,36,0},
	{24,25,26,0},
	{26,57,58,0},
	{26,35,0,0},
	{47,48,0,0},
	{35,36,0,0},
	{35,36,0,0},
	{36,0,0,0},
	{47,58,0,0},
	{15,0,0,0},
	{26,47,0,0},
	{47,58,0,0},
	{35,36,47,0},
	{24,58,0,0},
	{15,47,0,0} };
	
int configs[19][9]={
	{-1, -1, -1, 1, 0, 0, 0, 1, 1},
	{-1, -1, -1, 0, 1, 0, 1, 0, 1},
	{-1, 0, -1, -1, 1, 0, 0, 0, 1},
	{0, -1, -1, 1, -1, 0, 0, 0, 1},
	{-1, 0, -1, 1, 1, 0, 0, 1, 0},
	{-1, -1, 0, 1, 0, 1, 0, 0, 1},
	{0, -1, -1, 0, -1, 1, 1, 0, 0},
	{0, -1, -1, -1, 1, 1, 1, 0, 0},
	{-1, 0, -1, -1, 0, 1, 0, 1, 0},
	{0, -1, -1, 0, 1, 0, 0, 0, 1},
	{0, -1, -1, 0, 1, 0, 1, 0, 0},
	{-1, 0, -1, 1, 0, 0, 0, 0, 1},
	{0, 0, -1, -1, -1, 1, 0, 0, 0},
	{-1, 0, 0, 1, 1, 1, 0, 0, 0},
	{0, -1, 0, -1, 1, 1, 0, 0, 0},
	{-1, 0, 0, -1, -1, 1, 0, 0, 0},
	{0, 0, -1, -1, 1, 0, 0, 0, 0},
	{0, -1, 0, 1, -1, 0, 0, 0, 0},
	{-1, 0, 0, -1, 1, 0, 0, 0, 0} };

int mirrormoves(int x){

	if(x==1)
	{
		x=3;
		return x;
	}
	if(x==3)
	{
		x=1;
		return x;
	}
	if(x==4)
	{
		x=6;
		return x;
	}
	if(x==6)
	{
		x=4;
		return x;
	}
	if(x==9)
	{
		x=7;
		return x;
	}
	if(x==7)
	{
		x=9;
		return x;
	}
}

void CPUmove(){

	int currentboard[9], mirrorcurrent[9],i,j,k=0,l=0,e,s;
	bool mirr;
	
	for(i=0;i<19;i++)
	{
		
		memcpy(currentboard, configs[i], 4*9);
		
		memcpy(mirrorcurrent, configs[i], 4*9);
		mirrorcurrent[0]=currentboard[2];
		mirrorcurrent[2]=currentboard[0];
		mirrorcurrent[3]=currentboard[5];
		mirrorcurrent[5]=currentboard[3];
		mirrorcurrent[6]=currentboard[8];
		mirrorcurrent[8]=currentboard[6];
		
		if(memcmp(currentboard, board, 4*9)==0)
		{
			mirr=false;
			break;
		}
		if(memcmp(mirrorcurrent, board, 4*9)==0)
		{
			
			mirr=true;
			break;
		}
	}
	
	for(j=0;j<4;j++)
		if(moves[i][j]!=0)
			k++;
	
	int strategylist[k];
	
	for(j=0;j<4;j++)
	{
		if(moves[i][j]!=0)
		{
			strategylist[l]=j;
			l++;	
		}
	}

	time_t t;
	srand((unsigned) time(&t));
	
	j=strategylist[(rand() % (k*100))/100];

	
	s=moves[i][j]/10;
	e=moves[i][j]%10;
	
	crrs=((i*10)+j);
	
	if(mirr==true)
	{
		board[mirrormoves(e)-1]=-1;
		board[mirrormoves(s)-1]=0;
		printf("\nI am going from %d to %d\n",mirrormoves(s), mirrormoves(e));
		sleep(1);
		printboard();
	}
	else
	{
		board[e-1]=-1;
		board[s-1]=0;
		printf("\nI am going from %d to %d\n", s, e);
		sleep(1);
		printboard();
	}
	
	
	win = CPUwinner();
}


int main(){

	int i, wins=0, loss=0;
	printf("To move enter a number on that board that has your pawn on it (W) and then a number on the board you wish to move it to. Enemy pawns are marked with (B)\ne.g. if you input 7, 4 you'll move your leftmost pawn one space up (forward)\n");
	printf("\nThe board looks like this:\n\t1 2 3\n\t4 5 6\n\t7 8 9\n\n");
	while(true){
	printboard();

		while(win !=-1)
		{
			playermove();
			sleep(1.5);
		
			if(win==1)
			{
				break;
			}
			CPUmove();
		}
	
		if(win==1)
		{
			wins++;
			moves[crrs/10][crrs%10]=0;
		}
		else 
			loss++;
		
		statistic(wins, loss);
		boardreset();
		win=0;
		sleep(2.5);
	}
}


