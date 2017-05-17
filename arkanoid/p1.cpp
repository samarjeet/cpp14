#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;


int main(){
  const int windowWidth = 800;
  const int windowHeight = 600;
  cout << "Hello World\n";
  RenderWindow window{{windowWidth, windowHeight}, "Arkanoid - 1"};
  window.setFramerateLimit(60);

  while (true) {
    window.clear(Color::Black);

    if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

    window.display();
  
  }
  return 0;
}
