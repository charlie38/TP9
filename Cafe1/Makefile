test_automate: main.o automate.o
	clang main.o automate.o -o test_automate

main.o: main.c automate.h
	clang -c main.c

automate.o: automate.c automate.h
	clang -c automate.c
