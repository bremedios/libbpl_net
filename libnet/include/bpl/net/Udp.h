//
// Created by Bradley Remedios on 11/24/24.
//

#ifndef BPL_NET_UDP_H
#define BPL_NET_UDP_H

#include <string>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "bpl/net/AddrInfo.h"

namespace bpl::net {
    class Udp {
    public:
        ~Udp();

        bool OpenSocket();
        bool Bind(uint16_t port);
        void Close();
        size_t Recv(char* buffer,  uint32_t bufferSize, AddrInfo& addr);
        size_t Send(const char* buffer, size_t bufferSize, const AddrInfo& addr);
    private:

        int m_socket=-1;
    }; // Udp
} // bpl::net

#endif //BPL_NET_UDP_H
