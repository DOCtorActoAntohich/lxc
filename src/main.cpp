#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "doc.h"

std::vector<std::string> read_benchmark_commands(std::string path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int benchmark(std::vector<std::string> commands) {
    for (auto& line : commands) {
        auto _ = std::system(line.c_str());
    }
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

    std::cout << "\nExecuting benchmark function...\n";
    auto lines = read_benchmark_commands("benchmarks.sh");
    auto new_pid = container.run(benchmark, lines);
    std::cout << "New pid: " << new_pid << std::endl;

    // Just cos I want benchmarks to finish before
    // Container attempts to shut down and fails miserably.
    // so basically i should mark this line as follows.
    // TODO: remove when deadlock is fixed.
    std::this_thread::sleep_for(std::chrono::minutes(10));
}

int main(int argc, char** argv) {
    try {
        run_the_funny();
    } catch (doc::container_exception const& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
