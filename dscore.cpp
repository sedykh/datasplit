// dscore.cpp : shortened version of core.cpp -source file, to be used for dataset-class
//

#include "dscore.h"

//-------   memory leaks catcher for the current source-file  --------
#ifdef ADV_LEAK_CATCHER
#ifdef _DEBUG 
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
//--------------------------------------------------------------------

REALNUM_TYPE getMetricDistance(apvector<REALNUM_TYPE> &V1, apvector<REALNUM_TYPE> &V2, REALNUM_TYPE metricPower, UNSIGNED_1B_TYPE metricFunc)
/*
description: calculates various metric distances depending on metricFunc value:
metricFunc = 0 - Euclidean/Minkowski; 1 - Cosine, 2 - Correlation, 3 - Tanimoto

in case of using similarity-based coeffients, they are transformed into distances by using
'1 - () ^ metricPower' equation */
{
	REALNUM_TYPE X, diff, diff1;
	UNSIGNED_4B_TYPE j, D = min( V1.length(), V2.length() );

	if (metricFunc == 0)
	{//Euclidean, general Minkowski
		for (X = j = 0; j < D; j++)	
		{
			diff = fabs(V1[j] - V2[j]);
			if (diff == 0)	continue;
			X += pow(diff, metricPower);
		}
		if (X == 0)	return X;
		return pow(X, 1.0/metricPower);
	}

	//non-Euclidean
	REALNUM_TYPE rtMean = 0, rtMean1 = 0;
	if (metricFunc == 2)
	{//Correlation coff-based. Calculate mean-centered values
		for (j = 0; j < D; j++)	
		{
			rtMean += V1[j]; 
			rtMean1 += V2[j];
		}
		rtMean	/= D;
		rtMean1	/= D;
	}

	for (diff = diff1 = X = j = 0; j < D; j++)
	{
		X += (V1[j] - rtMean)*(V2[j] - rtMean1);
		diff += sqr(V1[j] - rtMean);
		diff1 += sqr(V2[j] - rtMean1);
	}

	if ( (metricFunc < 3) )
	{//cosine similarity coeff, which is r-correlation if vectors are mean-centered
		diff *= diff1;
		if (diff > 0)	X	/= sqrt(diff); 	else X = 0; //make totally dissimilar in exceptional cases
	}

	if (metricFunc == 3)
	{//Tanimoto
		X = fabs(X);
		diff += diff1 - X;
		if (diff != 0)	X	/=	diff; else X = 0; //make totally dissimilar in exceptional cases
	}

	if (X == 0) return 2.0;
	return (1.0 - pow(X, metricPower));	
}

REALNUM_TYPE RRound(REALNUM_TYPE x)
{
	if (fabs(x- floor(x)) > 0.5)
		return ceil(x);
	return floor(x);
}

SIGNED_4B_TYPE Round(REALNUM_TYPE x)
{	
	return ( (SIGNED_4B_TYPE)RRound(x) );
}

void GeneratePrimeNumbers(apvector<UNSIGNED_4B_TYPE> &PN, UNSIGNED_4B_TYPE N)
{
	UNSIGNED_4B_TYPE k, l, a = 0, b = 0, c;
	UNSIGNED_4B_TYPE Candidat1, Candidat2, MaxD;

	l = 2;
	PN.resize(l);
	PN[0] = 2;
	PN[1] = 3;

	k = 0;
	while (l < N)
	{
		k++;
		Candidat1 = 6*k-1;
		Candidat2 = 6*k+1;
		MaxD = UNSIGNED_4B_TYPE( sqrt(REALNUM_TYPE(Candidat2)) );
		
		for (c=2; (c<l)&&(PN[c]<=MaxD)&&(Candidat1 + Candidat2); c++)
		{
			if (Candidat1)	a = Candidat1 / PN[c];
			if (Candidat2)	b = Candidat2 / PN[c];

			if (Candidat1 == a*PN[c])	Candidat1 = 0;
			if (Candidat2 == b*PN[c])	Candidat2 = 0;
		};

		if (Candidat1)
		{
			PN.resize(l+1);
			PN[l] = Candidat1;
			l++;
		};

		if (Candidat2)
		{
			PN.resize(l+1);
			PN[l] = Candidat2;
			l++;
		};
	};//while l < N

}

bool CheckStrEnding(STRING_TYPE &A, STRING_TYPE ends) 
//can unambiguously check file-types by means of file-extension masks
{
	STRING_TYPE TStr = A.substr( A.length() - ends.length(), ends.length() );
	return ( TStr.find(ends) == 0 );
}

void CutStrEnding(STRING_TYPE &S)
{//cuts the file-extention '.xxx' off the string's end
	char * v = (char *)strrchr(S.c_str(), '.');
	if ( v  > strrchr(S.c_str(), '\\') )
		S = S.substr( 0, SIGNED_4B_TYPE(v - S.c_str()) );
}

