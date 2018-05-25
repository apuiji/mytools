TARGET:=../libmem.a
MOD:=nof1 bitmsk bitlogic shift
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

debug:*.h *.c
	gcc -o $@ *.c -g

%.o:%.c
	gcc -o $@ $< -c

clean-debug:
	rm debug

clean:
	rm *.o $(TARGET) debug

