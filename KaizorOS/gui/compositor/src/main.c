#include "server.h"

int main(void) {
    struct kaizor_server server;

    kaizor_server_init(&server);
    kaizor_server_run(&server);

    return 0;
}
