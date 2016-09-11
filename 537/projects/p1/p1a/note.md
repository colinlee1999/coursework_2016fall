# Project 1 part a #


1. Compile ```genvar.c```

		gcc -o genvar genvar.c -Wall -Werror -I../include

2. Generate the input file

		./genvar -s 200 -n 100 -o input_file -m 32

3. Compile ```dumpvar.c```

		gcc -o dumpvar dumpvar.c -Wall -Werror -I../include
4. 