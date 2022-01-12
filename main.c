#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"

/*
Grzegorz Kodrzycki
Projekt w C na WDC
Zimowy 2021/22

Szachy na konsolę korzystające z dłuższej nota  cji szachowej
*/

int CzyjRuch = 1, enRank, enFile, prevRank = -1, prevFile = -1, Draw = 0;
int wKR = 7, wKF = 4, bKR = 0, bKF = 4;

bool enPas = false, CzyDraw = false;
char WhoseMove[2][10] = {"Bialy", "Czarny"};

char Move[10];
char kto;

int main()
{
    SetBoard();
    PrintBoard();
    printf("\nObecnie ruch ma: Bialy\n");
    FILE *f = fopen("PrzebiegPartii.txt","w+");
    fclose(f);
    ResetAttacked();

    while(strcmp(Move, "SURR"))
    {
		bool Done = false;

		scanf("\n%[^\n]%*c", Move);
		int dl = strlen(Move);

		if(!Draw && dl == 3)
		{
		    FindAttacked();
		    if(CzyjRuch%2 == 1)
		    {
		        if(ShortW() && !WhereBoard[7][5]->byBlack && !WhereBoard[7][6]->byBlack)
		        {
		            Done = true;
		            enPas = false;
		            Board2[7][6]->Figure = Board2[7][4]->Figure;
		            Board2[7][6]->IsFirst = false;
		            Board2[7][6]->IsFree = false;
		            Board2[7][6]->Kolor = Board2[7][4]->Kolor;

		            Board2[7][4]->Figure = '.';
		            Board2[7][4]->IsFirst = false;
		            Board2[7][4]->IsFree = true;
		            Board2[7][4]->Kolor = 'N';

		            Board2[7][5]->Figure = Board2[7][7]->Figure;
		            Board2[7][5]->IsFirst = false;
		            Board2[7][5]->IsFree = false;
		            Board2[7][5]->Kolor = Board2[7][7]->Kolor;

		            Board2[7][7]->Figure = '.';
		            Board2[7][7]->IsFirst = false;
		            Board2[7][7]->IsFree = true;
		            Board2[7][7]->Kolor = 'N';
		        }
		    }
		    else
		    {
		        if(ShortB() && !WhereBoard[0][5]->byWhite && !WhereBoard[0][6]->byWhite)
		        {
		            Done = true;
		            enPas = false;
		            Board2[0][6]->Figure = Board2[0][4]->Figure;
		            Board2[0][6]->IsFirst = false;
		            Board2[0][6]->IsFree = false;
		            Board2[0][6]->Kolor = Board2[0][4]->Kolor;

		            Board2[0][4]->Figure = '.';
		            Board2[0][4]->IsFirst = false;
		            Board2[0][4]->IsFree = true;
		            Board2[0][4]->Kolor = 'N';

		            Board2[0][5]->Figure = Board2[0][7]->Figure;
		            Board2[0][5]->IsFirst = false;
		            Board2[0][5]->IsFree = false;
		            Board2[0][5]->Kolor = Board2[0][7]->Kolor;

		            Board2[0][7]->Figure = '.';
		            Board2[0][7]->IsFirst = false;
		            Board2[0][7]->IsFree = true;
		            Board2[0][7]->Kolor = 'N';
		        }
		    }
		    FindAttacked();
		}
		if(!Draw && dl == 5 && Move[0] == 'O')
		{
		    FindAttacked();
		    if(CzyjRuch%2 == 1)
		    {
		        if(LongW() && !WhereBoard[7][2]->byBlack && !WhereBoard[7][3]->byBlack)
		        {
		            Done = true;
		            enPas = false;
		            Board2[7][2]->Figure = Board2[7][4]->Figure;
		            Board2[7][2]->IsFirst = false;
		            Board2[7][2]->IsFree = false;
		            Board2[7][2]->Kolor = Board2[7][4]->Kolor;

		            Board2[7][4]->Figure = '.';
		            Board2[7][4]->IsFirst = false;
		            Board2[7][4]->IsFree = true;
		            Board2[7][4]->Kolor = 'N';

		            Board2[7][3]->Figure = Board2[7][0]->Figure;
		            Board2[7][3]->IsFirst = false;
		            Board2[7][3]->IsFree = false;
		            Board2[7][3]->Kolor = Board2[7][0]->Kolor;

		            Board2[7][0]->Figure = '.';
		            Board2[7][0]->IsFirst = false;
		            Board2[7][0]->IsFree = true;
		            Board2[7][0]->Kolor = 'N';
		        }
		    }
		    else
		    {
		        if(LongB() && !WhereBoard[0][2]->byWhite && !WhereBoard[0][3]->byWhite)
		        {
		            Done = true;
		            enPas = false;
		            Board2[0][2]->Figure = Board2[0][4]->Figure;
		            Board2[0][2]->IsFirst = false;
		            Board2[0][2]->IsFree = false;
		            Board2[0][2]->Kolor = Board2[0][4]->Kolor;

		            Board2[0][4]->Figure = '.';
		            Board2[0][4]->IsFirst = false;
		            Board2[0][4]->IsFree = true;
		            Board2[0][4]->Kolor = 'N';

		            Board2[0][3]->Figure = Board2[0][0]->Figure;
		            Board2[0][3]->IsFirst = false;
		            Board2[0][3]->IsFree = false;
		            Board2[0][3]->Kolor = Board2[0][0]->Kolor;

		            Board2[0][0]->Figure = '.';
		            Board2[0][0]->IsFirst = false;
		            Board2[0][0]->IsFree = true;
		            Board2[0][0]->Kolor = 'N';
		        }
		    }
		}
		if(!Draw && dl == 5)
		{
		    int t_rank1 = 8 - ((int)Move[1] - 48), t_file1 = Wartosc(Move[0]), t_rank2 = 8 - ((int)Move[4] - 48), t_file2 = Wartosc(Move[3]);
		    if((Board[t_rank1][t_file1]->Figure == 'P' || Board[t_rank1][t_file1]->Figure == 'p') && CanPawn(t_rank1, t_file1, t_rank2, t_file2, CzyjRuch, enPas, enFile, enRank))
		    {
		        Ruch(t_rank1, t_file1, t_rank2, t_file2);
		        FindAttacked();
		        if(CzyjRuch%2 == 0) kto = 'W' ;
		        else                kto = 'B';
		        if(!IsCheck(kto, wKR, wKF, bKR, bKF))   Done = true;
		    }
		}
		if(!Draw && dl == 7)
		{

		    int t_rank1 = 8 - ((int)Move[3] - 48), t_file1 = Wartosc(Move[2]), t_rank2 = 8 - ((int)Move[6] - 48), t_file2 = Wartosc(Move[5]);
		         if(Move[0] == 'R' || Move[0] == 'r')
		         {
		            if(CanRook(t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto, wKR, wKF, bKR, bKF))
		                {
		                	Done = true;
		                	enPas = false;
		                }
		            }
		         }
		    else if(Move[0] == 'N' || Move[0] == 'n')
		    {
		            if(CanKnight(t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto, wKR, wKF, bKR, bKF))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'B' || Move[0] == 'b')
		    {
		            if(CanBishop(t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto, wKR, wKF, bKR, bKF))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'Q' || Move[0] == 'q')
		    {
		            if(CanQueen( t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto, wKR, wKF, bKR, bKF))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'K' || Move[0] == 'k')
		    {
		            if(CanKing(  t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0)
		                {
		                    kto = 'W';
		                    prevRank = bKR;
		                    prevFile = bKR;

		                    bKR = t_rank2;
		                    bKF = t_file2;
		                }
		                else
		                {
		                    kto = 'B';
		                    prevRank = wKR;
		                    prevFile = wKF;

		                    wKR = t_rank2;
		                    wKF = t_file2;
		                }
		                if(!IsCheck(kto, wKR, wKF, bKR, bKF))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		}

		if(Done)
		{
		    CopyBoard2To1();
		    PrintBoard();
		}
		if(IsCheck(kto, wKR, wKF, bKR, bKF))   printf("Jestes w szachu!\n");
		if(!strcmp(Move, "SURR"))
		{
		    printf("%s sie poddal\nWygral %s\n",WhoseMove[(CzyjRuch+1)%2], WhoseMove[CzyjRuch%2]);
		    break;
		}
		if(Draw == 1 && !strcmp(Move,"NO"))
        {
            Draw = 0;
            printf("Nie zgodzono sie na remis\n");
        }
		if(!strcmp(Move,"DRAW"))
		{
		    Draw++;
		    CzyDraw = true;
		    if(Draw == 2)
            {
                printf("REMIS!\n");
                break;
            }
		}
		if(kto == 'W') kto = 'B';
		else           kto = 'W';
		if(!CzyDraw && IsCheck(kto, wKR, wKF, bKR, bKF))
		{
		    if(CheckMate(kto, prevRank, prevFile, wKR, wKF, bKR, bKF))
		    {
		        printf("Szach i mat!\nWygral %s\n",WhoseMove[(CzyjRuch+1)%2]);
		        break;
		    }
		}
		if(!CzyDraw && !Done)
		{
		    CopyBoard1To2();
		    printf("To nie jest legalny ruch!\nWpisz nowy ruch\n");
		    if(prevFile != -1 && prevRank != -1)
		    {
		             if(kto == 'W')
		             {
		                 wKR = prevRank;
		                 wKF = prevFile;
		             }
		        else if(kto == 'B')
		        {
		                 bKR = prevRank;
		                 bKF = prevFile;
		        }
		    }
		}
		else if(!CzyDraw && Done)
		{
		    printf("\nObecnie ruch ma: %s\n", WhoseMove[CzyjRuch%2]);
		    CzyjRuch++;
		}
		if(Done)
        {
            FILE *f = fopen("PrzebiegPartii.txt","a");
		    fprintf(f,"%s\n", Move);
		    fclose(f);
        }
        if(!strcmp(Move,"NO"))
        {
            CzyDraw = false;
            PrintBoard();
            printf("\nObecnie ruch ma: %s\n", WhoseMove[(CzyjRuch+1)%2]);
        }
		ResetAttacked();
		prevFile = -1;
		prevRank = -1;
    }

    return 0;
}
