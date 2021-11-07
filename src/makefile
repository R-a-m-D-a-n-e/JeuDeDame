all: test.o partie.o coordonnees.o damier.o piece.o forme_de_prise.o deplacement.o jouer.o capture.o mouvement.o liste_config.o jouer_partie.o prise_dame.o dep_n_dame.o sauvegarder.o
	gcc -g -Wall test.o coordonnees.o deplacement.o partie.o mouvement.o piece.o forme_de_prise.o jouer.o capture.o liste_config.o jouer_partie.o prise_dame.o dep_n_dame.o sauvegarder.o damier.o -o "test12";rm *.o *~
test.o: test.c
	gcc -c -Wall test.c -o test.o
partie.o: partie.c partie.h 
	gcc -c -Wall partie.c -o partie.o
coordonnees.o: coordonnees.c coordonnees.h
	gcc -c -Wall coordonnees.c -o coordonnees.o
damier.o:  damier.c  damier.h
	gcc -c -Wall  damier.c -o  damier.o
piece.o: piece.c piece.h
	gcc -c -Wall piece.c -o piece.o
forme_de_prise.o: forme_de_prise.c forme_de_prise.h
	gcc -c -Wall forme_de_prise.c -o forme_de_prise.o
deplacement.o: deplacement.h deplacement.c
	gcc -c -Wall deplacement.c -o deplacement.o
jouer.o: jouer.h jouer.c
	gcc -c -Wall jouer.c -o jouer.o
capture.o: capture.c capture.h
	gcc -c -Wall capture.c -o capture.o
mouvement.o: mouvement.h mouvement.c
	gcc -c -Wall mouvement.c -o mouvement.o
liste_config.o: liste_config.c liste_config.h
	gcc -c -Wall liste_config.c -o liste_config.o
jouer_partie.o: jouer_partie.c jouer_partie.h
	gcc -c -Wall jouer_partie.c -o jouer_partie.o
prise_dame.o: prise_dame.c prise_dame.h
	gcc -c -Wall prise_dame.c -o prise_dame.o
dep_n_dame.o: dep_n_dame.c dep_n_dame.h
	gcc -c -Wall dep_n_dame.c -o dep_n_dame.o
sauvegarder.o: sauvegarder.c sauvegarder.h
	gcc -c -Wall sauvegarder.c -o sauvegarder.o
