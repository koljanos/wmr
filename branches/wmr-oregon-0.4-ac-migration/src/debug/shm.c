#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

int main(void)
{

struct shmid_ds shmstat;
key_t shmID = 16908290;
int id;

    if( (id = shmget(shmID, 0, 0666)) < 0 )
    {
	perror("1) shmget ");
	exit(1);
    }

    if( (shmctl(id, IPC_STAT, &shmstat)) < 0 )
    {
	perror("1) shmstl ");
	exit(1);
    }

/*
printf("- (shared memory)Perm: %o Attach: %o Creator: %d LastConnected: %d\n", \
    shmstat.shm_perm.mode, \
    shmstat.shm_nattch, \
    shmstat.shm_cpid, \
    shmstat.shm_lpid \
    );
*/

              
printf ("\n\nId polzovatelya = %d\n", 		shmstat.shm_perm.uid);
printf ("Id gruppyi pol'zovatelya = %d\n",	shmstat.shm_perm.gid);
printf ("Id sozdatelya = %d\n", 		shmstat.shm_perm.cuid);
printf ("Id gruppyi sozdatelya = %d\n", 	shmstat.shm_perm.cgid);
printf ("Prava na operacii = 0%o\n",		shmstat.shm_perm.mode);
printf ("Posledovatelnost nomerov %d",		shmstat.shm_perm.cgid);
printf ("Ispolzuemyih slotov = 0%x\n",		shmstat.shm_perm.__seq);
printf ("Klyuch = 0%x\n", 			shmstat.shm_perm.__key);
printf ("Razmer segmenta = %d\n", 		shmstat.shm_segsz);
printf ("Vyipolnil poslednyuyu operaciyu = %d\n",shmstat.shm_lpid);
printf ("Sozdal segment = %d\n", 		shmstat.shm_cpid);
printf ("Chislo prisoedinivshih segment = %d\n",(int)shmstat.shm_nattch);
printf ("Chislo attached = %d\n", 		(int)shmstat.shm_nattch);
printf ("Poslednee prisoedinenie = %d\n",	(int)shmstat.shm_atime);
printf ("Poslednee otsoedinenie = %d\n",	(int)shmstat.shm_dtime);
printf ("Poslednee izmenenie = %d\n\n",		(int)shmstat.shm_ctime);

    if( (shmctl(id, IPC_RMID, (struct shmid_ds *) NULL)) == -1)
    {
	perror("2) shmstl ");
	exit(1);
    }

exit(0);
}
