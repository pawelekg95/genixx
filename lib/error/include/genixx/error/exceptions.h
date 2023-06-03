#pragma once

#include <exception>
#include <string>

namespace genixx {

class WrongSizeException : public std::exception
{
public:
    WrongSizeException() = default;

    explicit WrongSizeException(const std::string& comment)
        : m_comment("Container has invalid size. " + comment)
    {}

    const char* what() const noexcept override { return m_comment.c_str(); }

private:
    std::string m_comment{"Container has invalid size"};
};

class NullFunctionException : public std::exception
{
public:
    NullFunctionException() = default;

    explicit NullFunctionException(const std::string& comment)
        : m_comment("No callable object. " + comment)
    {}

    const char* what() const noexcept override { return m_comment.c_str(); }

private:
    std::string m_comment{"No callable object"};
};

} // namespace genixx
