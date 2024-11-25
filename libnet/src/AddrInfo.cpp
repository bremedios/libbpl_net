//
// Created by Bradley Remedios on 11/25/24.
//
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

#include "bpl/net/AddrInfo.h"

#include "Debug.h"

namespace bpl::net {
    AddrInfo::AddrInfo() {
        memset(&m_addr, 0, sizeof(m_addr));
    }

    void AddrInfo::Reset() {
        m_addrLen = sizeof(m_addr);
    } // Reset

    bool AddrInfo::FromIp(const std::string& ip) {
        Reset();

        int result = inet_pton(AF_INET, ip.c_str(), &m_addr.sin_addr);

        if (result == 0) {
            return true;
        }

        ERROR_MSG("inet_pton failed to convert IP " << ip << "to network address");

        return false;
    } // FromIp

    const std::string& AddrInfo::getIp() {
        char str[INET6_ADDRSTRLEN];

        m_ip = "";

        if (NULL == inet_ntop(AF_INET, &m_addr.sin_addr, str, INET_ADDRSTRLEN)) {
            ERROR_MSG("inet_ntop failed");

            return m_ip;
        }

        m_ip = std::string(str);

        return m_ip;
    } // GetIp

    void AddrInfo::setPort(unsigned short port) {
        m_addr.sin_port = htons(port);
    } // setPort

    unsigned short AddrInfo::getPort() {
        return ntohs(m_addr.sin_port);
    } // getPort
} //