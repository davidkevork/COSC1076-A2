.defautl: all

all: azul

clean:
	rm -f azul *.o

azul: Credits.o Menu.o main.o BoxLid.o Factory.o GameEngine.o TileBag.o Tile.o TileLList.o TileNode.o Player.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
