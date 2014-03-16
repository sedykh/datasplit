/* datasplit.cpp 2008 - 2013
Console application (Linux, Windows). 

Based on dataset-class

TODO:
(Add here problems and suggestions to be worked upon)

0) LGO with Activity bins may result in less than perfect bin sampling (i.e. -A=2R may lead to one split with lower #actives)
1)	
	undocumented for now (not sure, if such features are really needed)
	-APP= is a mode to work with subsets

DONE: 

(history list of recent changes)
4.14		Feb 8 2013
			-M=X expanded to allow splitting by original activity when '-REF=_'

4.13		Nov 9 2012
			safety valve added for removing descriptors by correlation RemoveHiCorrDims()

4.12		Oct 8 2012
			Minor fix (help cleaned and extended)

4.11		July 31 2012
			added -M=U for removing dupicates etc (points above similarity cut-off)

4.01		July 3 2012
			minor fix in PrintMoreHelp()

4.0			Aug 11 2011
			isScaled() added for high-level check for the presence of scaling in the dataset
			normalization mode adjusted to prevent scaling by reference if scaling exists

3.9			May 26 2011
			added descriptor filtering by min.# of non-zero signals -MINO=
			(in the -M=N normalization mode).
			Fixed silent handling of blanks in datapoint names (for a tab separated file this may shift descr values)

3.83		Nov 21 2010
			qsar class updated,
			ExpandDescriptors() fixed.

3.82		Oct 4 2010
			minor fix in rand_split() to make act-independent splits if nActBins = 1

3.81		Sept 4 2010
			-M=X mode modified to use specified descriptor for splitting!
			
3.8			Aug 20-24 2010
			New modes added;
			-M=G to glue two descriptor files
			-M=X to use specified descriptor as new activity

3.71
			June 20 2010
			fix in save(): Bfr[20] changed to Bfr[100] to prevent buffer overflow.

3.7
			June 17 2010
			Outlier removal mode added -M=O -REM=3.0_d1@2A


3.6-3.61
			May 16 2010
			fixed Sphere Exclusion's Radius calculation (was -INF for ~1000 frag descriptors); NB: -R=D could be used in such cases

			May 12 2010 
				svm load/save critical fix (dscr indexation was from 0, not from 1)!!
			

3.50-52		May 2-5 2010
				get_act_bins() fixed, wrong range-binning of continuous data!!
				upper/lower case problems fixed for reference and output files


3.40-41	April 14-27 2010
				minor fix in load()
				critical fix in scale_dimensions()

3.3		April 3 2010
				adjusted group size added to lgo_split() to make splits more even.

3.2		March 30 2010 
				minor fix: RRound() added into lgo_split(), 11 splits were generated instead of 10 for 127 compounds of binary activity
				commentary line removed from .list file

3.1		March 3 2010
				Minor fix removed wrong call of PrintMoreHelp() everytime in -M= mode

3.0		February 27 2010
				LoadDataset(), SaveDataset() are added to simplify loading

				New mode added -M=N to normalize matrices
				-REF= to specify reference matrix file, also new normalization options.
					
				New member-functions in dataset-class:
				RemoveLowVarDims(), RemoveHiCorrDims()
				normalizeby(), scale_dimensions()

Tested with:
test.xa -M=X
test.xa -M=X -REF=_
2E9N_2C3K_entess.x -M=N -MINO=2 (only 2 sample points to normalize)
mdr1_moe_mdf.xa -M=O -REM=3.0_d1@2A
BI -M=N -REF=p -OUT=BI_pept1.xa
p.xa -M=N -MXR2=0.9 -MINS=0.1
p -M=N -BKSC
p_mdf -M=N

2.6		January 10 2010
					a change to interproject universal core.* and typedef.h files
					stack class and bond.h are included for that sake

2.5		December 20 2009
					alterations of load() in dataset class:
					less strict reading (empty lines, mode for a-files absence)

2.41-4  December 1-10 2009
					minor fix in load()
					fix in get_dscr_pos()
					minor fix in SaveOneSplitFiles()

		November 13-18 2009
					minor fix in -M-T mode for .x/.a conversion
					minor fix in get_NearNeibDistances()
		

2.4 November 7 2009
					added -M=T mode to convert matrix-files
					-S= and -F= options merged
					-M=V mode removed (too special feature)
					added support of SVM files

2.34 October 19 2009
					saving .xa-files enabled in the .list format

2.33 October 5 2009
					proper handling of case sensitive names in t2t-file
					SaveDataName() modified, stInput used

2.3 August 7-8 2009
					replace() function in apstring class fixed
					load() updated in dataset class
					getlines..() functions in apstring class updated
					warning on data-format in help

2.2 July 1 2009		added user-controlled seed for randomizer srand()
2.2 June 26 2009	matrix.h overhauled, 
					more service f() in dscore: SaveSetAsText(), LoadSetAsText(), ...
					output format corrected (first, training set is written, then test set)

2.1 June 15-16 2009 Y-randomization was adjusted to generate many trials
					rand_shuffle() fixed

2.1 June 14-15 2009 minor fixes in dataset (ids retrieval) and dscore (random number generation)

2.0 May 6 2009: alternative mode for activity-bins implemented by get_act_bins()
	altered: rand_split(), lgo_split(), randomizeY();

1.9 February 18 2009: dataset-class updated:	
					added functions: get_dscr(), get_dscr_pos(), expandby()
1.9 March 31 2009: minor fixes in dataset.cpp and explicit type-conversions

1.8 February 17 2009: def. nFraction for Sphere Exclusion is now 5 (accd. Sasha)

1.8 February 4-7 2009: -4EXT added to distinguish split on external/modeling vs train/test datasets
	default SFEXCL_NEXTSF_RAND now goes with SFEXCL_SEED_MAXACT/MINACT, max and min are picked randomly now.
	
1.8	February 3 2009: filenaming changed to match conventional extensions
1.8 January 28 2009: "getdist" group of functions was extended

1.7 January 15 2009: t2t-output format adjusted to store datafile-references

1.6 June 20 2008: Added stInput to preserve case-sensitivity in the input-file name
1.6 May 30 2008: Added feature to work on subgroup and then reintegrate the results

1.5 May 29 2008: Leave-group-out rewriten as part of dataset-class: see lgo_split()

1.4 May 26 2008: more secure data loading, see load(), extra help output

1.3 May 21 2008: random generator minor fix

1.2 May 13 2008: Progressive scrambling added, etc
*/

