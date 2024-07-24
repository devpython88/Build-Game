#include <raylib.h>
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "utils.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QMessageBox>
#include <qt5/QtWidgets/QFileDialog>
#include <qt5/QtCore/QDir>

const float DEFAULT_SIZE = 40.0f;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
const int MOVEMENT = 40;
std::string VERSION = "0.5.0";


std::vector<Block> blocks;
std::vector<std::string> textures = {
    "assets/bricks.png",
    "assets/broken_stone.png",
    "assets/mossy_stone.png"};
int currentTextureIndex = 0;

std::vector<float> GetCenter(int width, int height)
{
    return std::vector<float>({static_cast<float>(SCREEN_WIDTH - width) / 2,
                               static_cast<float>(SCREEN_HEIGHT - height) / 2});
}

void addBlock(float x, float y, Texture2D texture, std::string file_path)
{
    blocks.push_back({x, y, DEFAULT_SIZE, DEFAULT_SIZE, texture, file_path});
}

void DrawBlocks()
{
    for (Block &block : blocks)
    {
        DrawTexture(block.texture, block.x, block.y, WHITE);
    }
}

void updateTexture(Texture2D *texture, Texture2D newTexture)
{
    *texture = newTexture;
    texture->width = DEFAULT_SIZE;
    texture->height = DEFAULT_SIZE;
}

void removeBlock(float x, float y)
{
    for (int i = 0; i < blocks.size(); ++i)
    {
        Block block = blocks.at(i);
        if (block.x == x && block.y == y)
        {
            blocks.erase(blocks.begin() + i);
            return;
        }
    }
}

std::vector<std::string> split(std::string str, char del)
{
    std::istringstream ss(str);
    std::vector<std::string> toks;
    std::string tok;

    while (std::getline(ss, tok, del))
    {
        toks.push_back(tok);
    }

    return toks;
}

/*********************************************************************
*********************************************************************
*********************************************************************
**********************************************************************/

void Game(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, ("Build Game " + VERSION).c_str());
    InitAudioDevice();
    SetTargetFPS(40);

    Texture2D currentTexture;
    updateTexture(&currentTexture, LoadTexture(textures.at(currentTextureIndex).c_str()));
    currentTexture.height = 40;
    currentTexture.width = 40;

    Camera2D cam = {0};
    cam.target = {0, 0};
    cam.offset = {-1, 0};
    cam.rotation = 0;
    cam.zoom = 1;

    Sound walkSound = LoadSound("assets/sounds/walk_1.wav");
    Sound placeSound = LoadSound("assets/sounds/place_1.wav");
    Rectangle player = {GetCenter(40, 40).at(0), GetCenter(40, 40).at(1), 40, 40};
    Font defaultFont = LoadFont("assets/fonts/DejaVuSans.ttf");
    while (!WindowShouldClose())
    {
        // Block removal logic    currentTextureIndex = 0;
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (IsKeyPressed(KEY_W))
            {
                removeBlock(player.x, player.y - MOVEMENT);
            }
            else if (IsKeyPressed(KEY_S))
            {
                removeBlock(player.x, player.y + MOVEMENT);
            }
            else if (IsKeyPressed(KEY_A))
            {
                removeBlock(player.x - MOVEMENT, player.y);
            }
            else if (IsKeyPressed(KEY_D))
            {
                removeBlock(player.x + MOVEMENT, player.y);
            }
        }
        else
        {
            // Player movement logic
            if (IsKeyPressed(KEY_W) && !checkCollisionBlocks(&blocks, player.x, player.y - MOVEMENT))
            {
                changePositionWithCamera(&player, 0, -MOVEMENT, &cam);
                PlaySound(walkSound);
            }
            else if (IsKeyPressed(KEY_S) && !checkCollisionBlocks(&blocks, player.x, player.y + MOVEMENT))
            {
                changePositionWithCamera(&player, 0, MOVEMENT, &cam);
                PlaySound(walkSound);
            }
            else if (IsKeyPressed(KEY_A) && !checkCollisionBlocks(&blocks, player.x - MOVEMENT, player.y))
            {
                changePositionWithCamera(&player, -MOVEMENT, 0, &cam);
                PlaySound(walkSound);
            }
            else if (IsKeyPressed(KEY_D) && !checkCollisionBlocks(&blocks, player.x + MOVEMENT, player.y))
            {
                changePositionWithCamera(&player, MOVEMENT, 0, &cam);
                PlaySound(walkSound);
            }
        }

        if (IsKeyPressed(KEY_TAB))
        {
            if (currentTextureIndex < textures.size() - 1)
            {
                currentTextureIndex++;
                updateTexture(&currentTexture, LoadTexture(textures.at(currentTextureIndex).c_str()));
            }
            else
            {
                currentTextureIndex = 0;
                updateTexture(&currentTexture, LoadTexture(textures.at(currentTextureIndex).c_str()));
            }
        }

        // Block adding logic
        if (IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            addBlock(player.x, player.y, currentTexture, textures.at(currentTextureIndex));
            PlaySound(placeSound);
        }

        BeginDrawing();
        ClearBackground({100, 100, 255, 255});
        BeginMode2D(cam);
        DrawRectangleRec(player, WHITE);
        DrawBlocks();
        EndMode2D();

        // Graphical User Interface
        if (GuiButton((Rectangle){0, static_cast<float>(SCREEN_HEIGHT) - 50, 120, 50}, "Clean"))
        {
            blocks.clear();
        }

        if (GuiButton((Rectangle){0, static_cast<float>(SCREEN_HEIGHT) - 100, 120, 50}, "Save"))
        {
            int res = save_as_json(blocks, player, textures.at(currentTextureIndex));

            if (res == 0)
            {
                QMessageBox::information(NULL, "Info", "Succesfully saved world as world.json");
            }
            else
            {
                QMessageBox::critical(NULL, "Error", "Could not world.\nPossibly due to existing world.json file.");
            }
        }

        if (GuiButton((Rectangle){0, static_cast<float>(SCREEN_HEIGHT) - 150, 120, 50}, "Load..."))
        {
            QFileDialog dialog;

            QString file = dialog.getOpenFileName();

            if (file != NULL)
            {
                load(file.toStdString(), &blocks, &player, &currentTexture, &cam);
            }
        }

        std::string text = "Current Block: " + split(split(textures.at(currentTextureIndex), '/').at(1), '.').at(0);

        GuiSetFont(defaultFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        GuiLabel((Rectangle){0, 0, 270, 20}, text.c_str());

        EndDrawing();
    }

    UnloadTexture(currentTexture);
    UnloadSound(walkSound);
    UnloadSound(placeSound);
    UnloadFont(defaultFont);
    for (Block &block : blocks)
    {
        UnloadTexture(block.texture);
    }

    CloseAudioDevice();
    CloseWindow();
}

/***************************************************/

int TitleScreen(int argc, char *argv[])
{
    QApplication app(argc, argv);

    InitWindow(800, 600, ("Build Game: " + VERSION).c_str());
    SetTargetFPS(45);

    int code = -1;

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Build Game", 350, 20, 22, BLACK);
        if (GuiButton((Rectangle){350, 60, 100, 45}, "Play"))
        {
            code = 1;
            break;
        }
        EndDrawing();
    }

    if (code == 1)
    {
        CloseWindow();
        return 1;
    }
    else
    {
        CloseWindow();
        return 0;
    }
}

/***************************************************/

int main(int argc, char *argv[])
{
    int res = TitleScreen(argc, argv);

    if (res == 1)
    {
        Game(argc, argv);
        return 0;
    }
    else
    {
        return 0;
    }
}
