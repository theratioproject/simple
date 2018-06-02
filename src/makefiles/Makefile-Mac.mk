program_VERSION := s0.3.303
program_NAME := simple
program_SOURCE_DIR := ../sources
program_C_SRCS := $(wildcard $(program_SOURCE_DIR)/*.c)
program_CXX_SRCS := $(wildcard $(program_SOURCE_DIR)/*.cpp)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(CC) -dynamiclib $(program_SOURCE_DIR)/*.o -o simple.dylib
	$(CC) ../simple.c -id simple.dylib
