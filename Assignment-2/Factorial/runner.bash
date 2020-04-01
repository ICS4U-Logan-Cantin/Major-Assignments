for file in *.txt; do
    ./a.out < $file > ${file/.txt/.out}
done