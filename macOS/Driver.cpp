#include <iostream>
#include <fstream>
#include "DiamondSquare.h"
#include "xmlwriter.h"
#include "TileMap.h"
#include "TerrainPass.h"

using namespace std;
using namespace	xmlw;

int N = 5;
int SEED = 16;

int TILE_SIZE = 32;

float WATER_RATIO = .55f;
float TREE_RATIO = .1f;

void CreateMapXML(int width, int height, TileMap * terrainLayer, TileMap* objectLayer);
void CreateGameXML(int playerX, int playerY, TileMap* tilemap, string gameName);

int main()
{

    DiamondSquare diamondSquare;
    float** heightmap = diamondSquare.GenerateHeightMap(N, SEED);
    int size = pow(2, N) + 1;

    // Calculate water level using average altitude of heightmap
    TerrainPass terrainPass;
    float water_level = terrainPass.CalculateWaterLevel(heightmap, size, WATER_RATIO);
    
    // Create tilemap from heightmap values
    TileMap* terrainLayer = new TileMap(heightmap, size, water_level);

    // Clean up lone land/water patches around map
    terrainPass.CleanUpPatches(terrainLayer, LAND_TILE, WATER_TILE);
    terrainPass.CleanUpPatches(terrainLayer, WATER_TILE, LAND_TILE);

    // Change water-bordering land tiles to sand
    terrainPass.AddSand(terrainLayer);
    terrainLayer->Print();

    // Create object layer with trees
    TileMap* objectLayer = new TileMap(size);
    terrainPass.PopulateTrees(terrainLayer, objectLayer, TREE_RATIO);

    // Find a sand tile on the map
    int player_x, player_y;
    if (terrainLayer->FindTileByType(SAND_TILE, player_x, player_y)) {
        player_x *= TILE_SIZE;
        player_y *= TILE_SIZE;
        printf("\n\nPlayer spawn position: %d,%d\n", player_x, player_y);
    }

    // Write map/game data to xml
    CreateMapXML(size, size, terrainLayer, objectLayer);
    CreateGameXML(player_x, player_y, terrainLayer, "The Beach");
}

void CreateMapXML(int width, int height, TileMap * terrainLayer, TileMap* objectLayer)
{
    ofstream f("my_map.xml");
    XmlStream xml(f);

    // <map> root tag (endtag() called by destructor)
    xml << prolog()
        << tag("map")
        << attr("version") << "A4"
        << attr("orientation") << "orthogonal"
        << attr("width") << width << attr("height") << height
        << attr("tilewidth") << TILE_SIZE << attr("tileheight") << TILE_SIZE;
    
    // <properties> tag with map metadata
    xml << tag("properties")
        << tag("property") << attr("name") << "name" << attr("value") << "My Map" 
    << endtag("properties");

    // <tileset> tag with link to spritesheet (graphics.png)
    xml << tag("tileset") << attr("firstgid") << 1 << attr("name") << "graphics" << attr("tilewidth") << TILE_SIZE << attr("tileheight") << TILE_SIZE
        << tag("image") << attr("source") << "graphics.png" << attr("width") << 320 << attr("height") << 1184
    << endtag("tileset");

    // <layer> -> <data> tag holding tile data
    xml << tag("layer") << attr("name") << "Terrain Layer" << attr("width") << width << attr("height") << height;
    xml << tag("data");

    // Populate <data> with tiles
    for (int y = 0; y < height; y++)  {
        for (int x = 0; x < width; x++)   {
            // Insert tile values from tilemap
            xml << tag("tile") << attr("gid") << terrainLayer->GetTileAt(x, y) << endtag();
        }
    }
    xml << endtag("layer");

    // <layer> -> <data> tag holding tile data
    xml << tag("layer") << attr("name") << "Object Layer" << attr("width") << width << attr("height") << height;
    xml << tag("data");

    // Populate <data> with tiles
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Insert tile values from tilemap
            xml << tag("tile") << attr("gid") << objectLayer->GetTileAt(x, y) << endtag();
        }
    }
    xml << endtag("layer");
}

void CreateGameXML(int playerX, int playerY, TileMap* tilemap, string gameName)
{
    ofstream f("my_game.xml");
    XmlStream xml(f);

    // <A4Game> root tag (endtag() called by destructor)
    xml << prolog()
        << tag("A4Game")
        << attr("name") << "example"
        << attr("title") << gameName;

    // <allowSaveGames>
    xml << tag("allowSaveGames") << attr("value") << false << endtag();

    // <story>
    xml << tag("story") << tag("line") << chardata() << "You wake up on a beach..."
    << endtag("story");

    // <ending>
    xml << tag("ending") << attr("id") << 1
        << tag("line") << chardata() << "End of the game"
    << endtag("ending");

    // <tiles>
    xml << tag("tiles") << attr("sourcewidth") << TILE_SIZE << attr("sourceheight") << TILE_SIZE << attr("targetwidth") << TILE_SIZE << attr("targetheight") << TILE_SIZE;

    // <types>
    xml << tag("types") << attr("file") << "graphics.png"
        << chardata() <<
        "\n0,0,1,0,1,0,0,0,0,0,\n""1,1,1,0,0,0,0,0,0,0,\n""4,0,1,1,1,0,0,0,0,0,\n""0,0,0,0,0,0,0,0,0,0,\n"
        "0,1,1,1,2,3,1,1,1,0,\n""0,1,1,1,1,0,0,0,1,0,\n""0,0,0,1,0,0,1,0,1,0,\n""0,0,0,0,0,0,0,0,0,0,\n"
        "0,0,0,0,0,0,1,1,1,1,\n""0,0,0,0,0,1,0,0,0,0,\n""0,0,0,0,0,1,0,0,0,0,\n""0,0,0,0,0,1,0,0,0,0,\n"
        "0,0,0,0,0,1,0,0,0,0,\n""0,0,0,0,0,1,0,0,0,0,\n""0,0,0,0,0,0,0,1,0,0,\n""0,0,0,0,1,0,0,0,0,0,\n"
        "0,0,0,0,0,0,0,0,0,0,\n""0,0,0,0,0,0,0,0,0,0,\n""0,0,0,0,0,0,0,0,0,0,\n""0,0,0,0,0,0,0,0,0,0,\n"
        "0,0,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,1,1,1,1,\n""1,1,0,0,0,0,1,1,1,1,\n""1,1,0,0,0,0,0,0,0,0,\n"
        "1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n"
        "1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n"
        "1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n""1,1,0,0,0,0,0,0,0,0,\n"
        "1,1,0,0,0,0,0,0,0,0,\n" << endtag("types");

    // <seeThrough>
    xml << tag("seeThrough") << attr("file") << "graphics.png"
        << chardata() <<
        "\n0,0,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,1,"
        "\n0,0,0,0,0,0,0,0,0,1," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,1,0,1,0," "\n0,0,0,0,0,0,0,0,0,0,"
        "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,1,0,0,0,0,"
        "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0,"
        "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0," "\n0,0,0,0,0,0,0,0,0,0,"
        "\n0,0,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0,"
        "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0,"
        "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0,"
        "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0," "\n1,1,0,0,0,0,0,0,0,0,"
        "\n1,1,0,0,0,0,0,0,0,0," 
    << endtag("tiles");
    
    // <characteDefinition>
    xml << tag("characterDefinition") << attr("file") << "players.xml" << endtag();

    // <map>
    xml << tag("map") << attr("file") << "my_map.xml" << endtag();

    // <player>
    xml << tag("player") << attr("class") << "Warrior" << attr("x") << playerX << attr("y") << playerY << attr("map") << 0 << endtag();
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