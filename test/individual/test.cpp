#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"

#include <catch2/catch_all.hpp>

#include <cstring>

TEST_CASE("Comparing individuals")
{
    genixx::Individual::mutationProbability(100.0);
    genixx::Individual individual1(genixx::Chromosomes{{"x", genixx::NumericChromosome<double>::random(11)}});

    REQUIRE(individual1 == individual1.copy());

    // This comparison should fail. 100% mutation probability should make breeding completely vulnerable to mutation.
    REQUIRE(individual1 != individual1.breed());
}

TEST_CASE("Expected exceptions")
{
    genixx::Individual individual1(genixx::Chromosomes{{"x", genixx::NumericChromosome<double>::random(11)}});
    genixx::Individual individual2(genixx::Chromosomes{{"x", genixx::NumericChromosome<double>::random(11)}});
    genixx::Individual individual3(genixx::Chromosomes{{"x", genixx::NumericChromosome<double>::random(11)},
                                                       {"y", genixx::NumericChromosome<double>::random(11)}});
    genixx::Individual individual4(genixx::Chromosomes{{"y", genixx::NumericChromosome<double>::random(11)}});

    try
    {
        // Should succeed.
        individual1.cross(individual2);
        REQUIRE(true);
    }
    catch (std::exception& e)
    {
        REQUIRE(false);
    }

    try
    {
        // Should fail. Different number of chromosomes.
        individual1.cross(individual3);
        REQUIRE(false);
    }
    catch (std::exception& e)
    {
        REQUIRE(std::strcmp(e.what(),
                            genixx::WrongSizeException("Incorrect amount of chromosomes in individuals").what()) == 0);
        REQUIRE(true);
    }

    try
    {
        // Should fail. Different name of chromosomes.
        individual1.cross(individual4);
        REQUIRE(false);
    }
    catch (std::exception& e)
    {
        REQUIRE(std::strcmp(e.what(),
                            genixx::InvalidArgumentException(
                                "Chromosome mismatch. Cannot find chromosome: x in second individual")
                                .what()) == 0);
        REQUIRE(true);
    }
}
