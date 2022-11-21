#pragma once

#include <lxc/lxccontainer.h>
#include <sstream>
#include <string>

namespace doc {
    struct container_settings {
        std::string rootfs_template;
        std::string distributive;
        std::string release;
        std::string architecture;

        std::string string() const;
    };

    class container {
    public:
        container(std::string name, container_settings settings);
        ~container();

        const std::string& name() const;

        void run() const;

    private:
        struct lxc_container* c_;
        std::string name_;
        container_settings settings_;
    };
}
