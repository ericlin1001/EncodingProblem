all:compile run

.PHONY:compile

compile:main.cpp
	g++  main.cpp

run:a.out
	./a.out
