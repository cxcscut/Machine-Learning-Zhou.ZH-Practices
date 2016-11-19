#ifndef ML_EXCEPTION_H
#define ML_EXCEPTION_H

#include <stdexcept>
#include <iostream>

class MLexception : public std::logic_error
{

public:
	MLexception(const std::string &message) :
		std::logic_error(message)
	{
	}

	virtual ~MLexception() throw () {}
};
#endif // ML_EXCEPTION_H
