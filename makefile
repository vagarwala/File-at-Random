randfile: randfile.c
	gcc randfile.c
clean:
	rm *~
run: randfile
	./randfile
