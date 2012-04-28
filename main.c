
#include <stdio.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 80

const char* usage = 
"datecmd [/f | /d | /t] /e /?]  \n\
	   /f - format string for strftime C function                         \n\
       /d - date only = /f=\"%Y%m%d\"                                     \n\
       /t - time only = /f=\"%H%M%S\"                                     \n\
	   /e - add CR/LF (default: no EOL)                                   \n\
       /? - display this help                                             \n\
       defaults: /f=\"%Y.%m.%d %H:%M:%S\"\n";

int main(int argc, char *argv[]) {
	
	char *format = "%Y.%m.%d %H:%M:%S";
	short date_only = 0;
	short time_only = 0;
	short crlf = 0;
    short i = 0;
	time_t rawtime;
	struct tm *ct;
	char buffer[BUFFER_SIZE];
	
	if ((argc == 2) && (strcmp(argv[1], "/?") == 0)) {
		goto usage;
	}

	i=0;
	while (++i < argc) {
		if (strcmp(argv[i], "/e") == 0) {
			crlf = 1;
			continue;
		}

		if (strcmp(argv[i], "/d") == 0) {
			date_only = 1;
			continue;
		}

		if (strcmp(argv[i], "/t") == 0) {
			time_only = 1;
			continue;
		}

		if (strcmp(argv[i], "/f") == 0) {
			if (argc <= i+1)
				goto usage;
			format = argv[++i];
			continue;
		}
	};

	time(&rawtime);
	ct = localtime(&rawtime);

	if (date_only)
		strftime(buffer, BUFFER_SIZE, "%Y%m%d", ct);
	else if (time_only)
		strftime(buffer, BUFFER_SIZE, "%H%M%S", ct);
	else
		strftime(buffer, BUFFER_SIZE, format, ct);
		
	printf(buffer);
	if (crlf)
		printf("\r\n");

	return 0;

usage:
	printf(usage);
	return 1;
}