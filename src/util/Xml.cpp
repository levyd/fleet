#include <fstream>
#include "Xml.h"

XmlNode XmlNode::getChild(const std::string tag) {
    rapidxml::xml_node<>* childNode = this->node->first_node(tag.c_str());
    XmlNode child(childNode);
    return child;
}

std::vector<XmlNode>* XmlNode::getChildren(const std::string tag) {
    std::vector<XmlNode>* children = new std::vector<XmlNode>();

    rapidxml::xml_node<>* childNode = this->node->first_node(tag.c_str());
    while(childNode != NULL) {
        XmlNode child(childNode);
        children->push_back(child);
        childNode = childNode->next_sibling(tag.c_str());
    }
    return children;
}

std::string XmlNode::getAttribute(std::string name) {
    rapidxml::xml_attribute<>* attribute = this->node->first_attribute(name.c_str());
    if(attribute == NULL) {
        return "";
    } else {
        return attribute->value();
    }
}

XmlDocument::XmlDocument(const std::string filename) {
    std::ifstream infile(filename.c_str(), std::ios::in);
    if(!infile) {
        return;
    }

    long begin = infile.tellg();
    infile.seekg(0, std::ios::end);
    long filesize = (long)infile.tellg() - begin;
    this->buffer = new char[filesize + 1];

    infile.seekg(0, std::ios::beg);
    infile.read(this->buffer, filesize);
    infile.close();
    this->buffer[filesize] = 0;

    this->xml = new rapidxml::xml_document<>();
    this->xml->parse<rapidxml::parse_no_data_nodes>(buffer);
}

XmlDocument::~XmlDocument() {
    xml->clear();
    delete this->xml;
    delete this->buffer;
}

XmlNode XmlDocument::getRootNode(std::string tag) {
    XmlNode root = this->xml->first_node(tag.c_str());
    return root;
}
