#include <iostream>
#include <cstdint>
#include <string>
#include "gui_message_table_ids.h"
#include "SeededXorshift128.h"

// Gets the save seed from the SteamID3 
uint32_t GetSaveSeedForSteamID(uint32_t steamID) {
    return GUI_MESSAGE_TABLE_IDS[steamID % (GUI_MESSAGE_TABLE_IDS.size()-1)];
}

std::string GetSaveBlowfishKeyForSteamID(uint32_t steamID) {
    auto save_seed = GetSaveSeedForSteamID(steamID);

    SeededXorshift128 mrand;
    mrand.Init(save_seed);

    char output[56];
    memset(output, 0, sizeof(output));

    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";
    auto alphabet_length = strlen(alphabet);

    for (size_t i = 0; i < sizeof(output); i++)
    {
        char x = alphabet[mrand.NextRand() % alphabet_length];
        output[i] = x;
    }

    return std::string(output, sizeof(output));
}


int main() {
    uint32_t steam_id = 0;
    std::cout << "Enter your Steam32 ID (e.g. from https://steamid.xyz): ";
    std::cin >> steam_id;

    std::cout << "Blowfish seed: " << std::hex << GetSaveSeedForSteamID(steam_id) << "\n";
    std::cout << "Blowfish key: \"" << GetSaveBlowfishKeyForSteamID(steam_id) << "\"\n";


    // Old .arc blowfish key generation stuff
    /*
    const char alphabet[] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2D, 0x5F, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x00, 0x00};
    uint64_t alphabet_length = 0;
    do                                      // strlen(alphabet)
        ++alphabet_length;
    while (alphabet[alphabet_length]);


    SeededXorshift128 mrand;
    char output[56];
    uint32_t rand_seed = 0x1FE01ED9;


    bool unk_mode = 1;
    if (unk_mode == 1)
    {
        mrand.Init(rand_seed);
        for (size_t i = 0; i < 56; i++)
        {
            char x = alphabet[(unsigned int)mrand.NextRand() % 0x62];
            output[i] = x;
        }
    }
    else
    {
        mrand.Init((rand_seed >> 1) + 1);
        for (size_t i = 0; i < 56; i++)
        {
            output[i] = alphabet[(unsigned int)mrand.NextRand() % 0x62];
        }
    }
    

    for (int i = 0; i < 56; i++)
    {
        printf("%02X", output[i]);
    }
    printf("\n");
    */

	return 0;
}