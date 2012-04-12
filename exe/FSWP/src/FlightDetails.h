
#ifndef FSWP__FlightDetails_H
#define FSWP__FlightDetails_H

#include "AirportDetails.h"

class FlightDetails {
	public:
		int flightType;//0-Wanna Get Away , 1-Select , 2-Business
		int price;
		int mainFlightNumber;
		std::string departTime;
		std::string arriveTime;
		int numberOfStops;
		bool changePlanes;
		int changePlaneFlightNumber;
		AirportDetails changePlanesAirport;

		FlightDetails()
			:flightType(0)
			,price(0)
			,mainFlightNumber(0)
			,departTime("")
			,arriveTime("")
			,numberOfStops(0)
			,changePlanes(false)
			,changePlaneFlightNumber(0)
		{
		}

		FlightDetails(const QString &details,const int &_flightType){
			flightType=_flightType;
			QStringList results = details.split(" ");
			if(results.count()==9){//Nonstop
				price = results[3].remove(0,1).toInt();
				mainFlightNumber = results[2].toInt();
				departTime = results[4].toStdString();
				arriveTime = results[6].toStdString();
				numberOfStops=0;
				changePlanes=false;
				changePlaneFlightNumber=0;
			}else if(results.count()==13){//No Plane Change
				price = results[3].remove(0,1).toInt();
				mainFlightNumber = results[2].toInt();
				departTime = results[4].toStdString();
				arriveTime = results[6].toStdString();
				numberOfStops=results[8].toInt();
				changePlanes=false;
				changePlaneFlightNumber=0;
			}else if(results.count()==14){//Plane Change
				price = results[3].remove(0,1).toInt();
				QStringList flightNumbers = results[2].split("/");
				mainFlightNumber = flightNumbers[0].toInt();
				departTime = results[4].toStdString();
				arriveTime = results[6].toStdString();
				numberOfStops=results[8].toInt();
				changePlanes=true;
				changePlaneFlightNumber=flightNumbers[1].toInt();;
				AirportDetails _changePlanesAirport;
				_changePlanesAirport.setCode(results[13].toStdString());
				changePlanesAirport = _changePlanesAirport;
			}
		}

		JSON::Object getJSON() const {
			JSON::Object flight("flight");
			flight.insert("t",flightType);
			flight.insert("p",price);
			flight.insert("n",mainFlightNumber);
			flight.insert("d",departTime);
			flight.insert("a",arriveTime);
			flight.insert("s",numberOfStops);
			flight.insert("c",changePlanes);
			flight.insert("cN",changePlaneFlightNumber);
			flight.insert("cA",changePlanesAirport.getCode());
			return flight;
		}
};


#endif
