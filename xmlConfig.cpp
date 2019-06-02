/*
 * @kangkang
 */
#include "xmlConfig.h"  
 
using namespace std; 


xmlConfig::xmlConfig(){  
    m_pdoc = NULL;  
    m_proot = NULL;   
}  
  
xmlConfig::~xmlConfig(){  
    if (m_pdoc)  
    {   
        m_pdoc = NULL;  
        xmlCleanupParser();  
    }  
}  

void xmlConfig::setMap(map<ky, ve> &m){
    this->m = m;
}
map<ky, ve> xmlConfig::getMap(){
    return this->m;
}

void xmlConfig::print() const{
    map<ky, ve>::const_iterator it;
    for(it=m.begin();it!=m.end();++it)
        cout<<"key: "<<it->first <<"\tvalue: "<<it->second<<endl;
}
  


void xmlConfig::save(const string &oufile){  
    m_pdoc = xmlNewDoc(BAD_CAST"1.0");
    m_proot = xmlNewNode(NULL,BAD_CAST"root");

    xmlDocSetRootElement(m_pdoc,m_proot);

    map<ky, ve>::iterator it;
    for(it=m.begin();it!=m.end();++it)
        xmlNewTextChild(m_proot, NULL, BAD_CAST ((it->first).c_str()), BAD_CAST ((it->second).c_str()));

    int nRel = xmlSaveFile(oufile.c_str(),m_pdoc);

    xmlFreeDoc(m_pdoc);

}  

map<ky, ve> xmlConfig::load(const string &infile){
	m.clear();
	m_pdoc = xmlReadFile(infile.c_str(),"UTF-8",XML_PARSE_RECOVER);
	m_proot = xmlDocGetRootElement(m_pdoc); 

    if (xmlStrcmp(m_proot->name, BAD_CAST "root"))
    {
       fprintf(stderr,"document of the wrong type, root node != root");
       xmlFreeDoc(m_pdoc);
       return m;
    }
    
    xmlNodePtr curNode;
    curNode = m_proot->xmlChildrenNode;
    xmlNodePtr propNodePtr = curNode;

    while(curNode != NULL)
    {
        m[(const char*)BAD_CAST(curNode->name)] = (const char*)BAD_CAST(xmlNodeGetContent(curNode));

       if (xmlHasProp(curNode,BAD_CAST "attribute"))
       {
           propNodePtr = curNode;
       }
       curNode = curNode->next;
    }

    xmlAttrPtr attrPtr = propNodePtr->properties;

    xmlFreeDoc(m_pdoc);
    return m;
}



