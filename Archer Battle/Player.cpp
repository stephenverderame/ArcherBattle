#include "Player.h"
#include <SDL_mixer.h>
#include <string>
namespace archer {
	int dist(int x1, int y1, int x2, int y2) {
		int dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		return dist;
	}
	int tileDist(Tile * tile, int x2, int y2) {
		int dist = sqrt(pow(tile->getHitBox().x - x2, 2) + pow(tile->getHitBox().y - y2, 2));
		return dist;
	}
		Player::Player(SDL_Renderer * renderer, int x, int y, Uint8 id) {
			airStartTime = SDL_GetTicks();
			holdStartTime = SDL_GetTicks();
			ah = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/ah.wav");
			arrowHit = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/arrowHit1.wav");
			arrowHit2 = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/arrowHit2.wav");
			pickup = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/pickup.wav");
			step = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/footstepsnow1.wav");
			woodstep = Mix_LoadWAV("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/footstepwood3.wav");
			startTime = SDL_GetTicks();
			this->renderer = renderer;
			spawnx = x;
			this->id = id;
			spawny = y;
			hitBox = { x, y, 85, 120 };
			ammoT.setRenderer(renderer);
			SDL_Color idColor = { 0, 0, 0, 0xFF };
			ammoT.loadFont("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/libel.ttf", idColor, 28);
			idT.setRenderer(renderer);
			cross.setRenderer(renderer);
			cross.loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/cross.bmp", true, 0, 255, 255);
			SDL_Color color = { 0x0, 0xFF, 0x0, 0xFF };
			idT.loadFont("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/libel.ttf", color, 28);
			idT.loadFromRenderedText(std::to_string(id));
			textures[idle] = new LTexture(renderer);
			textures[idle]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/idle.bmp", true, 0, 255, 255);
			textures[hit] = new LTexture(renderer);
			textures[hit]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/hit.bmp", true, 0, 255, 255);
			textures[walk_1] = new LTexture(renderer);
			textures[walk_1]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk1.bmp", true, 0, 255, 255);
			textures[walk_2] = new LTexture(renderer);
			textures[walk_2]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk2.bmp", true, 0, 255, 255);
			textures[walk_3] = new LTexture(renderer);
			textures[walk_3]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk3.bmp", true, 0, 255, 255);
			textures[walk_4] = new LTexture(renderer);
			textures[walk_4]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk4.bmp", true, 0, 255, 255);
			textures[walk_5] = new LTexture(renderer);
			textures[walk_5]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk5.bmp", true, 0, 255, 255);
			textures[walk_6] = new LTexture(renderer);
			textures[walk_6]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/walk6.bmp", true, 0, 255, 255);
			textures[fire_1] = new LTexture(renderer);
			textures[fire_1]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/fire1.bmp", true, 0, 255, 255);			
			textures[fire_2] = new LTexture(renderer);
			textures[fire_2]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/fire2.bmp", true, 0, 255, 255);
			textures[fire_3] = new LTexture(renderer);
			textures[fire_3]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/fire3.bmp", true, 0, 255, 255);
			textures[fire_4] = new LTexture(renderer);
			textures[fire_4]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/fire4.bmp", true, 0, 255, 255);
			textures[stab_1] = new LTexture(renderer);
			textures[stab_1]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/stab1.bmp", true, 0, 255, 255);
			textures[stab_2] = new LTexture(renderer);
			textures[stab_2]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/stab2.bmp", true, 0, 255, 255);
			textures[stab_3] = new LTexture(renderer);
			textures[stab_3]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/stab3.bmp", true, 0, 255, 255);
			textures[stab_4] = new LTexture(renderer);
			textures[stab_4]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/stab4.bmp", true, 0, 255, 255);
			textures[stab_5] = new LTexture(renderer);
			textures[stab_5]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/stab5.bmp", true, 0, 255, 255);
			textures[sprites::arrow] = new LTexture(renderer);
			textures[sprites::arrow]->loadFromFile("C:/Users/stephen/Documents/Visual Studio 2015/Projects/Archer Battle/Assets/arrow.bmp", true, 0, 255, 255);


		}
		void Player::setSpawnLocation(int x, int y) {
			spawnx = x;
			spawny = y;
		}
		Player::~Player() {
			for (int i = 0; i < total_sprites; i++) {
				delete textures[i];
			}
		}
		void Player::handleControllerEvents(SDL_Event event) {
			if (dead) {
				return;
			}
			if (event.type == SDL_JOYAXISMOTION) {
				if (event.jaxis.which == 0) {
					if (event.jaxis.axis == 0) {
						if (event.jaxis.value < -8000) {
							xmotion = -1;
						}
						else if (event.jaxis.value > 8000) {
							xmotion = 1;
						}
						else {
							xmotion = 0;
						}
					}
					else if (event.jaxis.axis == 1) {
						if (event.jaxis.value < -8000) {
							ymotion = -1;
						}
						else if (event.jaxis.value > 8000) {
							ymotion = 1;
						}
						else {
							ymotion = 0;
						}
					}
					else if (event.jaxis.axis == 3) {
						if (event.jaxis.value > 8000) {
							lastPos = RIGHT;
							right = true;
						}
						else if (event.jaxis.value < -8000) {
							lastPos = LEFT;
							left = true;
						}
						else {
							left = false;
							right = false;
						}
					}
				}
			}
			else if (event.type == SDL_JOYBUTTONDOWN) {
				switch (event.jbutton.button) {
				case 9:
					if (jump) {
						break;
					}
					vely = 25;
					startTime = SDL_GetTicks();
					jump = true;
					break;
				case 2:
					stab = true;
					frame = 0;
					break;
				case 3:
					if (hitBox.x > 150 && hitBox.x < 480 && hitBox.y > 300 && hitBox.y < 549) {
						if (SDL_GetTicks() - holdStartTime >= 5000) {
							Mix_PlayChannel(0, pickup, 0);
							ammo = 24;
						}
					}
					break;
				case 8:
					if (fire == false) {
						firePos = lastPos;
					}
					fire = true;
					break;
				}
			}
			else if (event.type == SDL_JOYBUTTONUP) {
				switch (event.jbutton.button) {
				case 8:
					newArrow = true;
					release = true;
					break;
				}

			}
		}
		void Player::handleEvents(SDL_Event event) {
			if (dead) {
				return;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_d:
					right = true;
					lastPos = RIGHT;
					break;
				case SDLK_a:
					lastPos = LEFT;
					left = true;
					break;
				case SDLK_SPACE:
					if (jump) {
						break;
					}
					printf("Jump \n");
					vely = 25;
					startTime = SDL_GetTicks();
					jump = true;
					break;
				case SDLK_f:
					stab = true;
					stabKill = false;
					frame = 0;
					break;
				case SDLK_e:
					printf("e \n");
					if (hitBox.x > 150 && hitBox.x < 480 && hitBox.y > 300 && hitBox.y < 549) {
						if (SDL_GetTicks() - holdStartTime >= 5000) {
							Mix_PlayChannel(0, pickup, 0);
							ammo = 24;
						}
					}

				}
			}
			else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_d:
					right = false;
					break;
				case SDLK_a:
					left = false;
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (fire == false) {
					firePos = lastPos;
				}
				fire = true;
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				newArrow = true;
				release = true;
			}
			else if (event.type == SDL_MOUSEMOTION) {
				mx = event.motion.x;
				my = event.motion.y;
			}
		}
		void Player::handleArrows(SDL_Rect hurtBox, int & health, Tile * tiles[]) {
			int storedx = 0, storedy = 0;
			if (newArrow && dead == false) {
				Mix_PlayChannel(-1, arrowHit, 0);
				printf("New arrow \n");
				newArrow = false;
				if (--ammo < 0) {
					ammo = 0;
					return;
				}
				if (mx < hitBox.x && firePos == RIGHT) {
					mx = hitBox.x;
				}
				else if (mx > hitBox.x && firePos == LEFT) {
					mx = hitBox.x;
				}
				double angleX, angleY;
				arrows++;
				arrowPos.resize(arrows);
				arrowPos.back() = firePos;
				ax.resize(arrows);
				ay.resize(arrows);
				avx.resize(arrows);
				avy.resize(arrows);
				active.resize(arrows);
				angle.resize(arrows);
				visible.resize(arrows);
				visible.back() = true;
				if (mx > hitBox.x) {
					int vel = 17 * abs(mx - hitBox.x) * 0.002;
					avx.back() = (vel > 23 ? 23 : vel);
				}
				else if (mx < hitBox.x) {
					int vel = -17 * abs(mx - hitBox.x) * 0.002;
					avx.back() = vel < -23 ? -23 : vel;
				}
				active.back() = true;
				ay.back() = hitBox.y - 20;
				if (firePos == RIGHT) {
					ax.back() = hitBox.x + hitBox.w;
				}
				else {
					ax.back() = hitBox.x - hitBox.w;
				}
				avy.back() = 22 * (1080 - my) * 0.002;
				double newx = ax.back() - hitBox.x;
				double newy = ay.back() - hitBox.y;
				angle.back() = atan(newy / newx) * (180.0/M_PI);


			}
			for (int i = arrowStart; i < arrows; ++i) {
				if (arrows - arrowStart > 7) {
					arrowStart++;
				}
				if (visible.at(i) == false) {
					continue;
				}
				textures[sprites::arrow]->render(ax.at(i), ay.at(i), NULL, angle.at(i), NULL, arrowPos.at(i));
				if (active.at(i) == false) {
					continue;
				}
				if (ax.at(i) < -65 || ax.at(i) > 1990 || ay.at(i) > 1100) {
					active.at(i) = false;
				}
				avy.at(i) -= 1;
				ax.at(i) += avx.at(i);
				ay.at(i) -= avy.at(i);
				if (avy.at(i) == 0) {
					storedx = ax.at(i);
					storedy = ay.at(i);
				}
				double newx, newy;
				if (avy.at(i) < 0 && arrowPos.at(i) == RIGHT) {
					newx = ax.at(i) - storedx;
					newy = ay.at(i) - storedy;
				}
				else if (avy.at(i) < 0 && arrowPos.at(i) == LEFT) {
					newx = ax.at(i) - hitBox.x;
					newy = ay.at(i) - (hitBox.y - 300);
				}
				else {
					newx = ax.at(i) - hitBox.x;
					newy = ay.at(i) - hitBox.y;
				}
				angle.at(i) = atan(newy / newx) * (180.0 / M_PI);
				printf("Vely %d \n", avy.at(i));
				SDL_Rect arrow;
				if (arrowPos.at(i) == RIGHT) {
					arrow = { ax.at(i) + angle.at(i), ay.at(i) - angle.at(i), 65, 20 };
				}
				else {
					arrow = { ax.at(i) + 65 + angle.at(i), ay.at(i) + angle.at(i), 65, 20 };
				}
				if (arrow.x > (hurtBox.x - arrow.w) && arrow.x < (hurtBox.x + hurtBox.w) && arrow.y >(hurtBox.y - arrow.h) && arrow.y < (hurtBox.y + hurtBox.h)) {
					active.at(i) = false;
					visible.at(i) = false;
					Mix_PlayChannel(0, ah, 0);
					health -= 20;
				}
				for (int t = 0; t <= 42; t++) {
					if (arrow.x > (tiles[t]->getHitBox().x - arrow.w) && arrow.x < (tiles[t]->getHitBox().x + tiles[t]->getHitBox().w) && arrow.y > (tiles[t]->getHitBox().y - arrow.h) && arrow.y < tiles[t]->getHitBox().y + tiles[t]->getHitBox().h) {
						active.at(i) = false;
						Mix_PlayChannel(-1, arrowHit2, 0);
					}


				}
			}
		}
		void Player::renderCross() {
			if (xmotion == 1) {
				mx += 15;
			}
			else if (xmotion == -1) {
				mx -= 15;
			}
			if (ymotion == 1) {
				my += 15;
			}
			else if (ymotion == -1) {
				my -= 15;
			}
			if (mx < 0) {
				mx = 0;
			}
			else if (mx > 1920 - 40) {
				mx = 1880;
			}
			if (my < 0) {
				my = 0;
			}
			else if (my > 1040) {
				my = 1040;
			}
			cross.render(mx, my);
		}
		void Player::render() {
			textures[sprites::arrow]->render(325, 439, NULL, 315.0);
			if (dead) {
				return;
			}
			idT.render(hitBox.x + 30, hitBox.y - 30);
			if (stab) {
				if (lastPos == RIGHT) {
					textures[stab_1 + (frame / 10)]->render(hitBox.x, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				else {
					textures[stab_1 + (frame / 10)]->render(hitBox.x - 70, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				frame++;
				if (frame > (49)) {
					stab = false;
					frame = 0;
				}
			}
			else if (fire) {
				if (ammo < 0) {
					return;
				}
				if (fireFrame > 35 && release == false) {
					fireFrame = 35;
				}
				if (firePos == RIGHT) {
					textures[fire_1 + (fireFrame / 12)]->render(hitBox.x, hitBox.y, NULL, 0.0, NULL, firePos);
				}
				else {
					textures[fire_1 + (fireFrame / 12)]->render(hitBox.x - 70, hitBox.y, NULL, 0.0, NULL, firePos);
				}
				fireFrame++;
				if (fireFrame > 59) {
					fire = false;
					release = false;
					fireFrame = 0;
				}
			}
			else if (jump) {
				if (lastPos == RIGHT) {
					textures[stab_1]->render(hitBox.x, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				else {
					textures[stab_1]->render(hitBox.x - 70, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
			}
			else if (right || left) {
				if (frame > 47) {
					frame = 0;
				}
				if (lastPos == RIGHT) {
					textures[walk_1 + (frame / 8)]->render(hitBox.x, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				else {
					textures[walk_1 + (frame / 8)]->render(hitBox.x - 70, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				frame++;

			}
			else {
				if (lastPos == RIGHT) {
					textures[idle]->render(hitBox.x, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
				else {
					textures[idle]->render(hitBox.x - 30, hitBox.y, NULL, 0.0, NULL, lastPos);
				}
			}

		}
		void Player::checkBounds(int screen_width, int screen_height) {
			if (hitBox.x < 0) {
				hitBox.x= 0;
			}
			else if (hitBox.x > screen_width - hitBox.w) {
				hitBox.x = screen_width - hitBox.w;
			}
			if (hitBox.y < 0) {
				hitBox.y = 0;
			}
			else if (hitBox.y > screen_height - hitBox.h) {
				hitBox.y = screen_height - hitBox.w;
			}
		}
		void Player::loadGui(points & score) {
			if (health <= 0) {
				health = 100;
				score.player2++;
				dead = true;
				respawnTimeStart = SDL_GetTicks();

			}
			if (dead) {
				if (SDL_GetTicks() - respawnTimeStart >= 5000) {
					hitBox.x = spawnx;
					hitBox.y = spawny;
					dead = false;
				}
			}
			int length = health * 3;
			SDL_Color color = { 0x0, 0x0, 0x0, 0xFF };
			color.r = 0x0;
			color.b = 0x0;
			color.g = 0x0;
			color.a = 0xFF;
			ammoT.loadFromRenderedText(std::to_string(ammo));
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
			SDL_Rect health = {100, 100, (length), 20};
			SDL_RenderFillRect(renderer, &health);
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_Rect bar = { 100, 100, 300, 20 };
			SDL_RenderDrawRect(renderer, &bar);
			textures[sprites::arrow]->render(120, 130, NULL, 320.0);
			ammoT.render(200, 170);


		}
		void Player::loadControllerGui(points & score) {
			if (health <= 0) {
				health = 100;
				score.player1++;
				dead = true;
				respawnTimeStart = SDL_GetTicks();

			}
			if (dead) {
				if (SDL_GetTicks() - respawnTimeStart >= 5000) {
					hitBox.x = spawnx;
					hitBox.y = spawny;
					dead = false;
				}
			}
			int length = health * 3;
			SDL_Color color = { 0x0, 0x0, 0x0, 0xFF };
			color.r = 0x0;
			color.b = 0x0;
			color.g = 0x0;
			color.a = 0xFF;
			ammoT.loadFromRenderedText(std::to_string(ammo));
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
			SDL_Rect health = { 1520, 100, (length), 20 };
			SDL_RenderFillRect(renderer, &health);
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_Rect bar = { 1520, 100, 300, 20 };
			SDL_RenderDrawRect(renderer, &bar);
			textures[sprites::arrow]->render(1600, 130, NULL, 320.0);
			ammoT.render(1720, 170);


		}
		void Player::reset() {
			arrows = 0;
			jump = false;
			hitBox.x = spawnx;
			hitBox.y = spawny;
			crossX = 0;
			crossY = 0;
			velx = 0;
			vely = 0;
			ax.empty();
			ay.empty();
			avx.empty();
			avy.empty();
			visible.empty();
			active.empty();
			angle.empty();
			arrowPos.empty();
			frame = 0;
			fireFrame = 0;
			stab = false;
			dead = false;
			fire = false;
			release = false;
			left = false;
			right = false;
			arrowStart = 0;

		}
		void Player::aiMove(Tile * tiles[], SDL_Rect & otherhurtBox, int & otherhealth) {
			if (dead) {
				return;
			}
			if (otherhurtBox.x < hitBox.x && aiWaterCol == false) {
				left = true;
				lastPos = LEFT;
			}
			if (otherhurtBox.x > hitBox.x) {
				right = true;
				lastPos = RIGHT;
			}
			if (dist(otherhurtBox.x, otherhurtBox.y, hitBox.x, hitBox.y) < 400) {
				left = false;
				right = false;
				mx = otherhurtBox.x;
				my = otherhurtBox.y;
				if (aiFireable) {
					aiFireable = false;
					firePos = lastPos;
					aiFireTime = SDL_GetTicks();
					fire = true;
					release = true;
					newArrow = true;
				}
				else {
					fire = false;
					release = false;
					newArrow = false;
				}
				if (SDL_GetTicks() - aiFireTime >= 3000) {
					aiFireable = true;
				}
				if (dist(otherhurtBox.x, otherhurtBox.y, hitBox.x, hitBox.y) < 100) {
					stab = true;
				}
				else {
					stab = false;
				}
			}
			if (aiXCol == true) {
				jump = true;
			}
			if (aiWaterCol) {
				jump = true;
				left = true;
			}
			if (otherhurtBox.y < hitBox.y) {
				jump = true;
			}
			if ((tileDist(tiles[10], hitBox.x, hitBox.y) < 200 || tileDist(tiles[11], hitBox.x, hitBox.y) < 200 || tileDist(tiles[28], hitBox.x, hitBox.y) < 200) && (left || right)) {
				jump = true;
			}
		}
		void Player::move(int elapsed, Tile * tiles[], SDL_Rect & otherhurtBox, int & otherhealth) {
			if (dead) {
				return;
			}
			if (fire || stab || release) {
				right = false;
				left = false;
			}
			if (right == true) {
				velx = 5;
			}
			else if (left == true) {
				velx = -5;
			}
			else {
				velx = 0;
			}
			if (stab) {
				if (lastPos == LEFT && stabKill != true) {
					SDL_Rect left = { hitBox.x - 50, hitBox.y, 50, 25 };
					if(!(left.x < otherhurtBox.x - left.w || left.x > otherhurtBox.x + otherhurtBox.w || left.y < otherhurtBox.y - left.h || left.y > otherhurtBox.y + otherhurtBox.h)) {
						otherhurtBox.x -= 75;
						otherhealth -= 50;
						Mix_PlayChannel(0, ah, 0);
						stabKill = true;
					}
				}
				else if(lastPos == RIGHT && stabKill != true){
					SDL_Rect right = { hitBox.x + 50, hitBox.y, 50, 25 };
					if (!(right.x < otherhurtBox.x - right.w || right.x > otherhurtBox.x + otherhurtBox.w || right.y < otherhurtBox.y - right.h || right.y > otherhurtBox.y + otherhurtBox.h)) {
						otherhurtBox.x += 75;
						otherhealth -= 50;
						Mix_PlayChannel(0, ah, 0);
						stabKill = true;
					}
				}
			}
			int gDuration = SDL_GetTicks() - airStartTime;
			int jumpTime = 0;
			if (jump) {
				jumpTime = SDL_GetTicks() - startTime;
				vely -= 1;
				hitBox.y -= vely;
			}
			else {
				//hitBox.y += (3 * gDuration * 0.02) * (elapsed * 0.06);
				gy++;
				hitBox.y += gy;
			}
			bool stepable = false;
			for (int i = 0; i <= 42; i++) {
				if ((hitBox.x > (tiles[i]->getHitBox().x + tiles[i]->getHitBox().w)) || (hitBox.x < (tiles[i]->getHitBox().x - hitBox.w)) || (hitBox.y > (tiles[i]->getHitBox().y + tiles[i]->getHitBox().h)) || (hitBox.y < (tiles[i]->getHitBox().y - hitBox.h))) {
					aiYCol = false;
					aiWaterCol = false;
					continue;
				}
				else {
					aiYCol = true;
					if (i == 41) {
						onWood = true;
					}
					else {
						onWood = false;
					}
					stepable = true;
					if (tiles[i]->getDamage() != 0) {
						aiWaterCol = true;
						stepable = false;
						if (jump) {
							hitBox.y -= 60;
						}
						jump = false;
						vely = 25;
						gy = 0;
						if (damagable) {
							health -= tiles[i]->getDamage();
							Mix_PlayChannel(0, ah, 0);
							damagable = false;
							damageCounter = SDL_GetTicks();
						}
						if (SDL_GetTicks() - damageCounter >= 500) {
							damagable = true;
						}
						continue;
					}
					airStartTime = SDL_GetTicks();
					startTime = SDL_GetTicks();
					if (jump) {
						hitBox.y += vely;
					}
					else {
						//hitBox.y -= (3 * gDuration * 0.02) * (elapsed * 0.06);
						hitBox.y -= gy;
					}
					jump = false;
					vely = 25;
					gy = 0;
				}
			}
			hitBox.x += velx;
			for (int i = 0; i <= 42; i++) {
				if ((hitBox.x >(tiles[i]->getHitBox().x + tiles[i]->getHitBox().w)) || (hitBox.x < (tiles[i]->getHitBox().x - hitBox.w)) || (hitBox.y >(tiles[i]->getHitBox().y + tiles[i]->getHitBox().h)) || (hitBox.y < (tiles[i]->getHitBox().y - hitBox.h))) {
					aiXCol = false;
					aiWaterCol = false;
					continue;
				}
				else {
					aiXCol = true;
					if (tiles[i]->getDamage() != 0) {
						aiWaterCol = true;
						stepable = false;
						if (damagable) {
							health -= tiles[i]->getDamage();
							damagable = false;
							damageCounter = SDL_GetTicks();
						}
						if (SDL_GetTicks() - damageCounter >= 500) {
							damagable = true;
						}
						continue;
					}
					//airStartTime = SDL_GetTicks();
					//startTime = SDL_GetTicks();
					hitBox.x -= velx;
				}
			}
			if (velx != 0 && stepable) {
				if (onWood) {
					Mix_PlayChannel(-1, woodstep, 0);
				}
				else {
					Mix_PlayChannel(-1, step, 0);
				}
			}
			

		}
		int arrows = 0;
		int holdStartTime;
		bool hold = false;
		int mx, my;
		std::vector<int> ax, ay, avx, avy, angle;
		std::vector<bool> active;
		std::vector<SDL_RendererFlip> arrowPos;
		double velx, vely, gy;
		int crossX = 0, crossY = 0;
		int xmotion = 0, ymotion = 0;
		int spawnx, spawny;
		bool left = false, right = false, jump = false, stab = false, fire = false;
		int health = 100;
		Uint8 id = 0;
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
}