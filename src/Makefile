CPPFLAGS=-g -std=c++14 -pthread
LDFLAGS=-g -std=c++14 -pthread
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX=g++

SRCS=main.cpp EnvironmentThing.cpp Render.cpp Thing.cpp Player.cpp Bullet.cpp Weapon.cpp Playfield.cpp Enemy.cpp \
Animation.cpp Ability.cpp Cursor.cpp Camera.cpp Ui.cpp Stats.cpp WeaponMod.cpp WeaponWidget.cpp EnemyDemon.cpp \
EnemyEye.cpp Teleporter.cpp BreakableThing.cpp EnemyLegion.cpp ThingEntrance.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: sfml-test

sfml-test: $(OBJS)
	$(CXX) $(LDLIBS) $(OBJS) -o sfml-test $(LDLIBS)
	mv sfml-test ../

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm *.o ../sfml-test

include .depend