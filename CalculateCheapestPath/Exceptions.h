/*!
 * \file
 * \brief �������� ����������, ����������� ��� ���������������� ���������
*/

#pragma once
#include <exception>
#include <string>

/*!
* \brief ���������� ��������� ����� ������
*/
class InvalidInputFileException : public std::exception {
public:
	/*!
	* \brief ����������� ����������
	* \param[in] message - ��������� ����������
	*/
	InvalidInputFileException(const std::string& message);

	/*!
	* \brief �������� ��������� ����������
	* \return ��������� ����������
	*/
	const char* what() const noexcept override;
private:
	/*!
	* \brief ��������� ����������
	*/
	std::string m_message;
};

/*!
* \brief ���������� ��������� ��������
*/
class InvalidValueException : public std::exception {
public:
	/*!
	* \brief ����������� ����������
	* \param[in] message - ��������� ����������
	*/
	InvalidValueException(const std::string& message);
	/*!
	* \brief �������� ��������� ����������
	* \return ��������� ����������
	*/
	const char* what() const noexcept override;

private:
	/*!
	* \brief ��������� ����������
	*/
	std::string m_message;
};


