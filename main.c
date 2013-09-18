/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <validator/validator.h>
#include <validator/val_dane.h>

int main(int argc, char *argv[])
{
    char *hostname;
    int port;
    int dane_ret;

    struct val_daneparams parameters;
    struct val_danestatus *status = NULL;

    val_context_t *context = NULL;

    if (0 != val_create_context(NULL, &context))
    {
        printf("Unable to create context\n");
        return EXIT_FAILURE;
    }

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hostname = argv[1];
    port = atoi(argv[2]);

    while (true)
    {
        parameters.port = port;
        parameters.proto = DANE_PARAM_PROTO_TCP;

        dane_ret = val_getdaneinfo(context, hostname, &parameters, &status);

        if (dane_ret == VAL_DANE_NOERROR)
            printf("DANE: TLSA record for hostname %s exists\n", hostname);
        else if (dane_ret != VAL_DANE_IGNORE_TLSA)
            printf("DANE: TLSA record for hostname %s could not be verified\n", hostname);

        val_free_dane(status);
    }

    val_free_context(context);

    return EXIT_SUCCESS;
}
