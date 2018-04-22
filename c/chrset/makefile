TARGET:=../libchrset.a
MOD:=ascii gbk utf8
OBJ:=chrset.o $(addprefix chrset/, $(addsuffix .o, $(MOD)))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

debug:chrset.h chrset.c chrset/*.h chrset/*.c
	gcc -o $@ *.c chrset/*.c -I chrset -g

%.o:%.c %.h
	gcc -o $@ $< -I chrset -c

clean-debug:
	rm debug

clean:
	rm *.o $(TARGET) debug

