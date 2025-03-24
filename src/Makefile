CC = g++
CFLAGS = -std=c++17 -Werror -Wextra -Wall
CHECK_FLAGS = -lgtest -pthread

# Исходные файлы
SRC_FILES = s21_matrix_oop.cpp tests.cpp
# Заголовочные файлы
HEADER_FILES = s21_matrix_oop.h
# Объектные файлы
OBJ_FILES = s21_matrix_oop.o tests.o

all: s21_matrix_oop test

# Сборка библиотеки
s21_matrix_oop: s21_matrix_oop.o
	ar rc s21_matrix_oop.a $^
	ranlib s21_matrix_oop.a

# Сборка тестов
test: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o test $(CHECK_FLAGS)
	./test

# Компиляция объектных файлов
s21_matrix_oop.o: s21_matrix_oop.cpp $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

tests.o: tests.cpp $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f *.o s21_matrix_oop.a test

check_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.cpp *.h
	@rm .clang-format
