#include "genixx/chromosome/Chromosome.h"
#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/error/exceptions.h"

#include <catch2/catch_all.hpp>

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

TEST_CASE("All random chromosomes phenotypes in range")
{
    const auto cChromosomes = 1000;
    std::vector<std::shared_ptr<genixx::IChromosome>> chromosomes(cChromosomes);

    for (std::uint32_t i = 0; i < cChromosomes; i++)
    {
        chromosomes[i] = genixx::NumericChromosome<double>::random(11, 1, 100);
        auto phenotype = dynamic_cast<genixx::NumericChromosome<double>*>(chromosomes[i].get())->phenotype();
        REQUIRE((phenotype >= 1 && phenotype <= 100));
    }
}

TEST_CASE("Expected exception")
{
    auto chromosome1 = genixx::NumericChromosome<double>::random(11);
    auto chromosome2 = genixx::NumericChromosome<double>::random(19);

    try
    {
        chromosome1->cross(chromosome2);
        REQUIRE(false);
    }
    catch (std::exception& e)
    {
        REQUIRE(std::strcmp(e.what(), genixx::WrongSizeException().what()) == 0);
    }
}
