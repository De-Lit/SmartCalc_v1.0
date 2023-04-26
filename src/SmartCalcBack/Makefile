#-------------------------------------------------------
#    Узнаем какая ОС, Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
    LEAKS_RUN = valgrind ./test
else
    TEST_FLAGS = -lcheck
    LEAKS_RUN = CK_FORK=no leaks -atExit -- ./test
endif

FLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

#-------------------------------------------------------
#    Переменная для компилятора
#-------------------------------------------------------

CC = gcc

#-------------------------------------------------------
#    Ищем файлы для библиотеки, делаем переменную
#    Переименовываем для объектных файлов
#-------------------------------------------------------

SRCS = $(wildcard smart_calc.c) $(wildcard list_operations/*.c) $(wildcard operation_functions/*.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRCS))

#-------------------------------------------------------
#    Переменная которая указывает на наш Makefile
#-------------------------------------------------------

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#-------------------------------------------------------
#    Переменная для создания каталога report
#-------------------------------------------------------

REPORT = @mkdir -p report

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: run

run: smart_calc.c smart_calc.a
	$(CC) main.c $(FLAGS) -L. smart_calc.a -o SmartCalc -lm
	@$(MAKE) -f $(THIS_FILE) clean_src
	rm -f smart_calc.a

smart_calc.a: $(OBJ_FILES)
	ar rcs smart_calc.a $(OBJ_FILES)
	ranlib smart_calc.a
	@$(MAKE) -f $(THIS_FILE) clean_src

smart_calc_tests: ./tests/tests_header ./tests/test_*
	cat  ./tests/tests_header ./tests/test_* > ./tests/smart_calc_tests

tests.c: smart_calc_tests
	checkmk ./tests/smart_calc_tests > tests.c

test: tests.c $(SRCS)
	$(CC) tests.c $(SRCS) $(FLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) -o test
	./test

gcov_report: test
	$(REPORT)
	gcovr -r . --html --html-details -o report/report.html
	@$(MAKE) -f $(THIS_FILE) clean_src

google_style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i **/*.c **/*.h *.c *.h
	rm .clang-format

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n **/*.c **/*.h *.c *.h
	rm .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem **/*.c **/*.h *.c *.h

clean_src:
	rm -rf *.o **/*.o  *.gcda *.gcno *.gcov

leaks: test
	$(LEAKS_RUN)
	@$(MAKE) -f $(THIS_FILE) clean_src

clean: clean_src
	rm -rf report *.a test tests.c ./tests/calc_tests ./SmartCalc
