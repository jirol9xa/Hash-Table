CC = gcc

I_FLAG      = -I src/Include/
DEBUG_FLAGS = -fsanitize=address,leak,undefined -Wall -g
C_FLAGS     = -c -O2
AVX_FLAGS   = -mavx -mavx2 -msse4.2 
ASM_FLAG    = -no-pie 

all: AVX

noAVX: table.o readerMEM32.o List.o logsLib.o main.o strcmp.o crc32.o
    $(CC) $(ASM_FLAG) src/strcmp.o src/crc32.o table.o readerMEM32.o List.o logsLib.o main.o  -o table 

AVX:   tableAVX.o readerAVX.o ListAVX.o logsLib.o mainAVX.o 
    $(CC) tableAVX.o readerAVX.o ListAVX.o logsLib.o mainAVX.o -o avx 

clear:
    rm -rf *.o 


main.o:			src/main.cpp
    $(CC) $(C_FLAGS) src/main.cpp 		  					$(I_FLAG)
mainAVX.o:		src/mainAVX.cpp
    $(CC) $(C_FLAGS) $(AVX_FLAGS) src/mainAVX.cpp			$(I_FLAG)
table.o:		src/Table/table.cpp
    $(CC) $(C_FLAGS) src/Table/table.cpp   					$(I_FLAG)
tableAVX.o:		src/Table/tableAVX.cpp
    $(CC) $(C_FLAGS) $(AVX_FLAGS) src/Table/tableAVX.cpp	$(I_FLAG)
reader.o:		Parser/reader.cpp
    $(CC) $(C_FLAGS) src/Parser/reader.cpp 					$(I_FLAG)
readerMEM32.o: 	src/Parser/readerMEM32.cpp
    $(CC) $(C_FLAGS) src/Parser/readerMEM32.cpp 			$(I_FLAG)
readerAVX.o:	src/Parser/readerAVX.cpp
    $(CC) $(C_FLAGS) $(AVX_FLAGS) src/Parser/readerAVX.cpp	$(I_FLAG)
List.o:			src/List/List.cpp
    $(CC) $(C_FLAGS) src/List/List.cpp		  				$(I_FLAG)
ListAVX.o:		src/List/ListAVX.cpp
    $(CC) $(C_FLAGS) $(AVX_FLAGS) src/List/ListAVX.cpp		$(I_FLAG)
logsLib.o:		src/List/logsLib.cpp
    $(CC) $(C_FLAGS) src/List/logsLib.cpp  					$(I_FLAG)
strcmp.o:		src/strcmp.asm
    nasm -f elf64 -w+all src/strcmp.asm
crc32.o:		src/crc32.asm
    nasm -f elf64 -w+all src/crc32.asm