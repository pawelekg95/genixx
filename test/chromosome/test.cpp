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

TEST_CASE("Comparing chromosomes")
{
    auto chromosome1 = genixx::NumericChromosome<double>::random(11);
    auto chromosomeCpy1 = chromosome1->copy();
    auto chromosomeCpy2 = chromosome1->copy();
    auto differentSizeChromosome = genixx::NumericChromosome<double>::random(10);
    auto differentTypeChromosome = genixx::NumericChromosome<int>::random(10);
    chromosomeCpy2->mutate();
    REQUIRE(*chromosome1 == *chromosomeCpy1);
    REQUIRE(*chromosome1 != *chromosomeCpy2);
    REQUIRE(*chromosome1 != *differentSizeChromosome);

    try
    {
        // This should throw std::bad_cast exception
        *chromosome1 == *differentTypeChromosome;

        // We should not reach here
        REQUIRE(false);
    }
    catch (std::bad_cast& e)
    {
        REQUIRE(true);
    }
}
