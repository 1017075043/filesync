CC=g++ --std=c++11

CFLAGS=-DMYLINUX
LIB=-pthread

SRCS=wnh_license.cpp\
	
OBJS=$(SRCS:.cpp=.o)

EXEC=wnh_license

.cpp.o:
	$(CC) -o $@ -c -g $< $(CFLAGS)

start: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LIB)

clean:
	rm -rf $(OBJS)

install:
	rm -rf $(OBJS)
	./$(EXEC)
