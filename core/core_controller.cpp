//
// Created by Dominic Järmann on 19/01/2021.
//

#include <network.h>
#include "include/core_controller.h"

namespace cfx {
    CoreController::CoreController() {

    }

    CoreController::~CoreController() {

    };

    void CoreController::setEndpoint(const std::string & value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == "host_auto_ip4") {
            endpointBuilder.set_host(Network::hostIPv4());
        }
        else if (endpointURI.host() == "host_auto_ip6") {
            endpointBuilder.set_host(Network::hostIPv6());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        std::cout << endpointBuilder.to_uri().to_string() << std::endl;
        _listener = http_listener(endpointBuilder.to_uri());
    }

    std::string CoreController::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> CoreController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> CoreController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> CoreController::requestPath(const http_request & message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);
    }

}