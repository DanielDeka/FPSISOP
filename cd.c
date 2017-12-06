#include "types.h"
#include "user.h"

int main (int argc, char *argv[])
{
	if (argc<2)
	{
		printf(2, "Kegunaan: pindah direktori\n");
		exit();
	}

	if(chdir(argv[1])<0)
	{
		printf(1,"Gagal pindah direktori\n");
	}

	exit();
}