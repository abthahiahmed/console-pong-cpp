#include <iostream>
#include <SDL2/SDL.h>

#define WIDTH 70
#define HEIGHT 20

using namespace std;

SDL_Window *win = SDL_CreateWindow("PING PONG | Abthahi & Programming", 800, 400, 100, 100, 0);
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
SDL_Event event;


int main(int argc, char* argv[]){
	
	bool isRunning = true;
	
	int map[HEIGHT][WIDTH];
	
	
	for (int j = 0; j < HEIGHT; j++){
		for (int i = 0; i < WIDTH; i++){
			
			map[j][i] = 0;
		
		}
	}
	
	int p1x = 1, p1y = 9;
	int p2x = WIDTH - 2, p2y = 9;	
	int ballx = WIDTH / 2, bally = HEIGHT / 2;
	int ballvx = 1, ballvy = 1;
	
	for (int i = p1y; i < p1y + 3; i++){
		map[i][p1x] = 1;
	}
	for (int i = p2y; i < p2y + 3; i++){
		map[i][p2x] = 1;
	}
	
	map[bally][ballx] = 2;
	int t = 0;
	
	int p1_score = 0;
	int p2_score = 0;
	
	
	while(isRunning){
		
		system("clear"); // For linux "clear" and for windows "cls"
		
		map[bally][ballx] = 2;
		
		
		// Output
		for (int i = 0; i < WIDTH + 2; i++) cout<<"%";
		cout<<endl;
		for (int j = 0; j < HEIGHT; j++){
			cout<<"%";
			for (int i = 0; i < WIDTH; i++){
				
				if (i == WIDTH / 2){
					cout<<"|";
				}else{
					if (map[j][i] == 0){
						cout<<" ";
					}
					else if (map[j][i] == 1){
						cout<<"#";
					}
					else if (map[j][i] == 2){
						cout<<"o";
					}
				}
			}
			cout<<"%"<<endl;
		}
		for (int i = 0; i < WIDTH + 2; i++) cout<<"%";
		cout<<endl;	
		cout<<"Player 1 : "<<p1_score<<"\t\t\tPlayer 2 : "<<p2_score<<endl;
		cout<<flush;
		
		if(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				isRunning = false;
			}
			
			if (event.type == SDL_KEYDOWN){
				
				if (event.key.keysym.sym == SDLK_UP){
					for (int i = p2y; i < p2y + 3; i++){
						map[i][p2x] = 0;
					}
					if (p2y > 0) p2y--;
					for (int i = p2y; i < p2y + 3; i++){
						map[i][p2x] = 1;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN){
					for (int i = p2y; i < p2y + 3; i++){
						map[i][p2x] = 0;
					}
					if (p2y + 2 < HEIGHT - 1) p2y++;
					for (int i = p2y; i < p2y + 3; i++){
						map[i][p2x] = 1;
					}
				}
				if (event.key.keysym.sym == SDLK_w){
					for (int i = p1y; i < p1y + 3; i++){
						map[i][p1x] = 0;
					}
					if (p1y > 0) p1y--;
					for (int i = p1y; i < p1y + 3; i++){
						map[i][p1x] = 1;
					}
				}
				else if (event.key.keysym.sym == SDLK_s){
					for (int i = p1y; i < p1y + 3; i++){
						map[i][p1x] = 0;
					}
					if (p1y + 2 < HEIGHT - 1) p1y++;
					for (int i = p1y; i < p1y + 3; i++){
						map[i][p1x] = 1;
					}
				}			
			
			}
		}
		
		// Ball Logic
		
		if (map[bally][ballx] != 1) map[bally][ballx] = 0;
		
		if (t > 10){
			ballx += ballvx;
			bally += ballvy;
			t = 0;
		}
		
		if (ballx < WIDTH - 1 && map[bally][ballx + 1] == 1) ballvx *= -1;
		if (ballx > 0 && map[bally][ballx - 1] == 1) ballvx *= -1;
		
		if (ballx == WIDTH - 1){
			p1_score++;
			ballx = WIDTH / 2, bally = HEIGHT / 2;
		}
		if (ballx == 0){
			p2_score++;
			ballx = WIDTH / 2, bally = HEIGHT / 2;
		}
		
		if (ballx >= WIDTH - 1 || ballx <= 0) ballvx *= -1; 
		if (bally >= HEIGHT - 1 || bally <= 0) ballvy *= -1; 
		
		
		SDL_RenderPresent(ren);
		
		SDL_Delay(20);
		t++;
	}
	
	
	
	return 0;
}