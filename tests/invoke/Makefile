AR=ar
CC=gcc -g
CFLAGS=`pkg-config --cflags glib-2.0` -I../../libffi/include -I../../src
LIBS=`pkg-config --libs glib-2.0 gobject-2.0`

TESTFNS_OBJS = 		\
	testfns.o	\
	testfns-metadata.o

INVOKE_OBJS = 		\
	invoke.o

all: testfns.so invoke

testfns.so: $(TESTFNS_OBJS)
	$(CC) -shared -o $@ $(TESTFNS_OBJS) $(LIBS) ../../src/libirepository.so

testfns-metadata.c: testfns.xml
	../../src/g-idl-compiler testfns.xml -o testfns-metadata.c

invoke: $(INVOKE_OBJS)
	$(CC) -o $@ $(INVOKE_OBJS) $(LIBS) -ldl ../../src/libirepository.so

.c.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o *~ *.a *.so 
