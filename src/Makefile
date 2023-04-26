OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    BUILD_FILE_TMP = SmartCalcFront
    BUILD_FILE = SmartCalc
    OPEN = xdg-open
else
    BUILD_FILE_TMP = SmartCalcFront.app
    BUILD_FILE = SmartCalc.app
    OPEN = open
endif

#-------------------------------------------------------
#    Расположение каталога
#-------------------------------------------------------

TMP_DIR = ./tmp
BUILD_DIR = ../build
DIST_DIR = ./"SmartCalc_v1.0"

#-------------------------------------------------------
#    Переменная для создания каталогов
#-------------------------------------------------------

BUILD = @mkdir -p $(BUILD_DIR)

TMP = @mkdir -p $(TMP_DIR)

DIST = @mkdir -p $(DIST_DIR)

#-------------------------------------------------------
#    dist name
#-------------------------------------------------------

DIST_NAME = $(DIST_DIR).tar.gz

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: install

install:
	$(BUILD)
	$(TMP)
	cd tmp && cmake ../SmartCalcFront/. -B . && cmake --build .
	cp -R ./tmp/$(BUILD_FILE_TMP) $(BUILD_DIR)/$(BUILD_FILE)
	rm -rf tmp

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	open dvi.html

dist:
	$(DIST)
	cp -r Makefile ./SmartCalcFront ./SmartCalcBack $(DIST_DIR)
	tar -cvzf $(DIST_NAME) $(DIST_DIR)
	rm -rf $(DIST_DIR)

smart_calc.a:
	cd SmartCalcBack && make smart_calc.a

test:
	cd SmartCalcBack && make test

gcov_report:
	cd SmartCalcBack && make gcov_report
	$(OPEN) ./SmartCalcBack/report/report.html

clang:
	cd SmartCalcBack && make clang

cppcheck:
	cd SmartCalcBack && make cppcheck

leaks:
	cd SmartCalcBack && make leaks

clean_src:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_NAME)
	rm -rf $(TMP_DIR)

clean: clean_src
	cd SmartCalcBack && make clean
