
#ifndef JSON__Object_H
#define JSON__Object_H

#include "AIO_json.h"
#include "Boolean.h"
#include "Node.h"
#include "Null.h"
#include "Number.h"
#include "Object.h"
#include "String.h"
#include <vector>
#include <string>
#include <sstream>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight String class from ACore to remove using std::string across DLL boundries

namespace JSON {

class AIO_JSON_DLL_EXPORT Object : public Node {

	public:

		typedef Object ThisType;

		virtual ThisType * const clone() const {return new ThisType(*this);};

		ThisType(const Object &_other):name(_other.name),data(_other.data){}
		ThisType(const std::string &_name):name(_name){}

		void insert(const Number &_element){data.push_back(StdNode(&_element));}
		void insert(const Null &_element){data.push_back(StdNode(&_element));}
		void insert(const Boolean &_element){data.push_back(StdNode(&_element));}
		void insert(const Object &_element){data.push_back(StdNode(&_element));}
		void insert(const String &_element){data.push_back(StdNode(&_element));}

		void insert(const Node * const _element){data.push_back(StdNode(_element));}
		void insert(const std::string &_name,const std::string &_data){JSON::String  tempNode(_name,_data);  data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const bool        &_data){JSON::Boolean tempNode(_name,_data);  data.push_back(StdNode(&tempNode));}

		void insert(const std::string &_name,const I1  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I1u &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I2  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I2u &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I4  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I4u &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I8  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const I8u &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const F4  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}
		void insert(const std::string &_name,const F8  &_number){JSON::Number tempNode(_name,_number);data.push_back(StdNode(&tempNode));}


		void appendToNoName(std::ostringstream &stream) const {
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
		
		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
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

		void appendTo(std::ostringstream &stream) const {
			stream<<"\""<<name<<"\":{";
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
			stream<<prefix<<"\""<<name<<"\":\n"<<prefix<<"{\n";
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

		std::string name;
		std::vector<StdNode> data;
};

}

#endif
