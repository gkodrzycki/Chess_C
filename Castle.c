#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Funkcje.h"


bool LongW(int wKR, int wKF, int bKR, int bKF)
{
    if(!IsCheck('B', wKR, wKF, bKR, bKF) && Board[7][1]->IsFree && Board[7][2]->IsFree && Board[7][3]->IsFree && Board[7][0]->IsFirst && Board[7][4]->IsFirst)   return true;
    return false;
}
bool ShortW(int wKR, int wKF, int bKR, int bKF)
{
    if(!IsCheck('B', wKR, wKF, bKR, bKF) && Board[7][5]->IsFree && Board[7][6]->IsFree && Board[7][7]->IsFirst && Board[7][4]->IsFirst)   return true;
    return false;
}
bool LongB(int wKR, int wKF, int bKR, int bKF)
{
    if(!IsCheck('W', wKR, wKF, bKR, bKF) && Board[0][1]->IsFree && Board[0][2]->IsFree && Board[0][3]->IsFree && Board[0][0]->IsFirst && Board[0][4]->IsFirst)   return true;
    return false;
}
bool ShortB(int wKR, int wKF, int bKR, int bKF)
{
    if(!IsCheck('W', wKR, wKF, bKR, bKF) && Board[0][5]->IsFree && Board[0][6]->IsFree && Board[0][7]->IsFirst && Board[0][4]->IsFirst)   return true;
    return false;
}
