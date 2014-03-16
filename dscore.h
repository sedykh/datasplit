//dscore.h shortened-version of core.cpp to provide most useful subroutines
//A.Sedykh, April, 2008

#if !defined(DSCORE_)
#define DSCORE_

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include "hash.h"
#include "set.h"

typedef apvector<set> apvector_set_type;

//swapping elements MACRO
#define Swap(a, b, t)		{(t) = (a); (a) = (b); (b) = (t);}

REALNUM_TYPE getMetricDistance(apvector<REALNUM_TYPE> &, apvector<REALNUM_TYPE> &, REALNUM_TYPE = 2.0, UNSIGNED_1B_TYPE = 0);

void GeneratePrimeNumbers(apvector<UNSIGNED_4B_TYPE> &, UNSIGNED_4B_TYPE);

bool CheckStrEnding(STRING_TYPE &, STRING_TYPE);
void CutStrEnding(STRING_TYPE &);
REALNUM_TYPE String2Number(STRING_TYPE &);
void SplitString(STRING_TYPE &, STRING_TYPE , apvector<STRING_TYPE> &);
SIGNED_4B_TYPE SaveSetAsText(FILETYPE_OUT &, set &, SIGNED_4B_TYPE = 1);
SIGNED_4B_TYPE LoadSetAsText(FILETYPE_IN &, set &, SIGNED_4B_TYPE = 1);

REALNUM_TYPE RRound(REALNUM_TYPE x);
SIGNED_4B_TYPE Round(REALNUM_TYPE x);
UNSIGNED_4B_TYPE GetRandomNumber(UNSIGNED_4B_TYPE);
void SortRandomly (apvector<REALNUM_TYPE> &);
UNSIGNED_4B_TYPE GetCRC32 (const GENERIC_POINTER, UNSIGNED_4B_TYPE);

void BubbleSort(apvector<REALNUM_TYPE> &, apvector<SIGNED_4B_TYPE> &);

//--- Qsort interface
int QSortCompareGreater(const void *, const void *);
int QSortCompareLess(const void *, const void *);
extern REALNUM_TYPE *QSortScore;


//finds a value in a sorted array
SIGNED_4B_TYPE FindArrPoz(apvector<SIGNED_4B_TYPE> &, SIGNED_4B_TYPE);

//returns a subset of elements, every call gives next combination
bool GetCombination(apvector<SIGNED_4B_TYPE> &, apvector<SIGNED_4B_TYPE> &, UNSIGNED_2B_TYPE = 0);
bool GetCombination(set &, set &, UNSIGNED_2B_TYPE = 0);

#endif		//#define DSCORE_
