
#ifndef JSON__Node_H
#define JSON__Node_H

#include "AIO_json.h"
#include <string>
#include <sstream>

namespace JSON {

class AIO_JSON_DLL_EXPORT Node {

	public:

		typedef Node ThisType;

		virtual ThisType * const clone() const {return new ThisType;};

		std::string toStringNoName() const {std::ostringstream stream;appendToNoName(stream);return stream.str();}
		std::string appendToNoName(const std::string &string) const {return string+toStringNoName();}
		virtual void appendToNoName(std::ostringstream &stream) const {};

		std::string toStringNoName(const std::string &prefix) const {std::ostringstream stream;appendToNoName(stream,prefix);return stream.str();}
		std::string appendToNoName(const std::string &string,const std::string &prefix) const {return string+toStringNoName(prefix);}
		virtual void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {};

		std::string toString() const {std::ostringstream stream;appendTo(stream);return stream.str();}
		std::string appendTo(const std::string &string) const {return string+toString();}
		virtual void appendTo(std::ostringstream &stream) const {};
		
		std::string toString(const std::string &prefix) const {std::ostringstream stream;appendTo(stream);return stream.str();}
		std::string appendTo(const std::string &string,const std::string &prefix) const {return string+toString(prefix);}
		virtual void appendTo(std::ostringstream &stream,const std::string &prefix) const {};
};

class AIO_JSON_DLL_EXPORT StdNode {

	public:

		typedef StdNode ThisType;

		ThisType(const Node &_other)        {data = _other.clone();}
		ThisType(const Node * const &_other){data = _other->clone();}
		ThisType(const ThisType &_other)    {data = _other.data->clone();}

		ThisType(ThisType &&_other){
			data = _other.data;
			_other.data=nullptr;
		}

		~StdNode(){if(data!=nullptr){delete data;}}

		void appendToNoName(std::ostringstream &stream) const {data->appendToNoName(stream);};
		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {data->appendToNoName(stream,prefix);};
		void appendTo(std::ostringstream &stream) const {data->appendTo(stream);};
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {data->appendTo(stream,prefix);};

		Node * data;
};


}

#endif
