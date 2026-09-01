#include "onion.h"
#include <openssl/evp.h>

std::vector<uint8_t> OnionCrypto::wrapOnionLayer(const std::vector<uint8_t>& data, const PublicKey& relayKey) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> encrypted(data.size() + 16);
    
    int len;
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr, relayKey.data(), nullptr);
    EVP_EncryptUpdate(ctx, encrypted.data(), &len, data.data(), data.size());
    EVP_EncryptFinal_ex(ctx, encrypted.data() + len, &len);
    
    EVP_CIPHER_CTX_free(ctx);
    return encrypted;
}

std::vector<uint8_t> OnionCrypto::unwrapOnionLayer(const std::vector<uint8_t>& encrypted, const PrivateKey& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> decrypted(encrypted.size());
    
    int len;
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr, key.data(), nullptr);
    EVP_DecryptUpdate(ctx, decrypted.data(), &len, encrypted.data(), encrypted.size());
    EVP_DecryptFinal_ex(ctx, decrypted.data() + len, &len);
    
    EVP_CIPHER_CTX_free(ctx);
    return decrypted;
}