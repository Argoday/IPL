
#ifndef JSON__Number_H
#define JSON__Number_H

#include "AIO_json.h"
#include "Node.h"
#include <Data/DataTypes.h>
#include <string>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight String class from ACore to remove using std::string across DLL boundries

namespace JSON {

class AIO_JSON_DLL_EXPORT Number : public Node {

	public:

		typedef Number ThisType;

		virtual ThisType * const clone() const {return new ThisType(*this);};

		ThisType(const ThisType &_other):name(_other.name),isFloatingPoint(_other.isFloatingPoint),isSigned(_other.isSigned),iData(_other.iData),sData(_other.sData),fData(_other.fData){}

		ThisType(const std::string &_name,const I1  &_data):name(_name),isFloatingPoint(false),isSigned(true),iData(_data),sData(0),fData(0.0){}
		ThisType(const std::string &_name,const I2  &_data):name(_name),isFloatingPoint(false),isSigned(true),iData(_data),sData(0),fData(0.0){}
		ThisType(const std::string &_name,const I4  &_data):name(_name),isFloatingPoint(false),isSigned(true),iData(_data),sData(0),fData(0.0){}
		ThisType(const std::string &_name,const I8  &_data):name(_name),isFloatingPoint(false),isSigned(true),iData(_data),sData(0),fData(0.0){}

		ThisType(const std::string &_name,const I1u &_data):name(_name),isFloatingPoint(false),isSigned(false),iData(0),sData(_data),fData(0.0){}
		ThisType(const std::string &_name,const I2u &_data):name(_name),isFloatingPoint(false),isSigned(false),iData(0),sData(_data),fData(0.0){}
		ThisType(const std::string &_name,const I4u &_data):name(_name),isFloatingPoint(false),isSigned(false),iData(0),sData(_data),fData(0.0){}
		ThisType(const std::string &_name,const I8u &_data):name(_name),isFloatingPoint(false),isSigned(false),iData(0),sData(_data),fData(0.0){}

		ThisType(const std::string &_name,const F4  &_data):name(_name),isFloatingPoint(true),isSigned(false),iData(0),sData(0),fData(_data){}
		ThisType(const std::string &_name,const F8  &_data):name(_name),isFloatingPoint(true),isSigned(false),iData(0),sData(0),fData(_data){}


		void appendToNoName(std::ostringstream &stream) const {
			appendData(stream);
		}
		
		void appendToNoName(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix;
			appendData(stream);
		}

		void appendTo(std::ostringstream &stream) const {
			stream<<"\""<<name<<"\":";
			appendData(stream);
		}
		
		void appendTo(std::ostringstream &stream,const std::string &prefix) const {
			stream<<prefix<<"\""<<name<<"\":";
			appendData(stream);
		}

	private:

		void appendData(std::ostringstream &stream) const {
			if(isFloatingPoint==true){
				stream.precision(20);
				stream<<fData;
			}else if(isSigned==true){
				stream<<iData;
			}else{
				stream<<sData;
			}
		}

		std::string name;
		
		bool isFloatingPoint; //TODO: Change isFloatingPoint and isSigned to use a string enum { int / int u / float } to remove strange naming
		bool isSigned;
		I8  iData;
		I8u sData;
		F8  fData;
};

}

#endif
