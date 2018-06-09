#include <SDL.h>
#include <SDL_ttf.h>
#include "LTexture.cpp"
#include "Player.h"
#include <string>
#include <sstream>
#include <SDL_mixer.h>
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
SDL_Window * window;
SDL_Renderer * renderer;
using namespace archer;
LTexture * textures[13];
LTexture scoreTexture;
LTexture finalTexture;
LTexture finalTexture2;
SDL_Color color;
Tile * tiles[42];
points score;
int totalTime;
SDL_Joystick * controller;
std::stringstream scoring;
bool musicStart = false;
Mix_Music * music;
bool freeze = true;
void close() {
	for (int i = 0; i <= 42; i++) {
		delete tiles[i];
	}
	for (int i = 0; i < 13; i++) {
		delete textures[i];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
void loadObjects(){
	textures[0] = new LTexture(renderer);
	textures[0]->enableBlend();
	textures[0]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t1.bmp", true, 240, 0, 255);
	textures[1] = new LTexture(renderer);
	textures[1]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t2.bmp", true, 240, 0, 255);
	textures[2] = new LTexture(renderer);
	textures[2]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t3.bmp", true, 240, 0, 255);
	textures[3] = new LTexture(renderer);
	textures[3]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t4.bmp", true, 240, 0, 255);
	textures[4] = new LTexture(renderer);
	textures[4]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t5.bmp", true, 240, 0, 255);
	textures[5] = new LTexture(renderer);
	textures[5]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t14.bmp", true, 240, 0, 255);
	textures[6] = new LTexture(renderer);
	textures[6]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t15.bmp", true, 240, 0, 255);
	textures[7] = new LTexture(renderer);
	textures[7]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t16.bmp", true, 240, 0, 255);
	textures[8] = new LTexture(renderer);
	textures[8]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t17.bmp", true, 240, 0, 255); //water
	textures[9] = new LTexture(renderer);
	textures[9]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/t18.bmp", true, 240, 0, 255);
	textures[10] = new LTexture(renderer);
	textures[10]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/tree.bmp", true, 240, 0, 255);
	textures[11] = new LTexture(renderer);
	textures[11]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/rock.bmp", true, 240, 0, 255);
	textures[12] = new LTexture(renderer);
	textures[12]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/snowman.bmp", true, 240, 0, 255);
	textures[13] = new LTexture(renderer);
	textures[13]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/crate.bmp", true, 240, 0, 255);
	tiles[0] = new Tile();
	tiles[0]->createTile(0, 952, 128, 128, 0, textures[0]);
	tiles[1] = new Tile();
	tiles[1]->createTile(128, 952, 128, 128, 0, textures[1]);
	tiles[2] = new Tile();
	tiles[2]->createTile(256, 952, 128, 128, 0, textures[1]);
	tiles[3] = new Tile();
	tiles[3]->createTile(384, 952, 128, 128, 0, textures[4]);
	tiles[4] = new Tile();
	tiles[4]->createTile(512, 952, 128, 128, 0, textures[4]);
	tiles[5] = new Tile();
	tiles[5]->createTile(640, 952, 128, 128, 0, textures[4]);
	tiles[6] = new Tile();
	tiles[6]->createTile(384, 824, 128, 128, 0, textures[0]);
	tiles[7] = new Tile();
	tiles[7]->createTile(512, 824, 128, 128, 0, textures[1]);
	tiles[8] = new Tile();
	tiles[8]->createTile(640, 824, 128, 128, 0, textures[1]);
	tiles[9] = new Tile();
	tiles[9]->createTile(768, 824, 128, 93, 0, textures[7]);
	tiles[10] = new Tile();
	tiles[10]->createTile(768, 982, 128, 128, 10, textures[8]);
	tiles[11] = new Tile();
	tiles[11]->createTile(896, 982, 128, 128, 10, textures[8]);
	tiles[12] = new Tile();
	tiles[12]->createTile(1024, 982, 128, 128, 10, textures[8]);
	tiles[13] = new Tile();
	tiles[13]->createTile(1152, 952, 128, 128, 0, textures[4]);
	tiles[14] = new Tile();
	tiles[14]->createTile(1152, 824, 128, 128, 0, textures[4]);
	tiles[15] = new Tile();
	tiles[15]->createTile(1152, 806, 128, 128, 0, textures[4]);
	tiles[16] = new Tile();
	tiles[16]->createTile(1152, 678, 128, 128, 0, textures[0]);
	tiles[17] = new Tile();

	tiles[17]->createTile(1280, 952, 128, 128, 0, textures[4]);
	tiles[18] = new Tile();
	tiles[18]->createTile(1280, 824, 128, 128, 0, textures[4]);
	tiles[19] = new Tile();
	tiles[19]->createTile(1280, 806, 128, 128, 0, textures[4]);
	tiles[20] = new Tile();
	tiles[20]->createTile(1280, 678, 128, 128, 0, textures[1]);
	tiles[21] = new Tile();

	tiles[21]->createTile(1408, 952, 128, 128, 0, textures[4]);
	tiles[22] = new Tile();
	tiles[22]->createTile(1408, 824, 128, 128, 0, textures[4]);
	tiles[23] = new Tile();
	tiles[23]->createTile(1408, 806, 128, 128, 0, textures[4]);
	tiles[24] = new Tile();
	tiles[24]->createTile(1408, 678, 128, 128, 0, textures[1]);
	tiles[25] = new Tile();

	tiles[25]->createTile(1536, 952, 128, 128, 0, textures[4]);
	tiles[26] = new Tile();
	tiles[26]->createTile(1536, 824, 128, 128, 10, textures[9]);
	tiles[27] = new Tile();
	tiles[27]->createTile(1536, 806, 128, 128, 10, textures[9]);
	tiles[28] = new Tile();
	tiles[28]->createTile(1536, 710, 128, 128, 10, textures[8]);
	tiles[29] = new Tile();

	tiles[29]->createTile(1664, 952, 128, 128, 0, textures[4]);
	tiles[30] = new Tile();
	tiles[30]->createTile(1664, 824, 128, 128, 0, textures[4]);
	tiles[31] = new Tile();
	tiles[31]->createTile(1664, 806, 128, 128, 0, textures[4]);
	tiles[32] = new Tile();
	tiles[32]->createTile(1664, 678, 128, 128, 0, textures[2]);
	tiles[33] = new Tile();
	tiles[33]->createTile(1300, 468, 180, 210, 0, textures[12]);
	tiles[33]->setImageOffset(-10);
	tiles[34] = new Tile();

	tiles[34]->createTile(1792, 952, 128, 128, 0, textures[4]);
	tiles[35] = new Tile();
	tiles[35]->createTile(1792, 824, 128, 128, 0, textures[1]);
	
	tiles[36] = new Tile();
	tiles[36]->createTile(256, 550, 128, 93, 0, textures[5]);
	tiles[37] = new Tile();
	tiles[37]->createTile(384, 550, 128, 93, 0, textures[6]);
	tiles[38] = new Tile();
	tiles[38]->createTile(512, 550, 128, 93, 0, textures[6]);
	tiles[39] = new Tile();
	tiles[39]->createTile(640, 550, 108, 93, 0, textures[7]);
	tiles[40] = new Tile();
	tiles[40]->createTile(490, 270, 158, 280, 0, textures[10]);
	tiles[40]->setImageOffset(-30);
	tiles[41] = new Tile();
	tiles[41]->createTile(280, 449, 101, 101, 0, textures[13]);
	tiles[42] = new Tile();
	tiles[42]->createTile(256, 874, 124, 78, 0, textures[11]);
	color = { 0x0, 0x0, 0xFF, 0xFF };
	scoreTexture.setRenderer(renderer);
	scoreTexture.loadFont("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/libel.ttf", color, 28);
	finalTexture.setRenderer(renderer);
	SDL_Color finColor = { 0xFF, 0, 0, 0xFF };
	finalTexture.loadFont("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/libel.ttf", finColor, 52);
	finalTexture2.setRenderer(renderer);
	finalTexture2.loadFont("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/libel.ttf", finColor, 52);
	music = Mix_LoadMUS("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/Carol.mp3");
	printf(music == NULL ? "Music is null \n %s" : "Music is not null \n", Mix_GetError());


}
void handleObjects() {
	for (int i = 0; i <= 42; i++) {
		tiles[i]->render();
	}
}
bool ai = false;
int main(int argc, char**args) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
	TTF_Init();
	score.player1 = 0;
	score.player2 = 0;
	totalTime = 300;
	int startClock = SDL_GetTicks();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2040);
	window = SDL_CreateWindow("Archer Battle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event event;
	LTexture bg;
	Mix_Chunk * win = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/victory1.wav");
	bg.setRenderer(renderer);
	bg.loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/bg.bmp", false);
	loadObjects();
	Player player(renderer, 100, 300, 1);
	Player cplayer(renderer, 1900, 300, 2);
	int elapsed = 0, startTime = SDL_GetTicks();
	bool running = true;
	if (SDL_NumJoysticks() >= 1) {
		controller = SDL_JoystickOpen(0);
	}
	else {
		ai = true;
		//cplayer.enableAI();
	}
	while (running) {
		startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			player.handleEvents(event);
			if (ai == false) {
				cplayer.handleControllerEvents(event);
			}
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		bg.render(0, 0);
		player.move(elapsed, tiles, cplayer.getHitBox(), cplayer.health);
		if(ai){
			cplayer.aiMove(tiles, player.getHitBox(), player.health);
		}
		cplayer.move(elapsed, tiles, player.getHitBox(), player.health);
		player.handleArrows(cplayer.getHitBox(), cplayer.health, tiles);
		cplayer.handleArrows(player.getHitBox(), player.health, tiles);
		handleObjects();
		player.checkBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
		cplayer.checkBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
		player.render();
		cplayer.render();
		player.loadGui(score);
		cplayer.loadControllerGui(score);
		cplayer.renderCross();
		scoring.str("");
		int ticks = SDL_GetTicks();
		scoring << "Player 1: " << score.player1 << "          Time Left: " << ((300 - (ticks - startClock) / 1000)) / 60 << ":" << (300 - ((ticks - startClock)/1000)) % 60 << "          Player 2: " << score.player2;
		scoreTexture.loadFromRenderedText(scoring.str());
		scoreTexture.render(700, 100);
		SDL_RenderPresent(renderer);
		if ((300 - ((ticks - startClock) / 1000) == 192) && musicStart == false) {
			Mix_PlayMusic(music, -1);
			musicStart = true;
			printf("Playing music \n");
		}
		if (300 - ((ticks - startClock) / 1000) < 0) {
			Mix_HaltMusic();
			Mix_RewindMusic();
			freeze = true;
			scoring.str("");
			if (score.player1 != score.player2) {
				scoring << (score.player1 < score.player2 ? "Player 2 " : "Player 1 ") << "won by a score of " << (score.player1 < score.player2 ? score.player2 : score.player1) << " to " << (score.player1 < score.player2 ? score.player1 : score.player2);
				Mix_PlayChannel(-1, win, 0);
			}
			else {
				scoring << "TIE!";
			}
			finalTexture.loadFromRenderedText(scoring.str());
			finalTexture2.loadFromRenderedText("Press Space to Restart!");
			while (freeze) {
				while (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						running = false;
						freeze = false;
					}
					else if (event.type == SDL_KEYDOWN) {
						if (event.key.keysym.sym == SDLK_SPACE) {
							freeze = false;
							score.player1 = 0;
							score.player2 = 0;
							totalTime = 300;
							startClock = SDL_GetTicks();
							player.health = 100;
							cplayer.health = 100;
							player.ammo = 24;
							cplayer.ammo = 24;
							musicStart = false;
							player.reset();
							cplayer.reset();
						}
					}
				}
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, 0x0, 0, 0, 0xFF);
				finalTexture.render((SCREEN_WIDTH - finalTexture.getWidth()) / 2, (SCREEN_HEIGHT - finalTexture.getHeight()) / 2);
				finalTexture2.render((SCREEN_WIDTH - finalTexture2.getWidth()) / 2, ((SCREEN_HEIGHT - finalTexture2.getHeight()) / 2) + finalTexture.getHeight());
				SDL_RenderPresent(renderer);

			}
		}
		elapsed = SDL_GetTicks() - startTime;
	}
	close();
	return 0;
}