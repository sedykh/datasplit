Datasplit is a "swiss-knife" tool for processing and preparation of data sets.
Datasplit works with descriptor matrices of the following formats:
.svm, .xa, .x (see input_demo* files)

To print detailed help, run datasplit without parameters.
"-M=" command key specifies the mode work,
additional help is available for each mode by running "datasplit -M=.."

-------
Usage examples:
1) Scaling descriptors and removing those with less than 5 unique values:
	"datasplit input_demo1.xa -M=N -MINO=5 -OUT=scaled.xa"

2) Splitting a dataset into random 5-fold modeling and external sets:
	"datasplit input_demo1.xa -M=L -N=5 -4EXT -OUT=ecv5f.list"

3) Splitting a modeling set into several internal training and test subsets:
	"datasplit input_demo1.xa -M=S -N=10 -OUT=ecv5f.t2t"

4) Splitting a dataset once by sampling randomly 9 points out:
	"datasplit input_demo1.xa -M=R -S=9 -N=1 -OUT=r1split.list"

NB: Examples 2-4) produce "split-files" (.t2t or .list) which can be used as input for knn+ modeling

Datasplit help print out (just run "datasplit")
---------------------------------------------
#Datasplit V4.14 - Divides data into training and test sets.
Usage:     datasplit filename [flags]
Default output: filename.t2t
Allowed input: .xa files or .x & .a files with matching names.
NB: Do not use blanks or tabs in descriptor or chem.names!

Possible flags are:
'-OUT=' specifies output name, use '.list'-ending to output in old format

'-M=m', m <METHOD> can be:
'S'  = Sphere-Exclusion split <default>
'R'  = Randomly pick test-set
'L'  = Leave-Group-Out split
'Y'  = Y-randomization (progressive scrambling)
'T'  = Transfer input matrix format into output format
'N'  = Normalize input matrix
'U'  = Remove duplicate points
'O'  = Remove outliers
'G'  = Merge two descriptor-matrices
'X'  = Partition based on values of a specified descriptor.
'-N=n', n is the number of splits to do <default 10>
'-S=s'	= Test-set size or fraction, where 's' is a real or integer number <default 0.1>
'-A=..' = Use activity-bins <1-255> for stratified sampling, i.e.'-A=2R' sets 2 bins of
equal act.range ('R'-flag); <default: bins with equal #dpoints>

Parameters related to 'Sphere-Exclusion' or 'Outlier-Removal':
'-Z=zx' = Metric to use; x - is a power coff. <default 2.0>
z: E -Euclidean <default>, T -Tanimoto, R -Corr., C -Cosine
'-R=rx', sphere's radius, where x is initial scale-factor <default 0.01>
r is 'U','D','V': User-defined <by x>, Distance- or Volume-based <default>

'-4EXT': to use 'external/modeling' naming instead of 'test/train'
'-SRND=..': to seed randomizer <default: by time>
Also, for more specific help run with -M= argument.

