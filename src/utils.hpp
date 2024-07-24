#ifndef UTILS_HPP
#define UTILS_HPP
#include <raylib.h>
#include <vector>
#include <string>

struct Block {
    float x, y, width, height;
    Texture2D texture;
    std::string f_path;
};
 
Rectangle blockToRectangle(struct Block block);
void changePositionWithCamera(struct Rectangle *rect, float x, float y, struct Camera2D *camera);
bool checkCollisionBlocks(std::vector<Block> *blocks, float x, float y);
int save_as_json(std::vector<Block> blocks, Rectangle player, std::string c_texture);
void load(std::string path, std::vector<Block> *blocks, Rectangle *player, Texture2D *text, Camera2D *cam);

#endif