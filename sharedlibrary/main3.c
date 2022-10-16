#include <stdio.h>
#include "library3.h"
#include "library4.h"

int main(int argc, char *argv[])
{
	wrapper_library_call();
	library_call();
	library_call();
	wrapper_library_call();
	return 0;
}
