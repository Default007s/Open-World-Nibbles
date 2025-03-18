#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

using namespace sf;
using namespace std;

int MAPWIDTH = 2520;
int MAPHEIGHT = 1280;

void writeText(Font &FontName, Text &Element, float x, float y, const char text[], int red, int green, int blue) {
    Element.setFont(FontName);
    Element.setString(text);
    Element.setPosition(x, y);
    Element.setFillColor(Color(red, green, blue));
    Element.setCharacterSize(30);
    Element.setOrigin(Element.getLocalBounds().width / 2, Element.getLocalBounds().height / 2);
}

void HighScore(RenderWindow& window, char hslevels[][10], char hsinfinites[][10], char hslevelsNames[][10], char hsinfinitesNames[][10], Font& FontName, int red, int green, int blue) {
    int keytime = 0;
    ifstream finl("levelhighscore.txt");
    ifstream fini("infinitehighscore.txt");
    Text hslevelsTxt[5];
    Text hslevelsNamesTxt[5];
    Text hsinfinitesTxt[5];
    Text hsinfinitesNamesTxt[5];
    Text hsLevel;
    writeText(FontName, hsLevel, 400, 200, "High Score Levels", red, green, blue);
    Text hsInfinite;
    writeText(FontName, hsInfinite, 900, 200, "High Score Infinite", red, green, blue);
    for (int i = 0; i < 5; i++)
    {
        finl >> hslevelsNames[i];
        finl >> hslevels[i];
        writeText(FontName, hslevelsNamesTxt[i], 320, 300 + i * 30, hslevelsNames[i], red, green, blue);
        writeText(FontName, hslevelsTxt[i], 480, 300 + i * 30, hslevels[i], red, green, blue);
        hslevelsNamesTxt[i].setOrigin(0, hslevelsNamesTxt[i].getLocalBounds().height / 2);
        fini >> hsinfinitesNames[i];
        fini >> hsinfinites[i];
        writeText(FontName, hsinfinitesNamesTxt[i], 820, 300 + i * 30, hsinfinitesNames[i], red, green, blue);
        writeText(FontName, hsinfinitesTxt[i], 980, 300 + i * 30, hsinfinites[i], red, green, blue);
        hsinfinitesNamesTxt[i].setOrigin(0, hsinfinitesNamesTxt[i].getLocalBounds().height / 2);
    } 
    int exit = 0;
    while (!exit) {
        Event event;

        bool focus = window.hasFocus();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (keytime < 8)keytime++;
        if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Enter) && keytime >=8) {
            exit = 1;
        }
        window.clear();
        for (int i = 0; i < 5; i++)
        {    
            window.draw(hsLevel);
            window.draw(hsInfinite);
            window.draw(hslevelsTxt[i]);
            window.draw(hslevelsNamesTxt[i]);
            window.draw(hsinfinitesTxt[i]);
            window.draw(hsinfinitesNamesTxt[i]);
        }
        window.display();
    }
}

void InfinteLevels(RenderWindow& window, int wallCheck, int customCheck, char username[], int red, int green, int blue, int bgred, int bggreen, int bgblue, int& saved, int savedOrNot, Music& clickSound, Music& moveSound, Music& escape, Music& menuMusic, int red2, int green2, int blue2, int& speedValueInt, int& miniMapCheck, int& directorCheck);
void changeColor(RenderWindow& window, int& red, int& green, int& blue, int& bgred, int& bggreen, int& bgblue, Music& clickSound);
void TweakSettings(RenderWindow& window, int red, int green, int blue, int red2, int  green2, int blue2, int& speedValueInt, int& miniMapCheck, int& director, int& sound, Music& clickSound, Music& moveSound, Music& menuMusic);

