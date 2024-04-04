#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <Windows.h>
#include <time.h>

#define Screen_WIDTH 110
#define Screen_HEIGHT 26
#define Win_WIDTH 90 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Cursor_position;

char keys[10];	
int keyPos[10][2];	
int score; 

void Position_xy(int x, int y)
{
	Cursor_position.X = x;
	Cursor_position.Y = y;
	SetConsoleCursorPosition(console, Cursor_position);
}

void Set_cursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void Draw_border()
{  
	for(int i=0; i<=Screen_WIDTH; i++)
	{
	    Position_xy(i,0); cout<<"*"; 
		Position_xy(i,Screen_HEIGHT); cout<<"*";
	}
	
	for(int i=1; i<Screen_HEIGHT; i++)
	{
		Position_xy(0,i); cout<<"*";
		Position_xy(Screen_WIDTH,i); cout<<"*";
	}
	
	for(int i=1; i<Screen_HEIGHT; i++)
	{
		Position_xy(Win_WIDTH,i); cout<<"*";
	}
}

void Create_alphabet(int ind)
{
	keys[ind] = 65+rand()%25;
	keyPos[ind][0] = 2 + rand()%(Win_WIDTH-2);
	keyPos[ind][1] = 1;
}

void Draw_alphabet(int ind)
{
	if( keyPos[ind][0] != 0 )
	{
		Position_xy(keyPos[ind][0], keyPos[ind][1]);   cout<<keys[ind];  
	} 
}

void Erase_alphabet(int ind)
{
	if( keyPos[ind][0] != 0 )
	{
		Position_xy(keyPos[ind][0], keyPos[ind][1]);   cout<<" ";  
	}
}

void Reset_alphabet(int ind)
{
	Erase_alphabet(ind);
	Create_alphabet(ind);
}

void Gameover()
{
	system("cls");
	cout<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl;
	cout<<"\t\t\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t\t\tPress any key to go back to menu.";
	getch();
}

void Update_score()
{
	Position_xy(Win_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void Instructions()
{
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n On Left side you will see falling characters ";
	cout<<"\n You have to keep them away from touching floor";
	cout<<"\n Press respective key from keyboard to keep playing";
	cout<<"\n\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void Play()
{
	score = 0;
	for(int i=0; i<10; i++)
	{
		keyPos[i][0] = keyPos[i][1] = 1;	
	}
	 
	system("cls"); 
	Draw_border(); 
	Update_score();
	
	for(int i=0; i<10; i++)
		Create_alphabet(i); 
	
	Position_xy(Win_WIDTH + 5, 2);cout<<"Typing Tutor";
	Position_xy(Win_WIDTH + 6, 4);cout<<"----------";
	Position_xy(Win_WIDTH + 6, 6);cout<<"----------";
	
	Position_xy(38, 5);cout<<"Press any key to start";
	getch();
	Position_xy(38, 5);cout<<"                      ";
	
	while(1)
	{
		if(kbhit())
		{
			char ch = getch();
			for(int i=0; i<10; i++)
			{
				if( ch == keys[i] || ch-32 == keys[i] )
				{
					Reset_alphabet(i);
					score++;
					Update_score();
				}
			}
			
			if(ch==27)
			{
				break;
			}
		} 
		
		for(int i=0; i<10; i++)
			Draw_alphabet(i);  
			
		Sleep(300); 
		
		for(int i=0; i<10; i++)
		{
			Erase_alphabet(i);  
			keyPos[i][1] += 1;
			
			if( keyPos[i][1] >= Screen_HEIGHT )
			{
				Gameover();
				return;
			}
		}
	}
}

int main()
{
	Set_cursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do
	{
		system("cls");
		Position_xy(30,7); cout<<" -------------------------- "; 
		Position_xy(30,8); cout<<" |     TYPING  TUTOR      | "; 
		Position_xy(30,9); cout<<" --------------------------";
		Position_xy(30,11); cout<<"1. Start Game";
		Position_xy(30,12); cout<<"2. Instructions";	 
		Position_xy(30,13); cout<<"3. Quit";
		Position_xy(30,15); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') Play();
		else if( op=='2') Instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
