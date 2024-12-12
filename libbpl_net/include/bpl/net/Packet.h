//
// Created by Bradley Remedios on 11/25/24.
//

#ifndef BPL_NET_PACKET_H
#define BPL_NET_PACKET_H

#include <cstddef>
#include <memory>

namespace bpl::net {
    class Packet {
    public:
        Packet();
        ~Packet();

        [[nodiscard]] bool Create(size_t maxPacketSize=4096);
        void Destroy();

        [[nodiscard]] bool isValid() const { return m_packetData != nullptr; }
        void setPacketDataSize(size_t size) { m_packetSize = size; }
        [[nodiscard]] size_t getPacketSize() const { return m_packetSize; }
        [[nodiscard]] size_t getMaxPacketSize() const { return m_maxPacketSize; }
        [[nodiscard]] void* getPacketData() { return (void*)m_packetData; }

    private:
        char* m_packetData = nullptr;
        size_t m_maxPacketSize=0;
        size_t m_packetSize = 0;
    }; // Packet

    typedef std::shared_ptr<Packet> PacketPtr;
}; // bpl::net

#endif //BPL_NET_PACKET_H