TARGET:=../libmem.a
MOD:=nof1 bitmsk bitlogic shift
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c ../mem.h
	gcc -o $@ $< -c

clean:
	rm *.o $(TARGET)

