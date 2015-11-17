#include <bitcoin/bitcoin.hpp>

std::string get_address(const bc::short_hash& key_hash)
{
    bc::data_chunk unencoded_address;
    unencoded_address.reserve(25);
    unencoded_address.push_back(0 /* version prefix: normal bitcoin address */);
    bc::extend_data(unencoded_address, key_hash);
    bc::append_checksum(unencoded_address);
    //
    assert(unencoded_address.size() == 25);
    return bc::encode_base58(unencoded_address);
}

int main()
{
    // private secret key
    bc::ec_secret secret;
    bool success = bc::decode_base16(secret,
                                     // private key in 64-digits hex format
                                     "038109007313a5807b2eccc082c8c3fbb988a973cacf1a7df9ce725c31b14776");
    assert(success);

    // bc::ec_point public_key = bc::secret_to_public_key(secret);

    bc::ec_compressed public_ckey;
    bc::ec_uncompressed public_key;
    bc::secret_to_public(public_key, secret);  // start with 04 (uncompressed)
    bc::secret_to_public(public_ckey, secret); // start with 02 or 03 (compressed)
    std::cout << "Public key (hex): "            << bc::encode_base16(public_key) << std::endl;
    std::cout << "Public compressed key (hex): " << bc::encode_base16(public_ckey) << std::endl;

    // Create Bitcoin address.
    //
    // bc::payment_address payaddr;
    // bc::set_public_key(payaddr, public_key);
    // const std::string address = payaddr.encoded();

    // Reserve 25 bytes
    //  [version:1]
    //  [hash:20]
    //  [checksum:4]
    {
        const std::string address = get_address(bc::bitcoin_short_hash(public_key));
        std::cout << "Bitcoin Address from uncompressed public key: " << address << std::endl;

    }

    {
        // generate bitcoin address from a compressed public key.
        const std::string address = get_address(bc::bitcoin_short_hash(public_ckey));
        std::cout << "Bitcoin Address from   compressed public key: " << address << std::endl;
    }

    return 0;
}
