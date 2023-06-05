#include <unistd.h>
#include <stdio.h>


int	main(void)
{
	access("/nfs/homes/xcharra/Documents/Cursus/minishell/Work/Misc/test", W_OK);
	perror(NULL);
}