#include "dataset.h"

#define Version "4.14"

void SaveDataset(dataset &dtstD, STRING_TYPE stName, UNSIGNED_1B_TYPE mtxTYPE)
{
	STRING_TYPE stO = stName;
	if ( !(CheckStrEnding(stO, ".x")||CheckStrEnding(stO, ".xa")||CheckStrEnding(stO, ".svm")) )
	switch (mtxTYPE)
	{
		case 1:	stO += ".x";		break;
		case 2:	stO += ".svm";		break;
		case 0:	default:
				stO += ".xa";		break;
	}

	FILETYPE_OUT foD(stO.c_str());
	if (mtxTYPE == 1)
	{
		CutStrEnding(stO);
		stO += ".a";
		FILETYPE_OUT foAfile(stO.c_str());
		dtstD.save(foD, &foAfile, 1);
		foAfile.close();
	}
	else
		dtstD.save(foD, NULL, mtxTYPE);
	foD.close();
}

SIGNED_2B_TYPE LoadDataset(dataset &dtstD, STRING_TYPE &stName)
{
	//input matrix format, new one by default
	SIGNED_2B_TYPE nTYPE = 0;
	STRING_TYPE stMTX = stName;
	stMTX.tolowercase();

	if (!CheckStrEnding(stMTX, ".xa") && !CheckStrEnding(stMTX, ".x") && !CheckStrEnding(stMTX, ".svm"))
	{//if no extension then by default assume a new format
		CutStrEnding(stName);
		stName += ".xa";
		FILETYPE_IN fiTest(stName.c_str());
		if (fiTest.eof() || fiTest.fail())
		{//revert to old format
			CutStrEnding(stName);
			stName	 += ".x";
			stMTX	 += ".x";
		}
		else
			stMTX	 += ".xa";
		fiTest.close();
	}
	
	FILETYPE_IN fiXAfile(stName.c_str());
	if (fiXAfile.eof() || fiXAfile.fail())
	{
		cout << "Can not open input file: '" << stName << "'" << endl;
		return -1;
	}

	bool ifRead = true;
	if (CheckStrEnding(stMTX, ".x"))
	{//old format
		nTYPE = 1;
		STRING_TYPE stA = stName;
		CutStrEnding(stA);
		stA += ".a";
		FILETYPE_IN fiAfile(stA.c_str());
		if (fiAfile.eof() || fiAfile.fail())
		{
			cout << "Can not open a-file :'" << stA << "'" << endl;
			return -1;
		}
		ifRead = dtstD.load(fiXAfile, &fiAfile, 1);
		fiAfile.close();
	}
	else
	{
		if (CheckStrEnding(stMTX, ".svm")) nTYPE = 2;
		ifRead = dtstD.load(fiXAfile, NULL, (UNSIGNED_1B_TYPE)nTYPE);
	}
	fiXAfile.close();
	if (ifRead) return (nTYPE);
	return -1;
}

void ReIntegrateData(dataset &dV, dataset &dX, dataset &dC)
/*	May 31, 2008, Aleks
	description:	dV's training and test sets are recalculated.
					test set = test set of dX, training set = 
					traininset of dX + extra chemicals that are in dV and not in dX

					This is specific service function to restore original indexation and 
					save full datasets when sequential splitting is done
					(i.e. dV is split on dX and dX1, then dX is split again, and so on)

	precondition:	dX is subset of dV;
	postcondition:	dC stores original dX, dX stores updated dV;
*/
{
	SIGNED_4B_TYPE i, j, N = dX.get_Ndatapoints();
	set xx, Extr, setdV(0, dV.get_Ndatapoints());
	
	dV.train.Dump();
	for (i = 0; i < N; i++)
	{
		j = dV.get_sid_pos(dX.get_sid(i));
		Extr.PutInSet(j);
		if (dX.train.IsInSet(i))	dV.train.PutInSet(j);
	}

	xx = setdV - Extr;
	dV.train |= xx;	
	dV.test	= setdV - dV.train;

	dC = dX;
	dX = dV;
}

