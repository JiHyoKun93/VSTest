#include "stdafx.h"
#include "xlang.h"

bool doc_lang_inited = false;
rapidjson::Document doc_lang;
char* curLanguageCode = nullptr;

void setCurrentLanguage(char* lang){
	curLanguageCode = lang;
}
const char* getCurrentLanguage(){
	if(curLanguageCode==nullptr) return Application::getInstance()->getCurrentLanguageCode();
	else return curLanguageCode;
}

std::string getString(const char* key){
	if(!doc_lang_inited){
		doc_lang_inited = true;
		std::string filename = "res/lang/";
		filename = filename + getCurrentLanguage();
		filename = filename + ".lang";
		if(FileUtils::getInstance()->isFileExist(filename)){
			Data jsonRaw = FileUtils::getInstance()->getDataFromFile(filename);
			char* stream = reinterpret_cast<char*>(jsonRaw.getBytes());
			std::string str(stream, jsonRaw.getSize());
			rapidjson::StringStream s = rapidjson::StringStream(str.c_str());
			doc_lang.ParseStream(s);
		}
		else if(FileUtils::getInstance()->isFileExist("res/lang/default.lang")){
			Data jsonRaw = FileUtils::getInstance()->getDataFromFile("res/lang/default.lang");
			char* stream = reinterpret_cast<char*>(jsonRaw.getBytes());
			std::string str(stream, jsonRaw.getSize());
			rapidjson::StringStream s = rapidjson::StringStream(str.c_str());
			doc_lang.ParseStream(s);
		}
		else{
			//doc_lang_inited = false;
			return key;
		}
	}
	if(doc_lang.HasMember(key)){
		return doc_lang[key].GetString();
	}
	else{
		return key;
	}
}