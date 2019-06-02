/*
 * @kangkang,∂¡–¥xml≈‰÷√ 
 */
#ifndef _XML_CONFIG_H_  
#define _XML_CONFIG_H_  
  
#include <iostream> 
#include <string> 
#include <map>
#include <cstdlib>  

#include <libxml/parser.h>  
#include <libxml/tree.h>  

typedef std::string ky;
typedef std::string ve;
  
class xmlConfig  
{  
public:  

    xmlConfig();  
    ~xmlConfig(); 
    void print() const;
    void setMap(std::map<ky, ve> &);
    std::map<ky, ve> getMap();
 
public:   
     
    void save(const std::string &);  
    std::map<ky, ve> load(const std::string &); 
  
private:  

    xmlDocPtr m_pdoc;  
    xmlNodePtr m_proot;  
    std::map<ky, ve> m; 
};  
  
  
#endif   
