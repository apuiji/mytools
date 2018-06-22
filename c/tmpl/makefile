TARGET:=../libtmpl.a
MOD:=bintree bst linked_iter
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c %.h
	gcc -o $@ $< -c

clean:
	rm *.o $(TARGET)

