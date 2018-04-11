window: src/window.cpp lib/SFML/Graphics.hpp
				g++ -c src/window.cpp -I"./lib/" -o src/window.o
				g++ src/window.o -I"./lib/"  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system 

