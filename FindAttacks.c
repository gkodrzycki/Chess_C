#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"

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
