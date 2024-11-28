//
// Created by Bradley Remedios on 11/25/24.
//
#include <bpl/net/Packet.h>

namespace bpl::net {
    Packet::Packet() = default;

    Packet::~Packet() {
        Destroy();
    }

    bool Packet::Create(size_t maxPacketSize) {
        m_maxPacketSize = maxPacketSize;
        m_packetSize = 0;

        m_packetData = new char[m_maxPacketSize];

        return true;
    } // Create

    void Packet::Destroy() {
        delete [] m_packetData;
    } // Destroy
}; // bpl::net