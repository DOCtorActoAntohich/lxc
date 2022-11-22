#include "container.h"

#include <iostream>
#include <string>

#include "doc/exceptions.h"

std::string doc::container_settings::string() const {
    std::stringstream ss;
    ss << "Template " << rootfs_template << " with settings: { dist: " << distributive
       << ", release: " << release << ", arch: " << architecture << " }";
    return ss.str();
}

doc::container::container(std::string name, container_settings settings) :
    name_(name), settings_(settings) {
    c_ = lxc_container_new(name_.data(), NULL);
    if (c_ == nullptr) {
        throw container_from_name_exception(name);
    }

    if (c_->is_defined(c_)) {
        throw container_already_exists_exception(name);
    }

    if (!c_->createl(
            c_,
            settings_.rootfs_template.data(),
            NULL,
            NULL,
            LXC_CREATE_QUIET,
            "-d",
            settings_.distributive.data(),
            "-r",
            settings.release.data(),
            "-a",
            settings.architecture.data(),
            NULL)) {
        throw container_creation_exception(name, settings);
    }
}

doc::container::~container() {
    if (c_->is_running(c_) && !c_->shutdown(c_, 30)) {
        std::cerr << "Failed to gracefully stop the container: " << name_ << "\n"
                  << "Forcing container to stop..." << std::endl;
    }

    if (c_->is_running(c_) && !c_->stop(c_)) {
        std::cerr << "Failed to kill the container: " << name_ << std::endl;
    }

    if (!c_->destroy(c_)) {
        std::cerr << "Failed to destroy the container: " << name_ << std::endl;
    }

    lxc_container_put(c_);
}

const std::string& doc::container::name() const {
    return name_;
}

void doc::container::start_() {
    if (!c_->start(c_, 0, NULL)) {
        throw container_start_exception(name_);
    }
}
