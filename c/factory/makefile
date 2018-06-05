TARGET:=../libfactory.a
MOD:=string_fty
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c %.h
	gcc -o $@ $< -c

clean:
	rm *.o $(TARGET)

