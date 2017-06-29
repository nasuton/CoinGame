#ifndef JsonHelper_h
#define JsonHelper_h

#include "cocos2d.h"

#include "json/rapidjson.h"
#include "json/document.h"

class JsonHelper
{
public:
	template<unsigned Flag>
	static rapidjson::Document DocumentParse(std::string jsonName);
};

template<unsigned Flag>
rapidjson::Document JsonHelper::DocumentParse(std::string jsonName)
{
	auto fileUtils = cocos2d::FileUtils::getInstance();
	auto path = fileUtils->getStringFromFile(jsonName);

	rapidjson::Document doc;
	doc.Parse<Flag>(path.c_str());

	return doc;
}

#endif