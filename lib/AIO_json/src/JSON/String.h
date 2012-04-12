
#ifndef JSON__String_H
#define JSON__String_H

#include "AIO_json.h"
#include "Node.h"
#include <string>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight String class from ACore to remove using std::string across DLL boundries

namespace JSON {

class AIO_JSON_DLL_EXPORT String : public Node {

	public:

		typedef String ThisType;

		virtual ThisType * const clone() const {return new ThisType(*this);};

		ThisType(const String &_other):name(_other.name),data(_other.data){}
		ThisType(const std::string &_name,const std::string &_data):name(_name),data(_data){}

		void appendToNoName(std::ostringstream &stream) const {
			stream<<"\""<<data<<"\"";
		}
		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix<<"\""<<data<<"\"";
		}
		void appendTo(std::ostringstream &stream) const {
			stream<<"\""<<name<<"\":\""<<data<<"\"";
		}
		
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix<<"\""<<name<<"\":\""<<data<<"\"";
		}

		std::string name;
		std::string data;
};

}

#endif
