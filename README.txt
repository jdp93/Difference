Joseph Pallansch

This program is designed to take in two files and print out the difference in
terms of each file to new files called diffone and difftwo using two different
methods of comparison. The time each method takes will be printed to the
screen. If the files diffone or difftwo already exist it will overwrite part
or all of the file with the new differences.

To compile the program use the command
make
OR
make myprog
OR
gcc difference.c -o difference

To run the program use the command
./difference input1 input2
Where input1 and input2 are the names of the files you wish to compare

After running the program use the command
make clean
OR
rm difference; rm diffone; rm difftwo
To remove the files created by compiling and running the program

In this project, the second method is faster than the first method for
comparing files, especially large files. I believe this is because the number
of times the read and write command are called for the first method is
dependent on the size of the file (i.e. larger files require more commands).
However, the second method uses only two read commands and one write command
regardless of file size.
