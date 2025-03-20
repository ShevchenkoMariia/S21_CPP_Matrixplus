CC = g++
CFLAGS = -std=c++17 -Werror -Wextra -Wall
CHECK_FLAGS = #g++ m.cpp -o test -lgtest -pthread

all: s21_matrix_oop 

s21_matrix_oop: main.cpp s21_matrix_oop.cpp 
	$(CC) $(FLAGS) main.cpp s21_matrix_oop.cpp 
	./a.out

# Содание статической библиотеки
s21_matrix_oop.a:
	ar rc $@ s21_matrix_oop.o
	ranlib $@
	rm *.o

s21_matrix_oop.o: s21_matrix_oop.c s21_matrix_oop.h 
	$(CC) $(CFLAGS) -c $< 
