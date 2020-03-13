#include <iostream>
#include <fstream>
#include "DiamondSquare.h"
#include "xmlwriter.h"
#include "TileMap.h"
#include "TerrainPass.h"

using namespace std;
using namespace	xmlw;

int N = 4;
int SEED = 0;

float WATER_LEVEL = .25f;

void CreateMapXML(int width, int height, int tilewidth, int tileheight, TileMap* tilemap);

int main()
{

    DiamondSquare diamondSquare;
    float** heightmap = diamondSquare.GenerateHeightMap(N, SEED);
    int size = pow(2, N) + 1;
    
    // Create tilemap from heightmap values
    TileMap* tileMap = new TileMap(heightmap, size, WATER_LEVEL);

    // Clean up lone land/water patches around map
    TerrainPass terrainPass;
    printf("\n\nREMOVING LAND PATCHES\n\n");
    terrainPass.CleanUpPatches(tileMap, LAND_TILE, WATER_TILE);
    printf("\n\nREMOVING WATER PATCHES\n\n");
    terrainPass.CleanUpPatches(tileMap, WATER_TILE, LAND_TILE);

    // Change water-bordering land tiles to sand
    terrainPass.AddSand(tileMap);
    tileMap->Print();

    CreateMapXML(size, size, 32, 32, tileMap);
}

void CreateMapXML(int width, int height, int tilewidth, int tileheight, TileMap* tilemap)
{
    ofstream f("my_map.xml");
    XmlStream xml(f);

    // <map> root tag (endtag() called by destructor)
    xml << prolog()
        << tag("map")
        << attr("version") << "A4"
        << attr("orientation") << "orthogonal"
        << attr("width") << width << attr("height") << height
        << attr("tilewidth") << tilewidth << attr("tileheight") << tileheight;
    
    // <properties> tag with map metadata
    xml << tag("properties")
        << tag("property") << attr("name") << "name" << attr("value") << "My Map" 
    << endtag("properties");

    // <tileset> tag with link to spritesheet (graphics.png)
    xml << tag("tileset") << attr("firstgid") << 1 << attr("name") << "graphics" << attr("tilewidth") << tilewidth << attr("tileheight") << tileheight
        << tag("image") << attr("source") << "data/graphics.png" << attr("width") << 320 << attr("height") << 1184
    << endtag("tileset");

    // <layer> -> <data> tag holding tile data
    xml << tag("layer") << attr("name") << "Terrain Layer" << attr("width") << width << attr("height") << height;
    xml << tag("data");

    // Populate <data> with tiles
    for (int y = 0; y < height; y++)  {
        for (int x = 0; x < width; x++)   {
            // Insert tile values from tilemap
            xml << tag("tile") << attr("gid") << tilemap->GetTileAt(x, y) << endtag();
        }
    }
    xml << endtag("layer");
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