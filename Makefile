CC=g++ -c
RESOLVE_DEP=g++ -MM
AR=ar rcs
WORKDIR=.
OUTPUT_DIR=.

CFLAGS=-Wall -Wextra -Wold-style-cast -Werror
MKTMP=tmp.mk

all:backtracpplib

%.d:$(WORKDIR)/%.cpp
	echo -n "$(WORKDIR)/" > $(MKTMP)
	$(RESOLVE_DEP) $< >> $(MKTMP)
	echo "	$(CC) $< $(CFLAGS) -o $(WORKDIR)/$*.o" >> $(MKTMP)
	make -f $(MKTMP)

backtracpplib:trace.d demangle.d
	$(AR) $(OUTPUT_DIR)/libbacktracpp.a $(WORKDIR)/trace.o $(WORKDIR)/demangle.o

LINK=g++ -rdynamic

sample:sample.d all
	$(LINK) $(WORKDIR)/sample.o -L$(OUTPUT_DIR) -lbacktracpp \
	        -o $(OUTPUT_DIR)/backtrace.out

clean:
	rm -f $(MKTMP)
	rm -f $(WORKDIR)/*.o
	rm -f $(OUTPUT_DIR)/libbacktracpp.a
	rm -f $(OUTPUT_DIR)/backtrace.out
