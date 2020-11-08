CC          := gcc
LINKER      := $(CC)
CFLAGS      := -O3
FFLAGS      := $(CFLAGS)

LDFLAGS     := -lm

UTIL_OBJS   := _network_layer.o _physical_layer.o _utils.o

SENDER_OBJS := sender.o
RECEIVER_OBJS := receiver.o

sender_driver.x: $(SENDER_OBJS) $(UTIL_OBJS)
	$(LINKER) $(SENDER_OBJS) $(UTIL_OBJS) $(BLAS_LIB) -o sender_driver.x $(LDFLAGS)

sender: sender_driver.x
	clear
	./sender_driver.x 127.0.0.1:5000 127.0.0.1:5055
	make clean

receiver_driver.x: $(RECEIVER_OBJS) $(UTIL_OBJS)
	$(LINKER) $(RECEIVER_OBJS) $(UTIL_OBJS) $(BLAS_LIB) -o receiver_driver.x $(LDFLAGS)

receiver: receiver_driver.x
	clear
	./receiver_driver.x 127.0.0.1:5055 127.0.0.1:5000
	make clean

# clean everything
clean:
	rm -f *.o *~ core *.x *.pdf
