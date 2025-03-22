#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "substring.h"


bool_t *
is_substring_1_svc(string_pair *argp, struct svc_req *rqstp)
{
    static bool_t result;
    char *s1 = argp->s1;
    char *s2 = argp->s2;

    // Check if s1 is a substring of s2 OR if s2 is a substring of s1
    if (strstr(s2, s1) != NULL || strstr(s1, s2) != NULL) {
        result = TRUE;
    } else {
        result = FALSE;
    }

    return (&result);
}

int
main(int argc, char **argv)
{
    register SVCXPRT *transp;

    pmap_unset(SUBSTRING_PROG, SUBSTRING_VERS);

    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "cannot create udp service.\n");
        exit(1);
    }
    if (!svc_register(transp, SUBSTRING_PROG, SUBSTRING_VERS, substring_prog_1, IPPROTO_UDP)) {
        fprintf(stderr, "unable to register (SUBSTRING_PROG, SUBSTRING_VERS, udp).\n");
        exit(1);
    }

    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
    if (transp == NULL) {
        fprintf(stderr, "cannot create tcp service.\n");
        exit(1);
    }
    if (!svc_register(transp, SUBSTRING_PROG, SUBSTRING_VERS, substring_prog_1, IPPROTO_TCP)) {
        fprintf(stderr, "unable to register (SUBSTRING_PROG, SUBSTRING_VERS, tcp).\n");
        exit(1);
    }

    svc_run();
    fprintf(stderr, "svc_run returned\n");
    exit(1);
}
