//
// Created by Bradley Remedios on 11/25/24.
//
#include "Debug.h"
#include <mutex>
#include <bpl/net/PacketCache.h>

namespace bpl::net {
    PacketCache& PacketCache::getInstance() {
      static PacketCache instance;

      return instance;
    } // getInstance

    PacketCache::~PacketCache() {
        std::lock_guard<std::mutex> lock(m_lock);
        m_packets.clear();
    } // ~PacketCache

    void PacketCache::Push(const PacketPtr& packet) {
        std::lock_guard<std::mutex> lock(m_lock);

        if (m_packets.size() >= m_maxPacketSize) {
            return;
        }
    } // Push

    PacketPtr PacketCache::Pop() {
        std::lock_guard<std::mutex> lock(m_lock);

        PacketPtr packet;

        if (m_packets.empty()) {
            packet = std::make_shared<Packet>();

            if (!packet->Create(m_maxPacketSize)) {
                ERROR_MSG("Failed to create packet");

                return packet;
            }
        }

        return packet;
    } // Pop

};// bpl::net
