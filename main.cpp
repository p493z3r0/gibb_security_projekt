#include <iostream>
#include "app/controllers/user/UserController.h"
#include <interrupt_handler.h>
#include <runtime_utils.h>

int main() {
    InterruptHandler::hookSIGINT();

    UserController server;
    server.setEndpoint("http://host_auto_ip4:6502/v1/api/user");
    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "API Pending " << server.endpoint() << '\n';

        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "something wrong happen! :(" << '\n';
    }
    catch(...) {
        RuntimeUtils::printStackTrace();
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
