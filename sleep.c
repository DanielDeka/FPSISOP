#include "types.h"
#include "user.h"

int main (int argc, char *argv[])
{
	int durasi;
	if (argc<2)
	{
		printf("2, Kegunaan: durasi sleep\n");
		exit();
	}

	durasi = atoi(argv[1]);
	if(durasi > 0) sleep(durasi);
	else printf(2,"Interval tidak valid %s\n", argv[1]);

	exit();
}