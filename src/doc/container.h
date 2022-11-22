#pragma once

#include <functional>
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

        template<typename... var_args>
        int run(int (*callable)(var_args...), var_args... args) {
            std::function<int(var_args...)> new_callable = callable;
            return run(new_callable, args...);
        }

        template<typename... var_args>
        int run(std::function<int(var_args...)> callable, var_args... args) {
            start_();

            using func_type = decltype(callable);
            using args_type = std::tuple<var_args...>;
            using c_payload = std::pair<func_type, args_type>;

            auto c_function = [](void* c_args) {
                auto [callable, args] = *static_cast<c_payload*>(c_args);
                return std::apply(callable, args);
            };
            c_payload c_args = std::make_pair(callable, std::make_tuple(args...));

            lxc_attach_options_t attach_options;
            int out_pid;
            int ret = c_->attach(
                c_, c_function, static_cast<void*>(&c_args), &attach_options, &out_pid);
            if (ret != 0) {
                std::cerr << "Failed to attach" << std::endl;
                return -1;
            }
            return out_pid;
        }

    private:
        void start_();

        struct lxc_container* c_;
        std::string name_;
        container_settings settings_;
    };
}
