
#include <String/AString.h>
using String::getString;

#include <JSON/JSON.h>
#include <ACURL.h>

#include <curl/curl.h>

#include <qapplication.h>
#include <qtimer.h>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElementCollection>

#include <sstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <vector>

#include "MainObject.h"
#include "SearchResults.h"

int main(int argc, char *argv[]){

	QApplication a(argc, argv);
 
	MainObject g;
	QTimer::singleShot(100, &g, SLOT(startApplication()));
 
	return a.exec();
}

void performSearch(CURL * curl_handle,const std::string &_fromAirport,const std::string &_toAirport, const int &_month,const int &_day,const int &_year);

void realMain(){
	curl_global_init(CURL_GLOBAL_ALL);
	CURL * curl_handle;
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);

	performSearch(curl_handle,"LAX","EWR",9,16,2011);

	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
}
void performSearch(CURL * curl_handle,const std::string &_fromAirport,const std::string &_toAirport, const int &_month,const int &_day,const int &_year){
	
	SearchResults results;

	AirportDetails fromAirportTemp;
	fromAirportTemp.setCode(_fromAirport);
	AirportDetails toAirportTemp;
	toAirportTemp.setCode(_toAirport);
	results.fromAirport = fromAirportTemp;
	results.toAirport = toAirportTemp;
	results.month = _month;
	results.day = _day;
	results.year = _year;
	results.passengerCount = 1;

	std::string pageData="";
	std::string nextURL = "www.example.com";
	bool foundURL=false;

	{

		struct ACURL::MemoryStruct chunk;
		struct ACURL::HeaderStruct headers;

		chunk.memory = (char*)malloc(1);
		chunk.size = 0;

		curl_easy_setopt(curl_handle, CURLOPT_HEADER, 1);

		curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, ACURL::write_data);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, (void *)&headers);
	
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, ACURL::WriteMemoryCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl_handle, CURLOPT_AUTOREFERER, 0);
		curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 0);
		curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

		curl_slist * headerList = nullptr;
		headerList=curl_slist_append(headerList,"Host: www.southwest.com");
		headerList=curl_slist_append(headerList,"Connection: keep-alive");
		headerList=curl_slist_append(headerList,"Cache-Control: max-age=0");
		headerList=curl_slist_append(headerList,"From: argoday@attrino.com");
		headerList=curl_slist_append(headerList,"User-Agent: argodaybot");
		headerList=curl_slist_append(headerList,"Content-Type: application/x-www-form-urlencoded");
		headerList=curl_slist_append(headerList,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
		headerList=curl_slist_append(headerList,"Accept-Encoding: identity");
		headerList=curl_slist_append(headerList,"Accept-Language: en-US,en;q=0.8");
		headerList=curl_slist_append(headerList,"Accept-Charset: UTF-8,*;q=0.5");

		curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headerList);
	
		curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.southwest.com/flight/search-flight.html?int=HOMEQBOMAIR");
		std::string postFields = std::string("ss=0&disc=&submitButton=&previouslySelectedBookingWidgetTab=&originAirportButtonClicked=no&destinationAirportButtonClicked=no&returnAirport=")
								+"&originAirport="+results.fromAirport.getCode()
								+"&originAirport_displayed="+results.fromAirport.getDisplayed()
								+"&destinationAirport="+results.toAirport.getCode()
								+"&destinationAirport_displayed="+results.toAirport.getDisplayed()
								+"&outboundDateString="+getString(results.month)
								+"%2F"+getString(results.day)
								+"%2F"+getString(results.year)
								+std::string("&outboundTimeOfDay=ANYTIME&returnTimeOfDay=ANYTIME")
								+"&adultPassengerCount="+getString(results.passengerCount)
								+"&seniorPassengerCount=0&promoCode=&book_now=";
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postFields.c_str());
		int res = curl_easy_perform(curl_handle);
		if(res!=0){
			std::cout<<res<<std::endl;
		}
		curl_slist_free_all(headerList);
	
		foundURL=false;
		for(auto headersIter = headers.memory.begin();headersIter!=headers.memory.end();++headersIter){
			if((*headersIter).find("Location: ")!=std::string::npos){
				nextURL=(*headersIter).substr(10);
				foundURL=true;
				break;
			}
		}

		std::cout<<nextURL<<std::endl;

		if(chunk.memory){free(chunk.memory);}

	}
	if(foundURL==false){return;}

	//////////////////////////////////////////
	struct ACURL::MemoryStruct chunk;
	struct ACURL::HeaderStruct headers;

	chunk.memory = (char*)malloc(1);
	chunk.size = 0;

	curl_easy_setopt(curl_handle, CURLOPT_HEADER, 1);

	curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, ACURL::write_data);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, (void *)&headers);
	
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, ACURL::WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	curl_easy_setopt(curl_handle, CURLOPT_AUTOREFERER, 0);
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 0);
	curl_easy_setopt(curl_handle, CURLOPT_POST, 0);

	curl_slist * headerList = nullptr;
	headerList=curl_slist_append(headerList,"Host: www.southwest.com");
	headerList=curl_slist_append(headerList,"Connection: keep-alive");
	headerList=curl_slist_append(headerList,"Cache-Control: max-age=0");	
	headerList=curl_slist_append(headerList,"From: argoday@attrino.com");
	headerList=curl_slist_append(headerList,"User-Agent: argodaybot");
	headerList=curl_slist_append(headerList,"Content-Type: application/x-www-form-urlencoded");
	headerList=curl_slist_append(headerList,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	headerList=curl_slist_append(headerList,"Accept-Encoding: identity");
	headerList=curl_slist_append(headerList,"Accept-Language: en-US,en;q=0.8");
	headerList=curl_slist_append(headerList,"Accept-Charset: UTF-8,*;q=0.5");

	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headerList);
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, nextURL.c_str());
	int res = curl_easy_perform(curl_handle);
	if(res!=0){
		std::cout<<res<<std::endl;
	}
	curl_slist_free_all(headerList);
	
	pageData=std::string(chunk.memory);

	if(chunk.memory){free(chunk.memory);}
	//////////////////////////////////////////

	QWebPage page;
	page.mainFrame()->setHtml(QString(pageData.c_str()));

	for(int index=1;;++index){
		std::stringstream stream;stream<<index;
		std::string rowID = "tr#outbound_flightRow_"+getString(index);
		QWebElementCollection elements = page.mainFrame()->findAllElements(rowID.c_str());
		if(elements.count()>0){
			for(auto elementsIter=elements.begin();elementsIter!=elements.end();++elementsIter){
				std::string businessID = "input#Out"+getString(index)+"A";
				std::string selectID = "input#Out"+getString(index)+"B";
				std::string webID = "input#Out"+getString(index)+"C";
				QWebElementCollection businessPlane = (*elementsIter).findAll(businessID.c_str());
				QWebElementCollection selectPlane = (*elementsIter).findAll(selectID.c_str());
				QWebElementCollection webPlane = (*elementsIter).findAll(webID.c_str());
				results.insertFlight(FlightDetails((*(businessPlane.begin())).attribute("title"),2));
				results.insertFlight(FlightDetails((*(selectPlane.begin())).attribute("title"),1));
				results.insertFlight(FlightDetails((*(webPlane.begin())).attribute("title"),0));
			}
		}else{
			break;
		}
	}

	std::cout<<results.getJSON();
}
