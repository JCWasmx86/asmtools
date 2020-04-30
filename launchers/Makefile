includePath=${JAVA_HOME}/include
includePath_OS=${JAVA_HOME}/include/linux
includePath_Lib=$(CURDIR)/./include 
libPath=${JAVA_HOME}/lib/server
all:
	mkdir -p $(CURDIR)/bin/obj
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/shared.o  $(CURDIR)/src/shared.c
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/jcdec.o  $(CURDIR)/src/jcdec.c
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/jdec.o  $(CURDIR)/src/jdec.c
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/jcoder.o  $(CURDIR)/src/jcoder.c
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/jasm.o  $(CURDIR)/src/jasm.c
	$(CC) -g3 -Wall -Wextra -pedantic $(CFLAGS) -I $(includePath) -I $(includePath_OS) -I $(includePath_Lib) -c -o $(CURDIR)/bin/obj/jdis.o  $(CURDIR)/src/jdis.c
	$(CC) -o $(CURDIR)/bin/jcdec $(CURDIR)/bin/obj/shared.o $(CURDIR)/bin/obj/jcdec.o -L $(libPath) -ljvm
	$(CC) -o $(CURDIR)/bin/jdec $(CURDIR)/bin/obj/shared.o $(CURDIR)/bin/obj/jdec.o -L $(libPath) -ljvm
	$(CC) -o $(CURDIR)/bin/jcoder $(CURDIR)/bin/obj/shared.o $(CURDIR)/bin/obj/jcoder.o -L $(libPath) -ljvm
	$(CC) -o $(CURDIR)/bin/jasm $(CURDIR)/bin/obj/shared.o $(CURDIR)/bin/obj/jasm.o -L $(libPath) -ljvm
	$(CC) -o $(CURDIR)/bin/jdis $(CURDIR)/bin/obj/shared.o $(CURDIR)/bin/obj/jdis.o -L $(libPath) -ljvm
clean:
	rm -rf $(CURDIR)/bin
