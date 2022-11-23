# Linux Containers (LXC)

An LXC example usage of LXC C API but with C++ with classes.

Features:

- Example usage of `lxc attach` in code.
- C++ classes that wrap around C-style code.
- Conversion between parameter pack (variadic templates) and `void* payload`.

## How to build and run

~~Doesn't really work on Arch.~~

### Requirements

On Ubuntu, `sudo apt-get install` these packages:

1. `make`
2. `cmake`
3. `ninja-build`
4. `gcc`
5. `g++`
6. `lxc`
7. `lxc-dev`

### Using `make` and `cmake`

`make configure` and `make build` will build an app for you.

`make run` will run it.

`make clean` if you think you messed everything up, but `make configure` should do the job too.

## Current issues

- `attach`ing the function to run inside the container creates a child subprocess. Supposedly it causes deadlock on `stop` call in `container::~container` because parent process waits for child process to be deleted but it's not getting deleted. That happens even when the child process (aka the given function) finishes execution successfully and returns `0`.
