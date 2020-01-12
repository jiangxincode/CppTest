#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main00011() //get the local hostent information
{
        struct hostent *he;
         if( ( he = gethostent()) == NULL)
         {
                herror("error:gethostend()");
                exit(1);
        }

        printf("h_name: %s\n",he->h_name); //hostname
        printf("addrtype: %d\n",he->h_addrtype); //the type of the address
        printf("length: %d\n",he->h_length); //the length of the address

        char **addr = he->h_addr_list;
        printf("h_addr_list:\n");
        while(*addr != NULL) //print the address list
        {
                printf("\t%s\n",inet_ntoa(*(struct in_addr *)(*addr)));
                addr ++;
        }

        char **aliase = he->h_aliases;
        printf("h_aliases:\n"); //print the aliase list
        while(*aliase != NULL)
        {
                printf("\t%s\n",*aliase);
                aliase ++;
        }
        return 0;
}

int main00012() //get any host's hostent information
{
        char *hostname = "www.baidu.com";
        //char *hostname = "127.0.0.1";
        struct hostent *he;
        if((he=gethostbyname(hostname))==NULL)
        {
                herror("gethostbyname");
                exit(1);
        }

        char **addr = he->h_addr_list;
        printf("IP Address:\n");
        while(*addr != NULL)
        {
                printf("\t%s\n",inet_ntoa(*(struct in_addr *)(*addr)));
                addr ++;
        }

        char *ip = "127.0.0.1";
        struct in_addr *ip_addr = (struct in_addr *)malloc(sizeof(struct in_addr));
        if(!(inet_aton(ip,ip_addr)))
        {
                herror("error:inet_aton()");
                exit(1);
        }
        if((he=gethostbyaddr(ip_addr,4,AF_INET)) == NULL)
        {
                herror("error:gethostbyaddr()");
                exit(1);
        }
        printf("hostname: %s",he->h_name);
        return 0;
}

int main00013() //get the local net information
{
        struct netent *nt;
        if((nt = getnetent()) == NULL)
        {
                herror("error:getnetent()");
        }
        printf("net name: %s\n",nt->n_name);
        printf("net address type: %d\n",nt->n_addrtype);
        printf("net num: %u\n",nt->n_net);

        char **aliase = nt->n_aliases;
        while(*aliase != NULL)
        {
                printf("%s\n",*aliase);
                aliase ++;
        }

        return 0;
}

int main00014() //get the any net information
{
        struct netent *np;
        if((np = getnetbyaddr(2851995648,AF_INET)) == NULL)
        {
                herror("error:getnetbyaddr()");
                exit(1);
        }
        printf("net name: %s\n",np->n_name);

        if((np = getnetbyname("link-local")) == NULL)
        {
                herror("error:getnetbyname()");
                exit(1);
        }
        printf("net num: %u\n",np->n_net);
        return 0;
}

int main00015()
{
        struct protoent *pe;
        if((pe = getprotoent()) == NULL)
        {
                herror("error:getprotoent()");
                exit(1);
        }
        printf("protocal name: %s\n",pe->p_name);
        printf("protocal numer: %d\n",pe->p_proto);
        char **aliase = pe->p_aliases;
        while(*aliase != NULL)
        {
                printf("%s\n",*aliase);
                aliase ++;
        }
        return 0;
}
int main0001()
{
        main00015();
        return 0;
}
