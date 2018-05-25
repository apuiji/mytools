TARGET:=../libchrset.a
MOD:=chrset ascii gbk utf8
OBJ:=$(addsuffix .o, $(MOD))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

%.o:%.c ../chrset.h
	gcc -o $@ $< -c

clean:
	rm *.o $(TARGET)

