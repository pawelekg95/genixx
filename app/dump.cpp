#include "dump.h"

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>

void dump([[maybe_unused]] const Data& data)
{
    rapidjson::Document doc{};
    doc.SetObject();
    auto& allocator = doc.GetAllocator();

    {
        rapidjson::Value generationsArray(rapidjson::kArrayType);

        for (const auto& generation : data.generations)
        {
            generationsArray.PushBack(generation, allocator);
        }

        doc.AddMember("generations", generationsArray, allocator);
    }

    {
        rapidjson::Value averageCorrectnessArray(rapidjson::kArrayType);

        for (const auto& correctness : data.averageCorrectness)
        {
            averageCorrectnessArray.PushBack(correctness, allocator);
        }

        doc.AddMember("averageCorrectness", averageCorrectnessArray, allocator);
    }

    {
        rapidjson::Value maxCorrectnessArray(rapidjson::kArrayType);

        for (const auto& correctness : data.maxCorrectness)
        {
            maxCorrectnessArray.PushBack(correctness, allocator);
        }

        doc.AddMember("maxCorrectness", maxCorrectnessArray, allocator);
    }

    std::ofstream ofs{"./data.json"};
    rapidjson::OStreamWrapper osw{ofs};
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writerOut{osw};

    if (!doc.Accept(writerOut))
    {
        throw "Failed to dump"; // NOLINT
    }

    ofs.flush();
    ofs.close();
}
