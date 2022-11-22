#include <iostream>

#include "doc.h"

int tester(int left, std::string middle, bool right) {
    std::cout << left << " " << middle << " " << (right ? "true" : "false")
              << std::endl;
    return 0;
}

void run_the_funny() {
    doc::container container(
        "mogringe",
        doc::container_settings{
            .rootfs_template = "download",
            .distributive = "ubuntu",
            .release = "kinetic",
            .architecture = "amd64"});

    std::cout << "Created contained: " << container.name() << "\n"
              << "Current state: " << container.state() << "\n"
              << "init_pid = " << container.init_pid() << std::endl;

    std::cout << "\nExecuting test function...\n";
    auto new_pid = container.run<int, std::string, bool>(tester, 5, "is", true);
    std::cout << "New pid: " << new_pid << std::endl;
}

int main(int argc, char** argv) {
    try {
        run_the_funny();
    } catch (doc::container_exception const& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
