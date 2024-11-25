//
// Created by Bradley Remedios on 11/25/24.
//
#ifndef BPL_NET_ADDRINFO_H
#define BPL_NET_ADDRINFO_H

#include <string>

namespace bpl::net {
    class AddrInfo{
    public:
        friend class Udp;

        AddrInfo();

        void setPort(unsigned short port);
        unsigned short getPort();

        bool FromIp(const std::string& ip);
        const std::string& getIp();
        void Reset();

        struct sockaddr_in& getAddr() { return m_addr;}

    private:
        std::string        m_ip;
        struct sockaddr_in m_addr;
        socklen_t          m_addrLen=sizeof(m_addr);

    };
} // bpl::net


#endif //BPL_NET_ADDRINFO_H
