iv:V:
	cc iv.c -lSDL2 -lSDL2_image -o iv

install:V: iv
	cp iv /usr/local/bin/iv
	chmod 755 /usr/local/bin/iv