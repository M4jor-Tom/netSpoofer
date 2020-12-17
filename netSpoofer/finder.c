#include "main.h"

int main(int argc, char *argv[])
{
	//---Writing found IPs in a tempfile instead of stdout
	char launch[300] = IP_FETCH;
	
	//Constructing command call
	strcat(launch, " > ");
	strcat(launch, ipTempFilePath);
	
	//Calling nmap
	system(launch);
	
	//---Loading data from temp file
	//Opening tempfile
	char ips[ipListLength];
	int tempFd = open(ipTempFilePath, O_RDONLY);
		
	//Preparing to read
	lseek(tempFd, 0, SEEK_SET);
	
	//Reading
	read(tempFd, ips, ipListLength);
	
	//Closing
	close(tempFd);
	
	//---Giving data into pipe for father process
	//Opening pipe
	int pipeFd = open(finderPipePath, O_WRONLY);
		
	//Preparing to write
	lseek(pipeFd, 0, SEEK_SET);
	
	//Writing into it
	write(pipeFd, ips, ipListLength);
	
	//Closing pipe
	close(pipeFd);
	
	//---Death
	exit(0);
	return 0;
}
