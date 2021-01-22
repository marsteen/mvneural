
#include <iostream>
#include <fstream>
#include <CTextFileParser.h>


using namespace std;


//---------------------------------------------------------------------------
//
// Klasse:   CTextFileParser
// Methode:  GetParam
//
//---------------------------------------------------------------------------

bool CTextFileParser::GetParam(const stringvector& param, std::map<std::string, std::string>& paramMap)
{
    bool r = false;
    if (param.size() >= 2)
    {        
        for (int i = 1; i < param.size(); i++)
        {
            
            if (param[i].size() > 0)
            {
                paramMap[param[0]] = param[i];
                break;
            }            
        }    
        r = true;
    }
    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:   CTextFileParser
// Methode:  ParseFile
//
//---------------------------------------------------------------------------

bool CTextFileParser::ParseFile(const std::string& filename, std::map<std::string, std::string>& paramMap)
{        
    bool r = false;
    ifstream infile(filename.c_str(), ios::binary);
    if (infile.good())
    {
        std::string line;
        while (NStringTool::ReadLine(infile, line))
        {
            if (line.size() > 0)
            {
                if (line[0] != '#')
                {
                    stringvector sv;            
                    //cout << "line=" << line << endl;
                    NStringTool::Split(line, sv, "\t ", '"');
                    if (GetParam(sv, paramMap))
                    {
                        cout << "KEY=" << sv[0] << " VALUE=" << paramMap[sv[0]] << endl;
                    }
                }
            }
        }
        infile.close();
        r = true;
    }
    
    cout << "ParseFile End r=" << r << endl;
    return r;
}
