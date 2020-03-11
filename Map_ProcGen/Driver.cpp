#include <iostream>
#include "DiamondSquare.h"
#include <fstream>
#include "xmlwriter.h"

using namespace std;
using namespace	xmlw;

int SIZE = 2;

void CreateMapXML();

int main()
{
    /*DiamondSquare diamondSquare;
    float** heightmap = diamondSquare.GenerateHeightMap(SIZE);

    int n = pow(2, SIZE);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%f ", heightmap[i][j]);
        }
        printf("\n");
    }*/

    CreateMapXML();
}

void CreateMapXML()
{
    ofstream f("my_map.xml");
    XmlStream xml(f);

    // Create root tag <map>
    xml << prolog()
        << tag("map")
        << attr("version") << "A4"
        << attr("orientation") << "orthogonal"
        << attr("width") << 16 << attr("height") << 16
        << attr("tilewidth") << 32 << attr("tileheight") << 32;
    
    // <properties> tag with map metadata
    xml << tag("properties")
        << tag("property") << attr("name") << "name" << attr("value") << "My Map" << endtag("properties");

    // <tileset> tag with link to spritesheet (graphics.png)
    xml << tag("tileset") << attr("firstgid") << 1 << attr("name") << "graphics" << attr("tilewidth") << 32 << attr("tileheight") << 32
        << tag("image") << attr("source") << "graphics.png" << attr("width") << 320 << attr("height") << 1184 << endtag()
    << endtag();
}

void SampleXML()
{
    ofstream f("sample1.xml");
    XmlStream xml(f);

    xml << prolog() // write XML file declaration
        << tag("sample-tag") // root tag

        // child tag
        << tag("some-tag") << attr("int-attribute") << 123 << attr("double-attribute") << 456.789
        << chardata() << "This is the text"
        << endtag() // close current tag

        << tag("empty-self-closed-tag") << endtag() // sibling of <some-tag>

        << tag() << "computed-name-tag" << attr("text-attr") << "a bit of text" << endtag()

        << tag("deep-tag") // deep enclosing
        << tag("sub-tag-2")
        << tag("sub-tag-3")
        << endtag("deep-tag"); // close all tags up to specified

    // look: I didn't close "sample-tag", it will be closed in XmlStream destructor
}