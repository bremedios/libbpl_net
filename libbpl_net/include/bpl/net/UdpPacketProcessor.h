//
// Created by Bradley Remedios on 11/25/24.
//
#ifndef UDPPACKETPROCESSOR_H
#define UDPPACKETPROCESSOR_H

#include <string>
#include <mutex>
#include <map>

#include <bpl/net/Packet.h>
#include <bpl/net/PacketOp.h>

namespace bpl::net {
    class UdpPacketProcessor {
    public:
        static UdpPacketProcessor& getInstance();

        ~UdpPacketProcessor();

        //  returns true
        //    packet has been processed succesfully by a registered packet op
        //  returns false
        //    packet has not been processed by a registered packet op
        //
        //  WARNING:
        //      Once packet is passed to this function it will be kept/disposed of as needed.
        bool ProcessPacket(bpl::net::PacketPtr packet, const bpl::net::AddrInfo& addr);

        //  returns false if packet op is already registered.
        void AddPacketOp(PacketOpPtr packetOp);

        void RemovePacketOp(const std::string& name);
    private:
        std::mutex m_lock;
        std::map<std::string, PacketOpPtr> m_packetOps;
    }; // UdpPacketProcessor

}; // bpl::net

#endif //UDPPACKETPROCESSOR_H
