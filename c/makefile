TARGET:=libmytools.so
MOD:=mem varray linked
OBJ:=$(addprefix obj/, $(addsuffix .o, $(MOD)))
HEAD:=head
HEADOP:=$(addprefix -I , $(HEAD))
LIB:=
LIBDIR:=
LIBOP:=$(addprefix -L , $(LIBDIR)) $(addprefix -l , $(LIB))

$(TARGET):$(OBJ)
	gcc $(HEADOP) $(LIBOP) -o $@ obj/*.o -shared

debug:head/*.h src/*.c
	gcc $(HEADOP) $(LIBOP) -o $@ src/*.c -g

obj/%.o:src/%.c head/%.h
	gcc $(HEADOP) -o $@ $< -c -fPIC

clean-debug:
	rm debug

clean:
	rm $(TARGET) debug obj/*

