//
// Created by Bradley Remedios on 11/25/24.
//

#ifndef BPL_NET_PACKETCACHE_H
#define BPL_NET_PACKETCACHE_H

#include <list>
#include <memory>

#include <bpl/net/Packet.h>

namespace bpl::net {
    class PacketCache {
    public:
        static PacketCache& getInstance();
        ~PacketCache();

        void Push(const PacketPtr& packet);
        PacketPtr Pop();

        [[nodiscard]] size_t getMaxPackets() const { return m_maxPackets; }
        void setMaxPackets(size_t maxPackets) { m_maxPackets = maxPackets; }

        [[nodiscard]] size_t getMaxPacketSize() const { return m_maxPacketSize; }
        void setMaxPacketSzie(size_t maxPacketSize) { m_maxPacketSize = maxPacketSize; }
    private:
        std::list<std::shared_ptr<Packet>> m_packets;
        std::mutex m_lock;

        size_t m_maxPackets=100;
        size_t m_maxPacketSize=4096;

    }; // class PacketCache

    typedef std::shared_ptr<PacketCache> PacketCachePtr;
};// bpl::net
#endif //BPL_NET_PACKETCACHE_H