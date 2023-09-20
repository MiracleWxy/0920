#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <math.h>

// Structure to store latitude, longitude, and point name
typedef struct {
    double latitude;
    double longitude;
    char name[100];
} Point;

// Function to calculate the Haversine distance between two coordinates
double haversineDistance(Point coord1, Point coord2) {
    // ... (same haversineDistance function as in the previous example)
}

int main() {
    xmlDocPtr doc;
    xmlNodePtr cur;
    
    // Parse the XML file
    doc = xmlParseFile("map.xml");
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse the XML file.\n");
        return 1;
    }

    // Find and process 'point' nodes in the XML
    cur = xmlDocGetRootElement(doc);
    cur = cur->children;
    Point points[100]; // Assuming a maximum of 100 points
    int pointCount = 0;
    
    while (cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar *)"point") == 0) {
            // Extract latitude, longitude, and point name information from the 'point' node
            xmlNodePtr node = cur->children;
            
            while (node != NULL) {
                if (xmlStrcmp(node->name, (const xmlChar *)"latitude") == 0) {
                    points[pointCount].latitude = atof(xmlNodeGetContent(node));
                } else if (xmlStrcmp(node->name, (const xmlChar *)"longitude") == 0) {
                    points[pointCount].longitude = atof(xmlNodeGetContent(node));
                } else if (xmlStrcmp(node->name, (const xmlChar *)"name") == 0) {
                    strncpy(points[pointCount].name, xmlNodeGetContent(node), sizeof(points[pointCount].name));
                }
                node = node->next;
            }
            
            pointCount++;
        }
        
        cur = cur->next;
    }

    // Display options to the user
    int choice;
    printf("Options:\n");
    printf("1. List all point names\n");
    printf("2. Calculate distance between two points\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // List all point names
        printf("Point names:\n");
        for (int i = 0; i < pointCount; i++) {
            printf("%d. %s\n", i + 1, points[i].name);
        }
    } else if (choice == 2) {
        // Calculate distance between two points
        int point1, point2;
        printf("Enter the index of the first point: ");
        scanf("%d", &point1);
        printf("Enter the index of the second point: ");
        scanf("%d", &point2);

        if (point1 >= 1 && point1 <= pointCount && point2 >= 1 && point2 <= pointCount) {
            double distance = haversineDistance(points[point1 - 1], points[point2 - 1]);
            printf("Distance between %s and %s: %.2f km\n", points[point1 - 1].name, points[point2 - 1].name, distance);
        } else {
            printf("Invalid point indices.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
    
    // Cleanup
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return 0;
}

