#ifndef UTILS_HPP
#define UTILS_HPP
#include <raylib.h>
#include <vector>
#include <string>

class Block {
    public:
    float x, y, width, height;
    Texture2D texture;
    std::string f_path;
    int blockType;

    Block(float x, float y, float width, float height, Texture2D texture, std::string f_path, int blockT = 0): x(x), y(y), width(width), height(height), texture(texture), f_path(f_path), blockType(blockT){
        this->blockType = blockT;
    }
    Block(){}
};

Rectangle blockToRectangle(Block block);
void changePositionWithCamera(struct Rectangle *rect, float x, float y, struct Camera2D *camera);
bool checkCollisionBlocks(std::vector<Block> *blocks, float x, float y);
int save_as_json(std::vector<Block> blocks, Rectangle player, std::string c_texture);
void load(std::string path, std::vector<Block> *blocks, Rectangle *player, int* ind, std::vector<std::string> textrs, Texture2D *text, Camera2D *cam);

#endif