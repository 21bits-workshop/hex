#include "MessageBuffer.h"

void MessageBuffer::push(const std::string &message) {
  m_messages.push_back(message);
}

// TODO: Replace with a method to pop the next x messages.
std::vector<std::string> MessageBuffer::popNextSix() {
  std::vector<std::string> messages;
  for (int i = 0; i < 6 && !m_messages.empty(); ++i) {
    messages.push_back(m_messages.front());
    m_messages.pop_front();
  }
  return messages;
}

bool MessageBuffer::isEmpty() const { return m_messages.empty(); }
