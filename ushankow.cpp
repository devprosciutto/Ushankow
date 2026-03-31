#include <iostream>
#include <string>
#include <raylib.h>
#define SFML_NO_DEPRECATED_WARNINGS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


using namespace std;


int main(){


sf::Event::GainedFocus; // window is focused aka on screen;
bool window_on_screen = true;
int Outline_Thickness = 0.9;


sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
sf::RenderWindow window(sf::VideoMode(640,480), "Ushankow", sf::Style::Default);


window.setVerticalSyncEnabled(true);
bool vsync = true;
window.setFramerateLimit(30);
std::cout << "vysnc is set as " << vsync << std::endl;


sf::Font default_font;
if (!default_font.loadFromFile("/home/amd/Documents/my cpp programs/ushankow my learning app/NotoSans-ExtraCondensedExtraBoldItalic.ttf")){
std::cerr << ". Error While Loading Font ." << std::endl;
return -1;
}
sf::Text ScreenText;
ScreenText.setFont(default_font);
ScreenText.setString("Welcome To Ushankow \n an indie software to help you with \n your russian learning journey!");
ScreenText.setCharacterSize(30);
ScreenText.setFillColor(sf::Color(255,188,217)); //Cotton Candy Color (Pink)
ScreenText.setOutlineThickness(Outline_Thickness);
ScreenText.setOutlineColor(sf::Color(244,240,236)); //Isabelline(yellowish white)
ScreenText.setOrigin(0,0); // diving the screen boundaries for the text properly

float volume = 50.0f;
bool volume_changed = false;
bool volume_check = false;

sf::Text VolumeBar;
VolumeBar.setString("Volume: " + std::to_string(volume));
VolumeBar.setFillColor(sf::Color(255,188,217));
VolumeBar.setOrigin(0,0);
sf::Clock Timer;
sf::Music music;
if(!music.openFromFile("katyusha.wav")){
std::cerr << ". Error Opening Music File ." << std::endl;
return -1;
} else { 
std::cerr << " katyusha.wav has been loaded" << std::endl;
}

music.setLoop(true);
music.play();


// string timer for changing vocabulary strings
float timer = 0.0f;
const int limit = 399;

window.setKeyRepeatEnabled(false);

while (window.isOpen()){

sf::Image icon;
if (icon.loadFromFile("ushankow.png")){
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

sf::Event main_window;
music.setVolume(volume);

if (vsync==false && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))){
    vsync = true;
    window.setVerticalSyncEnabled(true);
    std::cout << "vysnc is set as " << "true" << std::endl;

} else if (vsync==true && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))){
    vsync = false;
    window.setVerticalSyncEnabled(false);
    std::cerr << "vysnc is set as " << "false" << std::endl;
}


if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)){
volume = music.getVolume();
volume_check = true;
if (volume_check==true){
std::cerr << "this is the volume: " << volume << " " << std::endl;
} else {}
}



if (window_on_screen==true && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
volume_changed = true;
volume = (volume - 5.0f);
} else {
volume_changed = false;
}
if (window_on_screen==true && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
volume_changed = true;
volume = (volume + 5.0f);
} else {
volume_changed = false;
}


if (volume < 0.0f){
volume = 0.0f;
}
if (volume > 500.0f){
volume = 500.0f;
}


if (volume_changed==true){
std::cerr << "current volume: " << volume << " " << std::endl;
} else { }

//draw Volume: + the actual volume value on screen
//if ((volume_changed==true or volume_changed==false)){
VolumeBar.setString("Volume: " + std::to_string(volume));
//}

float last_volume = volume;

// STRING SYSTEM:
//change string to new vocab, the string system is fully working
if (timer>=0 && timer<99){
ScreenText.setString("Welcome To Ushankow \n an indie software to help you with \n your russian learning journey!");
}

if (timer>=100 && timer<199){
ScreenText.setString("testing.");
}


if (timer>=200 && timer<299){
ScreenText.setString("testing..");
}


if (timer>=300 && timer<399){
ScreenText.setString("testing...completed ");
}

// reset timer when it reaches 399, its working
if (timer>=399){
timer = 0;
ScreenText.setString("Welcome To Ushankow \n an indie software to help you with \n your russian learning journey!");
}

// this is a continuous loop alarm, i prefer using cout for this, cerr is way more static it seems, ill use cerr for everything but alarms aka loops like this;
std::cout << "string timer: " << timer << " " << std::endl;


if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))){
timer = 0;
}

timer += 1;

// END OF STRING SYSTEM


while(window.pollEvent(main_window)){
if (main_window.type == sf::Event::Closed){
window.close();
}


if (!IsWindowMinimized() or (!IsWindowHidden())){
window_on_screen = true;
} else {
window_on_screen = false;
}
if (window_on_screen==true){
main_window.type == sf::Event::GainedFocus;
} else {
window_on_screen = false;
sf::Event::LostFocus;
}
}



window.clear(sf::Color(15,15,15)); // black onyx (black) color as screen background
ScreenText.setPosition(GetScreenWidth() / 2 + 160 ,50);
VolumeBar.setPosition(GetScreenWidth() / 2 + 160 ,60);
window.draw(ScreenText);
window.draw(VolumeBar);
window.display();
}
window_on_screen = false;
return 0;
}