int main() {
    RenderWindow window(VideoMode(1260, 640), "Open World Nibbles", Style::Default);
    window.setFramerateLimit(60);  

    int red = 66, green = 245, blue = 197;
    int bgred = 0, bggreen = 0, bgblue = 255;
    int red2 = 64, green2 = 110, blue2 = 97;

    int speedValueInt = 50;
    int sound = 1;
    int director = 1;
    int miniMapCheck = 1;

    //Music
    Music menuMusic;
    menuMusic.openFromFile("Resources/menuMusic.mp3");
    menuMusic.setLoop(true);
    Music moveSound;
    moveSound.openFromFile("Resources/move.mp3");
    Music clickSound;
    clickSound.openFromFile("Resources/click.mp3");
    Music escape;
    escape.openFromFile("Resources/escape.mp3");
    Music ghost;
    ghost.openFromFile("Resources/ghost.mp3");
    ghost.play();
    menuMusic.play();
    menuMusic.setVolume(0.f);
    // Menu
    int focusMenu = 1, enterValue = -1, menuValue = 1;
    int saved = 0;
    Font Coolvetica;
    Coolvetica.loadFromFile("");
    Font Namaku;
    Namaku.loadFromFile("Fonts/Doto/Doto.ttf");

    Text heroHead;
    writeText(Namaku, heroHead, window.getSize().x / 2 - 100, window.getSize().y / 2 - 120, "OPEN WORLD NIBBLES", red, green, blue);
    heroHead.setStyle(Text::Bold);
    heroHead.setStyle(Text::Italic);
    heroHead.setCharacterSize(50);
    Text Saved;
    writeText(Namaku, Saved, window.getSize().x / 2, window.getSize().y - 350, "Continue", red, green, blue);
    Text Play;
    writeText(Namaku, Play, window.getSize().x / 2, window.getSize().y - 300, "Play", red, green, blue);
    Text ColorChange;
    writeText(Namaku, ColorChange, window.getSize().x / 2, window.getSize().y - 250, "Change Skin", red, green, blue);
    Text HighScores;
    writeText(Namaku, HighScores, window.getSize().x / 2, window.getSize().y - 200, "High Scores", red, green, blue);
    Text Settings;
    writeText(Namaku, Settings, window.getSize().x / 2, window.getSize().y - 150, "Settings", red, green, blue);
    Text Quit;
    writeText(Namaku, Quit, window.getSize().x / 2, window.getSize().y - 100, "Quit", red, green, blue);
    Text InfiniteMode;
    writeText(Namaku, InfiniteMode, window.getSize().x / 2, window.getSize().y - 250, "Infinite Mode", red, green, blue);
    Text WallMode;
    writeText(Namaku, WallMode, window.getSize().x / 2, window.getSize().y - 200, "Wall Mode", red, green, blue);
    Text Levels;
    writeText(Namaku, Levels, window.getSize().x / 2, window.getSize().y - 250, "Levels", red, green, blue);
    Text Custom;
    writeText(Namaku, Custom, window.getSize().x / 2, window.getSize().y - 200, "Custom", red, green, blue);
    Text usernameInst;
    writeText(Namaku, usernameInst, window.getSize().x / 2, window.getSize().y / 3, "Enter Username", red, green, blue);
    Text username;

    Clock clock;
    Time t1 = seconds(8.f);
    Time t2 = seconds(5.f);
    Time t3 = seconds(3.f);
    int fadeValue = 0.f;
    Texture logoT;
    logoT.loadFromFile("Resources/logo.png");
    logoT.setSmooth(true);
    Sprite LogoBg;
    LogoBg.setTexture(logoT);
    float scaleXL = float(window.getSize().x) / logoT.getSize().x;
    float scaleYL = float(window.getSize().y) / logoT.getSize().y;
    LogoBg.setScale(scaleXL, scaleYL);
    Texture bgmenuTexture;
    bgmenuTexture.loadFromFile("Resources/bg1.png");
    Sprite BgMenu;
    int menuCounter = 0;
    float scaleX = float(window.getSize().x) / bgmenuTexture.getSize().x;
    float scaleY = float(window.getSize().y) / bgmenuTexture.getSize().y;
    BgMenu.setTexture(bgmenuTexture);
    BgMenu.setScale(scaleX, scaleY);
    BgMenu.setColor(Color(bgred, bggreen, bgblue));
    int logo = 1;

    char hslevels[5][10];
    char hslevelsNames[5][10];
    char hsinfinites[5][10];
    char hsinfinitesNames[5][10];

    char inputArray[10] = "";
    char dummyUsername[10] = "UNKNOWN";
    int currentNameIndex = 0;
    int keytime = 0;

    RectangleShape walls[10];
    int wallX[10], wallY[10], wallSizeX[10], wallSizeY[10];

    while (window.isOpen())
    {

        Event event;

        bool focus = window.hasFocus();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (keytime < 20) keytime++;

        ifstream fin("state.txt");
        fin >> saved;
        if (Keyboard::isKeyPressed(Keyboard::Escape) && keytime >= 8)
        {
            if (clock.getElapsedTime() < t1)
            {
                t1 = seconds(0.f);
                ghost.setVolume(0.f);
            }
            else {
                keytime = 0;
                if (enterValue == 1) {
                    enterValue = 0;
                    menuValue = 1;
                }
                else if (enterValue == 4) {
                    enterValue = 1;
                    menuValue = 2;
                }
            }
            escape.play();
        }

        if (event.type == Event::TextEntered && enterValue == -1 && keytime >= 8 && clock.getElapsedTime() > t1) {
            if (event.text.unicode == 8) { // Backspace key
                escape.play();
                if (currentNameIndex > 0) {
                    inputArray[--currentNameIndex] = '\0';
                }
            }
            else if (event.text.unicode == 13 && clock.getElapsedTime() > t1) { // Enter key
                cout << 1;
                enterValue = 0;
                clickSound.play();
                int i;
                for (i = 0; inputArray[i]!=0; i++)
                {
                    if (inputArray[i] == ' ') {
                        for (int j = i; inputArray[j] != 0; j++)
                        {
                            if (j != 9)
                            {
                                swap(inputArray[j], inputArray[j + 1]);
                            }
                        }
                    }
                }
                if (!i)
                {
                    strcpy_s(inputArray, dummyUsername);
                }
                username.setPosition(window.getSize().x / 2, 10);
            }
            else {
                if (currentNameIndex < 9 && event.text.unicode != 27) {
                    moveSound.play();
                    inputArray[currentNameIndex++] = char(event.text.unicode);
                    inputArray[currentNameIndex] = '\0';
                }
            }
            writeText(Namaku, username, window.getSize().x / 2, window.getSize().y / 2, inputArray, red, green, blue);
            keytime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter) && keytime >= 8 && clock.getElapsedTime() > t1) {
            clickSound.play();
            if (menuValue == 1 && focusMenu == 1 && saved)
                enterValue = -2;
            else if ((menuValue == 1 && focusMenu == 1 && !saved) || (menuValue == 1 && focusMenu == 2 && saved))
                enterValue = 1;     //Play
            else if ((menuValue == 1 && focusMenu == 2 && !saved) || (menuValue == 1 && focusMenu == 3 && saved)) {
                enterValue = 2;     //Change Color
            }
            else if (menuValue == 2 && focusMenu == 1) {
                enterValue = 3;     //Infinite
            }
            else if (menuValue == 2 && focusMenu == 2) {
                enterValue = 4;     //Walls
            }
            else if (menuValue == 3 && focusMenu == 1) {
                enterValue = 5;     //Levels
            }
            else if (menuValue == 3 && focusMenu == 2) {
                enterValue = 6;     //Custom
            }
            else if ((menuValue == 1 && focusMenu == 3 && !saved) || (menuValue == 1 && focusMenu == 4 && saved))
                enterValue = 7;
            else if ((menuValue == 1 && focusMenu == 4 && !saved) || (menuValue == 1 && focusMenu == 5 && saved))
                enterValue = 8;
            else if ((menuValue == 1 && focusMenu == 5 && !saved) || (menuValue == 1 && focusMenu == 6 && saved))
                enterValue = 9;
            keytime = 0;
            menuValue++;
        }

        //Arrow Keys    
        if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && keytime >= 8 && clock.getElapsedTime() > t1)
        {
            moveSound.play();
            if (saved && menuValue == 1) {
                if (focusMenu == 1) focusMenu = 6;
                else if (focusMenu == 2) focusMenu = 1;
                else if (focusMenu == 3) focusMenu = 2;
                else if (focusMenu == 4) focusMenu = 3;
                else if (focusMenu == 5) focusMenu = 4;
                else if (focusMenu == 6) focusMenu = 5;
            }
            else if (menuValue == 1) {
                if (focusMenu == 1) focusMenu = 5;
                else if (focusMenu == 2) focusMenu = 1;
                else if (focusMenu == 3) focusMenu = 2;
                else if (focusMenu == 4) focusMenu = 3;
                else if (focusMenu == 5) focusMenu = 4;
            }
            else {
                if (focusMenu == 1) focusMenu = 2;
                else if (focusMenu == 2) focusMenu = 1;
            }

            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && keytime >= 8 && clock.getElapsedTime() > t1)
        {
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))  && keytime >= 8 && clock.getElapsedTime() > t1)
        {
            moveSound.play();
            if (saved && menuValue == 1) {
                if (focusMenu == 1) focusMenu = 2;
                else if (focusMenu == 2) focusMenu = 3;
                else if (focusMenu == 3) focusMenu = 4;
                else if (focusMenu == 4) focusMenu = 5;
                else if (focusMenu == 5) focusMenu = 6;
                else if (focusMenu == 6) focusMenu = 1;
            }
            else if (menuValue == 1) {
                if (focusMenu == 1) focusMenu = 2;
                else if (focusMenu == 2) focusMenu = 3;
                else if (focusMenu == 3) focusMenu = 4;
                else if (focusMenu == 4) focusMenu = 5;
                else if (focusMenu == 5) focusMenu = 1;
            }
            else {
                if (focusMenu == 1) focusMenu = 2;
                else if (focusMenu == 2) focusMenu = 1;
            }
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && keytime >= 8 && clock.getElapsedTime() > t1)
        {
            keytime = 0;
        }

        //Menu Movement
        if (saved && menuValue == 1)
        {
            if (focusMenu == 1)
            {
                Saved.setFillColor(Color(red, green, blue));
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 2) {
                Saved.setFillColor(Color(red2, green2, blue2));
                Play.setFillColor(Color(red, green, blue));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 3) {
                Saved.setFillColor(Color(red2, green2, blue2));
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red, green, blue));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 4) {
                Saved.setFillColor(Color(red2, green2, blue2));
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red, green, blue));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 5) {
                Saved.setFillColor(Color(red2, green2, blue2));
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red, green, blue));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 6) {
                Saved.setFillColor(Color(red2, green2, blue2));
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red, green, blue));
            }
        }
        else {
            if (focusMenu == 1)
            {
                Play.setFillColor(Color(red, green, blue));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
                WallMode.setFillColor(Color(red2, green2, blue2));
                InfiniteMode.setFillColor(Color(red, green, blue));
                Levels.setFillColor(Color(red2, green2, blue2));
                Custom.setFillColor(Color(red, green, blue));
            }
            else if (focusMenu == 2) {
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red, green, blue));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
                WallMode.setFillColor(Color(red, green, blue));
                InfiniteMode.setFillColor(Color(red2, green2, blue2));
                Levels.setFillColor(Color(red, green, blue));
                Custom.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 3)
            {
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red, green, blue));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 4)
            {
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red, green, blue));
                Quit.setFillColor(Color(red2, green2, blue2));
            }
            else if (focusMenu == 5)
            {
                Play.setFillColor(Color(red2, green2, blue2));
                ColorChange.setFillColor(Color(red2, green2, blue2));
                HighScores.setFillColor(Color(red2, green2, blue2));
                Settings.setFillColor(Color(red2, green2, blue2));
                Quit.setFillColor(Color(red, green, blue));
            }
        }

        //Draw
        window.clear(Color::Black);
        if (clock.getElapsedTime() < t1)
        {
            if (clock.getElapsedTime() < t2)
            {
                if (fadeValue < 254)
                {
                    LogoBg.setColor(Color(255, 255, 255, fadeValue += 2));
                }
            }
            else {
                if (fadeValue > 0)
                {
                    LogoBg.setColor(Color(255, 255, 255, fadeValue -= 2));
                }
            }
            window.draw(LogoBg);
        }
        else {
            if (sound)
            {
                menuMusic.setVolume(100.f);
            }
            else {
                menuMusic.setVolume(0.f);
            }
            window.clear(Color(bgred, bggreen, bgblue));
            if (menuCounter % 90 < 10)
            {
                bgmenuTexture.loadFromFile("Resources/bg1.png");
            }
            else if (menuCounter % 90 < 20) {
                bgmenuTexture.loadFromFile("Resources/bg2.png");
            }
            else if (menuCounter % 90 < 30) {
                bgmenuTexture.loadFromFile("Resources/bg3.png");
            }
            else if (menuCounter % 90 < 40) {
                bgmenuTexture.loadFromFile("Resources/bg4.png");
            }
            else if (menuCounter % 90 < 50) {
                bgmenuTexture.loadFromFile("Resources/bg5.png");
            }
            else if (menuCounter % 90 < 60) {
                bgmenuTexture.loadFromFile("Resources/bg6.png");
            }
            else if (menuCounter % 90 < 70) {
                bgmenuTexture.loadFromFile("Resources/bg7.png");
            }
            else if (menuCounter % 90 < 80) {
                bgmenuTexture.loadFromFile("Resources/bg8.png");
            }
            else if (menuCounter % 90 < 90) {
                bgmenuTexture.loadFromFile("Resources/bg9.png");
            }
            menuCounter++;
            window.draw(BgMenu);
            window.draw(username);
            if (enterValue == -1)
            {
                window.draw(usernameInst);
                window.draw(username);
            }
            else if (enterValue == -2) {
                menuMusic.stop();
                InfinteLevels(window, 0, 0, inputArray, red, green, blue, bgred, bggreen, bgblue, saved, 1, clickSound, moveSound, escape, menuMusic, red2, green2, blue2, speedValueInt, miniMapCheck, director);
                menuMusic.play();
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 0)
            {
                if (saved)
                {
                    window.draw(Saved);
                }
                window.draw(heroHead);
                window.draw(Play);
                window.draw(ColorChange);
                window.draw(HighScores);
                window.draw(Settings);
                window.draw(Quit);
                username.setPosition(window.getSize().x / 2, 10);
            }
            else if (enterValue == 1) {
                window.draw(heroHead);
                window.draw(InfiniteMode);
                window.draw(WallMode);
            }
            else if (enterValue == 2) {
                changeColor(window, red, green, blue, bgred, bggreen, bgblue, clickSound);
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 3) {
                menuMusic.stop();
                InfinteLevels(window, 0, 0, inputArray, red, green, blue, bgred, bggreen, bgblue, saved, 0, clickSound, moveSound, escape, menuMusic, red2, green2, blue2, speedValueInt, miniMapCheck, director);
                menuMusic.play();
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 4) {
                window.draw(heroHead);
                window.draw(Levels);
                window.draw(Custom);
            }
            else if (enterValue == 5) {
                menuMusic.stop();
                InfinteLevels(window, 0, 1, inputArray, red, green, blue, bgred, bggreen, bgblue, saved, 0, clickSound, moveSound, escape, menuMusic, red2, green2, blue2, speedValueInt, miniMapCheck, director);
                menuMusic.play();
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 6) {
                menuMusic.stop();
                InfinteLevels(window, 1, 0, inputArray, red, green, blue, bgred, bggreen, bgblue, saved, 0, clickSound, moveSound, escape, menuMusic, red2, green2, blue2, speedValueInt, miniMapCheck, director);
                menuMusic.play();
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 7) {
                HighScore(window, hslevels, hsinfinites, hslevelsNames, hsinfinitesNames, Namaku, red, green, blue);
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 8) {
                TweakSettings(window, red, green, blue, red2, green2, blue2, speedValueInt, miniMapCheck, director, sound, clickSound, moveSound, menuMusic);
                enterValue = 0;
                menuValue = 1;
            }
            else if (enterValue == 9) {
                window.close();
            }
        }
        window.display();
    }
    return 0;
}

