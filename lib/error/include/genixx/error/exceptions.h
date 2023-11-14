#pragma once

#include <exception>
#include <string>

namespace genixx {

class WrongSizeException : public std::exception
{
public:
    WrongSizeException() = default;

    explicit WrongSizeException(const std::string& comment)
        : m_comment(m_defaultComment + " " + comment)
    {
    }

    const char* what() const noexcept override { return m_comment.c_str(); }

private:
    const std::string m_defaultComment{"Container has invalid size."};
    std::string m_comment{m_defaultComment};
};

class NullFunctionException : public std::exception
{
public:
    NullFunctionException() = default;

    explicit NullFunctionException(const std::string& comment)
        : m_comment(m_defaultComment + " " + comment)
    {
    }

    const char* what() const noexcept override { return m_comment.c_str(); }

private:
    const std::string m_defaultComment{"No callable object."};
    std::string m_comment{m_defaultComment};
};

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException() = default;

    explicit InvalidArgumentException(const std::string& comment)
        : m_comment(m_defaultComment + " " + comment)
    {
    }

    const char* what() const noexcept override { return m_comment.c_str(); }

private:
    const std::string m_defaultComment{"Invalid argument."};
    std::string m_comment{m_defaultComment};
};

} // namespace genixx
