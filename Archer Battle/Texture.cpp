#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>
namespace archer {
	class Texture {
	public:
		Texture() {
			texture = NULL;
			width = 0;
			height = 0;
			printf("Loading texture \n");
		}
		~Texture() {
			SDL_DestroyTexture(texture);
		}
		void setRenderer(SDL_Renderer * renderer) { this->renderer = renderer; }
		void render(int x, int y, SDL_Rect * clip = NULL, double angle = 0.0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Rect renderRect = { x, y, width, height };
			if (clip != NULL) {
				renderRect.w = clip->w;
				renderRect.h = clip->h;
			}
			printf(texture == NULL ? "Rendering a null texture \n" : "Rendering a texture \n");
			SDL_RenderCopyEx(renderer, texture, clip, &renderRect, angle, center, flip);
		}
		void loadFromFile(std::string path, bool colorKey = false, Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0) {
			SDL_DestroyTexture(texture);
			SDL_Texture * newTexture;
			SDL_Surface * loadedSurface = IMG_Load(path.c_str());
			printf(loadedSurface != NULL ? "Surface is not null \n" : "Surface is null \n");
			if (colorKey) {
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue));
			}
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			this->texture = newTexture;
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
			SDL_FreeSurface(loadedSurface);
			printf(newTexture != NULL ? "Texture is not null \n" : "Texture is null \n");
			SDL_DestroyTexture(newTexture);


		}
		void enableBlending() {
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
		void loadFromText(std::string text, std::string path, SDL_Color textColor, int size) {
			this->textColor = textColor;
			font = TTF_OpenFont(path.c_str(), size);
			SDL_Surface * textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
			this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			width = textSurface->w;
			height = textSurface->h;
			SDL_FreeSurface(textSurface);
		}
		void changeText(std::string text) {
			SDL_Surface * textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
			this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			width = textSurface->w;
			height = textSurface->h;
			SDL_FreeSurface(textSurface);
		}
		int getHeight() { return height; }
		int getWidth() { return width; }
	private:
		SDL_Texture * texture;
		SDL_Renderer * renderer;
		TTF_Font * font;
		SDL_Color textColor;
		int width;
		int height;


	};
}