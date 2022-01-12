#ifndef Funkcje
#define Funkcje

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


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

extern Square *Board[8][8];
extern Square *Board2[8][8];
extern Attacked *WhereBoard[8][8];

//BoardManagment.c
extern int Wartosc(char x);
extern void CopyBoard2To1();
extern void CopyBoard1To2();
extern void SetBoard();
extern void PrintBoard();
extern void ResetAttacked();
extern void Ruch(int t_rank1, int t_file1, int t_rank2, int t_file2);
extern bool CzyMozna(int rank1, int file1, int rank2, int file2, int CzyjRuch);
extern bool CzyPuste(int rank1, int file1, int rank2, int file2);
extern void Upgrade(int t_rank1, int t_file1);

//FindAttacks.c
extern void FindRook(int rank, int file, char kol);
extern void FindKnight(int rank1, int file1, char kol);
extern void FindBishop(int rank, int file, char kol);
extern void FindQueen(int rank, int file, char kol);
extern void FindKing(int rank, int file, char kol);
extern void FindAttacked();

//CheckMovement.c
extern bool CanPawn(int t_rank1, int t_file1, int t_rank2, int t_file2, int CzyjRuch, bool enPas, int enFile, int enRank);
extern bool CanRook(int rank1, int file1, int rank2, int file2, int CzyjRuch);
extern bool CanBishop(int rank1, int file1, int rank2, int file2, int CzyjRuch);
extern bool CanKnight(int rank1, int file1, int rank2, int file2, int CzyjRuch);
extern bool CanQueen(int rank1, int file1, int rank2, int file2, int CzyjRuch);
extern bool CanKing(int rank1, int file1, int rank2, int file2, int CzyjRuch);

//Castle.c
extern bool LongW();
extern bool ShortW();
extern bool LongB();
extern bool ShortB();

//CheckMate.c
extern bool RookMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF);
extern bool KnightMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF);
extern bool BishopMate(int rank, int file, char kto, int wKR, int wKF, int bKR, int bKF);
extern bool KingMate(int rank, int file, char kto, int prevRank, int prevFile, int wKR, int wKF, int bKR, int bKF);
extern bool CheckMate(char kto, int prevRank, int prevFile, int wKR, int wKF, int bKR, int bKF);
extern bool IsCheck(char kto, int wKR, int wKF, int bKR, int bKF);


#endif
