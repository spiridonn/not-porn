# Global definitions
CC=gcc
CFLAGS = -g -Wconversion -Wall -pedantic -ansi
LDFLAGS = -g
# Directory structure
INC_DIR = ../../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../lib
LIB_NAME = libcHeap.so.1.0
LIB_LINK = libcHeap.so.1

# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET = heapTest.out
LIB_SRCS=heap.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) > depends


commit: $(LIB_FILE) $(LIB_DIR)/$(LIB_LINK) $(LIB_DIR)/libcHeap.so

$(LIB_FILE): $(LIB_OBJS)
	gcc -shared -Wl,-soname,$(LIB_LINK) -o $(LIB_NAME) *.o
	mv $(LIB_NAME) $(LIB_DIR)
	
$(LIB_DIR)/$(LIB_LINK):
	ln -sf $(LIB_NAME) $(LIB_DIR)/$(LIB_LINK)
	
$(LIB_DIR)/libcHeap.so:
	ln -sf $(LIB_NAME) $(LIB_DIR)/libcHeap.so


clean:
	-rm *.o
	-rm heapTest.out

run:
	./heapTest.out

