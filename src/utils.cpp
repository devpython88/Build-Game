#include "utils.hpp"
#include "json.hpp"
#include <fstream>
#include <string>
#include <variant>

Rectangle blockToRectangle(Block block)
{
    return {static_cast<float>(block.x), static_cast<float>(block.y),
            static_cast<float>(block.width), static_cast<float>(block.height)};
}

void changePositionWithCamera(struct Rectangle *rect, float x, float y, struct Camera2D *camera)
{
    rect->x += x;
    rect->y += y;
    camera->target.x += x;
    camera->target.y += y;
}

bool checkCollisionBlocks(std::vector<Block> *blocks, float x, float y)
{
    for (int i = 0; i < blocks->size(); i++)
    {
        Block b = blocks->at(i);

        if (b.x == x && b.y == y)
        {
            if (b.blockType == 1)
            {
                if (b.f_path == "assets/door.png")
                {
                    return true;
                }
            }
            else {
                return true;
            }
        }
    }
    return false;
}

int save_as_json(std::vector<Block> blocks, Rectangle player, std::string c_texture)
{
    nlohmann::json jsonObj;

    jsonObj["player"] = nlohmann::json();
    jsonObj["player"]["x"] = player.x;
    jsonObj["player"]["y"] = player.y;
    jsonObj["player"]["current"] = c_texture;

    jsonObj["blocks"] = nlohmann::json::array();

    for (Block b : blocks)
    {
        nlohmann::json blockObj;
        blockObj["x"] = b.x;
        blockObj["y"] = b.y;
        blockObj["width"] = b.width;
        blockObj["height"] = b.height;
        blockObj["texture"] = b.f_path;
        blockObj["blockType"] = b.blockType;

        jsonObj["blocks"].push_back(blockObj);
    }

    std::ofstream file("world.json");

    if (file.is_open())
    {
        file << jsonObj.dump(4);
        file.close();
        return 0;
    }

    return 1;
}

void load(std::string path, std::vector<Block> *blocks, Rectangle *player, Texture2D *text, Camera2D *cam)
{
    std::ifstream file(path);

    if (file.is_open())
    {
        nlohmann::json j;

        file >> j;
        std::vector<Block> blcks;
        blcks.clear();
        for (auto b : j["blocks"])
        {
            Block bl;
            bl.x = b["x"];
            bl.y = b["y"];
            bl.width = b["width"];
            bl.height = b["height"];
            bl.texture = LoadTexture(b["texture"].get<std::string>().c_str());
            bl.f_path = b["texture"].get<std::string>().c_str();
            bl.texture.width = bl.width;
            bl.texture.height = bl.height;

            if (b.contains("blockType"))
            {
                bl.blockType = b["blockType"];
            }
            blcks.push_back(bl);
        }

        *blocks = blcks;

        player->x = j["player"]["x"];
        player->y = j["player"]["y"];
        *text = LoadTexture(j["player"]["current"].get<std::string>().c_str());
        text->width = 40;
        text->height = 40;

        cam->target.x = player->x;
        cam->target.y = player->y;
        cam->offset = {800 / 2, 600 / 2};
        cam->rotation = 0;
        cam->zoom = 1;

        file.close();
    }
}
