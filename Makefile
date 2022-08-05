CC = $(CROSS)gcc
CXX = $(CROSS)g++
LD = $(CROSS)ld
AR = $(CROSS)ar
AS = $(CROSS)as

path=../

APP=test

CFLAGS   += -I. -I./zlog -g
CFLAGS   += -Wsign-compare -Wunused-function -Wunused-variable \
	-Wmissing-prototypes -Wunused-parameter -Wunused-but-set-variable \
	-Wreturn-type
LDLIBS   += ./libzlog.a 
CFLAGS+=-L./zlog

APP_OBJS  = main.c snic_log.c

all: build
	cp $(APP) ${path}

test:
	make CROSS=

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) $(CFLAGS) -o $@ $(APP_OBJS) -L ./ $(LDLIBS) -lpthread -l:libprotobuf-c.a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf *.o $(APP) ${path}/$(APP)

.PHONY: all clean build test $(APP)
