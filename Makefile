CC = gcc
CFLAGS = -Wall

EXEC =  manager PA PB PC PD 
FILS = estudiantes log.txt

all: compile run

compile: $(EXEC)

manager:
	$(CC) $(CFLAGS) manager.c -o manager

PA:
	$(CC) $(CFLAGS) PA.c -o PA

PB:
	$(CC) $(CFLAGS) PB.c -o PB

PC:
	$(CC) $(CFLAGS) PC.c -o PC

PD:
	$(CC) $(CFLAGS) PD.c -o PD

run:
	./manager

test:
	ls -R $(FILS)

clean:
	rm -r $(FILS) $(EXEC)
