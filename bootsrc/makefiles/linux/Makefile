program_NAME := simple
program_LIBRARY := simple.so
program_C_SRCS := $(wildcard *.c)
program_CXX_SRCS := $(wildcard *.cpp)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_CFLAGS := -c -fpic -g
program_LFLAGS := -lm -ldl

.PHONY: all clean distclean

$(program_NAME): $(program_OBJS)
	$(CC) -shared -o $(program_LIBRARY) $(program_OBJS)
	$(CC) $(program_LFLAGS) -o $(program_NAME) ../simple.c  $(program_LIBRARY)
	mkdir -p ../dist
	rm -rf *.o
	mv simple.so ../dist
	mv simple ../dist
	
	#ADD LIBARRY TO PATH
	LD_LIBRARY_PATH=../dist:${LD_LIBRARY_PATH}
	export LD_LIBRARY_PATH=./$LD_LIBRARY_PATH

$(program_OBJS): $(program_C_SRCS)
	$(CC) $(program_CFLAGS) $(program_C_SRCS)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean