#include "compact.h"
#include "descompact.h"

int main ()
{
	int option;
	printf("1.Compactar\n2.Descompactar\n");
	scanf("%d",&option);

  if (option == 1) {
		compact();
	}

  else if (option == 2) {
	 	descompact();
	}
    return 0;
}
