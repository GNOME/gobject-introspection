AR=ar
CC=gcc -g
CFLAGS=`pkg-config --cflags glib-2.0 gobject-2.0`
LIBS=`pkg-config --libs glib-2.0 gobject-2.0`

LIBIREPOSITORY_OBJS = 	\
	girepository.o 	\
	gmetadata.o	\
	ginfo.o

COMPILER_OBJS = 	\
	gidlparser.o	\
	gidlmodule.o	\
	gidlnode.o	\
	gmetadata.o	\
	compiler.o	

GENERATE_OBJS = generate.o

all: libirepository.so g-idl-generate g-idl-compiler

libirepository.so: $(LIBIREPOSITORY_OBJS)
	$(CC) -shared -o $@ $(LIBIREPOSITORY_OBJS) $(LIBS)

libirepository.a: $(LIBIREPOSITORY_OBJS)
	 $(AR) csr $@ $(LIBIREPOSITORY_OBJS) 

g-idl-generate: $(GENERATE_OBJS) libirepository.a
	$(CC) -o $@ $(GENERATE_OBJS) $(LIBS) -ldl libirepository.a

g-idl-compiler: $(COMPILER_OBJS) 
	$(CC) 	-o $@ $(COMPILER_OBJS) $(LIBS) -ldl 

.c.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o *~ *.a *.so g-idl-generate g-idl-compiler
