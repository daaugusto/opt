/*
 * Exception.h
 *
 *  Created on: 06/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>
#include "string.h"
#include <iostream>
using namespace std;

namespace opt {
	namespace base {

		class Exception : public exception {
			private:
				char* msg;
			public:
				Exception(const char* msg);
				Exception(const Exception &in);
				virtual ~Exception() throw ();
		        Exception& operator= (const Exception& in) throw();
		        virtual const char* what() const throw();
		};

	} /* namespace base */
}
#endif /* EXCEPTION_H_ */
