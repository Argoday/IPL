
#ifndef JSON__Boolean_H
#define JSON__Boolean_H

#include "AIO_json.h"
#include "Node.h"
#include <string>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight String class from ACore to remove using std::string across DLL boundries

namespace JSON {

class AIO_JSON_DLL_EXPORT Boolean : public Node {

	public:

		typedef Boolean ThisType;

		virtual ThisType * const clone() const {return new ThisType(*this);};

		ThisType(const Boolean &_other):name(_other.name),data(_other.data){}
		ThisType(const std::string &_name,const bool &_data):name(_name),data(_data){}

		void appendToNoName(std::ostringstream &stream) const {
			if(data==true){stream<<"true";}else{stream<<"false";}
		}

		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
			if(data==true){stream<<prefix<<"true";}else{stream<<prefix<<"false";}
		}

		void appendTo(std::ostringstream &stream) const {
			if(data==true){stream<<"\""<<name<<"\":true";}else{stream<<"\""<<name<<"\":false";}
		}
		
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {
			if(data==true){stream<<prefix<<"\""<<name<<"\":true";}else{stream<<prefix<<"\""<<name<<"\":false";}
		}

	private:
		std::string name;
		bool data;
};

}

#endif
