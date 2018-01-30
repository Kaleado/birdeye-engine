all: sfml-test

sfml-test: EnvironmentThing.o Render.o Thing.o Player.o Bullet.o Weapon.o Playfield.o Enemy.o main.o Animation.o Ability.o Cursor.o Camera.o Ui.o Stats.o WeaponMod.o WeaponWidget.o
	g++ -g -std=c++14 -pthread main.o EnvironmentThing.o Render.o Bullet.o Weapon.o Player.o Enemy.o Playfield.o Animation.o Ability.o Cursor.o Ui.o Thing.o Camera.o Stats.o WeaponMod.o WeaponWidget.o -o sfml-test -lsfml-graphics -lsfml-window -lsfml-system

Cursor.o: Cursor.hpp Cursor.cpp 
	g++ -g -std=c++14 -pthread -c Cursor.cpp -o Cursor.o

Stats.o: Stats.hpp Stats.cpp 
	g++ -g -std=c++14  -pthread -c Stats.cpp -o Stats.o

Thing.o: Thing.hpp Thing.cpp 
	g++ -g -std=c++14  -pthread -c Thing.cpp -o Thing.o

EnvironmentThing.o: EnvironmentThing.hpp EnvironmentThing.cpp 
	g++ -g -std=c++14  -pthread -c EnvironmentThing.cpp -o EnvironmentThing.o

Player.o: Thing.hpp Weapon.hpp Player.hpp Player.cpp
	g++ -g -std=c++14  -pthread -c Player.cpp -o Player.o

Playfield.o: Playfield.hpp Playfield.cpp 
	g++ -g -std=c++14  -pthread -c Playfield.cpp -o Playfield.o

Weapon.o: Weapon.hpp Weapon.cpp 
	g++ -g -std=c++14  -pthread -c Weapon.cpp -o Weapon.o

Animation.o: Animation.hpp Animation.cpp 
	g++ -g -std=c++14  -pthread -c Animation.cpp -o Animation.o

Bullet.o: Bullet.hpp Bullet.cpp 
	g++ -g -std=c++14  -pthread -c Bullet.cpp -o Bullet.o

Enemy.o: Enemy.hpp Enemy.cpp 
	g++ -g -std=c++14  -pthread -c Enemy.cpp -o Enemy.o

Ability.o: Ability.hpp Ability.cpp 
	g++ -g -std=c++14  -pthread -c Ability.cpp -o Ability.o

Camera.o: Camera.hpp Camera.cpp 
	g++ -g -std=c++14  -pthread -c Camera.cpp -o Camera.o

Ui.o: Ui.hpp Ui.cpp 
	g++ -g -std=c++14  -pthread -c Ui.cpp -o Ui.o

Render.o: Render.hpp Render.cpp 
	g++ -g -std=c++14  -pthread -c Render.cpp -o Render.o

WeaponMod.o: WeaponMod.hpp WeaponMod.cpp 
	g++ -g -std=c++14  -pthread -c WeaponMod.cpp -o WeaponMod.o

WeaponWidget.o: WeaponWidget.hpp WeaponWidget.cpp 
	g++ -g -std=c++14  -pthread -c WeaponWidget.cpp -o WeaponWidget.o


main.o: main.cpp
	g++ -g -std=c++14  -pthread -c main.cpp -o main.o

clean:
	rm *.o sfml-test
