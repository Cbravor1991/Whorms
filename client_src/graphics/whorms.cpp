#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <thread>

#include "whorms.h"




Whorms::Whorms()

{
    is_running = false;
}


 Texture Whorms::loadSprite(Renderer& render, std::string path)
{
   Texture sprites(render, path);
    return  sprites;
}

bool Whorms::estadoDelGusano(){
    return is_running;
}

void Whorms::seguirCorriendo(){
    is_running = true;

}

void Whorms::dejarDeCorrer(){
    is_running = false;

}

int Whorms::renderizar(Renderer& renderer,  Texture& sprites){try{
     // Game state
	// whether the character is currently running
	int run_phase = -1;      // run animation phase
	float position = 0.0;    // player position

    unsigned int prev_ticks = SDL_GetTicks();
	// Main loop
	
		// Timing: calculate difference between this and previous frame
		// in milliseconds
		unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;

		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
		// - If Right key is pressed, character would run
		// - If Right key is released, character would stop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				case SDLK_RIGHT: is_running = true; break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: is_running = false; break;
				}
			}
		}

		// Update game state for this frame:
		// if character is runnung, move it to the right
		if (is_running) {
			position += frame_delta * 0.2;
			run_phase = (frame_ticks / 100) % 8;
		} else {
			run_phase = 0;
		}

		// If player passes past the right side of the window, wrap him
		// to the left side
		if (position > renderer.GetOutputWidth())
			position = -50;

		int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center

		// Clear screen
		//renderer.Clear();

		// Pick sprite from sprite atlas based on whether
		// player is running and run animation phase
		int src_x = 8, src_y = 11; // by default, standing sprite
		if (is_running) {
			// one of 8 run animation sprites
			src_x = 8 + 51 * run_phase;
			src_y = 67;
		}

		// Draw player sprite
		renderer.Copy(
				sprites,
				Rect(src_x, src_y, 50, 50),
				Rect((int)position, vcenter - 50, 50, 50)
			);

		// Show rendered frame
		renderer.Present();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
	

	// Here all resources are automatically released and library deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}

}



Whorms::~Whorms() {}