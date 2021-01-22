#ifndef CTextFileParser_H
#define CTextFileParser_H

#include <string>
#include <map>
#include <NStringTool.h>

class CTextFileParser
{
    public:
        
        static bool ParseFile(const std::string& filename, std::map<std::string, std::string>& paramMap);
        
    protected:        
        
        static bool GetParam(const stringvector& param, std::map<std::string, std::string>& paramMap);    
};

#endif
