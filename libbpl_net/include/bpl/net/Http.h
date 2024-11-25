//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_NET_HTTP_H
#define BPL_NET_HTTP_H

#include <memory>

#include "curl/curl.h"

#include <bpl/storage/Payload.h>

namespace bpl::net {

    class Http {
    public:
        Http();
        ~Http();

        void Destroy();
        [[nodiscard]] bool Create();

        [[nodiscard]] bool Get(const std::string& url);

        [[nodiscard]] const bpl::storage::Payload& getPayload() const { return m_payload; };

    private:
        size_t WriteCallback_(const char* data, size_t size, size_t nmemb);
        static size_t WriteCallbackFunc_(const char* data, size_t size, size_t nmemb, void* userp);

        long                     m_httpVersion = CURL_HTTP_VERSION_3;
        CURL*                    m_curl= nullptr;
        CURLcode                 m_result=CURLE_OK;

        bpl::storage::Payload    m_payload;
    };

    typedef std::shared_ptr<Http> HttpPtr;

} // bpl::net

#endif // BPL_NET_HTTP_H
