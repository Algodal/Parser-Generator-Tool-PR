config: algodal-parser-header.h algodal-parser-vm.c config-program.c main.c
	gcc -g algodal-parser-header.h algodal-parser-vm.c config-program.c main.c -o config

test: config main.c
	clear && ./config config.ini
