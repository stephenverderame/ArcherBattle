#include <SDL.h>
#include "Player.h"
namespace archer {
	class Player {
	public:
		void handleEvents(SDL_Event event);
		void render();
		SDL_Rect getHitbox();
		int getHealth();
		void move(Tile * tiles[]);
	private:
		int posx, posy;
		int velx, vely;
		int frames;
		SDL_Rect hitBox;
	};
}