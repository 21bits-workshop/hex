#ifndef MESSAGE_BUFFER_H
#define MESSAGE_BUFFER_H

#include <string>
#include <deque>
#include <vector>

class MessageBuffer {
public:
    void push(const std::string& message);
    std::vector<std::string> popNextSix();
    bool isEmpty() const;

private:
    std::deque<std::string> m_messages;
};

#endif // MESSAGE_BUFFER_H
