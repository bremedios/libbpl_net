//
// Created by Bradley Remedios on 11/25/24.
//
#include <arpa/inet.h>
#include "bpl/net/Udp.h"
#include "bpl/net/AddrInfo.h"

int main(int argc, char *argv[]) {
    int port=333;
    bpl::net::Udp udp;
    bpl::net::AddrInfo client;
    uint32_t data=0;

    if (argc > 1) {
        port = atoi(argv[1]);
    }

    if (!udp.Bind(port)) {
        std::cerr << "Failed to bind to port " << port << std::endl;

        return -1;
    }

    size_t result = udp.Recv((char*)&data, sizeof(data), client);

    if (result == -1) {
        std::cerr << "Udp::Recv Failed" << std::endl;

        return -1;
    }

    if (result != sizeof(data)) {
        std::cerr << "Expected " << sizeof(data) << " bytes but received " << result << std::endl;

        udp.Close();
        return -1;
    }

    std::cout << "Received " << result << " bytes" << std::endl;
    std::cout << "Received data " << ntohl(data) << " sending back " << ntohl(data) * ntohl(data) << std::endl;

    data = htonl(ntohl(data) * ntohl(data));

    result = udp.Send((char*)&data, sizeof(data), client);

    if (result != sizeof(data)) {
        std::cerr << "Expected to send" << sizeof(data) << " bytes but sent " << result << std::endl;

        udp.Close();
        return -1;
    }

    udp.Close();

    return 0;
} // main
