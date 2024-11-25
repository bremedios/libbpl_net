//
// Created by Bradley Remedios on 11/20/24.
//

#include "bpl/net/Http.h"

#include <cstring>
#include <iostream>

namespace bpl::net {
    Http::Http() = default;

    Http::~Http() {
        Destroy();
    }

    bool Http::Create() {
        if (nullptr != m_curl) {
            std::cerr << "Http::Create: Curl already exists, cannot recreate" << std::endl;

            return false;
        }

        m_curl = curl_easy_init();

        if (nullptr == m_curl) {
            std::cerr << "Http::Create: curl_easy_init failed" << std::endl;
            return false;
        }

        return true;
    } // Create

    void Http::Destroy() {
        if (nullptr != m_curl) {
            curl_easy_cleanup(m_curl);
            m_curl = nullptr;
        }

        m_payload.Clear();

    } // Destroy

    bool Http::Get(const std::string& url) {
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_HTTP_VERSION, m_httpVersion);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Http::WriteCallbackFunc_);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

        m_result = curl_easy_perform(m_curl);

        if (CURLE_OK != m_result) {
            std::cerr << "Http::Get: curl_easy_perform failed: " << curl_easy_strerror(m_result) << std::endl;
            std::cerr << "Http::Get:     url: " << url << std::endl;

            return false;
        }

        return true;
    } // Get


    size_t Http::WriteCallback_(const char* data, size_t size, size_t nmemb) {
        if ((0 == size) || (nullptr == data) || (0 == nmemb)) {
            return 0;
        }

        if (!m_payload.CopyChunk(data, size*nmemb)) {
            std::cerr << "Http::WriteCallback_: Failed to copy chunk data" << std::endl;

            return 0;
        }

        return size * nmemb;
    } // WriteCallback_

    size_t Http::WriteCallbackFunc_(const char* data, size_t size, size_t nmemb, void* userp) {
        Http* http = static_cast<Http*>(userp);

        if (nullptr == http) {
            return 0;
        }

        return http->WriteCallback_(data, size, nmemb);
    } // WriteCallback_
} // bpl::net
