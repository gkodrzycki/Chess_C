#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"


bool CanPawn(int t_rank1, int t_file1, int t_rank2, int t_file2, int CzyjRuch, bool enPas, int enFile, int enRank)
{
    if(!CzyMozna(t_rank1, t_file1, t_rank2, t_file2, CzyjRuch))   return false;
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
bool CanRook(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    if(!CzyMozna(rank1, file1, rank2, file2, CzyjRuch))   return false;
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
bool CanBishop(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    if(!CzyMozna(rank1, file1, rank2, file2, CzyjRuch))   return false;
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
bool CanKnight(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    if(!CzyMozna(rank1, file1, rank2, file2, CzyjRuch))   return false;
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
bool CanQueen(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    return (CanBishop(rank1, file1, rank2, file2, CzyjRuch) || CanRook(rank1, file1, rank2, file2, CzyjRuch));
}
bool CanKing(int rank1, int file1, int rank2, int file2, int CzyjRuch)
{
    if(!CzyMozna(rank1, file1, rank2, file2, CzyjRuch))   return false;
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