void TweakSettings(RenderWindow& window, int red, int  green, int blue, int red2, int  green2, int blue2, int& speedValueInt, int& miniMapCheck, int& director, int& sound, Music& clickSound, Music& moveSound, Music& menuMusic) {
    Font Namaku;
    Namaku.loadFromFile("Fonts/Doto/Doto.ttf");
    Text Speed;
    writeText(Namaku, Speed, window.getSize().x / 2 - 100, window.getSize().y / 2 - 100, "Speed", red, green, blue);
    Text MiniMap;
    writeText(Namaku, MiniMap, window.getSize().x / 2 - 100, window.getSize().y / 2 - 50, "MiniMap", red, green, blue);
    Text Director;
    writeText(Namaku, Director, window.getSize().x / 2 - 100, window.getSize().y / 2, "Director", red, green, blue);
    Text Sound;
    writeText(Namaku, Sound, window.getSize().x / 2 - 100, window.getSize().y / 2 + 50, "Sound", red, green, blue);
    Text SpeedValue;
    writeText(Namaku, SpeedValue, window.getSize().x / 2 + 100, window.getSize().y / 2 - 100, "50", red, green, blue);
    Text YesorNo;
    writeText(Namaku, YesorNo, window.getSize().x / 2 + 100, window.getSize().y / 2 - 50, "Yes", red, green, blue);
    RectangleShape focusRect(Vector2f(70, 40));
    focusRect.setOrigin(focusRect.getLocalBounds().width / 2, focusRect.getLocalBounds().height / 2);
    focusRect.setFillColor(Color(red2, green2, blue2));

    int focusValue = 1;
    int done = 0;
    int keytime = 0;
    char speedStr[4] = { "0" };

    while (!done) {
        Event event;
        bool focus = window.hasFocus();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (keytime < 8)keytime++;
        if ((Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Enter)) && keytime >= 8) {
            done = 1;
            keytime = 0;
            clickSound.play();
        }
        if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && keytime >= 8)
        {
            if (focusValue == 1)focusValue = 4;
            else if (focusValue == 2)focusValue = 1;
            else if (focusValue == 3)focusValue = 2;
            else if (focusValue == 4)focusValue = 3;
            keytime = 0;
            moveSound.play();
        }
        if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) && keytime >= 8)
        {
            if (focusValue == 1)focusValue = 2;
            else if (focusValue == 2)focusValue = 3;
            else if (focusValue == 3)focusValue = 4;
            else if (focusValue == 4)focusValue = 1;
            keytime = 0;
            moveSound.play();
        }
        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && keytime >= 8)
        {
            if (focusValue == 1)
            {
                if (speedValueInt > 0)
                {
                    speedValueInt--;
                }
            }
            else if (focusValue == 2)
            {
                if (miniMapCheck)miniMapCheck = 0;
                else miniMapCheck = 1;
            }
            else if (focusValue == 3)
            {
                if (director)director = 0;
                else director = 1;
            }
            else if (focusValue == 4)
            {
                if (sound)sound = 0;
                else sound = 1;
            }
            keytime = 0;
            clickSound.play();
        }if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && keytime >= 8)
        {
            clickSound.play();
            if (focusValue == 1)
            {
                if (speedValueInt < 100)
                {
                    speedValueInt++;
                }
            }
            else if (focusValue == 2)
            {
                if (miniMapCheck)miniMapCheck = 0;
                else miniMapCheck = 1;
            }
            else if (focusValue == 3)
            {
                if (director)director = 0;
                else director = 1;
            }
            else if (focusValue == 4)
            {
                if (sound)sound = 0;
                else sound = 1;
            }
            keytime = 0;
        }

        if (sound)
        {
            menuMusic.setVolume(100.f);
        }
        else {
            menuMusic.setVolume(0.f);
        }

        //Menu Movement
        if (focusValue == 1) focusRect.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 - 90);
        else if (focusValue == 2) focusRect.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 - 40);
        else if (focusValue == 3) focusRect.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 + 10);
        else if (focusValue == 4) focusRect.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 + 60);

        //Speed Conversion
        int n = speedValueInt, speedSize;
        for (speedSize = 0; n != 0; speedSize++)
        {
            n /= 10;
        }
        if (speedSize == 0)speedSize = 1;
        speedStr[speedSize] = '\0';
        n = speedValueInt;
        for (; speedSize > 0; speedSize--)
        {
            speedStr[speedSize - 1] = (n % 10) + 48;
            n /= 10;
        }

        SpeedValue.setString(speedStr);

        window.clear(Color::Black);

        window.draw(focusRect);
        window.draw(Speed);
        window.draw(SpeedValue);

        YesorNo.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 - 50);
        if (miniMapCheck)YesorNo.setString("Yes");
        else YesorNo.setString("No");
        window.draw(YesorNo);
        window.draw(MiniMap);

        YesorNo.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2);
        if (director)YesorNo.setString("Yes");
        else YesorNo.setString("No");
        window.draw(Director);
        window.draw(YesorNo);

        YesorNo.setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 + 50);
        if (sound)YesorNo.setString("Yes");
        else YesorNo.setString("No");
        window.draw(Sound);
        window.draw(YesorNo);

        window.display();
    }
}

void changeColor(RenderWindow& window, int& red, int& green, int& blue, int& bgred, int& bggreen, int& bgblue, Music& clickSound) {
    int selected = 0;
    int keytime = 0;
    Font Namaku;
    Namaku.loadFromFile("Fonts/Doto/Doto.ttf");

    Text Instruction;
    writeText(Namaku, Instruction, window.getSize().x / 2, 30, "Select Your Color and Press Enter!", red, green, blue);
    RectangleShape sample(Vector2f(300.f, 20.f));
    sample.setOrigin(sample.getLocalBounds().width / 2, sample.getLocalBounds().height / 2);
    sample.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    Texture bggameTexture;
    bggameTexture.loadFromFile("Resources/grassPatch.jpg");
    Sprite BgGame;
    float scaleX = float(window.getSize().x) / bggameTexture.getSize().x;
    float scaleY = float(window.getSize().y) / bggameTexture.getSize().y;
    BgGame.setTexture(bggameTexture);
    BgGame.setScale(scaleX, scaleY);

    while (!selected) {
        Event event;
        bool focus = window.hasFocus();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (keytime < 8) keytime++;
        if (Keyboard::isKeyPressed(Keyboard::Enter) && keytime >= 8) {
            clickSound.play();
            selected = 1;
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && keytime >= 8)
        {
            red += 5;
            green += 15;
            blue += 12;
            bgred -= 5;
            bggreen -= 15;
            bgblue -= 12;
        }
        else if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && keytime >= 8)
        {
            red -= 5;
            green -= 15;
            blue -= 12;
            bgred += 5;
            bggreen += 15;
            bgblue += 12;
        }

        BgGame.setColor(Color(bgred, bggreen, bgblue));
        sample.setFillColor(Color(red, green, blue));
        Instruction.setFillColor(Color(red, green, blue));
        window.clear(Color(bgred, bggreen, bgblue));
        window.draw(BgGame);
        window.draw(Instruction);
        window.draw(sample);
        window.display();
    }
}

