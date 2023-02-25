cc=gcc
cflag = -c
target = hw2

objects = hw2.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflag) -o  $@ $<

.PHONY : clean
clean :
	rm $(target) $(objects)
