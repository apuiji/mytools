TARGET:=../libtemplate.a
MOD:=vlarr linked bintree bst strbuf
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c %.h
	gcc -o $@ $< -c

clean:
	rm *.o $(TARGET)

