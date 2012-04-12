
#ifndef JSON__Document_H
#define JSON__Document_H

#include "AIO_json.h"
#include "Array.h"
#include "Boolean.h"
#include "Node.h"
#include "Null.h"
#include "Number.h"
#include "Object.h"
#include "String.h"

#include <vector>

namespace JSON {

class AIO_JSON_DLL_EXPORT Document {

	public:

		typedef Document ThisType;

		void insert(const Array &_element){data.push_back(StdNode(&_element));}
		void insert(const Number &_element){data.push_back(StdNode(&_element));}
		void insert(const Null &_element){data.push_back(StdNode(&_element));}
		void insert(const Boolean &_element){data.push_back(StdNode(&_element));}
		void insert(const Object &_element){data.push_back(StdNode(&_element));}
		void insert(const String &_element){data.push_back(StdNode(&_element));}

		void insert(const Node * const _element){data.push_back(StdNode(_element));}
		void insertString(const std::string &_name,const std::string &_data){
			JSON::String tempNode(_name,_data);
			data.push_back(StdNode(&tempNode));
		}
		void insertBoolean(const std::string &_name,const bool &_data){
			JSON::Boolean tempNode(_name,_data);
			data.push_back(StdNode(&tempNode));
		}
		void insertInt(const std::string &_name,const int &_number){
			JSON::Number tempNode(_name,_number);
			data.push_back(StdNode(&tempNode));
		}

		std::string toString() const {std::ostringstream stream;appendTo(stream);return stream.str();}
		std::string toStringPretty() const {std::ostringstream stream;appendTo(stream,"");return stream.str();}

	private:

		void appendToNoName(std::ostringstream &stream) const {
			appendTo(stream);
		}
		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
			appendTo(stream,prefix);
		}

		void appendTo(std::ostringstream &stream) const {
			stream<<"{";
			if(data.size()>0){
				auto dataIter = data.begin();
				dataIter->appendTo(stream);
				++dataIter;
				if(dataIter!=data.end()){
					for(;dataIter!=data.end();++dataIter){
						stream<<",";
						dataIter->appendTo(stream);
					}
				}
			}
			stream<<"}";
		}
		
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {
			std::string nextPrefix = "\t"+prefix;
			stream<<prefix<<"{\n";
			
			if(data.size()>0){
				auto dataIter = data.begin();
				dataIter->appendTo(stream,nextPrefix);
				++dataIter;
				if(dataIter!=data.end()){
					for(;dataIter!=data.end();++dataIter){
						stream<<",\n";
						dataIter->appendTo(stream,nextPrefix);
					}
				}
				stream<<"\n";
			}
			stream<<prefix<<"}";
		}

		std::vector<StdNode> data;
};

}

#endif
