.SUFFIXES:.cpp .o

CC=g++ --std=c++0x

SRCS=006example_hash2.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=test

start:  $(OBJS) 
	$(CC)  -g -o  $(EXEC)  $(OBJS)
	@echo  "----------ok----------"

.cpp.o:
	$(CC)  -g -Wall  -o  $@  -c  $<

clean:
	rm  -rf  $(EXEC)  $(OBJS)
