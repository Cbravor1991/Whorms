#include "view.h"

#include <iostream>
GameView::GameView(): sdl(SDL_INIT_VIDEO), window("Worms",SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE),
                        renderer(window, -1, SDL_RENDERER_ACCELERATED)
{
    renderer.SetDrawColor(100, 149, 237, 0);//seteo el color de fondo
}

    
void GameView::mostrar() {
    renderer.Present();
}
void GameView::clear() {
    renderer.Clear();
}

SDL2pp::Renderer& GameView::getRenderer() {
    return this->renderer;
}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y) {

    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 12);

    SDL2pp::Texture texto_sprite(
            renderer,
            font.RenderText_Blended(texto, SDL_Color{255, 255, 255, 255})
        );

	renderer.Copy(texto_sprite, SDL2pp::NullOpt, 
                    SDL2pp::Rect(0, 0, texto_sprite.GetWidth(), texto_sprite.GetHeight()));
}

//con el for agarra el jugador y se lo manda a render y renderiza
void GameView::renderizar_gusano(JugadorDTO  jugador){
    Texture sprites(renderer, Surface(DATA_PATH "/sprites/worm/walk/wwalk.png")
			.SetColorKey(true, 0));

    int pos_x =  jugador.x;
    int pos_y = jugador.y;

 
		

        int src_x = 0, src_y = 0; // by default, standing sprite
		if (jugador.is_running) {
			
			src_y =  60 * jugador.run_phase;
		}
    if (jugador.direccion)
    {
        	renderer.Copy(
				sprites,
				Rect(src_x, src_y, 60, 60), // que parte del spike queres que te cargue
				Rect(pos_x, 200 - pos_y, 50, 50), // la posicion en pantalla y el tamaño
				0.0,              // don't rotate
				NullOpt,          // rotation center - not needed
				SDL_FLIP_HORIZONTAL // vertical flip
			);

    } else {

        renderer.Copy(
				sprites,
				Rect(src_x, src_y, 60, 60), // que parte del spike queres que te cargue
				Rect(pos_x, 200 - pos_y, 50, 50), // la posicion en pantalla y el tamaño
				0.0,              // don't rotate
				NullOpt,          // rotation center - not needed
				SDL_FLIP_NONE // vertical flip
        );


    }    }


    void GameView::renderizar_viga(VigaDTO viga){
        int pos_x =  viga.x;
        int pos_y = viga.y;

  // 140 20 70 20
  
  
  if(viga.tipo ){    
        Texture sprites(renderer, Surface(DATA_PATH "/sprites/vigas/grdl4.png"));
         renderer.Copy(
				sprites,
				Rect(0, 0, 140, 20), // que parte del spike queres que te cargue
				Rect(pos_x, 220 - pos_y, 140, 20), // la posicion en pantalla y el tamaño
				0.0,              // don't rotate
				NullOpt,          // rotation center - not needed
				SDL_FLIP_HORIZONTAL // vertical flip
			);

	
  }

  else {
     Texture sprites(renderer, Surface(DATA_PATH "/sprites/vigas/grds4.png"));
       renderer.Copy(
				sprites,
				Rect(0, 0, 70, 20), // que parte del spike queres que te cargue
				Rect(pos_x, 220 - pos_y, 70, 20), // la posicion en pantalla y el tamaño
				0.0,              // don't rotate
				NullOpt,          // rotation center - not needed
				SDL_FLIP_HORIZONTAL // vertical flip
			);
  }


       
    


}


