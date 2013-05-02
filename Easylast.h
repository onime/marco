#ifndef EASYLAST
#define EASYLAST

#define PATH_SCANS "/media/Data/Scans/"

#include <boost/tokenizer.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <dirent.h>
#include <QProcess>

using namespace std;

class Easylast 
{
private:
    Easylast();

public:
    
static vector<string> split(const string & msg,const string str_sep);
static map<string,string> parse_info(const string & type);
static string find_summary(const string name,const int & chap);

static vector<dirent *> list_dir( const string & path);
static vector<string> list_pages_scan(const string & path);

static string itos(const int & i);
static int stoi(const string & i);
static QString stoqs(const string & s);
static QString itoqs(const int & i);
    
};

#endif
