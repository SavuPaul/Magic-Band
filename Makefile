build: tema.c
	gcc tema.c -o tema1

run: tema1
	./tema1

clean:
	rm -f tema1
