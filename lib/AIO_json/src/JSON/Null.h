
#ifndef JSON__Null_H
#define JSON__Null_H

#include "AIO_json.h"
#include "Node.h"
#include <string>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight String class from ACore to remove using std::string across DLL boundries

namespace JSON {

class AIO_JSON_DLL_EXPORT Null : public Node {

	public:

		typedef Null ThisType;

		virtual ThisType * const clone() const {return new ThisType(*this);};

		ThisType(const Null &_other):name(_other.name){}
		ThisType(const std::string &_name):name(_name){}

		void appendToNoName(std::ostringstream &stream) const {
			stream<<"null";
		}

		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix<<"null";
		}

		void appendTo(std::ostringstream &stream) const {
			stream<<"\""<<name<<"\":null";
		}
		
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix<<"\""<<name<<"\":null";
		}

		std::string name;
};

}

#endif
