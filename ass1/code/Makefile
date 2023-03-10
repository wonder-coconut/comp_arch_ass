include config.mk

OBJECTS = main.o

main.o :
	$(CC) -c main.c

branch_predictor :	$(OBJECTS)
	$(CC) $(OBJECTS) -o branch_predictor.o $(LDFLAGS)