TARGET:=../libtemplate.a
MOD:=mem varray linked bintree bst strbuf
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

debug:*.h *.c
	gcc -o $@ *.c -g

%.o:%.c %.h
	gcc -o $@ $< -c

clean-debug:
	rm debug

clean:
	rm *.o $(TARGET) debug