void buildWalls(int wallNo, RectangleShape walls[], int wallX[], int wallY[], RenderWindow& window, int wallSizeX[], int wallSizeY[], int gridSize, int posX, int posY, int fruitX, int fruitY, int red, int green, int blue) {
    for (int i = 0; i < wallNo; i++)
    {
        wallX[i] = 0;
        wallY[i] = 0;
        wallSizeX[i] = 0;
        wallSizeY[i] = 0;
        walls[i].setSize(Vector2f(0, 0));
    }
    for (int i = 0; i < wallNo; i++)
    {
        wallX[i] = rand() % MAPWIDTH + 20;
        wallY[i] = (rand() % MAPHEIGHT) + 100;
        if (wallX[i] % 20 != 0) {
            wallX[i] -= wallX[i] % 20;
        }
        if (wallY[i] % 20 != 0) {
            wallY[i] -= wallY[i] % 20;
        }
        if (i % 2 == 1) {
            //Horizontal Wall
            wallSizeX[i] = gridSize * 3 + (rand() % 400);
            if (wallSizeX[i] % 20 != 0) {
                wallSizeX[i] += gridSize - (wallSizeX[i] % gridSize);
            }
            for (int j = 0; j < i; j++)
            {
                if ((wallSizeY[j] + wallY[j] >= wallY[i] && wallY[j] <= wallY[i]) && (wallX[j] >= wallX[i] && wallX[j] <= wallX[i] + wallSizeX[i]))
                {
                    wallX[i] -= (wallX[j] - wallX[i]) + 50;
                    wallSizeX[i] = 20;
                }
            }
            
            walls[i].setSize(Vector2f(wallSizeX[i], gridSize));
            if ((wallX[i] == posX && wallY[i] == posY) || (wallX[i] == fruitX && wallY[i] == fruitY))
            {
                wallX[i] += 60;
                wallY[i] += 60;
            }
            walls[i].setPosition(wallX[i], wallY[i]);
        }
        else {
            //Vertical Wall
            wallSizeY[i] = gridSize * 3 + (rand() % 400);
            if (wallSizeY[i] % 20 != 0) {
                wallSizeY[i] += gridSize-(wallSizeY[i] % gridSize);
            }

            for (int j = 0; j < i; j++)
            {
                if ((wallSizeX[j] + wallX[j] >= wallX[i] && wallX[j] <= wallX[i]) && (wallY[j] >= wallY[i] && wallY[j] <= wallY[i] + wallSizeY[i]))
                {
                    wallY[i] -= (wallY[j] - wallY[i]) + 50;
                    wallSizeY[i] = 20;
                }
            }
            
            walls[i].setSize(Vector2f(gridSize, wallSizeY[i]));
            if ((wallX[i] == posX && wallY[i] == posY) || (wallX[i] == fruitX && wallY[i] == fruitY))
            {
                wallX[i] += 60;
                wallY[i] += 60;
            }
            if (wallY[i] + wallSizeY[i] > MAPHEIGHT)
            {
                wallY[i] -= ((wallY[i]) - window.getSize().y) + gridSize;
            }
            walls[i].setPosition(wallX[i], wallY[i]);
        }
    }
}

void buildSpecifiedWalls(int wallNo, RectangleShape walls[], int wallX[], int wallY[], RenderWindow& window, int wallSizeX[], int wallSizeY[], int red, int green, int blue) {
    for (int i = 0; i < wallNo; i++)
    {
        if (wallX[i] % 20 != 0) {
            wallX[i] -= wallX[i] % 20;
        }
        if (wallY[i] % 20 != 0) {
            wallY[i] -= wallY[i] % 20;
        }
        if (wallSizeX[i]) {
            //Horizontal Wall
            walls[i].setSize(Vector2f(wallSizeX[i], 20));
            walls[i].setPosition(wallX[i], wallY[i]);
        }
        else {
            //Vertical Wall
            walls[i].setSize(Vector2f(20, wallSizeY[i]));
            walls[i].setPosition(wallX[i], wallY[i]);
        }
        walls[i].setFillColor(Color(red + 100, green + 150, blue + 50));
    }
}

void updateHS(int option, int key, int score, char username[], int hslevelsInt[], int hsinfinitesInt[], char hslevelsNames[][10], char hsinfinitesNames[][10]) {
    if (option == 1)
    {
        for (int i = 4; i > key; i--)
        {
            hslevelsInt[i] = hslevelsInt[i - 1];
            strcpy_s(hslevelsNames[i], hslevelsNames[i - 1]);
        }
        hslevelsInt[key] = score;
        strcpy_s(hslevelsNames[key], username);
        ofstream foutl("levelhighscore.txt");
        for (int i = 0; i < 5; i++)
        {
            foutl << hslevelsNames[i] << " " << hslevelsInt[i] << endl;
        }
        foutl.close();
    }
    else if (option == 2) {
        for (int i = 4; i > key; i--)
        {
            hsinfinitesInt[i] = hsinfinitesInt[i - 1];
            strcpy_s(hsinfinitesNames[i], hsinfinitesNames[i - 1]);
        }
        hsinfinitesInt[key] = score;
        strcpy_s(hsinfinitesNames[key], username);
        ofstream fouti("infinitehighscore.txt");
        for (int i = 0; i < 5; i++)
        {
            fouti << hsinfinitesNames[i] << " " << hsinfinitesInt[i] << endl;
        }
        fouti.close();
    }
}

void SaveData(int fruitX, int fruitY, int posX, int posY, int speedX, int speedY, int nTail, int scoreValue, int levelValue, int wallNo, int wallCheck, int customCheck, int currentWall, int wallX[], int wallY[], int wallSizeX[], int wallSizeY[]) {
    ofstream fout("state.txt");
    fout << 1 << endl;
    fout << fruitX << endl;
    fout << fruitY << endl;
    fout << posX << endl;
    fout << posY << endl;
    fout << speedX << endl;
    fout << speedY << endl;
    fout << nTail << endl;
    fout << scoreValue << endl;
    fout << levelValue << endl;
    fout << wallNo << endl;
    fout << wallCheck << endl;
    fout << customCheck << endl;
    fout << currentWall << endl;
    if (customCheck)
    {
        for (int i = 0; i < currentWall; i++) {
            fout << wallX[i] << endl;
        }
        for (int i = 0; i < currentWall; i++) {
            fout << wallY[i] << endl;
        }
        for (int i = 0; i < currentWall; i++) {
            fout << wallSizeX[i] << endl;
        }
        for (int i = 0; i < currentWall; i++) {
            fout << wallSizeY[i] << endl;
        }
    }
    if (wallCheck)
    {
        for (int i = 0; i < wallNo; i++) {
            fout << wallX[i] << endl;
        }
        for (int i = 0; i < wallNo; i++) {
            fout << wallY[i] << endl;
        }
        for (int i = 0; i < wallNo; i++) {
            fout << wallSizeX[i] << endl;
        }
        for (int i = 0; i < wallNo; i++) {
            fout << wallSizeY[i] << endl;
        }
    }
}

float lerp(float start, float end, float alpha) {
    return start + (end - start) * alpha;
}

void drawMiniMap(RenderTexture& miniMapT, Sprite& BgGame, int pause, RectangleShape& pause1, RectangleShape& pause2, Text& Resume, Text& SaveNQuit, Text& QuitWSaving,
    int wallCheck, int wallNo, RectangleShape walls[], int customCheck, int currentWall, int enterValue, Text& CustomInstruction1, Text& CustomInstruction2, int nTail,
    RectangleShape tail[], View& view, float gridSize, int tailX[], int tailY[], int red, int green, int blue, Text& Level,
    Text& LevelValue, Text& Score, Text& ScoreValue, RectangleShape& rect, RectangleShape& fruit, int bgred, int bggreen, int bgblue, int fruitX, int fruitY) {
    Texture cursorMap;
    cursorMap.loadFromFile("Resources/cursor.png");
    miniMapT.clear(Color::Black);
    CircleShape fruitMini(20);
    fruitMini.setPosition(fruitX, fruitY);
    if (wallCheck)
    {
        for (int i = 0; i < wallNo; i++)
        {
            walls[i].setFillColor(Color::Red);
            miniMapT.draw(walls[i]);
        }
    }
    if (customCheck)
    {
        for (int i = 0; i < currentWall; i++)
        {
            walls[i].setFillColor(Color::Red);
            miniMapT.draw(walls[i]);
        }
    }
    rect.setSize(Vector2f(150, 150));
    rect.setFillColor(Color::Green);
    fruitMini.setFillColor(Color::Green);
    rect.setTexture(&cursorMap);
    rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
    miniMapT.draw(rect);
    fruit.setTexture(nullptr);
    miniMapT.draw(fruitMini);
    rect.setOrigin(0, 0);
    rect.setFillColor(Color(red, green, blue));
    rect.setSize(Vector2f(20, 20));
}

