#include "shared.h"
int main(int argc,char** argv){
	return execute(argc-1,&argv[1],"org/openjdk/asmtools/jasm/Main");
}
