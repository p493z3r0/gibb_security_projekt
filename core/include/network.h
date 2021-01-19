//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_NETWORK_H
#define MAIN_NETWORK_H

#pragma once

#include <string>
#include "common.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace cfx {
    using HostInetInfo = tcp::resolver::iterator;

    class Network {
    private:
        static HostInetInfo queryHostInetInfo(unsigned short family);

        static std::string hostIP(unsigned short family);

    public:
        static std::string hostIPv4() {
            return hostIP(AF_INET);
        }

        static std::string hostIPv6() {
            return hostIP(AF_INET6);
        }

        static std::string hostName() {
            return ip::host_name();
        }
    };
}
#endif //MAIN_NETWORK_H
