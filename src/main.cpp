#include <iostream>

#include "doc.h"

int amogus(void* mog) {
    const char* sus = (const char*)mog;
    printf(sus);
    return 0;
}

void run() {
    doc::container container(
        "mogringe",
        doc::container_settings{
            .rootfs_template = "download",
            .distributive = "ubuntu",
            .release = "kinetic",
            .architecture = "amd64"});
    container.run();
}

int main(int argc, char** argv) {
    try {
        run();
    } catch (doc::container_exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}