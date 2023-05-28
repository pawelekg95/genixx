#pragma once

#include <exception>

namespace genixx {

class WrongSizeException : public std::exception
{
public:
    const char* what() const noexcept override { return "Container has invalid size"; }
};

class NullFunctionException : public std::exception
{
public:
    const char* what() const noexcept override { return "No callable object"; }
};

} // namespace genixx
