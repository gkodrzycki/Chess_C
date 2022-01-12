	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"


bool RookMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF)
{
    int rank1 = rank-1, file1 = file;
    while(rank1 >= 0)
    {
        if(rank1 < 0 || rank1 > 7)          break;

        Ruch(rank, file, rank1, file1);
        FindAttacked();
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
bool KnightMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF)
{
    if(rank-2 >= 0 && rank-2 < 8 && file+1 >= 0 && file+1 < 8)
    {
        Ruch(rank, file, rank-2, file+1);
        FindAttacked();
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
bool BishopMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF)
{
    int rank1 = rank-1, file1 = file+1;
    while(true)
    {
        if(rank1 < 0 || rank1 > 7 || file1 < 0 || file1 > 7)          break;

		Ruch(rank, file, rank1, file1);
		FindAttacked();
		if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
bool KingMate(int rank, int file, char kto, int prevRank, int prevFile, int wKR, int wKF, int bKR, int bKF)
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
bool CheckMate(char kto, int prevRank, int prevFile, int wKR, int wKF, int bKR, int bKF)
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
		                    if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		                    if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		                    if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		                    if(!IsCheck(kto, wKR, wKF, bKR, bKF))
                            {
                                CopyBoard1To2();
                                ResetAttacked();
                                return false;
                            }
		                }
		        }
		        else if(Board2[rank][file]->Figure == 'R' && RookMate  (rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		        else if(Board2[rank][file]->Figure == 'N' && KnightMate(rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		        else if(Board2[rank][file]->Figure == 'B' && BishopMate(rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		        else if(Board2[rank][file]->Figure == 'Q' &&(RookMate  (rank, file, kto, wKR, wKF, bKR, bKF) || BishopMate(rank, file, kto, wKR, wKF, bKR, bKF)))  return false;
		        else if(Board2[rank][file]->Figure == 'K' && KingMate  (rank, file, kto, prevRank, prevFile, wKR, wKF, bKR, bKF))   return false;
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
                            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
                            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
                            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
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
		                        if(!IsCheck(kto, wKR, wKF, bKR, bKF))
                                {
                                    CopyBoard1To2();
                                    ResetAttacked();
                                    return false;
                                }
		                    }
		                }
		                else if(Board2[rank][file]->Figure == 'r' && RookMate  (rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		                else if(Board2[rank][file]->Figure == 'n' && KnightMate(rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		                else if(Board2[rank][file]->Figure == 'b' && BishopMate(rank, file, kto, wKR, wKF, bKR, bKF))   return false;
		                else if(Board2[rank][file]->Figure == 'q' &&(RookMate  (rank, file, kto, wKR, wKF, bKR, bKF) || BishopMate(rank, file, kto, wKR, wKF, bKR, bKF)))  return false;
		                else if(Board2[rank][file]->Figure == 'k' && KingMate  (rank, file, kto, prevRank, prevFile, wKR, wKF, bKR, bKF))   return false;
		        }
		      }
		    }
		 }
return true;
}
bool IsCheck(char kto, int wKR, int wKF, int bKR, int bKF)
{
    if(kto == 'B')
        if(WhereBoard[wKR][wKF]->byBlack) return true;
    if(kto == 'W')
        if(WhereBoard[bKR][bKF]->byWhite) return true;
    return false;
}
