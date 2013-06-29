#include "Random.h"
#include <ctime>

Random::Random()
{
    setSeed();
}

Random::Random(unsigned long seedv)
{
    setSeed(seedv);
}

// ************************************
//  Init random generator
// ************************************
void Random::setSeed()
{
    seed = static_cast<unsigned long>(std::time(0));
    state[0] = seed & 0xffffffffUL;
    for (stateIndex = 1; stateIndex < N; ++stateIndex)
    {
        state[stateIndex] = (1812433253UL * (state[stateIndex - 1] ^
                    state[stateIndex - 1] >> 30) + stateIndex);

        state[stateIndex] &= 0xffffffffUL;
    }
}

void Random::setSeed(unsigned long seedv)
{
    seed = seedv;
    
    state[0] = seed & 0xffffffffUL;
    for (stateIndex = 1; stateIndex < N; ++stateIndex)
    {
        state[stateIndex] = (1812433253UL * (state[stateIndex - 1] ^
                    state[stateIndex - 1] >> 30) + stateIndex);

        state[stateIndex] &= 0xffffffffUL;
    }
}

// ************************************
//  Generate random number
// ************************************
unsigned long Random::genRand_Int32()
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0UL, MATRIX_A};

    if (stateIndex >= N)
    {
        unsigned int kk;

        for (kk = 0; kk < N - M; ++kk)
        {
            y = (state[kk] & UPPER_MASK) | (state[kk + 1] & LOWER_MASK);
            state[kk] = state[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }

        for (;kk < N - 1; ++kk)
        {
            y = (state[kk] & UPPER_MASK) | (state[kk + 1] & LOWER_MASK);
            state[kk] = state[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }

        y = (state[N - 1] & UPPER_MASK) | (state[0] & LOWER_MASK);
        state[N - 1] = state[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        stateIndex = 0;
    }

    y = state[stateIndex++];

    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

unsigned long Random::genRand(unsigned long max)
{
    return genRand_Int32() % max;
}

int Random::genRand(int min, int max)
{
    return min + genRand_Int32()%(max-min+1);
}

double Random::genRand(double min, double max)
{
    return min + ((genRand_Int32()*(1.0/4294967295.0))*(max-min));
}

unsigned long Random::getSeed() const
{
    return seed;
}

