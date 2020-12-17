#include "main.h"

int main()
{
	unlink(finderPipePath);
	mkfifo(finderPipePath, 0750);

	pid_t finderFork = fork();
	if(finderFork)
	{
		//Father
		//Reading finder son's pipe
		//Opening pipe
		int ipsFd = open(finderPipePath, O_RDONLY);
		
		//Preparing to read
		lseek(ipsFd, 0, SEEK_SET);
		
		//Reading
		char ips[ipListLength];
		read(ipsFd, ips, ipListLength);
		
		//Closing
		close(ipsFd);
		
		//Dumping IPs
		printf("%s", ips);
		
		//Waiting for son's death
		wait(NULL);
	}
	else
	{
		//ipFinder son
		execv(finderPath, (char *const []){"finder", NULL});
	}

	return 0;
}
