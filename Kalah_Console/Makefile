all : kalah

kalah : main.o manip_data.o manip_pile.o manip_game.o manip_affich.o
	gcc *.o -o kalah

main.o : main.c manip_affich.c manip_data.c manip_game.c manip_pile.c manip_saisie.c
	gcc -c main.c manip_affich.c manip_data.c manip_game.c manip_pile.c manip_saisie.c

manip_data.o :  manip_data.c
	gcc -c manip_data.c 

manip_pile.o : manip_pile.c
	gcc -c manip_pile.c

manip_game.o : manip_game.c manip_affich.c manip_pile.c
	gcc -c manip_game.c manip_affich.c manip_pile.c
	
manip_affich.o : manip_affich.c manip_game.c manip_pile.c manip_saisie.c
	gcc -c manip_affich.c manip_game.c manip_pile.c manip_saisie.c


