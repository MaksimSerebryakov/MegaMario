#pragma once

#define ACTION_TYPE_START "START"
#define ACTION_TYPE_END "END"

class Action
{
    std::string m_name;
    std::string m_type;

public:
    Action() {}
    Action(const std::string &otherName, const std::string &otherType)
        : m_name{otherName},
          m_type{otherType} {}

    std::string &name() { return m_name; }
    std::string &type() { return m_type; }
    const std::string &name() const { return m_name; }
    const std::string &type() const { return m_type; }
};