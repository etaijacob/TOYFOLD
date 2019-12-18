
# TOYFOLD
## A Software suite to perform enumeration and simulations of a simplified model (i.e. toy model) of protein structure and folding process

All code is written in C++ and Perl. 
Not all software features are currently documented. 
In the future, I plan to modify this software to an R package.

The software includes the following tools:
1) Enumerate all possible configuration of a sequence of length N on a 2D lattice.
2) Randomly generate sequenes of length N from a given composition of H P + -
3) Find the (global) minimal energy structure of a given sequence and the following energy matrix:
                           H       P       +       -
											H   -1.0    0.0      0.0     0.0 
 											P    0.0   -0.75    -0.25   -0.25 
											+    0.0   -0.25    +1.0    -1.25
											-    0.0   -0.25    -1.25   +1.0  

Other energy matrices could be configured also (currently it should be done hardcoded in the file "protchap.cpp")
4) Run folding of single domain and double domain proteins.
5) Compare results of folding simulations to minimal energy structure of each sequence.

There are additional features in the program that are not listed here which you are welcome to explore or email me for further questions.

If you use this software please cite:

A tale of two tails: why are terminal residues of proteins exposed?.
Etai Jacob, Ron Unger
Bioinformatics, Volume 23, Issue 2, 15 January 2007, Pages e225–e230

Different mechanistic requirements for prokaryotic and eukaryotic chaperonins: a lattice study.
Etai Jacob, Amnon Horovitz, Ron Unger
Bioinformatics, Volume 23, Issue 13, July 2007, Pages i240–i248

## To install from binary (compiled for Mac OS):
Download all binary files from the bin folder (TOYFOLD/bin/*).

## To install from source:
Download or clone this repository to a mac or Linux machine.

Open a terminal (on Mac or Linux machine) and do the following:
```
cd TOYFOLD/seqSeeker
```

Generate binary for 2D enumaration (1):

```
make enumeration
chmod +x ./noFixedStructEnum
```

An example of how to generate all possible 2D configurations of sequences of length 15 within a space of 18 by 18.
```
./noFixedStructEnum 15 3 3 ../outputdir/my_all_possible_15mer_2D_lattice_configurations.bindb
```


Generate binary for sequence permutations (2):
```
make seq
chmod +x ./seqperm
```

An example of how to generate 100 random sequences of length 15 with polar tails (+/-) and composition of 40% H, 40% P, 10% + and 10% -:
```
./seqperm 13 100 40 40 10 10 > ../outputdir/my_100_15mer_sequence_permutations.seq
```

Generate a binary file for the program which finds the (global) minimal energy structure of a given sequence:
```
make seeker
chmod +x ./skaV21
```

Find the minimal energy structures of all those 100 15mer sequences:
```
../bin/skaV21 15 ../outputdir/my_100_15mer_sequence_permutations.seq ../outputdir/my_all_possible_15mer_2D_lattice_configurations.bindb > ../outputdir/my100_15mer_native_global_minima_structures.fdb
```


Compiling and installing the protein folding simulator:

```
cd ../simulator/
make clean
make TOYFOLD

```

Running single domain of length 15 and sequence +PP-HPH+HHHPHP-, 10 folding simulations of 10000 steps each with a simulation factor of 1 and save output to a file with a prefix ../outputdir/my_tmp_free_fold (4):
```
../bin/V21 -freeFold 15 10000 5 10 1 ../outputdir/my_tmp_free_fold +PP-HPH+HHHPHP-
```

Looking for the closest structures from the kinetic simulations to the native (global minima structure) structure in means of RMSD (5):

```
../bin/V21 -RMSDsingle 15 ../outputdir/my_tmp_free_foldfc-itr10000.data ../outputdir/my100_15mer_native_global_minima_structures.fdb 1
```
Running double domain folding simulations (4):

```
../bin/V21 -freeFoldDouble 55 100000 5 5 1 ../outputdir/my_tmp_freeFoldDoubleDomain_ +-P+HPHH+HPHH-HPHPHHPHPH-PPPPP+HHHPPP+P+H-PHHHHHHPH-HP- 1 25 31 55
```

Looking for the closest structures from the kinetic simulations to the native (global minima structure) structure in means of RMSD:

```
TBD
```

Etai

