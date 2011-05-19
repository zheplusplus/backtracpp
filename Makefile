ifndef LIB_DIR
	LIB_DIR="."
endif

CC=g++ -c
RESOLVE_DEP=g++ -MM
AR=ar rcs
WORKDIR=.

CFLAGS=-Wall -Wextra -Wold-style-cast -Werror
MKTMP=tmp.mk

all:backtracpplib

%.d:$(WORKDIR)/%.cpp
	echo -n "$(WORKDIR)/" > $(MKTMP)
	$(RESOLVE_DEP) $< >> $(MKTMP)
	echo "	$(CC) $< $(CFLAGS) -o $(WORKDIR)/$*.o" >> $(MKTMP)
	make -f $(MKTMP)

backtracpplib:trace.d demangle.d
	$(AR) $(LIB_DIR)/libbacktracpp.a $(WORKDIR)/trace.o $(WORKDIR)/demangle.o

LINK=g++ -rdynamic
TEST_LIB=-lgtest -lgtest_main -lpthread

runtest:test/test-demangle.d all
	$(LINK) $(WORKDIR)/test/test-demangle.o \
	        -L$(LIB_DIR) -lbacktracpp $(TEST_LIB) \
	     -o $(WORKDIR)/test-backtracpp.out
	$(WORKDIR)/test-backtracpp.out

sample:sample.d all
	$(LINK) $(WORKDIR)/sample.o -L$(LIB_DIR) -lbacktracpp \
	     -o $(WORKDIR)/backtrace.out

clean:
	rm -f $(MKTMP)
	rm -f $(WORKDIR)/*.o
	rm -f $(WORKDIR)/test/*.o
	rm -f $(LIB_DIR)/libbacktracpp.a
	rm -f $(WORKDIR)/*.out
