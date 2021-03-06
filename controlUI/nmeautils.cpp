#include <string>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <cassert>
#include "nmeautils.h"

NmeaUtils::NmeaUtils()
{
	std::cout << "NmeaUtils CTOR" << std::endl;
}

NmeaUtils::~NmeaUtils()
{
	std::cout << "NmeaUtils DTOR" << std::endl;
}

int NmeaUtils::ConvertHexStrToInt(std::string csval)
{
	if(csval.empty())
		return 0;
	int iRes = 0;
	std::stringstream cs;
	cs << std::hex << csval;
	cs >> iRes;
	return iRes;
}

int NmeaUtils::ConvertStrToInt(std::string csval)
{
	int iRes = 0;
	std::stringstream cs(csval);
	cs >> iRes;
	return iRes;
}

double NmeaUtils::ConvertStrToDouble(std::string csval)
{
	double iRes = 0;
	std::stringstream cs(csval);
	cs >> iRes;
	return iRes;
}

int NmeaUtils::CalculateXoRCheckSum(const char * Sentence, int size)
{
	int iXorCS = 0;
	for (int i = 0; i < size; i++) {
		char c = Sentence[i];
		iXorCS ^= Sentence[i];
	}
		
	return iXorCS;
}

template <ConvertField Conv>
double NmeaUtils::ConvertStrToLatLon(std::string Value, std::string Dir)
{
	double dLatLon, dMin;
	int iDeg;
	int iDir = 0;
	if(Value.length() == 0)
		return 0.0;
	if(Dir.length() == 0)
		return 0.0;

	if(Conv == CONV_LAT)
		iDir = (Dir == "N")? 1: -1;
	if(Conv == CONV_LON)
		iDir = (Dir == "E")? 1: -1;

	dLatLon = ConvertStrToDouble(Value);
    //extract the degree part
    iDeg = (int)(dLatLon / 100.0);
    //mask out the degrees
    dMin = dLatLon - (iDeg * 100.0);
    //compute the actual lonitude in degrees.decimal-degrees
    dLatLon = (iDeg + (dMin / 60.0)) * iDir;

	return dLatLon;
}

double NmeaUtils::ConvertStrToLat(std::string Value, std::string Dir)
{
	return ConvertStrToLatLon<CONV_LAT>(Value, Dir);
}

double NmeaUtils::ConvertStrToLon(std::string Value, std::string Dir)
{
	return ConvertStrToLatLon<CONV_LON>(Value, Dir);
}

double NmeaUtils::ConvertStrToMagnDev(std::string Value, std::string Dir)
{
	int iDir = (Dir == "E")? 1: -1;
	double MagnVar = ConvertStrToDouble(Value)*iDir;
	return MagnVar;
}

double NmeaUtils::ConvertDoubleDistUnits(std::string Value, std::string Units)
{
	if(Value.length() == 0)
		return 0.0;
	double dRawVal = ConvertStrToDouble(Value);
	if(Units == "M")//Metric Units in Meters
		return dRawVal;
	else //Empiric Units in Feets
		return (dRawVal * FeetsInMeter);
}
