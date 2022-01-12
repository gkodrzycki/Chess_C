#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"

char *bP[] = {"♟"}, *bN[] = {"♞"}, *bB[] = {"♝"}, *bR[] = {"♜"}, *bQ[] = {"♛"}, *bK[] = {"♚"}, *wP[]={"♙"}, *wN[]={"♘"}, *wB[]={"♗"}, *wR[]={"♖"}, *wQ[]={"♕"}, *wK[]={"♔"};
char BeginingFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1";
char FILES[] = "ABCDEFGH";

Square *Board[8][8];
Square *Board2[8][8];
Attacked *WhereBoard[8][8];

void clearscr()

{
#if defined (_WIN32)
    system("cls");
#elif defined(unix) || (defined(APPLE) && defined(MACH__))
    system("clear");
#endif
}

void SetBoard()
{
    int i = 0, rank = 0, file = 0, temp;



    while(BeginingFen[i] != ' ')
    {
        temp = (int)BeginingFen[i] - 48;
        if(BeginingFen[i] == '/')
        {
            rank++;
            file = 0;
        }
        else
        {
            if(temp <= 8)
            {
                while(temp--)
                {
                    Square *P1 = malloc(sizeof(Square));
                    P1->Figure = '.';
                    P1->IsFree = true;
                    P1->IsFirst = true;
                    P1->Kolor = 'N';
                    Board[rank][file] = P1;
                    Board2[rank][file] = P1;

                    Attacked *P2 = malloc(sizeof(Attacked));
                    P2->byBlack = false;
                    P2->byWhite = false;
                    WhereBoard[rank][file] = P2;

                    file++;
                }
            }
            else
            {
                Square *P1 = malloc(sizeof(Square));
                P1->Figure = BeginingFen[i];
                P1->IsFree = false;
                P1->IsFirst = true;
                     if(rank == 0 || rank == 1)     P1->Kolor = 'B';
                else if(rank == 6 || rank == 7)     P1->Kolor = 'W';
                Board[rank][file] = P1;
                Board2[rank][file] = P1;

                Attacked *P2 = malloc(sizeof(Attacked));
                P2->byBlack = false;
                P2->byWhite = false;
                WhereBoard[rank][file] = P2;
            }
            file++;
        }
        i++;
    }
}
int Wartosc(char x)
{
                  if(x == 'a') return 0;
             else if(x == 'b') return 1;
             else if(x == 'c') return 2;
             else if(x == 'd') return 3;
             else if(x == 'e') return 4;
             else if(x == 'f') return 5;
             else if(x == 'g') return 6;
             else if(x == 'h') return 7;
    return -1;
}
void CopyBoard2To1()
{
    for(int rank = 0; rank < 8; rank++)
    {
        for(int file = 0; file < 8; file++)
        {
            Board[rank][file]->Figure  = Board2[rank][file]->Figure;
            Board[rank][file]->IsFirst = Board2[rank][file]->IsFirst;
            Board[rank][file]->IsFree  = Board2[rank][file]->IsFree;
            Board[rank][file]->Kolor   = Board2[rank][file]->Kolor;
        }
    }
}
void CopyBoard1To2()
{
    for(int rank = 0; rank < 8; rank++)
    {
        for(int file = 0; file < 8; file++)
        {
            Board2[rank][file]->Figure  = Board[rank][file]->Figure;
            Board2[rank][file]->IsFirst = Board[rank][file]->IsFirst;
            Board2[rank][file]->IsFree  = Board[rank][file]->IsFree;
            Board2[rank][file]->Kolor   = Board[rank][file]->Kolor;
        }
    }
}
void PrintBoard()
{
    clearscr();
    //system("clear"); //Linux
    //system(cls); //Windows
    int i = 0;
    for(int rank = 0; rank < 8; rank++)
    {
        printf("%d ", 8 - rank);
        for(int file = 0; file < 8; file++)
        {
                 if(Board[rank][file]->Figure != '.')
                 {

                	if(Board[rank][file]->Figure == 'p')	printf("%s ",*wP);
                	if(Board[rank][file]->Figure == 'r')	printf("%s ",*wR);
                	if(Board[rank][file]->Figure == 'n')	printf("%s ",*wN);
                	if(Board[rank][file]->Figure == 'b')	printf("%s ",*wB);
                	if(Board[rank][file]->Figure == 'q')	printf("%s ",*wQ);
                	if(Board[rank][file]->Figure == 'k')	printf("%s ",*wK);
                	if(Board[rank][file]->Figure == 'P')	printf("%s ",*bP);
                	if(Board[rank][file]->Figure == 'R')	printf("%s ",*bR);
                	if(Board[rank][file]->Figure == 'N')	printf("%s ",*bN);
                	if(Board[rank][file]->Figure == 'B')	printf("%s ",*bB);
                	if(Board[rank][file]->Figure == 'Q')	printf("%s ",*bQ);
                	if(Board[rank][file]->Figure == 'K')	printf("%s ",*bK);
                 }


            else if((rank%2 == 0 && file%2 == 0) || (rank%2 == 1 && file%2 == 1))  printf("⬜");
            else                                                                   printf("⬛");
            i++;
        }
       printf("\n");
    }
    printf("  ");
    for(int j = 0; j < 8; j++) printf("%c ",FILES[j]);
    printf("\n");
}
void ResetAttacked()
{
    for(int rank = 0; rank < 8; rank++)
    {
        for(int file = 0; file < 8; file++)
        {
            WhereBoard[rank][file]->byBlack = false;
            WhereBoard[rank][file]->byWhite = false;
        }
    }
}
void Ruch(int t_rank1, int t_file1, int t_rank2, int t_file2)
{
    Square *P1 = malloc(sizeof(Square));
	P1->IsFree = false;
	P1->Figure = Board2[t_rank1][t_file1]->Figure;
	P1->IsFirst = false;
	P1->Kolor = Board2[t_rank1][t_file1]->Kolor;
	Board2[t_rank2][t_file2] = P1;

	Square *P2 = malloc(sizeof(Square));
	P2->IsFree = true;
	P2->Figure = '.';
	P2->IsFirst = false;
	P2->Kolor = 'N';
	Board2[t_rank1][t_file1] = P2;
}
bool CzyMozna(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    if((rank1 < 0 || rank1 > 7) || (rank2 < 0 || rank2 > 7) || (file1 < 0 || file1 > 7) || (file2 < 0 || file2 > 7))    return false;
	if(Board[rank1][file1]->Kolor == 'W' && CzyjRuch%2 == 0)    return false;
	if(Board[rank1][file1]->Kolor == 'B' && CzyjRuch%2 == 1)    return false;
	return true;
}
bool CzyPuste(int rank1, int file1, int rank2, int file2)
{
         if( Board[rank1][file1]->Kolor == 'N')   return false;
         if( Board[rank2][file2]->IsFree)         return true;
	else if(!Board[rank2][file2]->IsFree && (Board[rank1][file1]->Kolor != Board[rank2][file2]->Kolor))
    {
         if((Board[rank1][file1]->Figure == 'P' || Board[rank1][file1]->Figure == 'p') && file1 == file2)  return false;
         else return true;
    }
	return false;
}
void Upgrade(int t_rank1, int t_file1)
{
    char co[1000];
    char ans;
	printf("Na co chcesz awansowac pionka?\n");
	scanf("\n%s", co);
	if(Board[t_rank1][t_file1]->Kolor == 'W')
	{
        for(unsigned int i = 0; i < strlen(co); i++)
        {
            if(i == 0)
            {
                ans = toupper(co[i]);
                break;
            }
        }
        if(ans == 'R' || ans == 'N' || ans == 'B' || ans == 'Q')
        {
            Square *P2 = malloc(sizeof(Square));
		    P2->IsFree = false;
		    P2->Figure = ans;
		    P2->IsFirst = false;
		    P2->Kolor = 'W';
		    Board2[t_rank1][t_file1] = P2;
        }
        else
        {
            printf("Zla figura, sprobuj ponownie\n");
            Upgrade(t_rank1, t_file1);
        }
    }
    else
    {
        for(unsigned int i = 0; i < strlen(co); i++)
        {
            if(i == 0)
            {
                ans = tolower(co[i]);
                break;
            }
        }
        if(ans == 'r' || ans == 'n' || ans == 'b' || ans == 'q')
        {
            Square *P2 = malloc(sizeof(Square));
            P2->IsFree = false;
            P2->Figure = ans;
            P2->IsFirst = false;
            P2->Kolor = 'B';
            Board2[t_rank1][t_file1] = P2;
        }
        else
        {
            printf("Zla figura, sprobuj ponownie\n");
            Upgrade(t_rank1, t_file1);
        }
    }
}
