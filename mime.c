#include <stdio.h>
#include <magic.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
		return 1;

	const char *mime;

	magic_t magic;

	magic = magic_open(MAGIC_MIME_TYPE);
	magic_load(magic, NULL);
	mime = magic_file(magic, argv[1]);

	printf("%s\n", mime);

	magic_close(magic);
	return 0;
}
