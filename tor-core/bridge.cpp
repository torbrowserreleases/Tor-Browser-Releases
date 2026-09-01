#include "bridge.h"
#include <curl/curl.h>

bool BridgeManager::connectViaObfs4(const std::string& bridgeAddress) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;
    
    curl_easy_setopt(curl, CURLOPT_URL, bridgeAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_PROXY, obfs4ProxyAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    
    return res == CURLE_OK;
}

bool BridgeManager::connectViaSnowflake() {
    // WebRTC-based pluggable transport
    return snowflakeClient.connect(stunServers, brokerURL);
}