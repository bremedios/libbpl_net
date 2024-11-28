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

        struct sockaddr_in addr={0};

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

    bool Udp::Recv(PacketPtr& packet, AddrInfo& addrInfo) const {
        if (!packet->isValid()) {
            ERROR_MSG("Invalid packet");

            return false;
        }

        size_t dataRead = Recv((char*)packet->getPacketData(), packet->getMaxPacketSize(), addrInfo);

        if (-1 == dataRead) {
            packet->setPacketDataSize(0);

            return false;
        }

        DEBUG_MSG("Received " << dataRead << " bytes");

        packet->setPacketDataSize(dataRead);

        return true;
    } // Recv

    bool Udp::Send(const PacketPtr& packet, const AddrInfo& addrInfo) const {
        if (!packet->isValid()) {
            ERROR_MSG("Invalid packet");

            return false;
        }

        DEBUG_MSG("Sending packet of " << packet->getPacketSize() << " bytes to " << addrInfo.getIp() << ":" << std::to_string(addrInfo.getPort()));

        size_t dataWritten = Send(static_cast<char*>(packet->getPacketData()), packet->getPacketSize(), addrInfo);

        if (-1 == dataWritten) {
            ERROR_MSG("Failed to send packet: errno(" << errno << ")");

            return false;
        }

        if (dataWritten != packet->getPacketSize()) {
            ERROR_MSG("Failed to send entire packet (" << dataWritten << " of " << packet->getPacketSize() << " bytes sent");

            return false;
        }

        return true;
    } // Send

    size_t Udp::Recv(char* buffer,  uint32_t bufferSize, AddrInfo& addrInfo) const {
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

        DEBUG_MSG("Received " << bytes << " bytes from " << addrInfo.getIp());

        return bytes;
    } // Recv

    size_t Udp::Send(const char* buffer, size_t bufferSize, const AddrInfo& addrInfo) const {
        if (0 > m_socket) {
            ERROR_MSG("Socket not open");

            return -1;
        }

        DEBUG_MSG("Sending " << bufferSize << " bytes");

        ssize_t sent = sendto(m_socket, buffer, bufferSize, 0, (const sockaddr*)&addrInfo.m_addr, addrInfo.m_addrLen);

        if (sent == -1) {
            ERROR_MSG("Failed to send");

            return sent;
        }

        DEBUG_MSG("Sent " << sent << " bytes");

        return sent;
    } // Send
} // bpl::net