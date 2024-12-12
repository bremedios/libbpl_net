//
// Created by Bradley Remedios on 11/25/24.
//
#include <mutex>
#include <thread>
#include <ranges>

#include <bpl/net/Packet.h>
#include <bpl/net/PacketOp.h>
#include <bpl/net/UdpPacketProcessor.h>
#include <bpl/net/PacketCache.h>

#include "Debug.h"

namespace bpl::net {
    UdpPacketProcessor& UdpPacketProcessor::getInstance() {
        static UdpPacketProcessor instance;

        return instance;
    } // getInstance

    UdpPacketProcessor::~UdpPacketProcessor() {
        std::lock_guard<std::mutex> guard(m_lock);
        m_packetOps.clear();
    }

    bool UdpPacketProcessor::ProcessPacket(bpl::net::PacketPtr& packet, const bpl::net::AddrInfo& addr) {
        PacketOpPtr op;

        // we don't process, but we look for a match.  We do not want to hold the lock for too long.
        {
            std::lock_guard<std::mutex> guard(m_lock);
            for (auto it : std::views::values(m_packetOps)) {
                if (it->isMatch(packet)) {
                    op = it;
                    break;
                }
            }
        }

        // nothing registered to handle the request
        if (op.get() == nullptr) {
            ERROR_MSG("Nothing registered to handle packet");
            PacketCache::getInstance().Push(packet);

            return false;
        }

        //  This normally should not fail as we should not have multiple handling types in our list of ops.
        if (!op->Process(packet, addr)) {
            ERROR_MSG("Failed to process packet that matched");
            PacketCache::getInstance().Push(packet);

            return false;
        }

        PacketCache::getInstance().Push(packet);

        return true;
    } // ProcessPacket

    //  returns false if packet op is already registered.
    void UdpPacketProcessor::AddPacketOp(PacketOpPtr packetOp) {
        DEBUG_MSG("Adding packetOp " << packetOp->getName());

        std::lock_guard<std::mutex> guard(m_lock);

        m_packetOps.emplace(packetOp->getName(), packetOp);
    } // AddPacketOp

    void UdpPacketProcessor::RemovePacketOp(const std::string& name) {
        std::lock_guard<std::mutex> guard(m_lock);

        m_packetOps.erase(name);
    } // RemovePacketOp

}; // bpl::net