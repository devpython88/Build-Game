#include <raylib.h>
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QMessageBox>
#include <qt5/QtWidgets/QFileDialog>
#include <qt5/QtCore/QDir>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QInputDialog>
#include <qt5/QtWidgets/QListWidget>
#include <qt5/QtWidgets/QVBoxLayout>
#include <filesystem>

namespace fs = std::filesystem;

const int BTYPE_DOOR = 1;

const float DEFAULT_SIZE = 40.0f;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
const int MOVEMENT = 40;
std::string VERSION = "Beta 0.4.2";

std::vector<Block> blocks;
std::vector<std::string> textures = {};
int currentTextureIndex = 0;

void toggle(Block &b, int defsize)
{
    if (b.f_path == "assets/door.png")
    {
        b.f_path = "assets/door_opened.png";
        b.texture = LoadTexture(b.f_path.c_str());
        b.texture.height = DEFAULT_SIZE;
        b.texture.width = DEFAULT_SIZE;
    }
    else
    {
        b.f_path = "assets/door.png";
        b.texture = LoadTexture(b.f_path.c_str());
        b.texture.height = DEFAULT_SIZE;
        b.texture.width = DEFAULT_SIZE;
    }
}

void loadWorld(Texture2D &currentTexture, Camera2D &cam, Rectangle &player);

std::vector<float> GetCenter(int width, int height)
{
    return std::vector<float>({static_cast<float>(SCREEN_WIDTH - width) / 2,
                               static_cast<float>(SCREEN_HEIGHT - height) / 2});
}

void addBlock(float x, float y, Texture2D texture, std::string file_path)
{
    int t = 0;
    if (textures[currentTextureIndex] == "assets/door.png")
    {
        t = BTYPE_DOOR;
    }
    Block block(x, y, DEFAULT_SIZE, DEFAULT_SIZE, texture, file_path, t);
    blocks.push_back(block);
}

