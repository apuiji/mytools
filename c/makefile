TARGET:=libmytools.a
MOD:=mem varray linked chrset
OBJ:=$(addprefix obj/, $(addsuffix .o, $(MOD)))
HEAD:=head
HEADOP:=$(addprefix -I , $(HEAD))
LIB:=
LIBDIR:=
LIBOP:=$(addprefix -L , $(LIBDIR)) $(addprefix -l , $(LIB))

$(TARGET):$(OBJ)
	ar -rcs $@ $^

debug:head/*.h src/*.c
	gcc $(HEADOP) -o $@ src/*.c -g $(LIBOP)

obj/%.o:src/%.c head/%.h
	gcc $(HEADOP) -o $@ $< -c

clean-debug:
	rm debug

clean:
	rm $(TARGET) debug obj/*

