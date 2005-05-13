AR=ar
CC=gcc -g

GLIB_CFLAGS=`pkg-config --cflags glib-2.0 gobject-2.0`
GLIB_LIBS=`pkg-config --libs glib-2.0 gobject-2.0`

LIBFFI_CFLAGS=-I../libffi/include -DHAVE_LIBFFI
LIBFFI_LIBS=../libffi/.libs/libffi.a

CFLAGS= $(GLIB_CFLAGS) $(LIBFFI_CFLAGS) 
LIBS= $(GLIB_LIBS) $(LIBFFI_LIBS)

LIBIREPOSITORY_OBJS = 	\
	girepository.o 	\
	gmetadata.o	\
	ginfo.o		\
	ginvoke.o

COMPILER_OBJS = 	\
	gidlparser.o	\
	gidlmodule.o	\
	gidlnode.o	\
	gmetadata.o	\
	compiler.o	

GENERATE_OBJS = generate.o

all: libirepository.a libirepository.so g-idl-generate g-idl-compiler

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