void DrawBlocks()
{
    for (const auto &block : blocks)
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

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/

std::string formatBlock(void)
{
    std::string text = "Current Block: " + split(split(textures.at(currentTextureIndex), '/').at(1), '.').at(0);
    return text;
}

void loadWorld(Texture2D &currentTexture, Camera2D &cam, Rectangle &player)
{
    QFileDialog dialog;

    QString file = dialog.getOpenFileName();

    if (file != NULL)
    {
        load(file.toStdString(), &blocks, &player, &currentTextureIndex, textures, &currentTexture, &cam);
    }
}

void changeBlock(QListWidgetItem *item, Texture2D *ctext)
{
    std::string texture = "assets/" + item->text().toStdString() + ".png";
    *ctext = LoadTexture(texture.c_str());
    ctext->width = 40;
    ctext->height = 40;

    for (int i = 0; i < texture.size(); ++i)
    {
        if (textures[i] == texture)
        {
            currentTextureIndex = i;
            break;
        }
    }
}

void openBlockSelectionMenu(Texture2D *currentTexture)
{
    QDialog dialog(nullptr);
    dialog.setWindowTitle("Select block");
    dialog.resize(300, 200);

    QVBoxLayout boxLayout;

    QLabel header("Select a block (by double clicking it)");

    QListWidget blockList;
    blockList.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    for (std::string blockName : textures)
    {
        QString item(blockName.c_str());
        item = item.replace(".png", "");
        item = item.replace("assets/", "");

        blockList.addItem(item);
    }

    QObject::connect(&blockList, &QListWidget::itemDoubleClicked, [&dialog, &currentTexture](QListWidgetItem *i)
                     {
        changeBlock(i, currentTexture);
        dialog.close(); });

    boxLayout.addWidget(&header);
    boxLayout.addWidget(&blockList);

    dialog.setLayout(&boxLayout);
    dialog.exec();
}

void showCMDDialog(Rectangle *player, Camera2D *cam){
    QInputDialog dialog;
    QString command = dialog.getText(nullptr, "Command input", "Enter a command");

    if (command.startsWith("mv ")){
        QStringList args = command.split(' ');

        if (args.size() == 1){
            QMessageBox::critical(nullptr, "error", "X and Y not provided.");
            return;
        }
        else if (args.size() == 2){
            QMessageBox::critical(nullptr, "error", "Y not provided.");
            return;
        }
        
        QString xSTR = args.at(1);

        QString ySTR = args.at(2);

        bool isXStrInt;
        bool isYStrInt;

        xSTR.toInt(&isXStrInt);
        ySTR.toInt(&isYStrInt);

        if (!isXStrInt){
            QMessageBox::critical(nullptr, "error", "X is not a valid number");
            return;
        }

        else if (!isYStrInt){
            QMessageBox::critical(nullptr, "error", "Y is not a valid number");
            return;
        }

        player->x = xSTR.toInt();
        player->y = ySTR.toInt();
        cam->target.x = player->x;
        cam->target.y = player->y;
        cam->offset = {800 / 2, 600 / 2};
        cam->rotation = 0;
        cam->zoom = 1;
    } else {
        QMessageBox::critical(nullptr, "error", ("Command `"+command.toStdString()+"` is not valid.").c_str());
    }
}

void Game(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, ("Build Game " + VERSION).c_str());
    InitAudioDevice();
    SetTargetFPS(40);

    /* LOAD ALL TEXTURES */

    for (auto item : fs::directory_iterator("assets"))
    {
        if (!item.is_directory())
        {
            fs::path itemPath = item.path();

            // make sure only good blocks appear

            if (itemPath.filename() != "door_opened.png")
            {
                textures.push_back(item.path());
            }
        }
    }

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
    bool showCoords = true;

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

        /*********************************************************************/

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

        /*********************************************************************/

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

        /*********************************************************************/

        if (IsKeyPressed(KEY_F3)){
            showCMDDialog(&player, &cam);
        }

        /*********************************************************************/

        if (IsKeyPressed(KEY_ENTER))
        {
            for (Block &b : blocks)
            {
                if (b.x == player.x + DEFAULT_SIZE && b.y == player.y &&
                    b.blockType == 1)
                {
                    toggle(b, DEFAULT_SIZE);
                }
                else if (b.x == player.x - DEFAULT_SIZE && b.y == player.y &&
                         b.blockType == 1)
                {
                    toggle(b, DEFAULT_SIZE);
                }
                else if (b.y == player.y + DEFAULT_SIZE && b.x == player.x &&
                         b.blockType == 1)
                {
                    toggle(b, DEFAULT_SIZE);
                }
                else if (b.y == player.y - DEFAULT_SIZE && b.x == player.x &&
                         b.blockType == 1)
                {
                    toggle(b, DEFAULT_SIZE);
                }
            }
        }

        /*********************************************************************/

        if (IsKeyPressed(KEY_F10)){
            if (showCoords) showCoords = false;
            else showCoords = true;
        }

        /*********************************************************************/

        // Block adding logic
        if (IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            addBlock(player.x, player.y, currentTexture, textures.at(currentTextureIndex));
            PlaySound(placeSound);
        }

        /*********************************************************************/
        /*                             BLOCK MENU                            */
        /*********************************************************************/

        if (IsKeyPressed(KEY_E))
        {
            openBlockSelectionMenu(&currentTexture);
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
            loadWorld(currentTexture, cam, player);
        }

        GuiSetFont(defaultFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        GuiLabel((Rectangle){0, 0, 270, 20}, formatBlock().c_str());
        if (showCoords)
        {
            GuiLabel((Rectangle){0, 20, 500, 20}, ("Coords: X=" + std::to_string(std::stoi(std::to_string(player.x))) + " Y=" + std::to_string(std::stoi(std::to_string(player.y)))).c_str());
        }
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
/***************************************************/
/***************************************************/
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
