CC = gcc

I_FLAG      = -I Include/
DEBUG_FLAGS = -fsanitize=address,leak,undefined -Wall -g
C_FLAGS     = -c
AVX_FLAGS   = -mavx -mavx2 -msse4.2 
ASM_FLAG    = -no-pie strcmp.o

all: AVX

noAVX: table.o readerMEM32.o List.o logsLib.o main.o strcmp.o crc32.o
	$(CC) $(ASM_FLAG) crc32.o table.o readerMEM32.o List.o logsLib.o main.o  -o table 
AVX:   tableAVX.o readerAVX.o ListAVX.o logsLib.o mainAVX.o 
	$(CC) tableAVX.o readerAVX.o ListAVX.o logsLib.o mainAVX.o -o avx 


clear:
	rm -rf *.o 

main.o:			main.cpp
	$(CC) $(C_FLAGS) main.cpp 		  		$(I_FLAG)
mainAVX.o:		mainAVX.cpp
	$(CC) $(C_FLAGS) $(AVX_FLAGS) mainAVX.cpp			$(I_FLAG)
table.o:		Table/table.cpp
	$(CC) $(C_FLAGS) Table/table.cpp   		$(I_FLAG)
tableAVX.o:		Table/tableAVX.cpp
	$(CC) $(C_FLAGS) $(AVX_FLAGS) Table/tableAVX.cpp		$(I_FLAG)
reader.o:		Parser/reader.cpp
	$(CC) $(C_FLAGS) Parser/reader.cpp 		$(I_FLAG)
readerMEM32.o: 	Parser/readerMEM32.cpp
	$(CC) $(C_FLAGS) Parser/readerMEM32.cpp 	$(I_FLAG)
readerAVX.o:	Parser/readerAVX.cpp
	$(CC) $(C_FLAGS) $(AVX_FLAGS) Parser/readerAVX.cpp	$(I_FLAG)
List.o:			List/List.cpp
	$(CC) $(C_FLAGS) List/List.cpp		  		$(I_FLAG)
ListAVX.o:		List/ListAVX.cpp
	$(CC) $(C_FLAGS) $(AVX_FLAGS) List/ListAVX.cpp			$(I_FLAG)
logsLib.o:		List/logsLib.cpp
	$(CC) $(C_FLAGS) List/logsLib.cpp  		$(I_FLAG)
strcmp.o:		strcmp.asm
	nasm -f elf64 -w+all strcmp.asm
crc32.o:		crc32.asm
	nasm -f elf64 -w+all crc32.asm