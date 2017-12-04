#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syslog.h>

int main (int argc, char* argv[])
{
	int status = daemon(0, 0);
	if (status == -1)
	{
		exit(5);
	}

	char* path_to_pid_file;
	if (argc == 2)
	{
		path_to_pid_file = argv[1];
		FILE* fd = fopen(path_to_pid_file, "w");
		if (fd == NULL)
		{
			exit(6);
		}
		fprintf(fd, "%d\n", getpid());
		fclose(fd);
	}

	// Daemon logic
	FILE* pipeHandle;
	const char* command = "who";
	char data[1024];

	while (1)
	{
		pipeHandle = popen(command, "r");
		while (fgets(data, 1024, pipeHandle) != NULL)
		{
			syslog(LOG_MAKEPRI(LOG_LOCAL7, LOG_INFO), "%s", data);
		}

		pclose(pipeHandle);
		sleep(5);
	}

	return 0;
}
