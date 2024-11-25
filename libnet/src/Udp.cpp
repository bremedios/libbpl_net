//
// Created by Bradley Remedios on 11/24/24.
//
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstddef>

#include "bpl/net/Udp.h"

#include "Debug.h"

namespace bpl::net {
    Udp::~Udp() {
        Close();
    }

    bool Udp::OpenSocket() {
        if (m_socket >= 0) {
            ERROR_MSG("Socket already open");

            return false;
        }

        DEBUG_MSG("Opening IPv4 DGRAM Socket");

        m_socket = socket(AF_INET, SOCK_DGRAM, 0);

        return true;
    } // OpenSocket

    bool Udp::Bind(uint16_t port) {
        if (!OpenSocket()) {
            ERROR_MSG("Failed to open socket");

            return false;
        }

        DEBUG_MSG("Binging to Any Address on Port " << port);

        struct sockaddr_in addr;

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            ERROR_MSG("Failed to bind socket");

            return false;
        }

        return true;
    } // Bind

    void Udp::Close() {
        if (0 <= m_socket) {
            close(m_socket);

            m_socket = -1;
        }
    } // Close

    size_t Udp::Recv(char* buffer,  uint32_t bufferSize, AddrInfo& addrInfo) {
        if (0 > m_socket) {
            ERROR_MSG("Socket not open");

            return -1;
        }

        addrInfo.Reset();

        size_t bytes = recvfrom(m_socket, buffer, bufferSize, 0, (struct sockaddr*)&addrInfo.m_addr, &addrInfo.m_addrLen);

        if (bytes == -1) {
            ERROR_MSG("recvfrom failed");

            return -1;
        }

        return bytes;
    } // Recv

    size_t Udp::Send(const char* buffer, size_t bufferSize, const AddrInfo& addrInfo) {
        if (0 > m_socket) {
            ERROR_MSG("Socket not open");

            return -1;
        }

        ssize_t sent = sendto(m_socket, buffer, bufferSize, 0, (const sockaddr*)&addrInfo.m_addr, addrInfo.m_addrLen);

        if (sent == -1) {
            ERROR_MSG("Failed to send");

            return sent;
        }

        DEBUG_MSG("Sent " << sent << " bytes");

        return sent;
    } // Send
} // bpl::net
