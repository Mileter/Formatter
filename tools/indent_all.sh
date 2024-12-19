# Find all source/header files
files=$(find ../source -type f \( -iname "*.cpp" -o -iname "*.c" -o -iname "*.h" -o -iname "*.hpp" \))

# List of files (improved handling of spaces)
printf "%s\n" $files

# Run indent, passing the combined list of files
indent -bap -bli0 -i4 -l79 -ncs -npcs -npsl -fca -lc79 -fc1 -ts4 $files

printf '\a'