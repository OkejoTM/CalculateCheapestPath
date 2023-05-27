#include <exception>
#include <string>
#include "Exceptions.h"

using namespace std;


InvalidInputFileException::InvalidInputFileException(const std::string& message) : m_message(message) {}

const char* InvalidInputFileException::what() const noexcept {
	return m_message.c_str();
}

InvalidValueException::InvalidValueException(const std::string& message) : m_message(message) {}

const char* InvalidValueException::what() const noexcept {
	return m_message.c_str();
} 