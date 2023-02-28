stringMe: vyasVedantA2.o vyasVedantA2Main.o
	gcc -Wall -std=c99 vyasVedantA2.o vyasVedantA2Main.o -o bin/stringMe

vyasVedantA2.o: src/vyasVedantA2.c include/vyasVedantA2.h
	gcc -Wall -std=c99 -c src/vyasVedantA2.c

vyasVedantA2Main.o: src/vyasVedantA2Main.c include/vyasVedantA2.h
	gcc -Wall -std=c99 -c src/vyasVedantA2Main.c
	
clean:
	rm *.o bin/stringMe
