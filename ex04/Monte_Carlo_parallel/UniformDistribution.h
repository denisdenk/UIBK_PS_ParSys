//
// Created by anykey on 06.11.17.
//

#ifndef MONTE_CARLO_PARALLEL_UNIFORMDISTRIBUTION_H
#define MONTE_CARLO_PARALLEL_UNIFORMDISTRIBUTION_H

#include <chrono>

class UniformDistribution {
public:
    UniformDistribution()
            : generator(),
              distribution(-1.0, 1.0)
    {
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }

    double sample()
    {
        return distribution(generator);
    }

    UniformDistribution(const UniformDistribution& ) = delete;
    UniformDistribution& operator()(const UniformDistribution& ) = delete;
    UniformDistribution(UniformDistribution&& ) = delete;
    UniformDistribution& operator()(UniformDistribution&& ) = delete;

private:
    std::default_random_engine generator;

    std::uniform_real_distribution<double> distribution;
};


#endif //MONTE_CARLO_PARALLEL_UNIFORMDISTRIBUTION_H
