/*
 * Exception.cpp
 *
 *  Created on: 06/02/2012
 *      Author: Eduardo Krempser
 */

#include "Exception.h"

namespace opt{
	namespace base {

		Exception::Exception(const char* msg) {
			this->msg = new char[strlen(msg)+1];
			strcpy(this->msg, msg);
			cout << "\n" << this->msg << "\n";
		}

		Exception::Exception(const Exception& in): exception(in){
			this->msg = new char[strlen(msg)+1];
			strcpy(this->msg, msg);
		}

	    Exception& Exception::operator= (const Exception& in) throw() {
	        Exception* e = new Exception(in);
	        return *e;
	    }

	    const char* Exception::what() const throw() {
	    	return this->msg;
	    }

		Exception::~Exception() throw (){
	        delete[] this->msg;
		}

	} /* namespace base */
}



