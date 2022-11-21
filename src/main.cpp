#include <iostream>

#include "doc/container.h"

int amogus(void* mog) {
    const char* sus = (const char*)mog;
    printf(sus);
    return 0;
}

int main(int argc, char** argv) {
    doc::container container(
        "mogringe",
        doc::container_settings{
            .rootfs_template = "download",
            .distributive = "ubuntu",
            .release = "kinetic",
            .architecture = "amd64"});
    container.run();

    return 0;
}