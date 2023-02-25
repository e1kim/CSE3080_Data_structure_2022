cc=gcc
cflag = -c
target = hw3

objects = hw3.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflag) -o  $@ $<

.PHONY : clean
clean :
	rm $(target) $(objects)
