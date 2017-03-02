# Set these things first.
# export NUMBER_OF_THREADS_TO_CREATE="12"
echo "Enter input file name:"
read INPUT_DATA
echo "Input file name is $INPUT_DATA ."
# output data
export OUTPUT_DATA="output.csv"
SOURCE_FILE="hipc.c"
OUT_FILE="hipc.o"

echo "Sourcefile is $SOURCE_FILE and outfile is $OUT_FILE ."
echo "Input is taken from $INPUT_DATA . Output is stored in $OUTPUT_DATA ."

# Remove any ouput and .o files
make clean
rm $OUTPUT_DATA
# Compilation
make compile
lines="0"
lines="$(wc -l < $INPUT_DATA)"
# Run it!!!
./$OUT_FILE $lines < $INPUT_DATA > $OUTPUT_DATA
