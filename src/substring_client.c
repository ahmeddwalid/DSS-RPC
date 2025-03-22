#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "substring.h"

int
main(int argc, char **argv)
{
    CLIENT *clnt;
    string_pair strings;
    bool_t *result_1;
    char *server;

    if (argc != 4) {
        fprintf(stderr, "usage: %s server string1 string2\n", argv);
        exit(1);
    }
    server = argv[4];
    strings.s1 = argv[1];
    strings.s2 = argv[2];

    /*
     * Create client handle used for calling SUBSTRING_PROG on the server.
     * I used both UDP and TCP.
     */
    clnt = clnt_create(server, SUBSTRING_PROG, SUBSTRING_VERS, "udp");
    if (clnt == NULL) {
        clnt = clnt_create(server, SUBSTRING_PROG, SUBSTRING_VERS, "tcp");
        if (clnt == NULL) {
            clnt_pcreateerror(server);
            exit(1);
        }
    }

     // Call the remote procedure "is_substring" on the server.
    result_1 = is_substring_1(&strings, clnt);
    if (result_1 == (bool_t *) NULL) {
        clnt_perror(clnt, server);
        exit(1);
    }

    if (*result_1 == TRUE) {
        printf("One string is a substring of the other.\n");
    } else {
        printf("Neither string is a substring of the other.\n");
    }

    // Destroy the client handle.
    clnt_destroy(clnt);
    exit(0);
}
