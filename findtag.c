#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void printNodesWithAttribute(xmlNodePtr node, const char *nodeName, const char *attributeName, const char *attributeValue) {
    xmlNodePtr currentNode = node;

    while (currentNode != NULL) {
        if (currentNode->type == XML_ELEMENT_NODE &&
            xmlStrcmp(currentNode->name, (const xmlChar *)nodeName) == 0) {
            xmlChar *kValue = xmlGetProp(currentNode, (const xmlChar *)attributeName);
            if (kValue != NULL && xmlStrcmp(kValue, (const xmlChar *)attributeValue) == 0) {
                xmlChar *vValue = xmlGetProp(currentNode, (const xmlChar *)"v");
                if (vValue != NULL) {
                    printf("v attribute value: %s\n", vValue);
                    xmlFree(vValue);
                }
            }
            xmlFree(kValue);
        }

        // Recursively search child nodes
        printNodesWithAttribute(currentNode->children, nodeName, attributeName, attributeValue);
        currentNode = currentNode->next;
    }
}

int main() {
    xmlDocPtr doc;
    xmlNodePtr root;

    // Parse the XML file
    doc = xmlParseFile("map.xml"); // Replace with your XML file path
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse the XML file.\n");
        return 1;
    }

    // Get the root element of the XML
    root = xmlDocGetRootElement(doc);

    // Call the function to print nodes with the specified criteria
    printNodesWithAttribute(root, "tag", "k", "name");

    // Cleanup
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}

