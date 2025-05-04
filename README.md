# recursive-dir-sync-c
A C program that recursively traverses a source directory and replicates its structure into a destination directory. It handles files based on their type and extension.
Write a program in the C language that takes 3 command-line arguments: a source directory, a destination directory, and a positive natural number.
The program will recursively traverse the directory structure starting from the source directory. For each entry in the source directory, the following operations will be performed depending on the entry type:

For directories, an equivalent directory will be created in the destination directory, with the same permissions as the original. Thus, the directory structure in the destination will mirror that of the source.

For regular files, depending on the file extension:

For files with the .txt extension, the program will count the number of spaces in the file. If the number of spaces is greater than the number given as the third argument, the program will create a symbolic link to that file in the destination directory (or in the appropriate subdirectory), using the original file name with the prefix "spaces_". These links will have the same access permissions as the original files.
Example: If a file named file1.txt contains more spaces than the given number, the program will create a symbolic link named spaces_file1.txt pointing to it.

For files with other extensions, a copy of the file will be created in the destination directory (and, if applicable, in the corresponding subfolder). The copied files will retain the read permissions of the original file only.
Example: If the original file has permissions -rwx-wxr-x, the copied file will have permissions -r-----r--.

For symbolic links, no operations will be performed.

The project must also include a corresponding Makefil
