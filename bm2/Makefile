OBJS = bstrlib.o bm2.o sqlite3.o bm2_db.o

CCFLAGS = -Wall

.c.o:
	gcc -c $(CCFLAGS) $<

bm2: $(OBJS)
	gcc -o $@ $(OBJS) -ldl -lpthread

.PHONY: clean
clean:
	$(RM) *.o bm2
