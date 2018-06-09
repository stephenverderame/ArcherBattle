#include "LTexture.cpp"
#include <SDl.h>
namespace archer {
	class Tile{
	public:
		Tile(bool passArguments = false, int x = 0, int y = 0, int w = 0, int h = 0, Uint8 damage = 0, LTexture * texture = NULL) {
			if (passArguments) {
				this->texture = texture;
				hitBox.x = x;
				hitBox.y = y;
				hitBox.w = w;
				hitBox.h = h;
				this->damage = damage;
			}
		}
		void setRenderer(SDL_Renderer * renderer) {
			texture->setRenderer(renderer);
		}
		void createTile(int x, int y, int w, int h, Uint8 damage, LTexture * texture) {
			this->texture = texture;
			hitBox.x = x;
			hitBox.y = y;
			hitBox.w = w;
			hitBox.h = h;
			this->damage = damage;
		}
		SDL_Rect getHitBox() { return hitBox; }
		void setHitBox(int x, int y, int w, int h) {
			hitBox.x = x;
			hitBox.y = y;
			hitBox.w = w;
			hitBox.h = h;
		}
		void setDamagable(Uint8 damage) {
			this->damage = damage;
		}
		Uint8 getDamage() { return damage; }
		void setTexture(LTexture * texture) { this->texture = texture; }
		void setImageOffset(int offset) {
			imageOffset = offset;
		}
		bool render() {
			texture->render(hitBox.x + imageOffset, hitBox.y);
			return true;
		}
		LTexture * getTexture() { return texture; }
	private:
		SDL_Rect hitBox;
		int imageOffset = 0;
		Uint8 damage;
		LTexture * texture;

	};
}
