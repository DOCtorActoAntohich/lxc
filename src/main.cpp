#include <iostream>

#include "doc.h"

int tester(int left, std::string middle, bool right) {
    std::cout << left << " " << middle << " " << (right ? "true" : "false")
              << std::endl;
    return left * 2 + 1;
}

void run_the_funny() {
    doc::container container(
        "mogringe",
        doc::container_settings{
            .rootfs_template = "download",
            .distributive = "ubuntu",
            .release = "kinetic",
            .architecture = "amd64"});

    auto _ = container.run<int, std::string, bool>(tester, 5, "is", true);
}

int main(int argc, char** argv) {
    try {
        run_the_funny();
    } catch (doc::container_exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
