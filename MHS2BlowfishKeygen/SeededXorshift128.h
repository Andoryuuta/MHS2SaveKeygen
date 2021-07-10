#pragma once
#include <cstdint>

class SeededXorshift128 {
public:
    unsigned long x;
    unsigned long y;
    unsigned long z;
    unsigned long w;

    void Init(unsigned int seed)
    {
        int v2; // r12
        int v3; // r3
        unsigned int v4; // lr
        unsigned int v5; // r2
        int i; // r1
        int v7; // r5

        v2 = 0x159A55E5;
        this->x = 123456789;
        this->y = 362436069;
        this->z = 521288629;
        this->w = 88675123;

        v3 = 521288629;
        v4 = 88675123;
        v5 = seed ^ 0xAC9365;

        for (size_t i = 0; i < 100; i++)
        {
            v7 = v2;
            v2 = v3;
            v3 = v4;
            v5 ^= (0x65AC9365u >> (v5 & 3)) ^ ((v5 ^ (0x65AC9365u >> (v5 & 3))) >> 3) ^ ((v5 ^ (0x65AC9365u >> (v5 & 3))) >> 4) ^ (8 * (v5 ^ (0x65AC9365u >> (v5 & 3)))) ^ (16 * (v5 ^ (0x65AC9365u >> (v5 & 3))));
            v4 ^= v5 ^ (v5 << 15) ^ ((v5 ^ (v5 << 15)) >> 4) ^ (v4 >> 21);
        }


        this->x = v7;
        this->y = v2;
        this->z = v3;
        this->w = v4;
    }

    int64_t NextRand()
    {
        int t = this->x ^ (this->x << 15);

        this->x = this->y;
        this->y = this->z;
        this->z = this->w;

        this->w = t ^ this->w ^ ((t ^ (this->w >> 17)) >> 4);
        return this->w;
    }
};