#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *win;
SDL_Surface *screen, *image;
int iwidth, iheight, wwidth, wheight;

void
iv_error(const char *str)
{
	fflush(stdout);
	fprintf(stderr, "ERROR: %s\n", str);
	fflush(stderr);
	exit(1);
}

void
update(void)
{
	screen = SDL_GetWindowSurface(win);
	SDL_BlitSurface(image, NULL, screen, NULL);
	SDL_UpdateWindowSurface(win);
}

void
load_image(const char *f)
{
	image = IMG_Load(f);
	if (image == NULL)
		iv_error("Failed to load image.");

	wwidth = iwidth = image->w;
	wheight = iheight = image->h;
	SDL_SetWindowSize(win, wwidth, wheight);
	SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	update();
}

int
main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		iv_error("Failed to initialize SDL.");
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		iv_error("Failed to initialize SDL_image.");

	if (argc < 2) {
		puts("usage: iv [image]");
		exit(0);
	}

	win = SDL_CreateWindow("iv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                       320, 240, SDL_WINDOW_SHOWN);
	if (win == NULL)
		iv_error("Failed to initialize SDL window.");

	load_image(argv[1]);
	if (image == NULL)
		iv_error("Failed to initialize image surface. (1)");

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_WINDOWEVENT:
				update();
				break;
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE)
					exit(0);
				break;
			}
		}
	}
	return 0;
}
