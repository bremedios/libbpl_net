//
// Created by Bradley Remedios on 11/25/24.
//

#include "bpl/net/Udp.h"
#include "bpl/net/AddrInfo.h"

int main(int argc, char *argv[]) {
    bpl::net::AddrInfo addr;
    bpl::net::AddrInfo server;

    bpl::net::Udp udp;
    uint32_t data=19;

    addr.FromIp("127.0.0.1");
    addr.setPort(9999);

    if (argc > 1) {
        addr.FromIp(argv[1]);
    }
    if (argc > 2) {
        addr.setPort(atoi(argv[2]));
    }
    if (argc > 3) {
        data = htonl(atoi(argv[3]));
    }

    if (!udp.OpenSocket()) {
        std::cerr << "Udp::OpenSocket() Failed" << std::endl;

        return -1;
    }

    size_t result = udp.Send((char*)&data, sizeof(data), addr);

    if (result == -1) {
        std::cerr << "Udp::Send failed" << std::endl;

        return -1;
    }

    if (result != sizeof(data)) {
        std::cerr << "Expected to send" << sizeof(data) << " bytes but sent " << result << std::endl;

        udp.Close();
        return -1;
    }

    std::cout << "Sent data " << ntohl(data) << std::endl;

    result = udp.Recv((char*)&data, sizeof(data), server);

    if (result != sizeof(data)) {
        std::cerr << "Expected " << sizeof(data) << " bytes but received " << result << std::endl;

        udp.Close();
        return -1;
    }

    std::cout << "Received data " << ntohl(data)  << std::endl;

    udp.Close();

    return 0;
} // main
