#Runs all of the scripts!

#Setup
for dir in */; do
    cd "$dir";

    #Reformatting original data files to new format
    for datafile in DATA*.txt; do
        if [ -e $datafile ]; then
            echo "New Datafile!"
            dirName=${dir:0:${#dir}-1}          # Removing the '/' from the end
            newdf=${datafile/DATA/$dirName}     # Changing DATA to be more descriptive (directory name)
            mv $datafile ${newdf/txt/in}        # Changing suffix to be .in instead of .txt
        fi
    done

    #Compiling and running scripts
    for script in *.cpp; do
        compiled=${script/%.cpp/}
        g++ -O2 -o $compiled $script      # Compile the script
        for datafile in *.in; do
            output=${datafile/%in/out}
            ./${compiled} < $datafile > $output
        done
    done


    cd ..;
done

