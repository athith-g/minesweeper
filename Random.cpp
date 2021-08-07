#include "Random.hpp"

std::mt19937 Random::random;

int Random::Int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    
    return dist(random);
}
