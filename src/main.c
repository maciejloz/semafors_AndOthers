#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <assert.h>


int main(int argc, char *argv[])
{
	const char * message = "Witaj świecie\n";
	int n = strlen(message);
	int odd = n & 1;
	n /= 2;
	printf("%i\n", n);
	printf("%i\n", odd);
	
	sem_t *sem = sem_open("/thesem", O_CREAT, S_IRUSR | S_IWUSR);
	assert(sem != NULL);

	
	int r = sem_init(sem, 1, 0);
	assert(r == 0);

	pid_t pid = fork();
	
	int i0 = (pid == 0 ) ? 0 : n + odd;	

	int i;
	
	if(pid)
		sem_wait(sem);

	
	int gr = 0;

	for(i = 0; i < n; i++)
	{
		write(1, message + i0 + i, 1); 
	}
	
	if(pid == 0)
		sem_post(sem);
	
	return 0;
















}
