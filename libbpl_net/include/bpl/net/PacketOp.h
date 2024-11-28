//
// Created by Bradley Remedios on 11/25/24.
//

#ifndef BPL_NET_PACKETOP_H
#define BPL_NET_PACKETOP_H
#include <memory>

#include <bpl/net/Packet.h>
#include <bpl/net/AddrInfo.h>

namespace bpl::net {
    class PacketOp {
    public:
        PacketOp() = default;
        virtual ~PacketOp() = default;

        //  Only check for a match.
        //
        //  This MUST not and should not block or wait.  This should only be a quick check to see if it "could" process
        //  the packet.
        [[nodiscard]] virtual bool isMatch(const PacketPtr& packet) const = 0;

        //  should return true if its processed the packet or false.
        //
        //  returns true
        //    - Packet was processed during the call
        //    - Drop the packet, do not put it back into the cache
        //
        //  returns false
        //    - Packet not processed / not applicable to operation.
        [[nodiscard]] virtual bool Process(const PacketPtr& packet, const bpl::net::AddrInfo& addr)=0;

        [[nodiscard]] const std::string& getName() const { return m_name; };
    protected:
        std::string m_name;
    }; // PacketOp

    typedef std::shared_ptr<PacketOp> PacketOpPtr;
}; // bpl::net
#endif //BPL_NET_PACKETOP_H