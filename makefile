SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
CFLAG= -g 
TARGET=	my_ftp
#TARGET=$(patsubst %.c,%,$(SRC))
#$(TARGET):$(OBJ)
#ALL:$(TARGET)

#$(TARGET):%.o
my_ftp:$(OBJ)
	gcc -T my_ftp.lds $^ -o $@ $(CFLAG)
%.o:%.c
	gcc -c	-Tmy_ftp.ld $<	-o	$@	-g
.PHONY:clean
clean:
	-rm -rf *.o $(TARGET)
