.defautl: all

all: azul

clean:
	rm -f azul *.o

azul: BoxLid.o Credits.o Factory.o GameEngine.o main.o Menu.o Player.o PointCalculator.o Tile.o TileBag.o TileLList.o TileNode.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