void InfinteLevels(RenderWindow& window, int wallCheck, int customCheck, char username[], int red, int green, int blue, int bgred, int bggreen, int bgblue, int& saved, int savedOrNot,
    Music& clickSound, Music& moveSound, Music& escape, Music& menuMusic, int red2, int green2, int blue2, int& speedValueInt, int& miniMapCheck, int& directorCheck) {
    int posX = 0, posY = 20;
    int tailX[100], tailY[100], nTail = 0;
    float gridSize = 20.f;
    float speedX = gridSize, speedY = 0;
    int scoreValue = 0;
    int levelValue = 0;
    int levelCoefficient = 1;
    int Breakthrough = 10;
    int enterValue = 0;
    int pauseMenu = 1;

    //Music
    Music laugh;
    laugh.openFromFile("Resources/laugh.mp3");
    Music eats;
    eats.openFromFile("Resources/eats.mp3");
    Music hits;
    hits.openFromFile("Resources/hits.mp3");

    //Views
    View view(FloatRect(0, 0, 900, 480));
    View MapView(FloatRect(0, 0, MAPWIDTH - 1000, MAPHEIGHT - 300)); // 1500, 900
    RenderTexture miniMapT;
    miniMapT.create(300, 300);
    CircleShape miniMap(50);
    CircleShape director(50);
    director.setFillColor(Color::Green);

    if (!customCheck)
    {
        window.setView(view);
    }
    else {
        if (enterValue)
        {
            window.setView(view);
        }
        else {
            window.setView(window.getDefaultView());
        }
    }

    ifstream finl("levelhighscore.txt");
    ifstream fini("infinitehighscore.txt");

    int hslevelsInt[5];
    int hsInfinitesInt[5];
    char hslevelsNames[5][10];
    char hsInfinitesNames[5][10];

    for (int i = 0; i < 5; i++)
    {
        finl >> hslevelsNames[i];
        finl >> hslevelsInt[i];
        fini >> hsInfinitesNames[i];
        fini >> hsInfinitesInt[i];
    }

    finl.close();
    fini.close();
    Font Namaku;
    Namaku.loadFromFile("Fonts/Doto/Doto.ttf");

    Text Score;
    writeText(Namaku, Score, 50, 10, "Score", red, green, blue);
    Text ScoreValue;
    writeText(Namaku, ScoreValue, 120, 10, "0", red, green, blue);
    Text CustomInstruction1;
    writeText(Namaku, CustomInstruction1, window.getSize().x / 2 + 250, 10, "Left and Right Mouse Click for building and removing walls. You can plant a total of 100 Walls.", red, green, blue);
    CustomInstruction1.setCharacterSize(20);
    Text CustomInstruction2;
    writeText(Namaku, CustomInstruction2, window.getSize().x / 2 + 70, 40, "Press Enter to start the Game.", red, green, blue);
    CustomInstruction2.setCharacterSize(20);
    Text Level;
    Text LevelValue;
    Text Resume;
    writeText(Namaku, Resume, view.getCenter().x / 2, view.getCenter().y / 3, "Resume", red, green, blue);
    Text SaveNQuit;
    writeText(Namaku, SaveNQuit, view.getCenter().x / 2, view.getCenter().y / 2.5, "Save And Quit", red, green, blue);
    Text QuitWSaving;
    writeText(Namaku, QuitWSaving, view.getCenter().x / 2, view.getCenter().y / 2, "Quit", red, green, blue);
    Text GameOverMsg;
    writeText(Namaku, GameOverMsg, window.getSize().x / 2, window.getSize().y / 2 - 100, "You are so bad at this! Just Give Up!", red, green, blue);
    Text ReturnMsg;
    writeText(Namaku, ReturnMsg, window.getSize().x / 2, window.getSize().y / 2, "Returning to Main menu", red, green, blue);
    RectangleShape GameOverRect(Vector2f(900, 300));
    GameOverRect.setOrigin(GameOverRect.getLocalBounds().width / 2, GameOverRect.getLocalBounds().height / 2);
    GameOverRect.setFillColor(Color(red2, green2, blue2));

    Texture bggameTexture;
    bggameTexture.loadFromFile("Resources/grassPatch.jpg");
    bggameTexture.setSmooth(true);
    Sprite BgGame;
    float scaleX = float(window.getSize().x) / bggameTexture.getSize().x;
    float scaleY = float(window.getSize().y) / bggameTexture.getSize().y;
    BgGame.setTexture(bggameTexture);
    BgGame.setScale(scaleX * 2, scaleY * 2);
    BgGame.setColor(Color(bgred, bggreen, bgblue));

    RectangleShape rect(Vector2f(gridSize, gridSize));
    RectangleShape fruit(Vector2f(gridSize, gridSize));
    RectangleShape pause1(Vector2f(20, 60));
    RectangleShape pause2(Vector2f(20, 60));
    pause1.setFillColor(Color(bgred, bggreen, bgblue));
    pause2.setFillColor(Color(bgred, bggreen, bgblue));

    Texture snakeHead;
    snakeHead.loadFromFile("Resources/head.png");
    rect.setTexture(&snakeHead);
    Texture snakeTail;
    snakeTail.loadFromFile("Resources/tail.png");

    RectangleShape tail[100];
    int tailMove = 0;
    float offset = 0.0f;
    rect.setFillColor(Color(red, green, blue));

    //Fruit Position
    int fruitX = rand() % MAPWIDTH;
    int fruitY = rand() % MAPHEIGHT + 40;
    Texture fruitT;
    fruitT.loadFromFile("Resources/fruit.png");
    fruit.setTexture(&fruitT);
    fruit.setFillColor(Color::White);

    if (fruitY >= MAPHEIGHT)
    {
        fruitY = (fruitY - MAPHEIGHT) + 20;
    }
    fruit.setPosition(fruitX, fruitY);
    if (fruitX % 20 != 0) {
        fruitX -= fruitX % 20;
    }
    if (fruitY % 20 != 0) {
        fruitY -= fruitY % 20;
    }
    int relax = 21;

    //Pause Functionality
    int lastSpeedX = 0, lastSpeedY = 0;
    int pause = 0;
    int keytime = 0;

    int gameOver = 0;
    int hit = 0;

    int wallNo = 50;
    RectangleShape walls[100];
    int wallX[100], wallY[100], wallSizeX[100] = { 0 }, wallSizeY[100] = { 0 };
    int currentWall = 0;
    int mousePosGridX;
    int mousePosGridY;

    int relaxedSpeedX, relaxedSpeedY;

    if (savedOrNot)
    {
        ifstream fin("state.txt");
        fin >> saved;
        fin >> fruitX;
        fin >> fruitY;
        fin >> posX;
        fin >> posY;
        fin >> speedX;
        fin >> speedY;
        fin >> nTail;
        fin >> scoreValue;
        fin >> levelValue;
        fin >> wallNo;
        fin >> wallCheck;
        fin >> customCheck;
        fin >> currentWall;
        if (customCheck)
        {
            enterValue = 1;
            for (int i = 0; i < currentWall; i++)
            {
                fin >> wallX[i];
            }
            for (int i = 0; i < currentWall; i++)
            {
                fin >> wallY[i];
            }for (int i = 0; i < currentWall; i++)
            {
                fin >> wallSizeX[i];
            }for (int i = 0; i < currentWall; i++)
            {
                fin >> wallSizeY[i];
            }
        }
        if (wallCheck)
        {
            for (int i = 0; i < wallNo; i++)
            {
                fin >> wallX[i];
            }
            for (int i = 0; i < wallNo; i++)
            {
                fin >> wallY[i];
            }for (int i = 0; i < wallNo; i++)
            {
                fin >> wallSizeX[i];
            }for (int i = 0; i < wallNo; i++)
            {
                fin >> wallSizeY[i];
            }
        }
        if (wallCheck)
        {
            buildSpecifiedWalls(wallNo, walls, wallX, wallY, window, wallSizeX, wallSizeY, red, green, blue);
        }
        else if (customCheck) {
            buildSpecifiedWalls(currentWall, walls, wallX, wallY, window, wallSizeX, wallSizeY, red, green, blue);
        }
    }
    fruit.setPosition(fruitX, fruitY);

    if (wallCheck)
    {
        writeText(Namaku, Level, 200, 10, "Level", red, green, blue);
        writeText(Namaku, LevelValue, 300, 10, "1", red, green, blue);
    }

    //Building Walls
    if (wallCheck && !savedOrNot) {
        buildWalls(wallNo, walls, wallX, wallY, window, wallSizeX, wallSizeY, 20, posX, posY, fruitX, fruitY, red, green, blue);
    }

    while (!gameOver)
    {
        Event event;
        bool focus = window.hasFocus();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
                if (!hit)
                {
                    SaveData(fruitX, fruitY, posX, posY, speedX, speedY, nTail, scoreValue, levelValue, wallNo, wallCheck, customCheck, currentWall, wallX, wallY, wallSizeX, wallSizeY);
                }
            }
        }
        if (keytime < 8) keytime++;

        if (Keyboard::isKeyPressed(Keyboard::Enter) && keytime >= 4) {
            if (customCheck) enterValue = 1;
            if (pause)
            {
                clickSound.play();
                if (pauseMenu == 1)
                {
                    speedX = lastSpeedX;
                    speedY = lastSpeedY;
                    pause = 0;
                }
                else if (pauseMenu == 2) {
                    SaveData(fruitX, fruitY, posX, posY, speedX, speedY, nTail, scoreValue, levelValue, wallNo, wallCheck, customCheck, currentWall, wallX, wallY, wallSizeX, wallSizeY);
                    gameOver = 1;
                }
                else if (pauseMenu == 3) {
                    gameOver = 1;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape) && keytime >= 8) {
            if (pause)
            {
                escape.play();
                menuMusic.stop();
                speedX = lastSpeedX;
                speedY = lastSpeedY;
                pause = 0;
                pause1.setFillColor(Color(bgred, bggreen, bgblue));
                pause2.setFillColor(Color(bgred, bggreen, bgblue));
            }
            else {
                menuMusic.play();
                escape.play();
                lastSpeedX = speedX;
                lastSpeedY = speedY;
                speedX = 0;
                speedY = 0;
                pause = 1;
                pause1.setFillColor(Color(red, green, blue));
                pause2.setFillColor(Color(red, green, blue));
            }
            keytime = 0;
        }

        mousePosGridX = Mouse::getPosition(window).x / gridSize;
        mousePosGridY = Mouse::getPosition(window).y / gridSize;

        if (customCheck && Mouse::isButtonPressed(Mouse::Left))
        {
            bool exists = false;
            for (int i = 0; i < currentWall && !exists; i++)
            {
                if (walls[i].getPosition().x / gridSize == mousePosGridX
                    && walls[i].getPosition().y / gridSize == mousePosGridY) {
                    exists = true;
                }
            }
            if (!exists && currentWall < 100 && mousePosGridY*gridSize > 40)
            {
                wallX[currentWall] = mousePosGridX * gridSize;
                wallY[currentWall] = mousePosGridY * gridSize;
                wallSizeX[currentWall] = 20;
                wallSizeY[currentWall] = 20;
                walls[currentWall].setPosition(wallX[currentWall], wallY[currentWall]);
                walls[currentWall].setSize(Vector2f(gridSize, gridSize));
                walls[currentWall].setFillColor(Color(red, green, blue));
                walls[currentWall].setFillColor(Color(red + 100, green + 150, blue + 50));
                currentWall++;
            }
        }
        if (customCheck && Mouse::isButtonPressed(Mouse::Right))
        {
            bool exists = false;
            int index = -1;
            for (int i = 0; i < currentWall && !exists; i++)
            {
                if (walls[i].getPosition().x / gridSize == mousePosGridX
                    && walls[i].getPosition().y / gridSize == mousePosGridY) {
                    exists = true;
                    index = i;
                }
            }
            if (exists)
            {
                for (int i = index; i < currentWall; i++)
                {
                    walls[i] = walls[i + 1];
                    wallX[i] = wallX[i + 1];
                    wallY[i] = wallY[i + 1];
                }
            }
        }

        if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)))
        {
            if (pause && keytime > 4)
            {
                if (pauseMenu == 1) pauseMenu = 3;
                else if (pauseMenu == 2)pauseMenu = 1;
                else if (pauseMenu == 3)pauseMenu = 2;
                moveSound.play();
            }
            else if (speedY != gridSize && keytime >= 1)
            {
                speedY = -gridSize;
                speedX = 0.f;
            }
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && !pause && speedX != gridSize && keytime >= 1)
        {
            speedX = -gridSize;
            speedY = 0.f;
            rect.setOrigin(rect.getSize().x / 2 + 10, rect.getSize().y / 2 + 10);
            rect.setRotation(180.f);
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)))
        {
            if (pause && keytime > 4)
            {
                moveSound.play();
                if (pauseMenu == 1)pauseMenu = 2;
                else if (pauseMenu == 2)pauseMenu = 3;
                else if (pauseMenu == 3)pauseMenu = 1;
            }
            else if (speedY != -gridSize && keytime >= 1)
            {
                speedY = gridSize;
                speedX = 0.f;
            }
            keytime = 0;
        }
        if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && speedX != -gridSize && !pause && keytime >= 1)
        {
            speedX = gridSize;
            speedY = 0.f;
            keytime = 0;
        }

        //Snake Head Movement
        if (speedY == gridSize)
        {
            rect.setOrigin(0, rect.getSize().y);
            rect.setRotation(90.f);
        }
        else if (speedY == -gridSize) {
            rect.setOrigin(rect.getSize().x, 0);
            rect.setRotation(-90.f);
        }
        else if (speedX == -gridSize) {
            rect.setOrigin(rect.getSize().x / 2 + 10, rect.getSize().y / 2 + 10);
            rect.setRotation(180.f);
        }
        else if (speedX == gridSize) {
            rect.setOrigin(0.f, 0.f);
            rect.setRotation(0.f);
        }

        //View Movement
        if (!customCheck)
        {
            float currentCameraPositionX = view.getCenter().x;
            float currentCameraPositionY = view.getCenter().y;
            float targetPositionX = rect.getPosition().x;
            float targetPositionY = rect.getPosition().y;
            float newCameraX = lerp(currentCameraPositionX, targetPositionX, 0.1f);
            float newCameraY = lerp(currentCameraPositionY, targetPositionY, 0.1f);
            view.setCenter(newCameraX, newCameraY);
            MapView.setCenter(targetPositionX, targetPositionY);
            window.setView(view);
        }
        else {
            if (enterValue)
            {
                float currentCameraPositionX = view.getCenter().x;
                float currentCameraPositionY = view.getCenter().y;
                float targetPositionX = rect.getPosition().x;
                float targetPositionY = rect.getPosition().y;
                float newCameraX = lerp(currentCameraPositionX, targetPositionX, 0.1f);
                float newCameraY = lerp(currentCameraPositionY, targetPositionY, 0.1f);
                view.setCenter(newCameraX, newCameraY);
                MapView.setCenter(targetPositionX, targetPositionY);
                window.setView(view);
            }
        }
        
        //Menu Movement
        if (pause)
        {
            if (pauseMenu == 1)
            {
                Resume.setFillColor(Color(red, green, blue));
                SaveNQuit.setFillColor(Color(red2, green2, blue2));
                QuitWSaving.setFillColor(Color(red2, green2, blue2));
            }
            else if (pauseMenu == 2)
            {
                Resume.setFillColor(Color(red2, green2, blue2));
                SaveNQuit.setFillColor(Color(red, green, blue));
                QuitWSaving.setFillColor(Color(red2, green2, blue2));
            }
            else if (pauseMenu == 3)
            {
                Resume.setFillColor(Color(red2, green2, blue2));
                SaveNQuit.setFillColor(Color(red2, green2, blue2));
                QuitWSaving.setFillColor(Color(red, green, blue));
            }
        }
        
        //Eating Fruit Functionality
        char scorePrinted[10] = { '0' };
        char levelPrinted[10] = { '0' };
        if (posX == fruit.getPosition().x && posY == fruit.getPosition().y)
        {
            eats.play();
            nTail++;
            tailX[nTail - 1] = posX;
            tailY[nTail - 1] = posY;
            fruitX = rand() % MAPWIDTH;
            fruitY = rand() % MAPHEIGHT +20;
            if (fruitY >= MAPHEIGHT)
            {
                fruitY = (fruitY - MAPHEIGHT) + 20;
            }
            if (fruitX % 20 != 0) {
                fruitX -= fruitX % 20;
            }
            if (fruitY % 20 != 0) {
                fruitY -= fruitY % 20;
            }
            fruit.setPosition(fruitX, fruitY);
            scoreValue += 10;
        }

        //Score and Level Calculations
        if (relax<20)
        {
            relax++;
            posX = relaxedSpeedX;
            posY = relaxedSpeedY;
        }
        if (scoreValue == Breakthrough && wallCheck)
        {
            levelValue++;
            if (wallNo<49)
            {
                wallNo += 2;
            }
            Breakthrough += 10;
            buildWalls(wallNo, walls, wallX, wallY, window, wallSizeX, wallSizeY, 20, posX, posY, fruitX, fruitY, red, green, blue);
            relax = 0;
            relaxedSpeedX = posX;
            relaxedSpeedY = posY;
        }
        int n = levelValue, levelLength;
        for (levelLength = 0; n != 0; levelLength++)
        {
            n /= 10;
        }

        if (levelLength == 0)levelLength = 1;
        n = levelValue;
        for (; levelLength > 0; levelLength--)
        {
            levelPrinted[levelLength - 1] = (n % 10) + 48;
            n /= 10;
        }
        LevelValue.setString(levelPrinted);

        int n1 = scoreValue, scoreLength;
        for (scoreLength = 0; n1 != 0; scoreLength++)
        {
            n1 /= 10;
        }
        if (scoreLength == 0)scoreLength = 1;
        n1 = scoreValue;
        for (; scoreLength > 0; scoreLength--)
        {
            scorePrinted[scoreLength - 1] = (n1 % 10) + 48;
            n1 /= 10;
        }
        ScoreValue.setString(scorePrinted);

        //Check to not print fruit on a wall
        if (wallCheck)
        {
            for (int i = 0; i < wallNo; i++)
            {
                if (fruitY == wallY[i] || fruitX == wallX[i])
                {
                    fruitY -= 20;
                    fruitX -= 20;
                    fruit.setPosition(fruitX, fruitY);
                }
            }
            if (fruitY < 0)
            {
                cout << 1;
                fruitY = 20;
            }
            if (fruitX < 0)
            {
                fruitX = 0;
            }
        }

        //Snake Movement
        if (!pause)
        {   
            if (customCheck)
            {
                if (enterValue)
                {
                    if (speedX == gridSize)
                    {
                        for (int i = nTail - 1; i > 0; i--)
                        {
                            tailX[i] = tailX[i - 1] - 1;
                            tailY[i] = tailY[i - 1];
                        }
                        Sleep(100 - speedValueInt);
                        tailX[0] = posX - 1;
                        tailY[0] = posY;
                    }
                    else if (speedX == -gridSize)
                    {
                        for (int i = nTail - 1; i > 0; i--)
                        {
                            tailX[i] = tailX[i - 1] + 1;
                            tailY[i] = tailY[i - 1];
                        }
                        Sleep(100 - speedValueInt);
                        tailX[0] = posX + 1;
                        tailY[0] = posY;
                    }
                    else if (speedY == gridSize)
                    {
                        for (int i = nTail - 1; i > 0; i--)
                        {
                            tailX[i] = tailX[i - 1];
                            tailY[i] = tailY[i - 1] - 1;
                        }
                        Sleep(100 - speedValueInt);
                        tailX[0] = posX;
                        tailY[0] = posY - 1;
                    }
                    else if (speedY == -gridSize)
                    {
                        for (int i = nTail - 1; i > 0; i--)
                        {
                            tailX[i] = tailX[i - 1];
                            tailY[i] = tailY[i - 1] + 1;
                        }
                        Sleep(100 - speedValueInt);
                        tailX[0] = posX;
                        tailY[0] = posY + 1;
                    }
                    posX += speedX;
                    posY += speedY;
                }
            }
            else {
                if (speedX == gridSize)
                {
                    for (int i = nTail - 1; i > 0; i--)
                    {
                        tailX[i] = tailX[i - 1] - 1;
                        tailY[i] = tailY[i - 1];
                    }
                    Sleep(100 - speedValueInt);
                    tailX[0] = posX - 1;
                    tailY[0] = posY;
                }
                else if (speedX == -gridSize)
                {
                    for (int i = nTail - 1; i > 0; i--)
                    {
                        tailX[i] = tailX[i - 1] + 1;
                        tailY[i] = tailY[i - 1];
                    }
                    Sleep(100 - speedValueInt);
                    tailX[0] = posX + 1;
                    tailY[0] = posY;
                }
                else if (speedY == gridSize)
                {
                    for (int i = nTail - 1; i > 0; i--)
                    {
                        tailX[i] = tailX[i - 1];
                        tailY[i] = tailY[i - 1] - 1;
                    }
                    Sleep(100 - speedValueInt);
                    tailX[0] = posX;
                    tailY[0] = posY - 1;
                }
                else if (speedY == -gridSize)
                {
                    for (int i = nTail - 1; i > 0; i--)
                    {
                        tailX[i] = tailX[i - 1];
                        tailY[i] = tailY[i - 1] + 1;
                    }
                    Sleep(100 - speedValueInt);
                    tailX[0] = posX;
                    tailY[0] = posY + 1;
                }
                posX += speedX;
                posY += speedY;
            }
            
        }
        
        if (customCheck)
        {
            if (enterValue)
            {
                rect.setPosition(posX, posY);
            }
        }
        else {
            rect.setPosition(posX, posY);
        }

        //Game over funtionality
        for (int i = 0; i < nTail; i++)
        {
            if (posX == tailX[i] && posY == tailY[i])
            {
                hit = 1;
            }
        }

        //Hitting Wall
        if (wallCheck)
        {
            for (int i = 0; i < wallNo; i++)
            {
                if (wallY[i] == rect.getPosition().y && wallX[i] == rect.getPosition().x) {
                    hit = 1;
                }
                else if (wallSizeX[i])
                {
                    if (rect.getPosition().y == wallY[i])
                    {
                        for (int j = 20; j <= wallSizeX[i]; j += 20)
                        {
                            if (rect.getPosition().x == wallX[i] + j) {
                                hit = 1;
                            }
                        }
                    }
                }
                else if (wallSizeY[i])
                {
                    if (rect.getPosition().x == wallX[i])
                    {
                        for (int j = 0; j <= wallSizeY[i]; j += gridSize)
                        {
                            if (rect.getPosition().y == wallY[i] + j) {
                                hit = 1;
                            }
                        }
                    }
                }
            }
        }
        if (customCheck)
        {
            if (enterValue)
            {
                for (int i = 0; i < currentWall; i++)
                {
                    if (walls[i].getPosition().y == posY && walls[i].getPosition().x == posX) {
                        hit = 1;
                    }
                }
            }
        }

        if (hit) {
            gameOver = 1;
            if (savedOrNot)
            {
                ofstream fout("state.txt");
                fout << 0;
                saved = 0;
                savedOrNot = 0;
            }
            if (wallCheck)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (hslevelsInt[i] < scoreValue)
                    {
                        updateHS(1, i, scoreValue, username, hslevelsInt, hsInfinitesInt, hslevelsNames, hsInfinitesNames);
                        i = 6;
                    }
                }
            }
            else {
                for (int i = 0; i < 5; i++)
                {
                    if (hsInfinitesInt[i] < scoreValue)
                    {
                        updateHS(2, i, scoreValue, username, hslevelsInt, hsInfinitesInt, hslevelsNames, hsInfinitesNames);
                        i = 6;
                    }
                }
            }
        }

        //Infinite Height and width
        if (posX < 0)
        {
            posX = MAPWIDTH;
        }
        else if (posX >= MAPWIDTH)
        {
            posX = 0;
        }
        else if (posY >= MAPHEIGHT)
        {
            posY = 0;
        }
        else if (posY < 20)
        {
            posY = MAPHEIGHT - 20;
        }

        //Clear and Draw
        window.clear(Color(bgred, bggreen, bgblue));
       
        window.draw(BgGame);
        
        if (wallCheck)
        {
            for (int i = 0; i < wallNo; i++)
            {
                walls[i].setFillColor(Color(red + 100, green + 150, blue + 50));
                window.draw(walls[i]);
            }
        }
        if (customCheck)
        {
            for (int i = 0; i < currentWall; i++)
            {
                walls[i].setFillColor(Color(red + 100, green + 150, blue + 50));
                window.draw(walls[i]);
            }
        }
        if (customCheck)
        {
            if (enterValue == 0)
            {
                window.draw(CustomInstruction1);
                window.draw(CustomInstruction2);
            }
            else {
                window.draw(rect);
                for (int i = 0; i < nTail; i++)
                {
                    if (i == nTail - 1)
                    {
                        tail[i].setTexture(&snakeTail);
                        if (nTail > 2)
                        {
                            if (tailX[i - 1] > tailX[i - 2])
                            {
                                tail[i].setOrigin(0.f, 0.f);
                                tail[i].setRotation(0.f);
                            }
                            else if (tailX[i - 1] < tailX[i - 2])
                            {
                                tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                                tail[i].setRotation(180.f);
                            }
                            else if (tailY[i - 1] > tailY[i - 2]) {
                                tail[i].setOrigin(0, tail[i].getSize().y);
                                tail[i].setRotation(90.f);
                            }
                            else if (tailY[i - 1] < tailY[i - 2]) {
                                tail[i].setOrigin(tail[i].getSize().x, 0);
                                tail[i].setRotation(-90.f);
                            }
                        }
                        else if (nTail == 2) {
                            if (tailX[i - 1] > posX)
                            {
                                tail[i].setOrigin(0.f, 0.f);
                                tail[i].setRotation(0.f);
                            }
                            else if (tailX[i - 1] < posX)
                            {
                                tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                                tail[i].setRotation(180.f);
                            }
                            else if (tailY[i - 1] > posY) {
                                tail[i].setOrigin(0, tail[i].getSize().y);
                                tail[i].setRotation(90.f);
                            }
                            else if (tailY[i - 1] < posY) {
                                tail[i].setOrigin(tail[i].getSize().x, 0);
                                tail[i].setRotation(-90.f);
                            }
                        }
                        else if (nTail == 1) {
                            if (speedY == gridSize)
                            {
                                tail[i].setOrigin(tail[i].getSize().x, 0);
                                tail[i].setRotation(-90.f);
                            }
                            else if (speedY == -gridSize) {

                                tail[i].setOrigin(0, tail[i].getSize().y);
                                tail[i].setRotation(90.f);
                            }
                            else if (speedX == -gridSize) {
                                tail[i].setOrigin(0.f, 0.f);
                                tail[i].setRotation(0.f);
                            }
                            else if (speedX == gridSize) {
                                tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                                tail[i].setRotation(180.f);
                            }
                        }
                    }
                    else {
                        tail[i].setTexture(nullptr);
                    }
                    tail[i].setSize(Vector2f(gridSize, gridSize));
                    tail[i].setFillColor(Color(red + i * 5, green, blue));
                    if (speedX)
                    {
                        tail[i].setPosition(tailX[i], tailY[i] + (sin(i * 0.5 + offset) * 7));
                    }
                    else {
                        tail[i].setPosition(tailX[i] + (sin(i * 0.5 + offset) * 7), tailY[i]);
                    }
                    if (nTail == 12)
                    {
                        offset = 0.12f;
                        offset += i / 10.f;
                    }
                    else {
                        if (nTail > 12)
                        {
                            offset += 0.01f;
                        }
                        else {
                            offset += 0.05f;
                        }
                    }
                    window.draw(tail[i]);
                }

            }
        }
        else {
            window.draw(rect);
            for (int i = 0; i < nTail; i++)
            {
                if (i == nTail-1)
                {
                    tail[i].setTexture(&snakeTail);
                    if (nTail>2)
                    {
                        if (tailX[i - 1] > tailX[i - 2])
                        {
                            tail[i].setOrigin(0.f, 0.f);
                            tail[i].setRotation(0.f);
                        }
                        else if (tailX[i - 1] < tailX[i - 2])
                        {
                            tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                            tail[i].setRotation(180.f);
                        }
                        else if (tailY[i - 1] > tailY[i - 2]) {
                            tail[i].setOrigin(0, tail[i].getSize().y);
                            tail[i].setRotation(90.f);
                        }
                        else if (tailY[i - 1] < tailY[i - 2]) {
                            tail[i].setOrigin(tail[i].getSize().x, 0);
                            tail[i].setRotation(-90.f);
                        }
                    }
                    else if (nTail == 2) {
                        if (tailX[i - 1] > posX)
                        {
                            tail[i].setOrigin(0.f, 0.f);
                            tail[i].setRotation(0.f);
                        }
                        else if (tailX[i - 1] < posX)
                        {
                            tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                            tail[i].setRotation(180.f);
                        }
                        else if (tailY[i - 1] > posY) {
                            tail[i].setOrigin(0, tail[i].getSize().y);
                            tail[i].setRotation(90.f);
                        }
                        else if (tailY[i - 1] < posY) {
                            tail[i].setOrigin(tail[i].getSize().x, 0);
                            tail[i].setRotation(-90.f);
                        }
                    }else if (nTail == 1) {
                        if (speedY == gridSize)
                        {
                            tail[i].setOrigin(tail[i].getSize().x, 0);
                            tail[i].setRotation(-90.f);
                        }
                        else if (speedY == -gridSize) {

                            tail[i].setOrigin(0, tail[i].getSize().y);
                            tail[i].setRotation(90.f);
                        }
                        else if (speedX == -gridSize) {
                            tail[i].setOrigin(0.f, 0.f);
                            tail[i].setRotation(0.f);
                        }
                        else if (speedX == gridSize) {
                            tail[i].setOrigin(tail[i].getSize().x / 2 + 10, tail[i].getSize().y / 2 + 10);
                            tail[i].setRotation(180.f);
                        }
                    }
                }
                else {
                    tail[i].setTexture(nullptr);
                }
                tail[i].setSize(Vector2f(gridSize, gridSize));
                tail[i].setFillColor(Color(red + i*5, green, blue));
                if (speedX)
                {
                    tail[i].setPosition(tailX[i], tailY[i] + (sin(i * 0.5 + offset) * 7));
                }
                else {
                    tail[i].setPosition(tailX[i] + (sin(i * 0.5 + offset) * 7), tailY[i]);
                }
                if (nTail==12)
                {
                    offset = 0.12f;
                    offset += i/10.f;
                }
                else {
                    if (nTail>12)
                    {
                        offset += 0.01f;
                    }
                    else {
                        offset += 0.05f;
                    }
                }
                window.draw(tail[i]);
            }
            if (wallCheck)
            {
                window.draw(Level);
                window.draw(LevelValue);
            }
        }


        window.draw(fruit);
        if (!customCheck)
        {
            window.draw(Score);
            window.draw(ScoreValue);
        }
        else {
            if (enterValue)
            {
                window.draw(Score);
                window.draw(ScoreValue);
            }
        }

        if (fruitX > rect.getPosition().x + 500)
        {
            director.setPosition(view.getCenter().x - 395, view.getCenter().y - 190);
        }
        else if (fruitX < rect.getPosition().x - 500)
        {
            director.setPosition(view.getCenter().x - 405, view.getCenter().y - 190);
        }
        else if (fruitY < posY - 300)
        {
            director.setPosition(view.getCenter().x - 400, view.getCenter().y - 195);
        }
        else if (fruitY > posY + 300)
        {
            director.setPosition(view.getCenter().x - 400, view.getCenter().y - 185);
        }
        else {
            director.setPosition(view.getCenter().x - 400, view.getCenter().y - 190);
        }

        //Mini Map 
        if (customCheck)
        {
            if (enterValue)
            {
                miniMapT.setView(MapView);
                drawMiniMap(miniMapT, BgGame, pause, pause1, pause2, Resume, SaveNQuit, QuitWSaving,
                    wallCheck, wallNo, walls, customCheck, currentWall, enterValue, CustomInstruction1, CustomInstruction2, nTail,
                    tail, view, gridSize, tailX, tailY, red, green, blue, Level,
                    LevelValue, Score, ScoreValue, rect, fruit, bgred, bggreen, bgblue, fruitX, fruitY);
                rect.setTexture(&snakeHead);
                miniMapT.display();
                window.setView(view);
                miniMapT.setSmooth(true);
                miniMap.setPosition(view.getCenter().x - 400, view.getCenter().y - 190);
                if (directorCheck)
                {
                    window.draw(director);
                }
                if (miniMapCheck)
                {
                    miniMap.setTexture(&miniMapT.getTexture());
                }
                window.draw(miniMap);
            }
        }
        else {
            miniMapT.setView(MapView);
            drawMiniMap(miniMapT, BgGame, pause, pause1, pause2, Resume, SaveNQuit, QuitWSaving,
                wallCheck, wallNo, walls, customCheck, currentWall, enterValue, CustomInstruction1, CustomInstruction2, nTail,
                tail, view, gridSize, tailX, tailY, red, green, blue, Level,
                LevelValue, Score, ScoreValue, rect, fruit, bgred, bggreen, bgblue, fruitX, fruitY);
            rect.setTexture(&snakeHead);
            miniMapT.display();
            window.setView(view);
            miniMapT.setSmooth(true);
            miniMap.setPosition(view.getCenter().x - 400, view.getCenter().y - 190);
            if (directorCheck)
            {
                window.draw(director);
            }
            if (miniMapCheck)
            {
                miniMap.setTexture(&miniMapT.getTexture());
            }
            window.draw(miniMap);
        }

        fruit.setTexture(&fruitT);
        if (pause)
        {
            pause1.setPosition(view.getCenter().x + 200, view.getCenter().y - 200);
            pause2.setPosition(view.getCenter().x + 240, view.getCenter().y - 200);
            Resume.setPosition(view.getCenter().x, view.getCenter().y - 150);
            SaveNQuit.setPosition(view.getCenter().x, view.getCenter().y - 100);
            QuitWSaving.setPosition(view.getCenter().x, view.getCenter().y - 50);
            window.draw(pause1);
            window.draw(pause2);
            window.draw(Resume);
            window.draw(SaveNQuit);
            window.draw(QuitWSaving);
        }   
        window.setView(window.getDefaultView());

        if (hit)
        {
            hits.play();
            Sleep(1000);
        }
        if (hit && gameOver)
        {
            GameOverRect.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            window.draw(GameOverRect);
            window.draw(GameOverMsg);
            window.draw(ReturnMsg);
            Score.setPosition(window.getSize().x/2 - 50, window.getSize().y/2 + 100);
            ScoreValue.setPosition(window.getSize().x/2 + 50, window.getSize().y/2 + 100);
            window.draw(Score);
            window.draw(ScoreValue);
            laugh.play();
        }
        window.display();
        if (hit && gameOver)
        {
            Sleep(5000);
        }
    }
}
