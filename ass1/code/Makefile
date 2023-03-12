include config.mk

OBJECTS = main.o

main.o :
	$(CC) -c main.c

branch_predictor :	clean $(OBJECTS)
	$(CC) $(OBJECTS) -o branch_predictor.o $(LDFLAGS)

clean :
	rm -rf $(OBJECTS)
	rm -rf branch_predictor.o