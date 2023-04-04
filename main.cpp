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

using namespace std;


int main(int argc, const char * argv[])
{
    //Variables para la ventana
    //-----------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    //------------------------------


    //Arrancamos la ventana
    //------------------------------
    InitWindow(screenWidth, screenHeight, "Lamento en el Tibet");
    //------------------------------

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

    //Image backgroundMenuImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgMenu.png");
    Texture2D backgroundImage = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgMenu.png");
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
    int startButtonState = 0;
    bool startButtonAction = false;

    Vector2 mousePoint = {0.0f, 0.0f};

    SetTargetFPS(60);

    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    string userInput;

    //Main loop del juego y cliente
    while(!WindowShouldClose()) {

        //Update
        //-------------
        mousePoint = GetMousePosition();
        startButtonAction = false;


        //-------------------------
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
            PlaySound(fxButton);
            CloseWindow();

            InitWindow(screenWidth, screenHeight, "Lamento en el Tibet");
            BeginDrawing();
            //ClearBackground(WHITE);
            DrawTexture(backgroundImage, 0,0, WHITE);
            EndDrawing();
        }

        sourceRecStart.y = startButtonState* frameHeightStart;

        //Draw

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(backgroundImage, 0,0, WHITE);
        DrawTextureRec(startButton, sourceRecStart, (Vector2){ startBottonBounds.x, startBottonBounds.y }, WHITE); // Draw button frame
        DrawTextureRec(settingsButton, sourceRecSettings, (Vector2){settingButtonBounds.x, settingButtonBounds.y}, WHITE);

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