# include "../incs/ft_traceroute.h"

int parser(char **argv, t_trace  *trace)
{    
    argv++;

    while (*argv)
    {
        if (!ft_strncmp("--help", *argv, ft_strlen(*argv)))
        {
            error(HELP);
        }
        else if (!ft_strncmp("-?", *argv, ft_strlen(*argv)))
            error(HELP);
        else if (!ft_strncmp("--", *argv, 2))
        {
            fprintf(stderr, "%s '%s'\n", INVOPT2, *argv);
            error(TRY);
        }
        else if (!ft_strncmp("-", *argv, 1))
        {
            fprintf(stderr, "%s'%c'\n", INVOPT1, (*argv)[1]);
            error(TRY);
        }
        else
        { 
            trace->info = dns_lookup(*argv);
            // if (!inet_ntop(AF_INET, &trace->info->ai_addr->sa_data[2], trace->ip, INET_ADDRSTRLEN))
            // {
		    //     printf("falsch\n");
            //     error(strerror(errno));
            // }
            trace->domain = *argv;
            trace->ip = inet_ntoa(((struct sockaddr_in *)(trace->info->ai_addr))->sin_addr);
        }
        argv++;
    }
    return (0);
}