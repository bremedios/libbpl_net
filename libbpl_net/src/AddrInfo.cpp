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
        m_addr.sin_family = AF_INET;
    }

    void AddrInfo::Reset() {
        m_addrLen = sizeof(m_addr);
    } // Reset

    bool AddrInfo::FromIp(const std::string& ip) {
        Reset();

        int result = inet_pton(AF_INET, ip.c_str(), &m_addr.sin_addr);

        if (result == 1) {
            return true;
        }

        ERROR_MSG("inet_pton failed to convert IP \"" << ip << "\" to network address");

        return false;
    } // FromIp

    std::string AddrInfo::getIp() const {
        char str[INET6_ADDRSTRLEN];

        if (nullptr == inet_ntop(AF_INET, &m_addr.sin_addr, str, INET_ADDRSTRLEN)) {
            ERROR_MSG("inet_ntop failed");

            return m_ip;
        }

        return {str};
    } // GetIp

    void AddrInfo::setPort(unsigned short port) {
        m_addr.sin_port = htons(port);
    } // setPort

    unsigned short AddrInfo::getPort() const {
        return ntohs(m_addr.sin_port);
    } // getPort
} //