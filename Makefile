create-dist:
	test -d dist || mkdir -p dist

build: create-dist
	gcc -o dist/ack -lncurses src/ack.c

run: build
	dist/ack 3 2

debug: build-verbose
	dist/ack 3 2
