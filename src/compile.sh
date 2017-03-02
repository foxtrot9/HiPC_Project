# Set these things first.
SOURCE_FILE="hipc.c"
OUT_FILE="hipc.o"

echo "Sourcefile is $SOURCE_FILE and outfile is $OUT_FILE ."
# Remove any ouput and .o files
make clean
rm $OUT_FILE
# Compilation
make compile