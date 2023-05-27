/*!
 * \file
 * \brief Основные исключения, необходимые для функционирования программы
*/

#pragma once
#include <exception>
#include <string>

/*!
* \brief Исключение неверного ввода данных
*/ 
class InvalidInputFileException : public std::exception {
public:
	/*!
	* \brief Конструктор исключения
	* \param[in] message - сообщение исключения
	*/
	InvalidInputFileException(const std::string& message);

	/*!
	* \brief Получить сообщение исключения
	* \return сообщение исключения
	*/
	const char* what() const noexcept override;
private:
	/*!
	* \brief сообщение исключения
	*/
	std::string m_message;
};

/*!
* \brief Исключение неверного значения
*/
class InvalidValueException : public std::exception {
public:
	/*!
	* \brief Конструктор исключения
	* \param[in] message - сообщение исключения
	*/
	InvalidValueException(const std::string& message);
	/*!
	* \brief Получить сообщение исключения
	* \return сообщение исключения
	*/
	const char* what() const noexcept override;

private:
	/*!
	* \brief сообщение исключения
	*/
	std::string m_message;
};


