//
// Created by Dominic Järmann on 19/01/2021.
//



#include "include/network.h"

namespace cfx {
    HostInetInfo Network::queryHostInetInfo(unsigned short family) {
        io_service ios;
        tcp::resolver resolver(ios);

        tcp::resolver::query query("127.0.0.1","6502",tcp::resolver::query::canonical_name);


        return resolver.resolve(query);
    }

    std::string Network::hostIP(unsigned short family) {
        auto hostInetInfo = queryHostInetInfo(family);

        tcp::resolver::iterator end;
        while (hostInetInfo != end) {
            tcp::endpoint ep = *hostInetInfo++;
            sockaddr sa = *ep.data();
            std::cout << sa.sa_family << std::endl;
            if (sa.sa_family == family) {
                return ep.address().to_string();
            }
        }

        return nullptr;
    }
}