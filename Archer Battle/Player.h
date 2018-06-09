#pragma once
#include <SDL.h>
#include <vector>
#include "Tile.cpp"
#include <SDL_mixer.h>
namespace archer {
	enum sprites {
		idle,
		hit,
		fire_1, fire_2, fire_3, fire_4,
		stab_1, stab_2, stab_3, stab_4, stab_5,
		walk_1, walk_2, walk_3, walk_4, walk_5, walk_6,
		arrow,
		total_sprites
	};
	struct points {
		int buffer;
		int player1;
		int player2;
	};
	class Player {
	public:
		Player(SDL_Renderer * renderer, int x, int y, Uint8 id);
		~Player();
		void handleEvents(SDL_Event event);
		void handleControllerEvents(SDL_Event event);
		void render();
		void renderCross();
		void move(int elapsed, Tile * tiles[], SDL_Rect & otherhurtBox, int & otherhealth);
		void aiMove(Tile * tiles[], SDL_Rect & otherhurtBox, int & otherhealth);
		void setSpawnLocation(int x, int y);
		void checkBounds(int screen_width, int screen_wheight);
		void handleArrows(SDL_Rect hurtBox, int & health, Tile * tiles[]);
		void enableAI() { ai = true; }
		int &getHealth() { return health; }
		SDL_Rect &getHitBox() { return hitBox; }
		void setHitBoxX(int x) { hitBox.x = x; }
		void loadGui(points  & score);
		void reset();
		void loadControllerGui(points & score);
	private:
		bool ai = false;
		int crossX = 0, crossY = 0;
		int xmotion = 0, ymotion = 0;
		int arrows = 0;
		int respawnTimeStart;
		bool damagable = true;
		bool aiYCol = true;
		bool aiXCol = false;
		bool aiWaterCol = false;
		int aiFireTime = 0;
		int aiFireable;
		int damageCounter;
		bool dead = false;
		bool onWood = false;
		Uint8 id = 0;
		bool hold = false;
		bool passed = false;
		bool stabKill = false;
		int holdStartTime;
		int mx, my;
		int arrowStart = 0;
		bool newArrow = false;
		std::vector<int> ax, ay, avx, avy, angle, storedmx;
		std::vector<bool> active, visible;
		std::vector<SDL_RendererFlip> arrowPos;
		std::vector<SDL_Rect> arrowHitBox;
		double velx, vely, gy;
		int spawnx, spawny;
		bool left = false, right = false, jump = false, stab = false, fire = false;
		SDL_RendererFlip lastPos;
		SDL_RendererFlip firePos;
		SDL_Renderer * renderer;
		const static SDL_RendererFlip LEFT = SDL_FLIP_HORIZONTAL;
		const static SDL_RendererFlip RIGHT = SDL_FLIP_NONE;
		int startTime;
		int airStartTime;
		int frame = 0;
		int fireFrame = 0;
		bool release = false;
		SDL_Rect hitBox;
		LTexture * textures[total_sprites];
		LTexture ammoT;
		LTexture idT;
		LTexture cross;
		Mix_Chunk * ah;
		Mix_Chunk * arrowHit;
		Mix_Chunk * arrowHit2;
		Mix_Chunk * pickup;
		Mix_Chunk * step;
		Mix_Chunk * woodstep;
	public:
		int health = 100;
		int ammo = 24;
	};
}