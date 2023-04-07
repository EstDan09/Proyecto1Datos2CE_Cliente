#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "raylib.h"
#define NUM_FRAMES 1 //recorte
#include "raymath.h"
using namespace std;

#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include "/home/esteban/raylib-cpp-4.5.0/include/raylib-cpp.hpp"

//Pantallas que voy a usar
//------------------------------
typedef enum GameScreen {MENU = 0, F1, F2, F3} GameScreen;
//------------------------------



int main(int argc, const char * argv[])
{
    //Variables para la ventana
    //-----------------------------
    const int screenWidth = 1500;
    const int screenHeight = 1000;
    //------------------------------


    //Arrancamos la ventana
    //------------------------------
    raylib::Window window (screenWidth, screenHeight, "Lamento en el Tibet");
    //------------------------------

    GameScreen currentScreen = MENU;

    //Audio
    //------------------------------
    InitAudioDevice();
    Sound fxButton = LoadSound("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/one.wav");
    //------------------------------

    //Imagenes
    //------------------------------
    Image startButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/start.png");
    ImageResize(&startButtonImage, 350, 200);
    Texture2D startButton = LoadTextureFromImage(startButtonImage);

    Image settingsButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/settings.png");
    ImageResize(&settingsButtonImage, 100, 100);
    Texture2D settingsButton = LoadTextureFromImage(settingsButtonImage);

    Image shipImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/ships.png");
    raylib::Texture shipUsableImage = LoadTextureFromImage(shipImage);

    Image bulletImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/blasts.png");
    raylib::Texture bulletUsableImage = LoadTextureFromImage(bulletImage);

    raylib::Texture backgroundImageF1 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF1.png");

    raylib::Texture backgroundImageMenu = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgMenu.png");
    //------------------------------

    //Objetos
    //------------------------------
    Player player (&shipUsableImage, raylib::Rectangle(40,8, 8,8),
                   raylib::Rectangle(100,GetScreenHeight()/2,64,64), 200.0f,
                   &bulletUsableImage, 0.25f);

    Enemy enemyF1T1(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64), 200.0f,
                &bulletUsableImage);

    Enemy enemyF1T2(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                 raylib::Rectangle(GetScreenWidth()-70, 700, 64,64), 200.0f,
                 &bulletUsableImage);
    Enemy enemyF1T3(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                    raylib::Rectangle(GetScreenWidth()-70, 790, 64,64), 200.0f,
                    &bulletUsableImage);
    Enemy enemyF1T4(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                    raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                    &bulletUsableImage);



    Background backgroundMenu(&backgroundImageMenu,raylib::Rectangle(200,100,1300, 1000),
                              raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);


    Background backgroundF1(&backgroundImageF1,raylib::Rectangle(200,100,1300, 1000),
                            raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
    //------------------------------


    //Parametros del boton Start
    //------------------------------
    float frameHeightStart = (float)startButton.height/NUM_FRAMES; //390
    Rectangle sourceRecStart = {0,0, (float)startButton.width, frameHeightStart};

    Rectangle startBottonBounds = { screenWidth/2.0f - startButton.width/2.0f, screenHeight/2.0f - startButton.height/NUM_FRAMES/2.0f,
                            (float)startButton.width, frameHeightStart};
    //------------------------------

    //Parametros del boton Settings
    //------------------------------
    float frameHeightSettings = (float)settingsButton.height/NUM_FRAMES; //390
    Rectangle sourceRecSettings = {0,0, (float)settingsButton.width, frameHeightSettings};

    Rectangle settingButtonBounds = { screenWidth/10.0f - settingsButton.width/2.0f, screenHeight/8.0f - settingsButton.height/NUM_FRAMES/2.0f,
                            (float)settingsButton.width, frameHeightSettings};
    //------------------------------


    //Variables que voy a usar
    //------------------------------
    int startButtonState = 0;
    bool startButtonAction = false;
    int framesCounter = 0;

    SetTargetFPS(60);

    Vector2 mousePoint = {0.0f, 0.0f};

    SetTargetFPS(60);

    //	Creo el socket
    //------------------------------
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }
    //------------------------------

    //	Info sobre el server al que me quiero conectar
    //------------------------------
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    //------------------------------

    //	Conectar al server
    //------------------------------
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    char buf[4096];
    string userInput;
    //------------------------------


    //Main loop del juego y cliente
    //------------------------------
    while(!WindowShouldClose()) {

        //Update
        //-------------
        switch(currentScreen){
            case MENU:{

                mousePoint = GetMousePosition();
                startButtonAction = false;

                if (CheckCollisionPointRec(mousePoint, startBottonBounds)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        startButtonState = 2 ;
                    }
                    else {
                        startButtonState = 1;
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        startButtonAction = true;
                    }
                }
                else {
                    startButtonState = 1;
                }
                if (startButtonAction) {
                    string message = "Test Miedo";
                    int sendRes = send(sock, message.c_str(), message.size() + 1, 0);
                    if (sendRes == -1)
                    {
                        cout << "Could not send to server! Whoops!\r\n";
                        continue;
                    }
                    //PlaySound(fxButton);
                    currentScreen = F1;
                }
            }
            break;

            case F1:{
                player.Event();
                backgroundMenu.Update();
                player.Update();
                enemyF1T1.Update();
                enemyF1T2.Update();
                enemyF1T3.Update();
                enemyF1T4.Update();
            }
            break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentScreen){
            case MENU:{
                backgroundMenu.Draw();
                DrawTextureRec(startButton, sourceRecStart, (Vector2){ startBottonBounds.x, startBottonBounds.y }, WHITE); // Draw button frame
                DrawTextureRec(settingsButton, sourceRecSettings, (Vector2){settingButtonBounds.x, settingButtonBounds.y}, WHITE);
            }
            break;

            case F1: {
                backgroundF1.Update();
                backgroundF1.Draw();
                player.Draw();
                enemyF1T1.Draw();
                enemyF1T2.Draw();
                enemyF1T3.Draw();
                enemyF1T4.Draw();
            }
            break;
            default: break;
        }
        EndDrawing();

        //		Enter lines of text


        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }


        else
        {
            //		Display response
            cout << string(buf, 0, bytesReceived) << "\r\n";
        }
    };
    UnloadTexture(startButton);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound

    CloseAudioDevice();     // Close audio device

    CloseWindow();
    close(sock);


}