void PrintMoreHelp(char HelpKey)
{
	char h = toupper(HelpKey);
	switch (h)
	{
		case 'G':
			cout << "Glues two descriptor-matrices (combining descriptors)." << endl;
			cout << "'-REF=' specifies the descriptor-file to be added." << endl << endl;
		break;
		
		case 'X':			
			cout << "Partitioning based on values of a selected descriptor." << endl;			
			cout << "'-REF=' specifies descriptor label to be used." << endl;
			cout << "NB: if '-REF=_' or skipped, activity values will be used." << endl;
			cout << "'-A=' defines the number of equal-range bins" << endl;
			cout << "to be used for the specified descriptor <def. 2>." << endl << endl;
		break;

		case 'O':
			cout << "Removes datapoints that are too far from others in descriptor space." << endl;
			cout << "NB! Descriptor matrix should be normalized before this procedure!!" << endl << endl;

			cout << "Use '-REM=fX@kM' to exclude data points >f st.dev. units <def. f=3>," << endl;
			cout << "X can be '_d1' - usual distance or '_d2'<def.> - squared distance." << endl << endl;			

			cout << "k - #nearest neighbors to be used to calculate distance distribution:" << endl;
			cout << "0 - use all datapoints, 1 - one nearest neighbor <def>, and so on." << endl;
			cout << "M: 'A' or 'K'; 'A' <def.> to use extra neibs if dist is the same," << endl;
			cout << "'K' forces to use for statistics exactly k neibs." << endl << endl;
		break;

		case 'N':
			cout << "Range-scales descriptor matrix. Use '-ATSC' for autoscaling instead." << endl;
			cout << "For removal of redundant descriptors use:" << endl;
			cout << "'-MXR2=' max.allowed pairwise intercorrelation (R2)," << endl;
			cout << "'-MINS=' lowest allowed variance (s)" << endl;
			cout << "'-MINO=' min.# or fraction of differing (e.g., nonzero) values." << endl;
			cout << "NB: if -MXR2/-MINS/-MINO are unspecified, no descriptors are removed." << endl << endl;
			
			cout << "If scale-coefficients already exist, no scaling will be done by default." << endl;
			cout << "To force scaling with existing coefficients, use '-RESC' or" << endl;
			cout << "Use '-BKSC' instead to scale back to the original values." << endl << endl;

			cout << "Use '-REF=' to specify the file to be used as normalization reference" << endl;
			cout << "Dimensions and scaling coefficients will be taken from it and applied" << endl;
		break;

		case 'T':
			cout << "Example x-to-svm conversion: 'datasplit AAA.x -M=T -OUT=BBB.svm' " << endl;
		break;

		case 'U':
			cout << "Finds points <= distance cut-off '-SIMD=' <def 0>:" << endl;
			cout << "Keeps one with adjusted activity ('-USEMAX'<def>,'-USEMIN','-USEAV')," << endl;
			cout << "but removes all if st.dev of their acts > '-ACTD=' <def 999>." << endl;
			cout << "Example: 'datasplit AAA.x -M=U -ACTD=0.5 -USEMAX -SIMD=0.1'" << endl;
		break;

		case 'L':
			cout << "->NB In Leave-Group-Out the number of splits defines the test/train ratio" << endl;
		break;

		case 'Y':			
			cout << "Use '-A=' to specify #activity bins for progressive scrambling" << endl;
		break;

		case 'S':
			cout << "->NB: In Sphere-Exclusion '-F' & '-S' are used as criteria of a valid test-set," << endl;
			cout << "Available additional settings:" << endl;
			cout << "'-E=e'	= randomly seed some spheres; 'e' is their number <1-255>" << endl;
			cout << "'-+=HI,LO,1,3,17' e.g. adds to the initial seeding the data points of " << endl;
			cout << "max and min activity and the points with IDs #1, #3 and #17 " << endl << endl;			

			cout << "'-D=R'	= spheres are randomly selected <default>" << endl;
			cout << "'-D=iok' = spheres are selected in a 2-level loop, where" << endl;
			cout << "'i' = inner-loop f(); can be 'H','L','S' <Max, Min, Sum>" << endl;
			cout << "'o' = outer-loop f(); can be 'H', 'L' <Max, Min>" << endl;
			cout << "'k' = level, on which existing spheres are scanned <default is 2>" << endl;
			cout << "e.g. '-D=LL1' = min-min mode of the next sphere selection," << endl;
			cout << "->NB: max/min.act datapoints are <default> seeds only for random sphere selection! (use '-+=' key to override this)" << endl << endl;

			cout << "'-TRN=p' p = #points to put in training-set from the curr.sphere" << endl;
			cout << "'-TST=p' p = #points to put in test-set from the curr.sphere" << endl;
			cout << "'-2TRN' or '-2TST' <default> specifies in which subset to put points first" << endl << endl;

			if (HelpKey != h)
			{//yet, print even more help
				cout << "General behavior of various sphere-selection modes: " << endl;
				cout << "-D=LL1,LL2	- snake-like creeping coverage of dataspace by spheres" << endl;
				cout << "-D=LH1 - lattice-like coverage of space" << endl;
				cout << "-D=HH1,HH1,SH1,SH2 - covers corners, creeps along edges and then closes in" << endl;
				cout << "-D=HL1,SL1,LH2 - tumor-like growth of the covered area" << endl;
				cout << "-D=HL2,SL2 - growth is controlled by existing sphere that is closest to the center of the dataspace. ";
				cout << "If initial starting point is in the corner, then performs like HH1,HH2" << endl;
			}
		break;

		default:
		break;
	}//switch
}

void SaveDataName(FILETYPE_OUT &fo, STRING_TYPE &df)
{
	fo << df << BLANK;
	STRING_TYPE dfa = df;
	dfa.tolowercase();
	if (CheckStrEnding(dfa, ".x"))
	{//old format
		dfa = df;
		dfa[df.length()-1] = 'a';
		fo << dfa;
	}
	else 
		fo << df;
	fo << endl;
}

void SaveOneSplitFiles(SIGNED_4B_TYPE sN, STRING_TYPE &stCore, FILETYPE_OUT &foLog, dataset &d, bool Name4External = false, SIGNED_2B_TYPE sv = 0)
{//macro-function to reuse repetitive part of the code
	char bfr[10]; //buffer for converting number to string
	sprintf(bfr, "%d", sN);
	STRING_TYPE stTrn_x, stTrn_a, stTst_x, stTst_a;
	STRING_TYPE part1 = "_trn", part2 = "_tst";
	STRING_TYPE ext1, ext2;
	
	if (Name4External) 
	{
		part1 = "_mdl"; 
		part2 = "_ext";
	}

	switch (sv)
	{
		case 1:
			ext1 = ".x";
			ext2 = ".a";
		break;

		case 2:
			ext1 = ext2 = ".svm";			
		break;

		case 0:
		default:
			ext1 = ext2 = ".xa";			
		break;
	}

	stTrn_x	= stCore + part1 + bfr + ext1;
	stTrn_a	= stCore + part1 + bfr + ext2;
	stTst_x	= stCore + part2 + bfr + ext1;
	stTst_a	= stCore + part2 + bfr + ext2;

	/*old naming scheme 
	stTrn_x	= stCore + "_a." + bfr;
	stTrn_a	= stCore + "_a1." + bfr;
	stTst_x	= stCore + "_b." + bfr;
	stTst_a	= stCore + "_b1." + bfr;
	*/

	foLog << stTrn_x << BLANK << stTrn_a << BLANK << d.train.Size() << BLANK;
	foLog << stTst_x << BLANK << stTst_a << BLANK << d.test.Size() << endl;

	FILETYPE_OUT foXfileTrn(stTrn_x.c_str()), foXfileTst(stTst_x.c_str()), foAfileTrn, foAfileTst;
	if (sv == 1)
	{
		foAfileTrn.open(stTrn_a.c_str());
		foAfileTst.open(stTst_a.c_str());
	}

	dataset datasetH = d.get_training_set();
	datasetH.save(foXfileTrn, &foAfileTrn, (UNSIGNED_1B_TYPE)sv);
	datasetH = d.get_test_set();
	datasetH.save(foXfileTst, &foAfileTst, (UNSIGNED_1B_TYPE)sv);
	
	if (sv == 1)
	{
		foAfileTrn.close();
		foAfileTst.close();
	}

	foXfileTrn.close();	
	foXfileTst.close();
	
}//SaveOneSplitFiles


