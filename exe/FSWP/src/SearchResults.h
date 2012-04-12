
#ifndef FSWP__SearchResults_H
#define FSWP__SearchResults_H

#include "FlightDetails.h"

class SearchResults {
	public:
	
		void insertFlight(const FlightDetails &_flight){flights.push_back(_flight);}
	
		AirportDetails fromAirport;
		AirportDetails toAirport;
		int month;
		int day;
		int year;
		int passengerCount;
		std::vector<FlightDetails> flights;

		std::string getJSON() const {
			JSON::Document doc;
			doc.insertString("f",fromAirport.getCode());
			doc.insertString("t",toAirport.getCode());
			doc.insertInt("m",month);
			doc.insertInt("d",day);
			doc.insertInt("y",year);
			doc.insertInt("p",passengerCount);
			JSON::Array flightArray("s");
			for(auto flightsIter = flights.begin();flightsIter!=flights.end();++flightsIter){
				flightArray.insert(flightsIter->getJSON());
			}
			doc.insert(flightArray);
			return doc.toString();
		}
};

#endif
