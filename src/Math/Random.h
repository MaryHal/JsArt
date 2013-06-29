#ifndef _Random_h_
#define _Random_h_

/*
* Class Comments:
* 		- Random number generator class. Implementation of mersenne twister
*/
class Random
{
    private:
        // constants
        static const unsigned long N  = 624;
        static const unsigned long M = 397;
        static const unsigned long MATRIX_A = 0x9908b0dfUL;
        static const unsigned long UPPER_MASK = 0x80000000UL;
        static const unsigned long LOWER_MASK = 0x7fffffffUL;

        unsigned long seed;
        unsigned long state[N];
        unsigned long stateIndex;

    public:
        Random();
        Random(unsigned long seedv);

        // Init random generator
        void setSeed();
        void setSeed(unsigned long seedv);

        // Generate random number
        unsigned long genRand_Int32();

        unsigned long genRand(unsigned long max);
        int genRand(int min, int max);
        double genRand(double min, double max);

        // Retrieve the number used as a seed
        unsigned long getSeed() const;
};

static Random rng;

#endif
