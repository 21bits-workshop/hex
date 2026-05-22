/* MessageBuffer.h
 * The MessageBuffer object holds all messages which are queued to be displayed
 * on the MessageDisplay. They will be cleared once displayed.
 */

#ifndef MESSAGE_BUFFER_H
#define MESSAGE_BUFFER_H

#include <deque>
#include <string>
#include <vector>

class MessageBuffer {
public:
  void push(const std::string &message);
  std::vector<std::string> popNextSix();
  bool isEmpty() const;

private:
  std::deque<std::string> m_messages;
};

#endif // MESSAGE_BUFFER_H
