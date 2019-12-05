#include <sys/stat.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#define VERSION "v0.1"

#define SITE_FOLDER "/usr/share/nginx/"
#define SITE_CONFIG "/etc/nginx/conf.d/"

struct site_info
{
	char *port;
	char *index;
	char *domain;
	char *directory;
};

static const char *config_file[] = {
	"server {",
	"	  listen",
	"	  server_name",
	"	  location / {",
	"	      root",
	"	      index",
	"	  }",
	"}",
};

struct site_info
get_user_opts(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	struct site_info site = get_user_opts(argc, argv);

	char filename[1024];
	sprintf(filename, "%s%s.conf", SITE_CONFIG, site.directory);

	int fd = open(filename, O_WRONLY | O_CREAT,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	for(int i = 0; i < 8; ++i)
	{
		if(i == 1)      dprintf(fd, "%s %s;\n", config_file[i], site.port);
		else if(i == 2) dprintf(fd, "%s %s;\n", config_file[i], site.domain);
		else if(i == 4) dprintf(fd, "%s %s%s;\n", config_file[i], SITE_FOLDER, site.directory);
		else if(i == 5) dprintf(fd, "%s %s %s;\n", config_file[i], site.index, site.index);
		else            dprintf(fd, "%s;\n", config_file[i]);
	}

	close(fd);

	execlp("cp", "cp", "-r", site.directory, SITE_FOLDER, (char *)NULL);

	return -1;
}

struct site_info
get_user_opts(int argc, char *argv[])
{
	int option_index = 0;
	static struct site_info ret = {
		.port = "8080",
		.index = "index.html",
		.domain = "localhost",
	};

	while (1)
	{

		static struct option long_options[] = {
			{"help",    no_argument, 0,  'h'},
			{"port",    no_argument, 0,  'p'},
			{"index",   no_argument, 0,  'i'},
			{"directory",  no_argument, 0,  'D'},
			{"domain",  no_argument, 0,  'd'},
			{"version", no_argument, 0,  'v'},
			{0,0,0,0},
		};

		int choice = getopt_long(argc, argv, "vhp:i:d:D:",
					 long_options, &option_index);

		if (choice == -1)
			break;

		switch(choice)
		{
		case 'p':
			ret.port = argv[optind - 1];
			break;
		case 'i':
			ret.index = argv[optind - 1];
			break;
		case 'f':
			ret.directory = argv[optind - 1];
			break;
		case 'D':
			ret.domain = argv[optind - 1];
			break;
		case 'v':
			printf("Author: Reberti Carvalho Soares\n"
			       "License: GPLv2\n"
			       "Version: %s\n", VERSION);
			exit(0);

		case 'h':
			printf("-h, --help for help\n"
			       "-d, --domain domain name\n"
			       "-D, --directory site\n"
			       "-i, --index index file name\n"
			       "-p, --port site port\n");
			exit(0);

		}

	}

	if(!ret.directory)
	{
		printf("error: directory must be supplied\n");
		exit(1);
	}

	return ret;
}
