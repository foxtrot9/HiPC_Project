HiPC Student Programmming Challenge Intel Track Phase 2 submission

Team name: [daiict_cache_miss]

Team Members:

(1) Aayush Kapadia

(2) Mit Naria

(3) Uttam Choudhary

Input files(Download):
 
[Large (20 MB)](https://www.dropbox.com/s/njnhdq3stw8x5uk/%5Bdaiict%5D_cache_miss_large_phase2.csv?dl=1)

[Medium (4.7 MB)](https://www.dropbox.com/s/0ruh2xr2wjkgxa9/%5Bdaiict%5D_cache_miss_medium_phase2.csv?dl=1)

-----------------Example of run.sh---------------------

[mit@ubuntu]$ bash run.sh

Enter input file name:

LargeDataSet_IntelTrack.csv

Input file name is LargeDataSet_IntelTrack.csv .

Sourcefile is hipc.c and outfile is hipc.o .

Input is taken from LargeDataSet_IntelTrack.csv . Output is stored in output.csv .

rm -f hipc.o

gcc hipc.c -o hipc.o -fopenmp

--- other user output (if any) ---

Algorithm time = 2917281.000000 microsecs

IO time = 818171.000000 microsecs

End to end time = 3.771630 secs

