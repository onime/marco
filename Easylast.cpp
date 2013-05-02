#include "Easylast.h"

Easylast::Easylast(){}

vector<string> Easylast::split(const string & msg,const string str_sep)
{
    vector<string> res;
    typedef boost::tokenizer<boost::char_separator<char> > my_tok;
    boost::char_separator<char> sep( str_sep.c_str() );
   
    my_tok tok( msg, sep );
 
    for ( my_tok::const_iterator i = tok.begin();i != tok.end(); ++i )
	res.push_back(*i);
    
    return res;
}

map<string,string> Easylast::parse_info(const string & type)
{
    QProcess p;
    QString o;
    string sep = "----------";
    string output;
    string cmd = "client_last --"+type+" -p"; 

    p.start( stoqs(cmd));
    p.waitForFinished(-1);
    
    o = p.readAllStandardOutput();
    output = o.toStdString();

    vector<string> line_infos_scan = split(output,"\n");
    vector<string> temp;
    map<string,string> hash_info_scan;

    for(vector<string>::iterator i = line_infos_scan.begin();  i != line_infos_scan.end(); ++i)
    {
	if( *i != sep && *i != type)
	{
	    temp = split(*i,"===>");
	    temp[0].erase(temp[0].end()-1,temp[0].end());
	    temp[1].erase(0,1);
	    hash_info_scan[temp[0]] = temp[1];
	}
    }
 
    return hash_info_scan;
}

string Easylast::find_summary(const string name,const int & chap)
{
    QProcess p;
    string cmd = "client_last --fs -t "+name+" -n "+itos(chap);
    
    p.start(stoqs(cmd));
    p.waitForFinished(-1);

    QString o = p.readAllStandardOutput();
    string output = o.toStdString();
    vector<string> lines = split(output,"\n");
    vector<string> temp;
    string ret;

    for(vector<string>::iterator i = lines.begin();  i != lines.end(); ++i)
    {
	temp = split(*i,"=");
	if(temp[0] == "summary")
	    ret = temp[1];
    }
    
    cout << ret;
    return ret;

}
vector<string> Easylast::list_pages_scan(const string & path)
{
    vector<dirent *> list_file;
    vector<string> list_name_img;
    
    list_file = list_dir(path);

    for(vector<dirent *>::iterator i=list_file.begin();i!=list_file.end();++i)
	list_name_img.push_back((*i)->d_name);

    return list_name_img;
}


vector<dirent *> Easylast::list_dir( const string &  path)
{
    vector<dirent *> list_dir_scan;
    DIR* d = opendir(path.c_str());
    struct dirent *ent = NULL;

    while ((ent = readdir(d)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && 
            strcmp(ent->d_name, "..") != 0) 
	    list_dir_scan.push_back(ent);
    }

    return list_dir_scan;
}

bool Easylast::is_dir(string path)
{
    DIR* d = opendir(path.c_str());
    return !(d == NULL);
}

string Easylast::itos(const int & i)
{
    ostringstream oss;
    oss << i;     
    return  oss.str();
}

QString Easylast::stoqs(const string & s)
{
    return QString(s.c_str());
}

QString Easylast::itoqs(const int & i)
{
    return stoqs(itos(i));
}

int Easylast::stoi(const string & i)
{
    return atoi(i.c_str());
}
