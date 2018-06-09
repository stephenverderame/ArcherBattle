#ifndef LTEXTURE
#define LTEXTURE
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
namespace archer {
	class LTexture {
	public:
		LTexture(SDL_Renderer * renderer = NULL) {
			this->renderer = renderer;
			texture = NULL;
			width = 0;
			height = 0;
			
		}
		void setRenderer(SDL_Renderer * renderer) { this->renderer = renderer; }
		~LTexture() {
			free();
		}
		bool loadFromFile(std::string path, bool colorKey = false, Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0) {
			free();
			SDL_Texture * newTexture;
			SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());
			printf(loadedSurface == NULL ? "surface is null \n" : "surface is not null\n");
			if (colorKey) {
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue));
			}
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			width = loadedSurface->w;
			height = loadedSurface->h;
			SDL_FreeSurface(loadedSurface);
			this->texture = newTexture;
			printf(newTexture == NULL ? "texture is null \n" : "false \n");
			if (newTexture == NULL) {
				printf("Texture Error: ", SDL_GetError(), "\n");
			}
			return (texture != NULL);
		}
		void free() {
			if (texture != NULL) {
				SDL_DestroyTexture(texture);
				texture = NULL;
				width = 0;
				height = 0;
			}

		}
		void enableBlend() {
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
		void setAlpha(Uint8 alpha) {
			SDL_SetTextureAlphaMod(texture, alpha);

		}
		void setColor(Uint8 red, Uint8 green, Uint8 blue) {
			SDL_SetTextureColorMod(texture, red, green, blue);
		}
		void renderBasic(int x, int y, SDL_Rect * clip = NULL) {
			SDL_Rect renderQuad = { x, y, this->width, this->height };
			if (clip != NULL) {
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			SDL_RenderCopy(renderer, texture, clip, &renderQuad);
		}
		bool render(int x, int y, SDL_Rect * clip = NULL, double angle = 0.0,
			SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Rect renderQuad = { x, y, width, height };
			if (clip != NULL) {
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
			return texture != NULL;
		}
		bool loadFont(std::string fontPath, SDL_Color textColor, int size) {
			free();
			TTF_Font * font = TTF_OpenFont(fontPath.c_str(), size);
			this->color = textColor;
			this->font = font;
			return font != NULL;
		}
		bool loadFromRenderedText(std::string textureText) {
			int b = 1;
			try {
				free();
				SDL_Surface * textSurface = TTF_RenderText_Solid(font, textureText.c_str(), color);
				if (textSurface == NULL) {
					throw b;
				}
				texture = SDL_CreateTextureFromSurface(renderer, textSurface);
				width = textSurface->w;
				height = textSurface->h;
				SDL_FreeSurface(textSurface);
				return texture != NULL;
			}
			catch (int b) {
				printf("Surface is null \n");
			}
		}
		int getWidth() { return width; }
		int getHeight() { return height; }
	private:
		SDL_Texture * texture;
		SDL_Renderer * renderer;
		TTF_Font * font;
		SDL_Color color;
		int width;
		int height;

	};
}
#endif