# Find all source/header files
files=$(find ../source -type f \( -iname "*.cpp" -o -iname "*.c" -o -iname "*.h" -o -iname "*.hpp" \))

# List of files (improved handling of spaces)
printf "%s\n" $files

# Run indent, passing the combined list of files
indent -bap -bli0 -i4 -l79 -ncs -npcs -npsl -fca -lc79 -fc1 -ts4 $files

# Remove old files that have ~ after them
find ../source -type f \( -iname "*.cpp~" -o -iname "*.c~" -o -iname "*.h~" -o -iname "*.hpp~" \) -exec rm -f {} \;

# Optional bell sound
printf '\a'
