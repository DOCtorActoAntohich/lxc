#pragma once

#include <exception>
#include <string>

#include "doc/container.h"

namespace doc {
    class container_exception : std::exception {
    public:
        container_exception(std::string message) : message_(message) {}

        const char* what() const noexcept {
            return message_.data();
        }

    protected:
        std::string message_;
    };

    class container_from_name_exception : public container_exception {
    public:
        container_from_name_exception(std::string name) :
            container_exception::container_exception(
                "Failed to create container with name: " + name),
            name_(name) {}

    private:
        std::string name_;
    };

    class container_already_defined_exception : public container_exception {
    public:
        container_already_defined_exception(std::string name) :
            container_exception::container_exception(
                "Container already defined: " + name),
            name_(name) {}

    private:
        std::string name_;
    };

    class container_creation_exception : public container_exception {
    public:
        container_creation_exception(std::string name, container_settings settings) :
            container_exception::container_exception(
                "Failed to create container (" + name +
                ") with setings: " + settings.string()),
            name_(name),
            settings_(settings) {}

    private:
        std::string name_;
        container_settings settings_;
    };

    class container_start_exception : public container_exception {
    public:
        container_start_exception(std::string name) :
            container_exception::container_exception(
                "Failed to start container: " + name),
            name_(name) {}

    private:
        std::string name_;
    };
}