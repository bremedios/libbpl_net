//
// Created by Bradley Remedios on 11/25/24.
//
#ifndef BPL_NET_ADDRINFO_H
#define BPL_NET_ADDRINFO_H

#include <string>
#include <netinet/in.h>

namespace bpl::net {
    class AddrInfo{
    public:
        friend class Udp;

        AddrInfo();

        void setPort(unsigned short port);
        [[nodiscard]] unsigned short getPort() const;

        [[nodiscard]] bool FromIp(const std::string& ip);
        [[nodiscard]] std::string getIp() const;
        void Reset();

        struct sockaddr_in& getAddr() { return m_addr;}

    private:
        std::string        m_ip;
        struct sockaddr_in m_addr={0};
        socklen_t          m_addrLen=sizeof(m_addr);

    };
} // bpl::net


#endif //BPL_NET_ADDRINFO_H