REALNUM_TYPE String2Number(STRING_TYPE &L)
//creates a string-representing number
//NOTE: unlike CRC32 similar numbers will be for similar strings!
{
	REALNUM_TYPE x = ZERO, ch, div = 1;	
	for (SIGNED_4B_TYPE sc = ZERO; sc < L.length(); sc++)
	{
		ch = UNSIGNED_1B_TYPE(L[sc]);
		ch /= div;
		x += ch;
		div *= 256;
	}
	return x;
}

void SplitString(STRING_TYPE &BASE, STRING_TYPE SEP, apvector<STRING_TYPE> &SPLIT)
{
	SPLIT.resize(0);
	if ( (BASE.length() < SEP.length()) || (SEP.length() == 0) ) return;

	STRING_TYPE B = BASE + SEP;
	SIGNED_4B_TYPE i =0, cx =0, ix =B.find(SEP);
	SPLIT.resize(B.length() / SEP.length());
	do 
	{
		SPLIT[i++] = B.substr(cx, ix - cx);
		cx = ix + SEP.length();
		B[ix]++; //to destroy SEP-match
		ix = B.find(SEP);
	} while (ix >= 0);
	SPLIT.resize(i);
}


SIGNED_4B_TYPE LoadSetAsText(FILETYPE_IN &fip, set &setData, SIGNED_4B_TYPE sh)
{//fip should point in a text file to a string of numbers: set_size element1 element2 ...
	setData.Dump();
	SIGNED_4B_TYPE uu, zz, ii;
	fip >> uu;
	for (ii = 0; ii < uu; ii++) {	fip >> zz;	setData.PutInSet(zz - sh); };
	return uu;
}

SIGNED_4B_TYPE SaveSetAsText(FILETYPE_OUT &fo, set &setData, SIGNED_4B_TYPE sh)
{
	SIGNED_4B_TYPE ii;
	apvector<SIGNED_4B_TYPE> els;
	setData.GetList(els);
	fo << els.length();
	for (ii = 0; ii < els.length(); ii++)	fo << " " << els[ii]+ sh;
	fo << endl;
	return els.length();
}

UNSIGNED_4B_TYPE GetRandomNumber(UNSIGNED_4B_TYPE RangeSize)
//the number generated will be within [0 .. RangeSize - 1]
//srand() have to be called earlier to provide unrepetitive randomization
//NB! RangeSize can be bigger than RAND_MAX!
{
	UNSIGNED_4B_TYPE RM = RAND_MAX;
	REALNUM_TYPE rt = rand();
	
	if (RangeSize > ++RM)
	{//this should be only Windows-specific; RAND_MAX on LINUX is (2^31)-1
		rt	*= RM;
		rt	+= rand();
		rt	/= RM;
	}
	
	rt	/= RM;
	rt	*= RangeSize;
	return UNSIGNED_4B_TYPE(rt);
}

void SortRandomly (apvector<REALNUM_TYPE> &V)
{
	SIGNED_4B_TYPE N = V.length();
	SIGNED_4B_TYPE *A	= GRAB_MEM_BLOCKS(SIGNED_4B_TYPE, N), ic = ZERO;
	REALNUM_TYPE *F		= GRAB_MEM_BLOCKS(REALNUM_TYPE, N);
	QSortScore = F;
	for (; ic < N; ic++)
	{
		A[ic] = ic;	
		F[ic] = (REALNUM_TYPE)rand(); 
	}
	qsort(A, (size_t)N, sizeof(SIGNED_4B_TYPE), QSortCompareGreater);
	DROP_MEM_BLOCKS(F);
	QSortScore = NULL;

	apvector<REALNUM_TYPE> VNEW(N);
	for (ic = ZERO; ic < N; ic++)	VNEW[ic] = V[A[ic]];
	DROP_MEM_BLOCKS(A);
	V = VNEW;
}

//QSort paraphernalia
REALNUM_TYPE *QSortScore = NULL;
int QSortCompareGreater(const void *arg1, const void *arg2)
{   
   if (QSortScore == NULL)
		return ZERO;

   if (QSortScore[* ( UNSIGNED_4B_TYPE* ) arg1] >  QSortScore[* ( UNSIGNED_4B_TYPE* ) arg2])
		return 1;
   
   return -1;
}

int QSortCompareLess(const void *arg1, const void *arg2)
{   
   if (QSortScore == NULL)
		return ZERO;

   if (QSortScore[* ( UNSIGNED_4B_TYPE* ) arg1] <  QSortScore[* ( UNSIGNED_4B_TYPE* ) arg2])
		return 1;
   
   return -1;
}