int main(int argc, char* argv[])
{
	SIGNED_4B_TYPE workSubgroup = INVALID;
	
	//reconstruct working mode
	UNSIGNED_1B_TYPE ModelID = 0, nSplits = 10; //default
	UNSIGNED_1B_TYPE nActBins = 1; bool ActBinEqSize = true;

	REALNUM_TYPE rtFraction = 0.1;	//will be used as acceptance criteria for the test-set/training-set split
	UNSIGNED_4B_TYPE  nFraction = 0;

	//distance metric
	REALNUM_TYPE k__Metric = 2.0;
	UNSIGNED_1B_TYPE MetricKind = 0;

	//parameters for sphere-exclusion algorithm
	UNSIGNED_2B_TYPE sfexclMode = SFEXCL_NEXTSF_RAND; //random sphere selection is default
	REALNUM_TYPE SfExclR = 0, SfDiss = 0.01;
	UNSIGNED_1B_TYPE p2test = 1, p2train = 1, p2seed = 0;
	set extseed;
	bool NameStyle4External = false;

	//parameters for outlier-removal mode
	REALNUM_TYPE OutlierZ = 3;
	UNSIGNED_2B_TYPE ByKdist = 1;
	
	UNSIGNED_1B_TYPE nSmth = 1; //flag-variable for distance distribution analysis in get_NearNeibDistances();
	apvector<REALNUM_TYPE> knn_stats;

	//parameters for normalization mode
	UNSIGNED_1B_TYPE scale_mode = 0; //range-scale is default
	REALNUM_TYPE MaxR2 = 1, MinStDev = 0;
	UNSIGNED_2B_TYPE MinOcc = 0;

	//parameters for duplicate removal mode
	UNSIGNED_1B_TYPE dupl_mode = 0; //max act
	REALNUM_TYPE minDcut = 0.0, maxStdAct = 999;

	srand((unsigned)time(NULL)); //default random seed

	if (argc < 2)
	{//print help
		cout << endl << "#Datasplit V" << Version << " - Divides data into training and test sets." << endl;
		cout << "Usage:     datasplit filename [flags]" << endl;
		cout << "Default output: filename.t2t" << endl;
		cout << "Allowed input: .xa files or .x & .a files with matching names." << endl;
		cout << "NB: Do not use blanks or tabs in descriptor or chem.names!" << endl << endl;

		cout << "Possible flags are:" << endl;
		cout << "'-OUT=' specifies output name, use '.list'-ending to output in old format" << endl << endl;

		cout << "'-M=m', m <METHOD> can be:" << endl;
		cout << "'S'  = Sphere-Exclusion split <default>" << endl;
		cout << "'R'  = Randomly pick test-set" << endl;
		cout << "'L'  = Leave-Group-Out split" << endl;
		cout << "'Y'  = Y-randomization (progressive scrambling)" << endl;
		cout << "'T'  = Transfer input matrix format into output format" << endl;
		cout << "'N'  = Normalize input matrix" << endl;
		cout << "'U'  = Remove duplicate points" << endl;
		cout << "'O'  = Remove outliers" << endl;
		cout << "'G'  = Merge two descriptor-matrices" << endl;
		cout << "'X'  = Partition based on values of a specified descriptor." << endl;

		cout << "'-N=n', n is the number of splits to do <default " << UNSIGNED_4B_TYPE(nSplits) << ">" << endl;
		cout << "'-S=s'	= Test-set size or fraction, where 's' is a real or integer number <default 0.1>" << endl;
		cout << "'-A=..' = Use activity-bins <1-255> for stratified sampling, i.e.'-A=2R' sets 2 bins of" << endl;
		cout << "equal act.range ('R'-flag); <default: bins with equal #dpoints>" << endl << endl;

		cout << "Parameters related to 'Sphere-Exclusion' or 'Outlier-Removal':" << endl;
		cout << "'-Z=zx' = Metric to use; x - is a power coff. <default 2.0>" << endl;
		cout << "z: E -Euclidean <default>, T -Tanimoto, R -Corr., C -Cosine" << endl;
		cout << "'-R=rx', sphere's radius, where x is initial scale-factor <default 0.01>" << endl;
		cout << "r is 'U','D','V': User-defined <by x>, Distance- or Volume-based <default>" << endl << endl;
		
		cout << "'-4EXT': to use 'external/modeling' naming instead of 'test/train'" << endl;
		cout << "'-SRND=..': to seed randomizer <default: by time>" << endl;
		cout << "Also, for more specific help run with -M= argument." << endl << endl;
		return 0;
	}

	STRING_TYPE stInput = argv[1], stXAfilename, stT2Tfilename, stRfilename;
	stXAfilename = stInput;
	stXAfilename.tolowercase();

	if (stXAfilename.find("-m=") >= 0)
	{//just print extra help
		PrintMoreHelp(stXAfilename[stXAfilename.find("-m=")+3]);
		return 0;
	}

	dataset datasetX, datasetC;	
	SIGNED_2B_TYPE inMTX = LoadDataset(datasetX, stInput); //save input matrix format
	stXAfilename = stInput;
	stXAfilename.tolowercase();
		
	if (inMTX == -1)
	{
		cout << "Can not load data from input file." << endl;
		return -1;
	}

	//temporary service variables
	REALNUM_TYPE f;
	SIGNED_4B_TYPE nArg = 1, intU;
	STRING_TYPE stArg, stJ;
	bool NoSeed = true;

	while (argc > ++nArg) 	
	{ 
		stArg = argv[nArg];
		stArg.parse_string();
		stJ = stArg;
		stArg.touppercase();

		intU = stArg.find("-APP="); //work only on a subset
		if (intU >= 0)
		{
			intU = atoi( stArg.substr(intU + 5, stArg.length()).c_str() );
			if ( (intU >= 0) && (intU < nActBins) ) workSubgroup = intU;
		}

		intU = stArg.find("-OUT="); //output file
		if (intU >= 0)	//use original case!
			stT2Tfilename = stJ.substr(intU + 5, stArg.length());
		
		intU = stArg.find("-REM="); //outliers analysis; e.g. -REM=3d2@1A -REM=2d1@1K
		if (intU >= 0)	
		{
			f = atof( stArg.substr(intU + 5, stArg.length()).c_str() );
			if (f > 0) OutlierZ = f;
			
			if (stArg.find("_D1") > 0)	nSmth = 0;	//use distance instead of squared distance
			
			intU = stArg.find('@');
			if (intU > 0)	ByKdist = atoi( stArg.substr(intU + 1, stArg.length()).c_str() );

			if (ByKdist > 1)
				if (stArg.find('K') > 0)	
					nSmth |= 2;	//use strictily k distances even if additional neighbors also qualify
		}

		//---------duplicate settings		
		if (stArg.find("-USEMAX") >= 0)	dupl_mode = 0;
		if (stArg.find("-USEMIN") >= 0)	dupl_mode = 1;
		if (stArg.find("-USEAV") >= 0)	dupl_mode = 2;
		intU = stArg.find("-SIMD=");	//distance cutoff
		if (intU >= 0)	
		{
			minDcut = atof( stArg.substr(intU + 6, stArg.length()).c_str() );			
			stArg = "";
		}
		intU = stArg.find("-ACTD=");
		if (intU >= 0)	
		{
			maxStdAct = atof( stArg.substr(intU + 6, stArg.length()).c_str() );			
			stArg = "";
		}

		//---------normalization settings
		intU = stArg.find("-REF="); //ref file
		if (intU >= 0)	stRfilename = stJ.substr(intU + 5, stArg.length());	//use original case!
		if (stArg.find("-ATSC") >= 0)	scale_mode = 1;
		if (stArg.find("-RESC") >= 0)	scale_mode = 2;
		if (stArg.find("-BKSC") >= 0)	scale_mode = 3;

		intU = stArg.find("-MXR2=");
		if (intU >= 0)	
		{
			f = atof( stArg.substr(intU + 6, stArg.length()).c_str() );
			if ((f > 0) && (f < 1)) MaxR2 = f;
			stArg = "";
		}

		intU = stArg.find("-MINS=");
		if (intU >= 0)	
		{
			f = atof( stArg.substr(intU + 6, stArg.length()).c_str() );
			if ((f > 0) && (f < 1)) MinStDev = f;
			stArg = "";
		}

		intU = stArg.find("-MINO=");
		if (intU >= 0)
		{
			if (stArg.find('.') > 0)
			{
				f = atof( stArg.substr(intU + 6, stArg.length()).c_str() );
				if ( (f > 0) && (f < 1.0) )	MinOcc = UNSIGNED_4B_TYPE(f*datasetX.get_Ndatapoints());
			}
			else
			{
				intU = atoi( stArg.substr(intU + 6, stArg.length()).c_str() );
				if (intU > 0) MinOcc = UNSIGNED_4B_TYPE(intU);
			}
			stArg = "";
		}
		//---------end of normalization settings


		intU = stArg.find("-M=");
		if (intU >= 0)
		{			
			if (stArg[intU + 3] == 'R') ModelID = 2;
			if (stArg[intU + 3] == 'S') ModelID = 0;
			if (stArg[intU + 3] == 'L')	ModelID = 1;
			if (stArg[intU + 3] == 'Y') ModelID = 20;
			if (stArg[intU + 3] == 'T') ModelID = 11;
			if (stArg[intU + 3] == 'N') ModelID = 12;
			if (stArg[intU + 3] == 'O') ModelID = 13;
			if (stArg[intU + 3] == 'X') ModelID = 14;
			if (stArg[intU + 3] == 'G') ModelID = 15;
			if (stArg[intU + 3] == 'U') ModelID = 16;			

			stArg = "";
		}
		intU = stArg.find("-N=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
			if ( (intU < 256) && (intU > 0) )
				if ( (intU > 1) || (ModelID != 1) )  nSplits = UNSIGNED_1B_TYPE(intU);
			stArg = "";
		}
		intU = stArg.find("-A=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
			if ( (intU > 0) && (intU < 256) ) nActBins = UNSIGNED_1B_TYPE(intU);
			if (ModelID == 0) sfexclMode|= SFEXCL_SEED_BYACTS;
			if (stArg[stArg.length()-1] == 'R')	ActBinEqSize = false;
			stArg = "";
		}

		intU = stArg.find("-S=");
		if (intU >= 0)
		{
			if (stArg.find('.') > 0)
			{
				f = atof( stArg.substr(intU + 3, stArg.length()).c_str() );
				if ( (f > 0) && (f < 1.0) )	rtFraction = f;
			}
			else
			{
				intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
				if (intU > 0) nFraction = UNSIGNED_4B_TYPE(intU);
			}
			stArg = "";
		}
		intU = stArg.find("-Z=");
		if (intU >= 0)
		{
			if (stArg[intU + 3] == 'C') { sfexclMode |= SFEXCL_METRIC_COSINE; MetricKind = 1; };
			if (stArg[intU + 3] == 'R') { sfexclMode |= SFEXCL_METRIC_CORR; MetricKind = 2; };
			if (stArg[intU + 3] == 'T') { sfexclMode |= SFEXCL_METRIC_TANIMOTO; MetricKind = 3; };
			if (stArg.length() > intU + 4)
			{
				f = atof( stArg.substr(intU + 4, stArg.length()).c_str() );
				if (f > 0)	k__Metric = f;
			}
		}
		intU = stArg.find("-R=");
		if (intU >= 0)
		{
			if (stArg[intU + 3] == 'U') sfexclMode |= SFEXCL_R_BYUSER;
			if (stArg[intU + 3] == 'D') sfexclMode |= SFEXCL_R_BYDIST;
			
			if (stArg.length() > intU + 4)
			{
				f = atof( stArg.substr(intU + 4, stArg.length()).c_str() );
				SfDiss = f;
			}
		}
		
		intU = stArg.find("-4EXT");
		if (intU >= 0) NameStyle4External = true;

		intU = stArg.find("-SRND=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 6, stArg.length()).c_str() );
			srand(UNSIGNED_4B_TYPE(intU));
			stArg = "";
		}

		if (ModelID) //the rest is the Sphere Exclusion parameters
			continue; 

		intU = stArg.find("-E=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
			if ((intU > 0) && (intU < 256))	p2seed = UNSIGNED_1B_TYPE(intU);
			stArg = "";
		}
		intU = stArg.find("-+=");
		if (intU >= 0) 
		{
			NoSeed = false;		//override default settings if the user specified this seeding key
			
			if (stArg.find("LO") > 0)	sfexclMode |= SFEXCL_SEED_MINACT;
			if (stArg.find("HI") > 0)	sfexclMode |= SFEXCL_SEED_MAXACT;
			stArg.replace("LO", "0");
			stArg.replace("HI", "0");
			stArg.replace("-+=", "");
			stArg += ',';
			while (stArg.length())
			{
				intU = stArg.find(',');
				intU = atoi(stArg.substr(0, stArg.find(',')).c_str());
				if (intU > 0 ) extseed.PutInSet(--intU);
				stArg = stArg.substr(stArg.find(',') + 1, stArg.length());
			}
		}
		intU = stArg.find("-D="); //next sphere selection
		if ((intU >= 0) && (stArg.length() > intU + 3))
		{
			if (sfexclMode & SFEXCL_NEXTSF_RAND) sfexclMode -= SFEXCL_NEXTSF_RAND; //remove default

			if (stArg[intU + 3] == 'R') sfexclMode |= SFEXCL_NEXTSF_RAND;
			if (stArg[intU + 3] == 'L') sfexclMode |= SFEXCL_NEXTSF_STEP1_MIN;
			if (stArg[intU + 3] == 'S') sfexclMode |= SFEXCL_NEXTSF_STEP1_SUMDIST;
			if (stArg.length() > intU + 4)
			{
				if (stArg[intU + 4] == 'L') sfexclMode |= SFEXCL_NEXTSF_STEP2_MIN;
				if (stArg.length() > intU + 5)
					if (stArg[intU + 5] == '1') sfexclMode |= SFEXCL_NEXTSF_SPHERES;
			}
		}
		intU = stArg.find("-TRN=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
			if ( (intU > 0) && (intU < 256) ) p2train = UNSIGNED_1B_TYPE(intU);
			stArg = "";
		}
		intU = stArg.find("-TST=");
		if (intU >= 0)
		{		
			intU = atoi( stArg.substr(intU + 3, stArg.length()).c_str() );
			if ( (intU > 0) && (intU < 256) ) p2test = UNSIGNED_1B_TYPE(intU);
			stArg = "";
		}
		intU = stArg.find("-2TRN");
		if (intU >= 0) sfexclMode |= SFEXCL_SPLIT_FIRST2TRN;
	}//while (argc > ++nArg) loop
	//----------- end of reading the settings
	
	if ((sfexclMode & SFEXCL_NEXTSF_RAND) && NoSeed)
	{//post-reading adjustments of defaults! Feb 04 2009 
		sfexclMode |= SFEXCL_SEED_MAXACT;
		sfexclMode |= SFEXCL_SEED_MINACT;
	}

	//------------------------------------------------------------------------------
	//standalone modes that do not create new splits. Separate handling	
	if (ModelID > 10)
	{
		char sst[16];	//service variable to convert counter into string
		//input matrix format, new one by default
		UNSIGNED_1B_TYPE outMTX = 0;
		if (stT2Tfilename.length() == 0)
		{
			stT2Tfilename = stXAfilename;
			outMTX = (UNSIGNED_1B_TYPE)inMTX;
		}
		else
		{
			if ( !CheckStrEnding(stT2Tfilename, ".x") && !CheckStrEnding(stT2Tfilename, ".xa")
					&& !CheckStrEnding(stT2Tfilename, ".svm") )
			{
				CutStrEnding(stT2Tfilename);
				stT2Tfilename += ".xa"; //default format
			}

			if (CheckStrEnding(stT2Tfilename, ".svm")) outMTX = 2;
			if (CheckStrEnding(stT2Tfilename, ".x")) outMTX = 1;
		}

		if ( (ModelID > 10) && (ModelID < 20) )
		if (stT2Tfilename == stXAfilename)
		{//modify output file name, if needed, to prevent overwriting
			CutStrEnding(stT2Tfilename);
			if (ModelID == 12)	stT2Tfilename += "_mdf";
			if (ModelID == 13)	stT2Tfilename += "_red";
			if (ModelID == 16)	stT2Tfilename += "_unq";
			if ((ModelID == 14)||(ModelID == 15))
			{
				stT2Tfilename += "_" + stRfilename;
				if (stRfilename.find('/') > 0) stT2Tfilename.replace("/", "_slash_");
			}
		}

		if (ModelID == 16)
		{
			datasetX.calc_dist(999, k__Metric, MetricKind);
			intU = datasetX.get_Ndatapoints();
			datasetX.test.Dump(); 
			datasetX.train = set(0, intU);					
			
			QSAR QQ;
			set dupl;
			SIGNED_4B_TYPE h;			
			apvector<REALNUM_TYPE> dacts;
			apvector<SIGNED_4B_TYPE> dids;

			for (nArg = 0; nArg < intU; nArg++)
			{
				if (datasetX.test.IsInSet(nArg)) continue;
				dupl.Dump();				
				for (h = nArg + 1; h < intU; h++)
				{
					if (datasetX.test.IsInSet(h)) continue;
					if (datasetX.get_Distance(nArg, h) > minDcut) continue;
					//below distance cutoff, treat as duplicates
					dupl.PutInSet(h);
					datasetX.test.PutInSet(h);
					datasetX.train.RemoveFromSet(h);					
				}
				if (dupl.IsEmpty()) continue;
				dupl.PutInSet(nArg);
				datasetX.test.PutInSet(nArg);
				dupl.GetList(dids);
				dacts.resize(dids.length());
				for (h = 0; h < dids.length(); h++)	dacts[h] = datasetX.get_Act(dids[h]);
				if (maxStdAct < QQ.stdev(dacts))
				//variation in activity exceeds allowed, remove all the points
					datasetX.train.RemoveFromSet(nArg);
				else
				{				
					switch (dupl_mode)
					{
						case 1:	f = QQ.minV(dacts); break;
						case 2:	f = QQ.meanV(dacts); break;
						case 0:
						default:
								f = QQ.maxV(dacts); break;
					}
					datasetX.set_Act(nArg, f); //adjust activity
				}				
			}//nArg	

			if (!datasetX.test.IsEmpty())			
			{
				datasetC = datasetX.get_training_set();
				SaveDataset(datasetC, stT2Tfilename, outMTX);

				datasetC = datasetX.get_test_set();
				CutStrEnding(stT2Tfilename);
				stT2Tfilename += "_dupls";
				SaveDataset(datasetC, stT2Tfilename, outMTX);
			}
		}

		if (ModelID == 15)
		{//merging descriptor matrices
			intU = INVALID;
			if (stRfilename.length() > 0)
			if (LoadDataset(datasetC, stRfilename) > -1)			
				intU = datasetX.ExpandDescriptors(datasetC);
					
			if (intU == INVALID)
				cout << "Specified file ('-REF=..')is invalid or has incorrect scaling." << endl;
			else
				SaveDataset(datasetX, stT2Tfilename, outMTX);			
		}

		if (ModelID == 14)
		{//splitting based on activity of a given descriptor
			intU = INVALID;
			if (stRfilename.length() == 0) 
				stRfilename = "_";	//use ACT if no label specified
			else
				intU = datasetX.get_dscr_pos( stRfilename );

			if ((intU == INVALID) && (stRfilename != "_"))
				cout << "Can not identify the descriptor. Check its label in '-REF=..'." << endl;
			else
			{
				nActBins = max(nActBins, 2); //def. 2 bins
				if (stRfilename == "_")
					datasetX.get_ActValues(knn_stats);
				else
				{					
					datasetX.get_DimRowValues(intU, knn_stats);					
					set setDims(0, datasetX.get_Ndimensions());
					setDims.RemoveFromSet(intU);
					datasetX.reduce_dimensions(setDims);
				}
				QSAR QQ;
				apvector_set_type Dsets(nActBins);
				REALNUM_TYPE minDV = QQ.minV(knn_stats), BinSpan;
				BinSpan = (QQ.maxV(knn_stats) - minDV) / nActBins;
				
				for (intU = 0; intU < knn_stats.length(); intU++)
				{
					for (nArg = 1; nArg < nActBins; nArg++)
					if ( knn_stats[intU] < (minDV + nArg*BinSpan) )						
						break;
					
					Dsets[nArg - 1].PutInSet(intU);
				}
				
				CutStrEnding(stT2Tfilename);
				for (intU = 0; intU < nActBins; intU++)
				{
					datasetX.test = Dsets[intU];
					datasetC = datasetX.get_test_set();					
					sprintf(sst, "_pt%d", intU);
					stArg = stT2Tfilename + sst;	
					SaveDataset(datasetC, stArg, outMTX);
				}
			}				
		}

		if (ModelID == 13)
		{//outlier removal mode, normally the descriptor file should be normalized prior to this!!			
			datasetX.calc_dist(0, k__Metric, MetricKind);

			intU = datasetX.get_Ndatapoints();
			datasetX.get_NearNeibDistances(knn_stats, ((ByKdist == 0) ? (intU - 1) : ByKdist), 0, nSmth);
			f = knn_stats[0] + OutlierZ * knn_stats[2];
			if (nSmth & 1) f = sqrt(f);
			
			datasetX.test.Dump(); 
			datasetX.train = set(0, intU);
			
			REALNUM_TYPE didi = 0;
			for (nArg = 0; nArg < intU; nArg++)
			{
				if (ByKdist)					
					didi = datasetX.get_MinDistance(nArg);
				else
					didi = datasetX.get_AverageDistance(nArg);

				if (didi > f) 
				{
					datasetX.train.RemoveFromSet(nArg);
					datasetX.test.PutInSet(nArg);
				}
			}
			
			if (!datasetX.test.IsEmpty())			
			{
				datasetC = datasetX.get_training_set();
				SaveDataset(datasetC, stT2Tfilename, outMTX);

				datasetC = datasetX.get_test_set();
				CutStrEnding(stT2Tfilename);
				stT2Tfilename += "_outlrs";
				SaveDataset(datasetC, stT2Tfilename, outMTX);
			}

		}//if (ModelID == 13)

		if (ModelID == 12)
		{//matrix file normalization
			if (stRfilename.length() == 0) 
			{//remove redundant and normalize by itself	
				if ((MaxR2 < 1) && (datasetX.get_Ndatapoints() > 2))	datasetX.RemoveHiCorrDims(MaxR2);
				if ((MinStDev > 0) || (MinOcc > 0)) datasetX.RemoveLowVarDims(MinStDev, MinOcc);
				datasetX.scale_dimensions(scale_mode);
			} 
			else
				if (LoadDataset(datasetC, stRfilename) > -1)
					datasetX.normalizeby(datasetC);

			SaveDataset(datasetX, stT2Tfilename, outMTX);

		}//if (ModelID == 12)

		if (ModelID == 11)
		{//matrix file conversion
			cout << "Input file '"<< stInput << "'conversion into '" << stT2Tfilename << "'" << endl;
			SaveDataset(datasetX, stT2Tfilename, outMTX);
		}

		if (ModelID == 20) 
		{//y-randomization or progressive scrambling
			stInput = stT2Tfilename;
			CutStrEnding(stInput);
					
			for (intU = 0; intU < nSplits; intU++)
			{
				cout << "Y-randomization #" << intU + 1 << endl;
				datasetX.randomizeY(nActBins, ActBinEqSize);
				
				sprintf(sst, "_Y%d", intU);
				stArg = stInput + sst;	
				SaveDataset(datasetX, stArg, outMTX);
			}//for intU
		};//if (ModelID == 20)

		cout << "Done." << endl;
		return 0;
	}//if (ModelID > 11)
	//------------------------------------------------------------------------------

	//save splits in the form of datapoint numbers that belong to test and training sets
	bool ifNewOutput = true;
	if (stT2Tfilename.length())
	{
		if (CheckStrEnding(stT2Tfilename, ".list"))
			ifNewOutput = false;
	}
	else
		stT2Tfilename = stXAfilename;

	if (ifNewOutput)
	{
		CutStrEnding(stT2Tfilename);
		stT2Tfilename += ".t2t";
	}

	FILETYPE_OUT foT2Tfile(stT2Tfilename.c_str());
	CutStrEnding(stT2Tfilename); //to prepare a naming core

	//commentary line
	stArg = "#Run with:'";		
	for (nArg = 0; nArg < argc; nArg++) { stArg += BLANK; stArg += argv[nArg]; };
	stArg += "'";
	if (ifNewOutput) foT2Tfile << stArg << endl; else cout << stArg << endl;
	//foT2Tfile << stArg << endl;
	//now we can run the appropriate algorithm

	//declare various variables that might be needed later
	set setC, setV, setX(0, datasetX.get_Ndatapoints());
	apvector<dataset> datasetActs;
	
	
	lneib lgos; //for leave-group-out
	
	bool ifReintegrate;
	dataset datasetV;
	if ( (nActBins > 1) && (workSubgroup > INVALID) )
	{//extract subset to work on!! dangerous : )
		ifReintegrate = true;
		datasetV = datasetX;
		f = datasetV.get_MaxAct() - datasetV.get_MinAct();
		f	/= nActBins;
		//workset is in setV
		setV = datasetV.get_ActPoints(datasetV.get_MinAct() + f*workSubgroup, 
			datasetV.get_MinAct() + f*(workSubgroup + 1));
		datasetX = datasetV.subset(setV);
	}
	else
		ifReintegrate = false;

	switch (ModelID)
	{
		case 2: //random split
			for (intU = 0; intU < nSplits; intU++)
			{
				cout << "Split #" << intU + 1 << " ...";
				if (nFraction)
					datasetX.rand_split(nFraction, nActBins, ActBinEqSize);
				else
					datasetX.rand_split(rtFraction, nActBins, ActBinEqSize);

				if (ifReintegrate) ReIntegrateData(datasetV, datasetX, datasetC);

				if (ifNewOutput)
				{
					SaveDataName(foT2Tfile, stInput);					
					SaveSetAsText(foT2Tfile, datasetX.train);
					SaveSetAsText(foT2Tfile, datasetX.test);
				}
				else
					SaveOneSplitFiles(intU, stT2Tfilename, foT2Tfile, datasetX, NameStyle4External, inMTX);

				if (ifReintegrate) datasetX = datasetC; //May 31 2008 Aleks
				cout << "ok" << endl;
			}//for intU
		break;
	
		case 1: //leave group out split onto nSplits groups
			cout << "Leave-group-out splitting..." << endl;
			datasetX.lgo_split(lgos, (1.0/REALNUM_TYPE(nSplits)), nActBins, ActBinEqSize);
			for (intU = 0; intU < lgos.length(); intU++)
			{
				cout << "Set " << (intU + 1) << endl;
				datasetX.test = lgos[intU];
				datasetX.train = setX - datasetX.test;

				if (ifReintegrate) ReIntegrateData(datasetV, datasetX, datasetC);
				if (ifNewOutput)
				{
					SaveDataName(foT2Tfile, stInput);					
					SaveSetAsText(foT2Tfile, datasetX.train);
					SaveSetAsText(foT2Tfile, datasetX.test);
				}
				else				
					SaveOneSplitFiles(intU, stT2Tfilename, foT2Tfile, datasetX, NameStyle4External, inMTX);

				if (ifReintegrate) datasetX = datasetC; //May 31 2008 Aleks
			}
		break;

		case 0:	//sphere exclusion
		default:
			if (nFraction == 0) nFraction = 5; //adjust default value, Feb 17 2009

			cout << "Optimizing initial radius..." << endl;
			//first run also calculated distance matrix!
			SfExclR = datasetX.sfexcl_split(extseed, sfexclMode, SfDiss, true, p2test, p2train, p2seed, k__Metric);
			f	 = datasetX.get_AverageDistance() - SfExclR;
			f	/= 3 * nSplits; //use triple presision while scanning for the starting R
			nArg = 0;
			intU = datasetX.test.Size();
			if (sfexclMode & SFEXCL_R_BYDIST) sfexclMode -= SFEXCL_R_BYDIST;
			sfexclMode |= SFEXCL_R_BYUSER;
			while ( (intU < SIGNED_4B_TYPE(nFraction)) || (intU < REALNUM_TYPE(datasetX.train.Size())*rtFraction/(1-rtFraction)) )
			{//radius has to be adjusted
				SfDiss = SfExclR + f;
				SfExclR = datasetX.sfexcl_split(extseed, sfexclMode, SfDiss, false, p2test, p2train, p2seed, k__Metric);
				intU = datasetX.test.Size();
				if (++nArg > 3 * nSplits)
				{
					stArg = "#No satisfactory split could be found.";
					foT2Tfile << stArg << endl;
					foT2Tfile.close();
					cout << stArg << endl;
					return -1;
				}
			}

			//use average of interpoint distance as upper boundary for the sphere's radius
			SfDiss	 = SfExclR;
			f	 = datasetX.get_AverageDistance() - SfExclR;
			f	/= nSplits;

			for (intU = 0; intU < nSplits; intU++)
			{
				cout << "Split " << intU + 1 << " ...";
				SfExclR = datasetX.sfexcl_split(extseed, sfexclMode, SfDiss, false, p2test, p2train, p2seed, k__Metric);
				SfDiss	+= f;
				cout << "|...";

				if (ifReintegrate) ReIntegrateData(datasetV, datasetX, datasetC);

				//for now let's save everything
				if (ifNewOutput)
				{
					SaveDataName(foT2Tfile, stInput);
					SaveSetAsText(foT2Tfile, datasetX.train);
					SaveSetAsText(foT2Tfile, datasetX.test);
				}
				else
					SaveOneSplitFiles(intU, stT2Tfilename, foT2Tfile, datasetX, NameStyle4External, inMTX);

				if (ifReintegrate) datasetX = datasetC; //May 31 2008 Aleks

				cout << "ok" << endl;
			}
		break;
	};

	foT2Tfile.close();
	cout << "Done." << endl;
	return 0;
}

