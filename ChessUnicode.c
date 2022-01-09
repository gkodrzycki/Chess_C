#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/*
Grzegorz Kodrzycki
Projekt w C na WDC
Zimowy 2021/22

Szachy na konsolę korzystające z dłuższej notacji szachowej
*/

typedef struct
{
    char Figure;
    bool IsFree;
    bool IsFirst;
    char Kolor;

}Square;
typedef struct
{
    bool byWhite;
    bool byBlack;
}Attacked;

Square *Board[8][8];
Square *Board2[8][8];
Attacked *WhereBoard[8][8];
int CzyjRuch = 1, enRank, enFile, prevRank = -1, prevFile = -1, wKR = 7, wKF = 4, bKR = 0, bKF = 4, Draw = 0;
bool enPas = false, CzyDraw = false;

char *bP[] = {"♟"}, *bN[] = {"♞"}, *bB[] = {"♝"}, *bR[] = {"♜"}, *bQ[] = {"♛"}, *bK[] = {"♚"}, *wP[]={"♙"}, *wN[]={"♘"}, *wB[]={"♗"}, *wR[]={"♖"}, *wQ[]={"♕"}, *wK[]={"♔"};
char BeginingFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1";
char FILES[] = "ABCDEFGH";
char WhoseMove[2][10] = {"Bialy", "Czarny"};
char Move[10];
char kto;

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
void PrintBoard()
{
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
void FindRook(int rank, int file, char kol)
	{
	    int rank1 = rank-1, file1 = file;
	    while(rank1 >= 0)
	    {
            if(rank1 < 0 || rank1 > 7)          break;

                 if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
            else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

            if(!Board2[rank1][file1]->IsFree)    break;
            rank1--;
	    }

	    rank1 = rank+1, file1 = file;
	    while(rank1 < 8)
	    {
             if(rank1 < 0 || rank1 > 7)          break;

                  if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
             else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

             if(!Board2[rank1][file1]->IsFree)    break;
             rank1++;
	    }

	    rank1 = rank, file1 = file-1;
	    while(file1 >= 0)
	    {
             if(file1 < 0 || file1 > 7)          break;

                  if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
             else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

             if(!Board2[rank1][file1]->IsFree)    break;
             file1--;
	    }

	    rank1 = rank, file1 = file+1;
	    while(file1 < 8)
	    {
             if(file1 < 0 || file1 > 7)          break;

                  if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
             else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

             if(!Board2[rank1][file1]->IsFree)    break;
             file1++;
	    }
	}
void FindKnight(int rank1, int file1, char kol)
{
    if(rank1-2 >= 0 && rank1-2 < 8 && file1+1 >= 0 && file1+1 < 8)
    {
             if(kol == 'W')  WhereBoard[rank1-2][file1+1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1-2][file1+1]->byBlack = true;
    }
    if(rank1-1 >= 0 && rank1-1 < 8 && file1+2 >= 0 && file1+2 < 8)
	{
		     if(kol == 'W')  WhereBoard[rank1-1][file1+2]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1-1][file1+2]->byBlack = true;
    }
    if(rank1+1 >= 0 && rank1+1 < 8 && file1+2 >= 0 && file1+2 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1+1][file1+2]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1+1][file1+2]->byBlack = true;
    }
    if(rank1+2 >= 0 && rank1+2 < 8 && file1+1 >= 0 && file1+1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1+2][file1+1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1+2][file1+1]->byBlack = true;
    }
    if(rank1+2 >= 0 && rank1+2 < 8 && file1-1 >= 0 && file1-1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1+2][file1-1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1+2][file1-1]->byBlack = true;
    }
    if(rank1+1 >= 0 && rank1+1 < 8 && file1-2 >= 0 && file1-2 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1+1][file1-2]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1+1][file1-2]->byBlack = true;
    }
    if(rank1-1 >= 0 && rank1-1 < 8 && file1-2 >= 0 && file1-2 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1-1][file1-2]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1-1][file1-2]->byBlack = true;
    }
    if(rank1-2 >= 0 && rank1-2 < 8 && file1-1 >= 0 && file1-1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank1-2][file1-1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1-2][file1-1]->byBlack = true;
    }
}
void FindBishop(int rank, int file, char kol)
{
    int rank1 = rank-1, file1 = file+1;
    while(true)
    {
        if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)          break;

		     if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

        if(!Board2[rank1][file1]->IsFree)    break;
		rank1--;
		file1++;
    }

    rank1 = rank+1, file1 = file+1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		     if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

		if(!Board2[rank1][file1]->IsFree)    break;
		rank1++;
		file1++;
    }

    rank1 = rank-1, file1 = file-1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		     if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

		if(!Board2[rank1][file1]->IsFree)    break;
		file1--;
		rank1--;
    }

    rank1 = rank+1, file1 = file-1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		     if(kol == 'W')  WhereBoard[rank1][file1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank1][file1]->byBlack = true;

		if(!Board2[rank1][file1]->IsFree)    break;
		file1--;
		rank1++;
    }
}
void FindQueen(int rank, int file, char kol)
{
    FindBishop(rank, file, kol);
      FindRook(rank, file, kol);
}
void FindKing(int rank, int file, char kol)
{
    if(rank-1 >= 0 && rank-1 < 8 && file-1 >= 0 && file-1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank-1][file-1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank-1][file-1]->byBlack = true;
    }
    if(rank-1 >= 0 && rank-1 < 8 && file >= 0 && file < 8)
    {
		     if(kol == 'W')  WhereBoard[rank-1][file]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank-1][file]->byBlack = true;
    }
    if(rank-1 >= 0 && rank-1 < 8 && file+1 >= 0 && file+1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank-1][file+1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank-1][file+1]->byBlack = true;
    }
    if(rank >= 0 && rank < 8 && file+1 >= 0 && file+1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank][file+1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank][file+1]->byBlack = true;
    }
    if(rank+1 >= 0 && rank+1 < 8 && file+1 >= 0 && file+1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank+1][file+1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank+1][file+1]->byBlack = true;
    }
    if(rank+1 >= 0 && rank+1 < 8 && file >= 0 && file < 8)
    {
		     if(kol == 'W')  WhereBoard[rank+1][file]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank+1][file]->byBlack = true;
    }
    if(rank+1 >= 0 && rank+1 < 8 && file-1 >= 0 && file-1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank+1][file-1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank+1][file-1]->byBlack = true;
    }
    if(rank >= 0 && rank < 8 && file-1 >= 0 && file-1 < 8)
    {
		     if(kol == 'W')  WhereBoard[rank][file-1]->byWhite = true;
		else if(kol == 'B')  WhereBoard[rank][file-1]->byBlack = true;
    }
}
void FindAttacked()
{
    for(int rank = 0; rank < 8; rank++)
    {
		for(int file = 0; file < 8; file++)
		{

                 if(Board2[rank][file]->Figure == 'P')
                 {
                    if(rank-1 >= 0 && rank-1 < 8 && file-1 >= 0 && file-1 < 8)  WhereBoard[rank-1][file-1]->byWhite = true;
                    if(rank-1 >= 0 && rank-1 < 8 && file+1 >= 0 && file+1 < 8)  WhereBoard[rank-1][file+1]->byWhite = true;
                 }
            else if(Board2[rank][file]->Figure == 'R' || Board2[rank][file]->Figure == 'r')     FindRook(rank, file, Board2[rank][file]->Kolor);
            else if(Board2[rank][file]->Figure == 'N' || Board2[rank][file]->Figure == 'n')   FindKnight(rank, file, Board2[rank][file]->Kolor);
            else if(Board2[rank][file]->Figure == 'B' || Board2[rank][file]->Figure == 'b')   FindBishop(rank, file, Board2[rank][file]->Kolor);
            else if(Board2[rank][file]->Figure == 'Q' || Board2[rank][file]->Figure == 'q')
            {
                FindBishop(rank, file, Board2[rank][file]->Kolor);
                  FindRook(rank, file, Board2[rank][file]->Kolor);
            }
            else if(Board2[rank][file]->Figure == 'K' || Board2[rank][file]->Figure == 'k')   FindKing(rank, file, Board2[rank][file]->Kolor);
            else if(Board2[rank][file]->Figure == 'p')
            {
                if(rank+1 >= 0 && rank+1 < 8 && file-1 >= 0 && file-1 < 8)  WhereBoard[rank+1][file-1]->byBlack = true;
                if(rank+1 >= 0 && rank+1 < 8 && file+1 >= 0 && file+1 < 8)  WhereBoard[rank+1][file+1]->byBlack = true;
            }
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
bool CzyMozna(int rank1, int file1, int rank2, int file2)
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
bool CanPawn(int t_rank1, int t_file1, int t_rank2, int t_file2)
{
    if(!CzyMozna(t_rank1, t_file1, t_rank2, t_file2))   return false;
    if(!CzyPuste(t_rank1, t_file1, t_rank2, t_file2))   return false;
	if(t_rank1 - t_rank2 == 2 || t_rank1 - t_rank2 == -2)
        if(!Board[t_rank1][t_file1]->IsFirst)           return false;
	if(Board[t_rank1][t_file1]->Kolor == 'W' && t_rank1 < t_rank2)  return false;
    if(Board[t_rank1][t_file1]->Kolor == 'B' && t_rank1 > t_rank2)  return false;
	if(t_file1 != t_file2)
    {
        if(Board[t_rank1][t_file1]->Kolor == 'W')
		{
		    if(t_file1 + 1 == t_file2)
		    {
		        if(t_rank1-1 == t_rank2)
		        {
		            if(enPas)
		            {
		                if(t_rank2 == enRank && t_file2 == enFile)
		                {
		                    Ruch(t_rank1, t_file1, enRank, enFile);
		                    CopyBoard1To2();
		                    Square *P2 = malloc(sizeof(Square));
		                    P2->IsFree = true;
		                    P2->Figure = '.';
		                    P2->IsFirst = false;
		                    P2->Kolor = 'N';
		                    Board2[enRank+1][enFile] = P2;

		                    enPas = false;
		                    return true;
		                }
		            }
		            if(!(Board[t_rank1][t_file1]->Kolor != Board[t_rank2][t_file2]->Kolor && Board[t_rank2][t_file2]->Kolor != 'N')) return false;
		        }
		    }
		    if(t_file1 - 1 == t_file2)
		    {
		        if(t_rank1-1 == t_rank2)
		        {
		            if(enPas)
		            {
		                if(t_rank2 == enRank && t_file2 == enFile)
		                {
		                    Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                    CopyBoard1To2();
		                    Square *P2 = malloc(sizeof(Square));
		                    P2->IsFree = true;
		                    P2->Figure = '.';
		                    P2->IsFirst = false;
		                    P2->Kolor = 'N';
		                    Board2[enRank+1][enFile] = P2;

		                    enPas = false;
		                    return true;
		                }
		            }
		            if(!(Board[t_rank1][t_file1]->Kolor != Board[t_rank2][t_file2]->Kolor && Board[t_rank2][t_file2]->Kolor != 'N'))   return false;
		        }
		    }
		}
		else if(Board[t_rank1][t_file1]->Kolor == 'B')
		{
		    if(t_file1 + 1 == t_file2)
		    {
		        if(t_rank1+1 == t_rank2)
		        {
		            if(enPas)
		            {
		                if(t_rank2 == enRank && t_file2 == enFile)
		                {
		                    Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                    CopyBoard1To2();
		                    Square *P2 = malloc(sizeof(Square));
		                    P2->IsFree = true;
		                    P2->Figure = '.';
		                    P2->IsFirst = false;
		                    P2->Kolor = 'N';
		                    Board2[enRank-1][enFile] = P2;
		                    enPas = false;
		                    return true;
		                }
		            }
		            if(!(Board[t_rank1][t_file1]->Kolor != Board[t_rank2][t_file2]->Kolor && Board[t_rank2][t_file2]->Kolor != 'N'))   return false;
		        }
		    }
		    if(t_file1 - 1 == t_file2)
		    {
		        if(t_rank1+1 == t_rank2)
		        {
		            if(enPas)
		            {
		                if(t_rank2 == enRank && t_file2 == enFile)
		                {
		                    Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                    CopyBoard1To2();
		                    Square *P2 = malloc(sizeof(Square));
		                    P2->IsFree = true;
		                    P2->Figure = '.';
		                    P2->IsFirst = false;
		                    P2->Kolor = 'N';
		                    Board2[enRank-1][enFile] = P2;
		                    enPas = false;
		                    return true;
		                }
		            }
		            if(!(Board[t_rank1][t_file1]->Kolor != Board[t_rank2][t_file2]->Kolor && Board[t_rank2][t_file2]->Kolor != 'N'))   return false;
		        }
		    }
		}
	    }

	    if(t_rank2 == 0 || t_rank2 == 7)    Upgrade(t_rank1, t_file1);

	    enPas = false;
	    if(t_rank1 - t_rank2 == 2)
	    {
		enRank = t_rank2 + 1;
		enFile = t_file1;
		enPas = true;
	    }
	    if(t_rank1 - t_rank2 == -2)
	    {
		enRank = t_rank2 - 1;
		enFile = t_file1;
		enPas = true;
	    }
	    return true;
}
bool CanRook(int rank1, int file1, int rank2, int file2)
{
    if(!CzyMozna(rank1, file1, rank2, file2))   return false;
    if(!CzyPuste(rank1, file1, rank2, file2))   return false;
    if(rank1 == rank2)
    {
		if(file1 < file2)
		{
		    for(int file = file1+1; file <= file2; file++)
		    {
		        if(!Board[rank1][file]->IsFree) return file == file2;
		        else if(file == file2)          return file==file2;
		    }
		}
		else
		{
		    for(int file = file1-1; file >= file2; file--)
		    {
		        if(!Board[rank1][file]->IsFree) return file==file2;
		        else if(file == file2)          return file==file2;
		    }
		}
    }
    if(file1 == file2)
    {
		if(rank1 < rank2)
		{
		    for(int rank = rank1+1; rank <= rank2; rank++)
		    {
		        if(!Board[rank][file1]->IsFree) return rank == rank2;
		        else if(rank == rank2)          return rank == rank2;
		    }
		}
		else
		{
		    for(int rank = rank1-1; rank >= rank2; rank--)
		    {
		        if(!Board[rank][file1]->IsFree) return rank == rank2;
		        else if(rank == rank2)          return rank == rank2;
		    }
		}
    }
    return false;
}
bool CanBishop(int rank1, int file1, int rank2, int file2)
{
    if(!CzyMozna(rank1, file1, rank2, file2))   return false;
    if(!CzyPuste(rank1, file1, rank2, file2))   return false;

    int rank = rank1, file = file1;
    while((rank >= 0 && rank < 8) && (file >= 0 && file < 8))
    {
		rank--;
		file++;
		if(((rank >= 0 && rank < 8) && (file >= 0 && file < 8)) && !Board[rank][file]->IsFree)
		{
		        if(rank == rank2 && file == file2)  return true;
		        else                                break;
		}
		if(rank == rank2 && file == file2)  return true;
    }

    rank = rank1, file = file1;
    while((rank >= 0 && rank < 8) && (file >= 0 && file < 8))
    {
		rank--;
		file--;
		if(((rank >= 0 && rank < 8) && (file >= 0 && file < 8)) && !Board[rank][file]->IsFree)
		{
		        if(rank == rank2 && file == file2)  return true;
		        else                                break;
		}
		if(rank == rank2 && file == file2)  return true;
    }

    rank = rank1, file = file1;
    while((rank >= 0 && rank < 8) && (file >= 0 && file < 8))
    {
		rank++;
		file++;
		if(((rank >= 0 && rank < 8) && (file >= 0 && file < 8)) && !Board[rank][file]->IsFree)
		{
		        if(rank == rank2 && file == file2)  return true;
		        else                                break;
		}
		if(rank == rank2 && file == file2)  return true;
    }

    rank = rank1, file = file1;
    while((rank >= 0 && rank < 8) && (file >= 0 && file < 8))
    {
		rank++;
		file--;
		if(((rank >= 0 && rank < 8) && (file >= 0 && file < 8)) && !Board[rank][file]->IsFree)
		{
		        if(rank == rank2 && file == file2)  return true;
		        else                                break;
		}
		if(rank == rank2 && file == file2)  return true;
    }
    return false;
}
bool CanKnight(int rank1, int file1, int rank2, int file2)
{
    if(!CzyMozna(rank1, file1, rank2, file2))   return false;
    if(!CzyPuste(rank1, file1, rank2, file2))   return false;

    if((rank2 == rank1-2 && file2 == file1+1) && Board[rank1-2][file1+1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1-1 && file2 == file1+2) && Board[rank1-1][file1+2]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+1 && file2 == file1+2) && Board[rank1+1][file1+2]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+2 && file2 == file1+1) && Board[rank1+2][file1+1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+2 && file2 == file1-1) && Board[rank1+2][file1-1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+1 && file2 == file1-2) && Board[rank1+1][file1-2]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1-1 && file2 == file1-2) && Board[rank1-1][file1-2]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1-2 && file2 == file1-1) && Board[rank1-2][file1-1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    return false;
}
bool CanQueen(int rank1, int file1, int rank2, int file2)
{
    return (CanBishop(rank1, file1, rank2, file2) || CanRook(rank1, file1, rank2, file2));
}
bool IsCheck(char kto)
{
    if(kto == 'B')
        if(WhereBoard[wKR][wKF]->byBlack) return true;
    if(kto == 'W')
        if(WhereBoard[bKR][bKF]->byWhite) return true;
    return false;
}
bool CanKing(int rank1, int file1, int rank2, int file2)
{
    if(!CzyMozna(rank1, file1, rank2, file2))   return false;
    if(!CzyPuste(rank1, file1, rank2, file2))   return false;

    if((rank2 == rank1-1 && file2 == file1-1) && Board[rank1-1][file1-1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1-1 && file2 == file1)   && Board[rank1-1][file1  ]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1-1 && file2 == file1+1) && Board[rank1-1][file1+1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1   && file2 == file1-1) && Board[rank1  ][file1-1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1   && file2 == file1+1) && Board[rank1  ][file1+1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+1 && file2 == file1-1) && Board[rank1+1][file1-1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+1 && file2 == file1  ) && Board[rank1+1][file1  ]->Kolor != Board[rank1][file1]->Kolor)   return true;
    if((rank2 == rank1+1 && file2 == file1+1) && Board[rank1+1][file1+1]->Kolor != Board[rank1][file1]->Kolor)   return true;
    return false;
}
bool LongW()
{
    if(!IsCheck('B') && Board[7][1]->IsFree && Board[7][2]->IsFree && Board[7][3]->IsFree && Board[7][0]->IsFirst && Board[7][4]->IsFirst)   return true;
    return false;
}
bool ShortW()
{
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
bool LongB()
{
    if(!IsCheck('W') && Board[0][1]->IsFree && Board[0][2]->IsFree && Board[0][3]->IsFree && Board[0][0]->IsFirst && Board[0][4]->IsFirst)   return true;
    return false;
}
void ShortB()
{
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
bool RookMate(int rank, int file, char kto)
{
    int rank1 = rank-1, file1 = file;
    while(rank1 >= 0)
    {
        if(rank1 < 0 || rank1 > 7)          break;

        Ruch(rank, file, rank1, file1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }

        if(!Board2[rank1][file1]->IsFree)    break;
        rank1--;
    }

    rank1 = rank+1, file1 = file;
	while(rank1 < 8)
    {
        if(rank1 < 0 || rank1 > 7)          break;

        Ruch(rank, file, rank1, file1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
        if(!Board2[rank1][file1]->IsFree)    break;
        rank1++;
    }

    rank1 = rank, file1 = file-1;
    while(file1 >= 0)
    {
        if(file1 < 0 || file1 > 7)          break;

        Ruch(rank, file, rank1, file1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }

        if(!Board2[rank1][file1]->IsFree)    break;
		file1--;
    }

    rank1 = rank, file1 = file+1;
    while(file1 < 8)
    {
        if(file1 < 0 || file1 > 7)          break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
		if(!Board2[rank1][file1]->IsFree)    break;
		file1++;
    }
    return false;
}
bool KnightMate(int rank, int file, char kto)
{
    if(rank-2 >= 0 && rank-2 < 8 && file+1 >= 0 && file+1 < 8)
    {
        Ruch(rank, file, rank-2, file+1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank-1 >= 0 && rank-1 < 8 && file+2 >= 0 && file+2 < 8)
    {
        Ruch(rank, file, rank-1, file+2);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank+1 >= 0 && rank+1 < 8 && file+2 >= 0 && file+2 < 8)
    {
        Ruch(rank, file, rank+1, file+2);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank+2 >= 0 && rank+2 < 8 && file+1 >= 0 && file+1 < 8)
    {
        Ruch(rank, file, rank+2, file+1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank+2 >= 0 && rank+2 < 8 && file-1 >= 0 && file-1 < 8)
    {
        Ruch(rank, file, rank+2, file-2);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank+1 >= 0 && rank+1 < 8 && file-2 >= 0 && file-2 < 8)
    {
        Ruch(rank, file, rank+1, file-2);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank-1 >= 0 && rank-1 < 8 && file-2 >= 0 && file-2 < 8)
    {
        Ruch(rank, file, rank-1, file-2);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
    if(rank-2 >= 0 && rank-2 < 8 && file-1 >= 0 && file-1 < 8)
    {
        Ruch(rank, file, rank-2, file-1);
        FindAttacked();
        if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
    }
return false;
}
bool BishopMate(int rank, int file, char kto)
{
    int rank1 = rank-1, file1 = file+1;
    while(true)
    {
        if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)          break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
		if(!Board2[rank1][file1]->IsFree)    break;
		rank1--;
		file1++;
    }

    rank1 = rank+1, file1 = file+1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
		if(!Board2[rank1][file1]->IsFree)    break;
		rank1++;
		file1++;
    }

    rank1 = rank-1, file1 = file-1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
		if(!Board2[rank1][file1]->IsFree)    break;
		file1--;
		rank1--;
    }

    rank1 = rank+1, file1 = file-1;
    while(true)
    {
		if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)    break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto))
        {
            CopyBoard1To2();
            ResetAttacked();
            return true;
        }
        else
        {
            CopyBoard1To2();
            ResetAttacked();
        }
		if(!Board2[rank1][file1]->IsFree)    break;
		file1--;
		rank1++;
    }
    return false;
}
bool KingMate(int rank, int file, char kto)
{
    if(rank-1 >= 0 && rank-1 < 8 && file-1 >= 0 && file-1 < 8)
    {
        if(Board2[rank-1][file-1]->IsFree || Board2[rank-1][file-1]->Kolor != Board2[rank][file]->Kolor)
        {

            Ruch(rank, file, rank-1, file-1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank-1;
                wKF  = file-1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank-1;
                bKF  = file-1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank-1 >= 0 && rank-1 < 8 && file >= 0 && file < 8)
    {
        if(Board2[rank-1][file]->IsFree || Board2[rank-1][file]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank-1, file);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank-1;
                wKF  = file;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank-1;
                bKF  = file;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank-1 >= 0 && rank-1 < 8 && file+1 >= 0 && file+1 < 8)
    {
        if(Board2[rank-1][file+1]->IsFree || Board2[rank-1][file+1]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank-1, file+1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank-1;
                wKF  = file+1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank-1;
                bKF  = file+1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank >= 0 && rank < 8 && file+1 >= 0 && file+1 < 8)
    {
        if(Board2[rank][file+1]->IsFree || Board2[rank][file+1]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank, file+1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank;
                wKF  = file+1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank;
                bKF  = file+1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank+1 >= 0 && rank+1 < 8 && file+1 >= 0 && file+1 < 8)
    {
        if(Board2[rank+1][file+1]->IsFree || Board2[rank+1][file+1]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank+1, file+1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank+1;
                wKF  = file+1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank+1;
                bKF  = file+1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank+1 >= 0 && rank+1 < 8 && file >= 0 && file < 8)
    {
        if(Board2[rank+1][file]->IsFree || Board2[rank+1][file]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank+1, file);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank+1;
                wKF  = file;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank+1;
                bKF  = file;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank+1 >= 0 && rank+1 < 8 && file-1 >= 0 && file-1 < 8)
    {
        if(Board2[rank+1][file-1]->IsFree || Board2[rank+1][file-1]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank+1, file-1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank+1;
                wKF  = file-1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank+1;
                bKF  = file-1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF  = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
    if(rank >= 0 && rank < 8 && file-1 >= 0 && file-1 < 8)
    {
        if(Board2[rank][file-1]->IsFree || Board2[rank][file-1]->Kolor != Board2[rank][file]->Kolor)
        {
            Ruch(rank, file, rank, file-1);
            if(kto == 'B')
            {
                prevRank = wKR;
                prevFile = wKF;
                wKR  = rank;
                wKF  = file-1;
            }
            else
            {
                prevRank = bKR;
                prevFile = bKF;
                bKR  = rank;
                bKF  = file-1;
            }
            FindAttacked();
            if(!IsCheck(kto))
            {
                CopyBoard1To2();
                ResetAttacked();
                return true;
            }
            else
            {
                CopyBoard1To2();
                ResetAttacked();
            }
            if(kto == 'B')
            {
                wKR  = prevRank;
                wKF = prevFile;
            }
            else
            {
                bKR  = prevRank;
                bKF  = prevFile;
            }
        }
    }
return false;
}
bool CheckMate(char kto)
{
    ResetAttacked();
    if(kto == 'B')
    {
        for(int rank = 0; rank < 8; rank++)
		{
		    for(int file = 0; file < 8; file++)
		    {
		        if(Board2[rank][file]->Kolor == 'W')
		        {
		            if(Board2[rank][file]->Figure == 'P')
		            {
		                if(rank-1 >= 0 && rank-1 < 8 && file-1 >= 0 && file-1 < 8 && Board2[rank-1][file-1]->Kolor == 'B')
		                {
		                    Ruch(rank, file, rank-1, file-1);
		                    FindAttacked();
		                    if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
		                }

		                if(rank-1 >= 0 && rank-1 < 8 && file+1 >= 0 && file+1 < 8 && Board2[rank-1][file+1]->Kolor == 'B')
		                {
		                    Ruch(rank, file, rank-1, file+1);
		                    FindAttacked();
		                    if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
		                }

		                if(rank-1 >= 0 && rank-1 < 8 && file >= 0 && file < 8 && Board2[rank-1][file]->IsFree)
		                {
		                    Ruch(rank, file, rank-1, file);
		                    FindAttacked();
		                    if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
		                }

		                if(rank-2 >= 0 && rank-2 < 8 && file >= 0 && file < 8 && Board2[rank][file]->IsFirst && Board2[rank-2][file]->IsFree && Board2[rank-1][file]->IsFree)
		                {
		                    Ruch(rank, file, rank-2, file);
		                    FindAttacked();
		                    if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
		                }
		        }
		        else if(Board2[rank][file]->Figure == 'R' && RookMate  (rank, file, kto))   return false;
		        else if(Board2[rank][file]->Figure == 'N' && KnightMate(rank, file, kto))   return false;
		        else if(Board2[rank][file]->Figure == 'B' && BishopMate(rank, file, kto))   return false;
		        else if(Board2[rank][file]->Figure == 'Q' &&(RookMate  (rank, file, kto) || BishopMate(rank, file, kto)))  return false;
		        else if(Board2[rank][file]->Figure == 'K' && KingMate  (rank, file, kto))   return false;
		    }
          }
      }
    }
    else if(kto == 'W')
    {
        for(int rank = 0; rank < 8; rank++)
        {
            for(int file = 0; file < 8; file++)
            {
                if(Board2[rank][file]->Kolor == 'B')
                {
                    if(Board2[rank][file]->Figure == 'p')
                    {
                        if(rank+1 >= 0 && rank+1 < 8 && file-1 >= 0 && file-1 < 8 && Board2[rank+1][file-1]->Kolor == 'W')
                        {
                            Ruch(rank, file, rank+1, file-1);
                            FindAttacked();
                            if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
                        }

                        if(rank+1 >= 0 && rank+1 < 8 && file+1 >= 0 && file+1 < 8 && Board2[rank+1][file+1]->Kolor == 'W')
                        {
                            Ruch(rank, file, rank+1, file+1);
                            FindAttacked();
                            if(!IsCheck(kto))
                            {
                                return false;
                                CopyBoard1To2();
                                ResetAttacked();
                            }
                        }

                        if(rank+1 >= 0 && rank+1 < 8 && file >= 0 && file < 8 && Board2[rank+1][file]->IsFree)
                        {
                            Ruch(rank, file, rank+1, file);
                            FindAttacked();
                            if(!IsCheck(kto))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
                        }

		                    if(rank+2 >= 0 && rank+2 < 8 && file >= 0 && file < 8 && Board2[rank][file]->IsFirst && Board2[rank+2][file]->IsFree && Board2[rank+1][file]->IsFree)
		                    {
		                        Ruch(rank, file, rank+2, file);
		                        FindAttacked();
		                        if(!IsCheck(kto))
                                {
                                    CopyBoard1To2();
                                    ResetAttacked();
                                    return false;
                                }
		                    }
		                }
		                else if(Board2[rank][file]->Figure == 'r' && RookMate  (rank, file, kto))   return false;
		                else if(Board2[rank][file]->Figure == 'n' && KnightMate(rank, file, kto))   return false;
		                else if(Board2[rank][file]->Figure == 'b' && BishopMate(rank, file, kto))   return false;
		                else if(Board2[rank][file]->Figure == 'q' &&(RookMate  (rank, file, kto) || BishopMate(rank, file, kto)))  return false;
		                else if(Board2[rank][file]->Figure == 'k' && KingMate  (rank, file, kto))   return false;
		        }
		      }
		    }
		 }
return true;
}
int main()
{
    SetBoard();
    PrintBoard();
    FILE *f = fopen("PrzebiegPartii.txt","w+");
    fclose(f);
    ResetAttacked();

    while(strcmp(Move, "SURR"))
    {
		bool Done = false;

		scanf("\n%[^\n]%*c", Move);
		int dl = strlen(Move);

		if(dl == 3)
		{
		    FindAttacked();
		    if(CzyjRuch%2 == 1)
		    {
		        if(!IsCheck('B') && Board[7][5]->IsFree && Board[7][6]->IsFree && Board[7][7]->IsFirst && Board[7][4]->IsFirst && !WhereBoard[7][5]->byBlack && !WhereBoard[7][6]->byBlack)
		        {
		            ShortW();
		            enPas = false;
		            Done = true;

		        }
		    }
		    else
		    {
		        if(!IsCheck('W') && Board[0][5]->IsFree && Board[0][6]->IsFree && Board[0][7]->IsFirst && Board[0][4]->IsFirst && !WhereBoard[0][5]->byWhite && !WhereBoard[0][6]->byWhite)
		        {
		            ShortB();
		            enPas = false;
		            Done = true;
		        }
		    }
		    FindAttacked();
		}
		if(dl == 5 && Move[0] == 'O')
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
		if(dl == 5)
		{
		    int t_rank1 = 8 - ((int)Move[1] - 48), t_file1 = Wartosc(Move[0]), t_rank2 = 8 - ((int)Move[4] - 48), t_file2 = Wartosc(Move[3]);
		    if((Board[t_rank1][t_file1]->Figure == 'P' || Board[t_rank1][t_file1]->Figure == 'p') && CanPawn(t_rank1, t_file1, t_rank2, t_file2))
		    {
		        Ruch(t_rank1, t_file1, t_rank2, t_file2);
		        FindAttacked();
		        if(CzyjRuch%2 == 0) kto = 'W' ;
		        else                kto = 'B';
		        if(!IsCheck(kto))   Done = true;
		    }
		}
		if(dl == 7)
		{

		    int t_rank1 = 8 - ((int)Move[3] - 48), t_file1 = Wartosc(Move[2]), t_rank2 = 8 - ((int)Move[6] - 48), t_file2 = Wartosc(Move[5]);
		         if(Move[0] == 'R' || Move[0] == 'r')
		         {
		            if(CanRook(  t_rank1, t_file1, t_rank2, t_file2))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto))
		                {
		                	Done = true;
		                	enPas = false;
		                }
		            }
		         }
		    else if(Move[0] == 'N' || Move[0] == 'n')
		    {
		            if(CanKnight(t_rank1, t_file1, t_rank2, t_file2))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'B' || Move[0] == 'b')
		    {
		            if(CanBishop(t_rank1, t_file1, t_rank2, t_file2))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'Q' || Move[0] == 'q')
		    {
		            if(CanQueen( t_rank1, t_file1, t_rank2, t_file2))
		            {
		                Ruch(t_rank1, t_file1, t_rank2, t_file2);
		                FindAttacked();
		                if(CzyjRuch%2 == 0) kto = 'W' ;
		                else                kto = 'B';
		                if(!IsCheck(kto))
		                {
		                   Done = true;
		                   enPas = false;
		                }
		            }
		    }
		    else if(Move[0] == 'K' || Move[0] == 'k')
		    {
		            if(CanKing(  t_rank1, t_file1, t_rank2, t_file2))
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
		                if(!IsCheck(kto))
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
		if(IsCheck(kto))   printf("Jestes w szachu!\n");
		if(!strcmp(Move, "SURR"))
		{
		    printf("%s sie poddal\nWygral %s\n",WhoseMove[(CzyjRuch+1)%2], WhoseMove[CzyjRuch%2]);
		    break;
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
		else
        {
            CzyDraw = false;
            Draw = 0;
        }
		if(kto == 'W') kto = 'B';
		else           kto = 'W';
		if(!CzyDraw && IsCheck(kto))
		{
		    if(CheckMate(kto))
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
		ResetAttacked();
		prevFile = -1;
		prevRank = -1;
    }

    return 0;
}
