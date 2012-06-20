OBJS = bstrlib.o bm2.o sqlite3.o bm2_db.o logging.o
CCFLAGS = -Wall

ifdef $(WIN32)
LDFLAGS = -ldl -lpthread
else
LDFLAGS = 
endif

.c.o:
	gcc -I. -c $(CCFLAGS) $<

bm2: $(OBJS)
	gcc -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) *.o bm2
