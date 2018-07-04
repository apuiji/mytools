TARGET:=../libwconv.a
MOD:=../wconv
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c %.h
	gcc -o $@ $< -c

clean:
	rm $(OBJ) $(TARGET)

