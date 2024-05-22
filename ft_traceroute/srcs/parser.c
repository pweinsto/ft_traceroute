# include "../incs/ft_traceroute.h"

int parser(char **argv, t_trace  *trace)
{    
    argv++;

    while (*argv)
    {
        if (!ft_strncmp("--help", *argv, ft_strlen(*argv)))
        {
            free(trace);
            error(HELP);
        }
        else if (!ft_strncmp("-?", *argv, ft_strlen(*argv)))
        {
            free(trace);
            error(HELP);
        }
        else if (!ft_strncmp("--", *argv, 2))
        {
            fprintf(stderr, "%s '%s'\n", INVOPT2, *argv);
            free(trace);
            error(TRY);
        }
        else if (!ft_strncmp("-", *argv, 1))
        {
            fprintf(stderr, "%s'%c'\n", INVOPT1, (*argv)[1]);
            free(trace);
            error(TRY);
        }
        else
        { 
            trace->info = dns_lookup(trace, *argv);
            trace->domain = *argv;
            trace->ip = inet_ntoa(((struct sockaddr_in *)(trace->info->ai_addr))->sin_addr);
        }
        argv++;
    }

    return (0);
}