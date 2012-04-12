
#ifndef FSWP__AirportDetails_H
#define FSWP__AirportDetails_H

class AirportDetails {
	public:
	
		const std::string &getCode() const {return code;}
		const std::string &getName() const {return name;}
		const std::string &getDisplayed() const {return displayed;}
	
		void setCode(const std::string &_code){
			code=_code;
			      if(code=="LAX"){name="Los Angeles";displayed="Los+Angeles%2C+CA+-+LAX";
			}else if(code=="EWR"){name="Newark"     ;displayed="Newark%2C+NJ+-+EWR"     ;
			}else if(code=="ISP"){name="Long Island";displayed="Long+Island%2C+NY+-+ISP";
			}else if(code=="PHX"){name="Phoenix"    ;displayed="Phoenix%2C+AZ+-+PHX"    ;
			}
		}

	private:
		std::string code;
		std::string name;
		std::string displayed;
};

#endif
