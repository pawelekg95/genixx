#include "parameters.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>

namespace parameters {

Parameters load(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
    {
        throw "File does not exist"; // NOLINT
    }
    std::ifstream parametersFile(path);
    rapidjson::Document document;
    rapidjson::IStreamWrapper fileStream(parametersFile);

    document.ParseStream(fileStream);

    if (document.HasParseError())
    {
        throw "Failed to parse document"; // NOLINT
    }

    auto parametersObject = document.GetObject();

    Parameters parameters{};
    parameters.generations = parametersObject["generations"].GetUint();
    parameters.population = parametersObject["population"].GetUint();
    parameters.mutationProbability = parametersObject["mutationProbability"].GetDouble();
    parameters.crossingProbability = parametersObject["crossingProbability"].GetDouble();
    parameters.searchingAreaBegin = parametersObject["searchingAreaBegin"].GetDouble();
    parameters.searchingAreaEnd = parametersObject["searchingAreaEnd"].GetDouble();
    return parameters;
}

} // namespace parameters
