#include <string>
#include <vector>
#include <rapidxml.hpp>

class XmlNode {
    friend class XmlDocument;
public:
    XmlNode getChild(const std::string tag);
    XmlNode addChild(const std::string tag);
    std::vector<XmlNode>* getChildren(const std::string tag);

    std::string getAttribute(const std::string attribute);
    void setAttribute(const std::string attribute, const std::string value);

private:
    XmlNode(rapidxml::xml_node<>* n) { this->node = n; }
    rapidxml::xml_node<>* node;
};

class XmlDocument {
public:
    XmlDocument(std::string filename);
    ~XmlDocument();

    XmlNode getRootNode(std::string tag);

private:
    char* buffer;
    rapidxml::xml_document<>* xml;
};
