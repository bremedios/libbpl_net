//
// Created by Bradley Remedios on 11/24/24.
//

#ifndef BPL_NET_UDP_H
#define BPL_NET_UDP_H

#include <bits/stdc++.h>

#include <bpl/net/AddrInfo.h>
#include <bpl/net/Packet.h>

namespace bpl::net {
    class Udp {
    public:
        ~Udp();

        [[nodiscard]] bool OpenSocket();
        [[nodiscard]] bool Bind(uint16_t port);
        void Close();

        [[nodiscard]] bool Recv(PacketPtr& packet, AddrInfo& addr) const;
        [[nodiscard]] bool Send(const PacketPtr& packet, const AddrInfo& addr) const;

        [[nodiscard]] size_t Recv(char* buffer,  uint32_t bufferSize, AddrInfo& addr) const;
        [[nodiscard]] size_t Send(const char* buffer, size_t bufferSize, const AddrInfo& addr) const ;
    private:

        int m_socket=-1;
    }; // Udp

    typedef std::shared_ptr<Udp> UdpPtr;
} // bpl::net

#endif //BPL_NET_UDP_H