CC = g++

I_FLAG      = -I Include/
DEBUG_FLAGS = -fsanitize=address,leak,undefined -Wall -g
C_FLAGS     = -c -O2

noAVX: table.o reader.o List.o logsLib.o main.o 
	$(CC) table.o reader.o List.o logsLib.o main.o -o table	$(DEBUG_FLAGS)
clear:
	rm -rf *.o 

main.o:		main.cpp
	$(CC) $(C_FLAGS) -c main.cpp 		  $(I_FLAG)
table.o:	Table/table.cpp
	$(CC) $(C_FLAGS) -c Table/table.cpp   $(I_FLAG)
reader.o:	Parser/reader.cpp
	$(CC) $(C_FLAGS) -c Parser/reader.cpp $(I_FLAG)
List.o:		List/List.cpp
	$(CC) $(C_FLAGS) -c List/List.cpp	  $(I_FLAG)
logsLib.o:	List/logsLib.cpp
	$(CC) $(C_FLAGS) -c List/logsLib.cpp  $(I_FLAG)