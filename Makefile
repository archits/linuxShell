all:
	gcc -o my_shell my_shell.c
shell:
	gcc -o my_shell my_shell.c
run: my_shell
	./my_shell
clean:
	rm -f my_shell *.o