void BubbleSort(apvector<REALNUM_TYPE> &x, apvector<SIGNED_4B_TYPE> &a)
//description:	sorts array "a" in descending order on the base of "x" ("x" gets sorted too)
//				this function is needed for internal purposes of DefineStereoisomers() and get3d()
//
//Note:			arrays x and a should have same length
{
	bool SwapFlag;
	SIGNED_4B_TYPE j;
	
	if (x.length() != a.length())
		return;

	SIGNED_4B_TYPE tm;
	REALNUM_TYPE   tmr;
	do
	{
		SwapFlag = false;
		for (j=0; j<x.length()-1; j++)
			if (x[j] < x[j+1])
			{
				Swap(x[j], x[j+1], tmr);
				Swap(a[j], a[j+1], tm);
				SwapFlag = true;
			};
	} while (SwapFlag);
}


UNSIGNED_4B_TYPE CRC32Table[256] = 
{ 0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
  0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
  0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
  0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
  0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
  0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
  0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
  0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
  0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
  0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
  0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
  0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
  0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
  0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
  0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
  0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,

  0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
  0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
  0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
  0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
  0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
  0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
  0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
  0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
  0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
  0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
  0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
  0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
  0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
  0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
  0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
  0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,

  0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
  0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
  0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
  0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
  0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
  0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
  0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
  0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
  0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
  0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
  0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
  0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
  0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
  0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
  0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
  0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,

  0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
  0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
  0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
  0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
  0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
  0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
  0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
  0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
  0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
  0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
  0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
  0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
  0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
  0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
  0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
  0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D};

UNSIGNED_4B_TYPE GetCRC32 (const GENERIC_POINTER p, UNSIGNED_4B_TYPE len)
//For each byte:
// 1.	XOR  the input byte with the low-order byte of
//		the CRC register to get a table index t
//
// 2.	Shift the CRC register eight bits to the right
//
// 3.	XOR the CRC register with the contents of CRC32Table[t]
{
  
  UNSIGNED_4B_TYPE CRCr = 0xFFFFFFFF;
  UNSIGNED_1B_TYPE * q = (UNSIGNED_1B_TYPE *)p, t;
  
  for (UNSIGNED_4B_TYPE i = ZERO;i < len; i++)
  {
	t  = *q++;
	t ^= (CRCr & 0xFF);
    CRCr >>= 8;
	CRCr ^= CRC32Table[t];    
  }

  return CRCr;
} //CalcCRC32

SIGNED_4B_TYPE FindArrPoz(apvector<SIGNED_4B_TYPE> &ARR, SIGNED_4B_TYPE V)
//description:		returns position in KEYS where hashkey V should be
//perconditon:		array must be sorted!
//postcondition:	returns found position or -1 otherwise
{
	UNSIGNED_4B_TYPE a = 0, e = ARR.length(), m;
	while (e > a + 1)
	{
		m = (a + e) >> 1;
		if ( ARR[m] < V) a = m;	else e = m;
	};

	if (ARR[a]> V) return INVALID;
	if (ARR[a] == V) return a;	
	return e;
}

bool GetCombination(set &setBase, set &setCmb, UNSIGNED_2B_TYPE k)
//alternative interface for the main version below
{
	apvector<SIGNED_4B_TYPE> b, c;
	setBase.GetList(b);
	setCmb.GetList(c);
	
	bool res = GetCombination(b, c, k);
	if (res) setCmb = c; else setCmb.Dump();
	return res;
}

bool GetCombination(apvector<SIGNED_4B_TYPE> &Base, apvector<SIGNED_4B_TYPE> &Cmb, UNSIGNED_2B_TYPE k)
/*description:	returns in Cmb a combination of k elements from Base, 
				if Cmb is not empty and has k-size then it is used
				as a current combination to get the next one
 postcondition:
				returns true if new combination was created in Cmb
 precondition:				
				first call should have 0 < k < set-size.
				consecutive calls should have k = 0 and Cmb of k-size;
*/
{
	SIGNED_4B_TYPE N = Base.length();
	if (k)
	{//first call, populate combinations
		if (k == N) {Cmb = Base; return true; };
		Cmb.resize(0);
		if (k > N) return false;
		Cmb.resize(k);
		for (UNSIGNED_2B_TYPE i = 0; i < k; i++) Cmb[i] = Base[i];
		return true;
	}

	SIGNED_4B_TYPE C = Cmb.length();
	if ((C > N) || (C == 0))
	{
		Cmb.resize(0);
		return false;
	}

	SIGNED_4B_TYPE B, C1 = 0;
	while (C1 < C)
	{
		C1++;
		B = FindArrPoz(Base, Cmb[C - C1]);
		if (B < 0) break; //should not happen!
		if ( (B + C1) < N ) 
		{
			while (C1)	Cmb[C - C1--] = Base[++B];
			return true;
		}
	}

	Cmb.resize(0);
	return false; //all possibilities are exhausted
}
