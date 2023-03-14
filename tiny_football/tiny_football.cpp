#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Utility.hpp"
#include "ScrollingBG.hpp"
#include "Ball.hpp"
#include "BluePlayer.hpp"

#define FPS		30

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	TTF_Init();
	return true;
}

bool SDLinit = init();

RenderWindow window("TINY FOOTBALL", 1520, 720); 


SDL_Texture* hockeyTexture = window.loadTexture("assets/hockey.png", ColorRGB(140, 254, 186));
SDL_Texture* rinkTexture = window.loadTexture("assets/rink.png", ColorRGB(140, 254, 186));


bool gameRunning = true;
bool singlePlayer = true;
bool secondPlayer = false;

int gameState = 0;

SDL_Event event;
const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);


//fps
int desiredDelta = 1000 / FPS;
int startLoop = 0;
int endLoop = 0;

//Background
ScrollingBG background = ScrollingBG(Vector2f(50, 70), rinkTexture, SDL_Rect{ 8,8,704,192 }, Vector2f(2, 2));

//Red Player
SDL_Rect redPlayerClip[15] = {
		SDL_Rect{4,4,16,16},
		SDL_Rect{24,4,16,16},
		SDL_Rect{44,4,16,16},
		SDL_Rect{64,4,16,16},
		SDL_Rect{84,4,16,16},
		SDL_Rect{104,4,16,16},
		SDL_Rect{124,4,16,16},
		SDL_Rect{144,4,16,16},
		SDL_Rect{164,4,16,16},
		SDL_Rect{184,4,16,16},
		SDL_Rect{200,0,20,20},
		SDL_Rect{220,0,20,20},
		SDL_Rect{240,0,20,20},
		SDL_Rect{260,0,20,20},
		SDL_Rect{280,0,20,20}
};
Player player1 = Player(Vector2f(300, 200),hockeyTexture, SDL_Rect{ 0,0, 16,16 }, Vector2f(2, 2), redPlayerClip);
Player goalKeeper1 = Player(Vector2f(300, 200), hockeyTexture, SDL_Rect{ 0,0, 16,16 }, Vector2f(2, 2), redPlayerClip);

//Blue Player
SDL_Rect bluePlayerClip[15] = {
		SDL_Rect{4,24,16,16},
		SDL_Rect{24,24,16,16},
		SDL_Rect{40,24,16,16},
		SDL_Rect{60,24,16,16},
		SDL_Rect{80,24,16,16},
		SDL_Rect{104,24,16,16},
		SDL_Rect{124,24,16,16},
		SDL_Rect{144,24,16,16},
		SDL_Rect{164,24,16,16},
		SDL_Rect{184,24,16,16},
		SDL_Rect{200,0,20,20},
		SDL_Rect{220,0,20,20},
		SDL_Rect{240,0,20,20},
		SDL_Rect{260,0,20,20},
		SDL_Rect{280,0,20,20}
};
BluePlayer player2 = BluePlayer(Vector2f(0, 0), hockeyTexture, SDL_Rect{ 0,0, 16,16 }, Vector2f(2, 2), bluePlayerClip);
BluePlayer goalKeeper2 = BluePlayer(Vector2f(0, 0), hockeyTexture, SDL_Rect{ 0,0, 16,16 }, Vector2f(2, 2), bluePlayerClip);

//Arrow
Entity arrow1 = Entity(Vector2f(0, 0), hockeyTexture, SDL_Rect{ 16,280,8,8 }, Vector2f(2, 2), Vector2f(0, 0));
Entity arrow2 = Entity(Vector2f(0, 0), hockeyTexture, SDL_Rect{ 16,280,8,8 }, Vector2f(2, 2), Vector2f(0, 0));

void updateArrowPosition(Entity& arrow, Entity& p_entity) {
	arrow.setPos(Vector2f(p_entity.getPos().x + 4, p_entity.getPos().y - 25));
}

//Ball
Ball ball = Ball(Vector2f(300, 300), hockeyTexture, SDL_Rect{ 4,280, 8,8 }, Vector2f(2, 2));

//GetPointArea
SDL_Rect getPointArea1 = SDL_Rect{ background.getPos().x + 72 * background.getScale().x , background.getPos().y + 80 * background.getScale().y, 20 ,80};
SDL_Rect getPointArea2 = SDL_Rect{ background.getPos().x + 614 * background.getScale().x , background.getPos().y + 80 * background.getScale().y, 20 ,80 };

//Game variable
int point1 = 0;
int point2 = 0;
TTF_Font* Pixel = TTF_OpenFont("font/Pixel.ttf", 24);

SDL_Color White = { 255, 255, 255 };

void resetLocation() 
{
	player2.setPos(Vector2f(880, 250));
	player2.setVelocity(Vector2f(0, 0));
	player2.isActive = true;
	player2.updateClip();

	player1.setPos(Vector2f(600, 250));
	player1.setVelocity(Vector2f(0, 0));
	player1.isActive = true;

	goalKeeper1.setPos(Vector2f(250, 250));
	goalKeeper1.setVelocity(Vector2f(0, 0));
	goalKeeper1.isActive = false;

	goalKeeper2.setPos(Vector2f(1200, 250));
	goalKeeper2.setVelocity(Vector2f(0, 0));
	goalKeeper2.isActive = false;
	goalKeeper2.updateClip();

	updateArrowPosition(arrow1, player1);
	updateArrowPosition(arrow2, player2);

	ball.updatePos(747,255);
	ball.setVelocity(Vector2f(0,0));
};

void resetLocationBlue()
{
	player2.setPos(Vector2f(1150, 180));
	player2.setVelocity(Vector2f(0, 0));
	player2.isActive = true;

	player1.setPos(Vector2f(1016, 180));
	player1.setVelocity(Vector2f(0, 0));
	player1.isActive = true;

	goalKeeper1.setPos(Vector2f(250, 250));
	goalKeeper1.setVelocity(Vector2f(0, 0));
	goalKeeper1.isActive = false;

	goalKeeper2.setPos(Vector2f(1200, 250));
	goalKeeper2.setVelocity(Vector2f(0, 0));
	goalKeeper2.isActive = false;

	updateArrowPosition(arrow1, player1);
	updateArrowPosition(arrow2, player2);

	ball.updatePos(1090, 180);
	ball.setVelocity(Vector2f(0, 0));
};

void resetLocationRed()
{
	player2.setPos(Vector2f(443, 180));
	player2.setVelocity(Vector2f(0, 0));
	player2.isActive = true;

	player1.setPos(Vector2f(310, 180));
	player1.setVelocity(Vector2f(0, 0));
	player1.isActive = true;

	goalKeeper1.setPos(Vector2f(250, 250));
	goalKeeper1.setVelocity(Vector2f(0, 0));
	goalKeeper1.isActive = false;

	goalKeeper2.setPos(Vector2f(1200, 250));
	goalKeeper2.setVelocity(Vector2f(0, 0));
	goalKeeper2.isActive = false;

	updateArrowPosition(arrow1, player1);
	updateArrowPosition(arrow2, player2);

	ball.updatePos(386, 180);
	ball.setVelocity(Vector2f(0, 0));
};

void delayTimeLoop()
{
	int delta = SDL_GetTicks() - startLoop;
	if (delta < desiredDelta)
	{
		SDL_Delay(desiredDelta - delta);
	}
}

void handleKeyBoardPlayer1(SDL_Event& p_event, Entity& p_entity) {
	switch (p_event.type)
	{
	case SDL_KEYDOWN:
		switch (p_event.key.keysym.sym)
		{
		case SDLK_w:
			p_entity.velocity.y = -1;
			break;
		case SDLK_s:
			p_entity.velocity.y = 1;
			break;
		case SDLK_a:
			p_entity.velocity.x = -1;
			break;
		case SDLK_d:
			p_entity.velocity.x = 1;
			break;
		default:
			break;
		};
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			if (!keyboard_state_array[SDL_SCANCODE_S]) {
				p_entity.velocity.y = 0;
			}
			break;
		case SDLK_s:
			if (!keyboard_state_array[SDL_SCANCODE_W]) {
				p_entity.velocity.y = 0;
			}
			break;
		case SDLK_a:
			if (!keyboard_state_array[SDL_SCANCODE_D]) {
				p_entity.velocity.x = 0;
			}
			break;
		case SDLK_d:
			if (!keyboard_state_array[SDL_SCANCODE_A]) {
				p_entity.velocity.x = 0;
			}
			break;
		default:
			break;
		};
		break;
	default:
		break;
	}
}

void handleKeyBoardPlayer2(SDL_Event& p_event, Entity& p_entity) {
	switch (p_event.type)
	{
	case SDL_KEYDOWN:
		switch (p_event.key.keysym.sym)
		{
		case SDLK_UP:
			p_entity.velocity.y = -1;
			break;
		case SDLK_DOWN:
			p_entity.velocity.y = 1;
			break;
		case SDLK_LEFT:
			p_entity.velocity.x = -1;
			break;
		case SDLK_RIGHT:
			p_entity.velocity.x = 1;
			break;
		default:
			break;
		};
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			if (!keyboard_state_array[SDL_SCANCODE_DOWN]) {
				p_entity.velocity.y = 0;
			}
			break;
		case SDLK_DOWN:
			if (!keyboard_state_array[SDL_SCANCODE_UP]) {
				p_entity.velocity.y = 0;
			}
			break;
		case SDLK_LEFT:
			if (!keyboard_state_array[SDL_SCANCODE_RIGHT]) {
				p_entity.velocity.x = 0;
			}
			break;
		case SDLK_RIGHT:
			if (!keyboard_state_array[SDL_SCANCODE_LEFT]) {
				p_entity.velocity.x = 0;
			}
			break;
		default:
			break;
		};
		break;
	default:
		break;
	}
}

void update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_SPACE) {
				if (ball.checkCollison(player1.mColliders) && !ball.shotFlag) {
					ball.speed = 1;
					ball.timer = -2;
					int direction = player1.currentDirection;
					switch (direction)
					{
					case DIRECTION_UP:
						ball.setVelocity(Vector2f(0, -1));
						break;
					case DIRECTION_DOWN:
						ball.setVelocity(Vector2f(0, 1));
						break;
					case DIRECTION_LEFT:
						ball.setVelocity(Vector2f(-1, 0));
						break;
					case DIRECTION_RIGHT:
						ball.setVelocity(Vector2f(1, 0));
						break;
					case DIRECTION_UP_LEFT:
						ball.setVelocity(Vector2f(-1,-1));
						break;
					case DIRECTION_UP_RIGHT:
						ball.setVelocity(Vector2f(1, -1));
						break;
					case DIRECTION_DOWN_LEFT:
						ball.setVelocity(Vector2f(-1, 1));
						break;
					case DIRECTION_DOWN_RIGHT:
						ball.setVelocity(Vector2f(1, 1));
						break;
					default:
						break;
					}
					ball.shot();
				}
			}
			else if (event.key.keysym.sym == SDLK_RETURN) {
				if (ball.checkCollison(player2.mColliders) && !ball.shotFlag) {
					ball.speed = 1;
					ball.timer = -2;
					int direction = player2.currentDirection;
					switch (direction)
					{
					case DIRECTION_UP:
						ball.setVelocity(Vector2f(0, -1));
						break;
					case DIRECTION_DOWN:
						ball.setVelocity(Vector2f(0, 1));
						break;
					case DIRECTION_LEFT:
						ball.setVelocity(Vector2f(-1, 0));
						break;
					case DIRECTION_RIGHT:
						ball.setVelocity(Vector2f(1, 0));
						break;
					case DIRECTION_UP_LEFT:
						ball.setVelocity(Vector2f(-1, -1));
						break;
					case DIRECTION_UP_RIGHT:
						ball.setVelocity(Vector2f(1, -1));
						break;
					case DIRECTION_DOWN_LEFT:
						ball.setVelocity(Vector2f(-1, 1));
						break;
					case DIRECTION_DOWN_RIGHT:
						ball.setVelocity(Vector2f(1, 1));
						break;
					default:
						break;
					}
					ball.shot();
				}
			}
			else if (event.key.keysym.sym == SDLK_c)
			{
				player1.isActive = !player1.isActive;
				goalKeeper1.isActive = !goalKeeper1.isActive;
			}
			else if (event.key.keysym.sym == SDLK_l)
			{
				player2.isActive = !player2.isActive;
				goalKeeper2.isActive = !goalKeeper2.isActive;
			}
			break;
		}
		if (player1.isActive)
			handleKeyBoardPlayer1(event, player1);
		else if (goalKeeper1.isActive)
			handleKeyBoardPlayer1(event, goalKeeper1);
		if (player2.isActive)
			handleKeyBoardPlayer2(event, player2);
		else if (goalKeeper2.isActive)
			handleKeyBoardPlayer2(event, goalKeeper2);
	}

	player1.updatePosition();
	player1.shiftColliders();

	player2.updatePosition();
	player2.shiftColliders();


	goalKeeper1.updatePosition();
	goalKeeper1.shiftColliders();
	if (goalKeeper1.getPos().x > 550) {
		goalKeeper1.moveBack();
		goalKeeper1.shiftColliders();
	}

	goalKeeper2.updatePosition();
	goalKeeper2.shiftColliders();
	if (goalKeeper2.getPos().x < 930) {
		goalKeeper2.moveBack();
		goalKeeper2.shiftColliders();
	}

	//move with ball player1
	if (ball.checkCollison(player1.mColliders) && !ball.shotFlag) 
	{
		int direction = player1.getDirection();
		switch (direction)
		{
		case DIRECTION_UP:
			ball.updatePos(player1.getPos().x + 8, player1.getPos().y - 1 );
			break;
		case DIRECTION_DOWN:
			ball.updatePos(player1.getPos().x + 12, player1.getPos().y + 21 );
			break;
		case DIRECTION_LEFT:
			ball.updatePos(player1.getPos().x - 1 , player1.getPos().y + 8 );
			break;
		case DIRECTION_RIGHT:
			ball.updatePos(player1.getPos().x + 21 , player1.getPos().y + 8 );
			break;
		case DIRECTION_UP_LEFT:
			ball.updatePos(player1.getPos().x + 8, player1.getPos().y - 1);
			break;
		case DIRECTION_UP_RIGHT:
			ball.updatePos(player1.getPos().x + 18, player1.getPos().y - 1);
			break;
		case DIRECTION_DOWN_RIGHT:
			ball.updatePos(player1.getPos().x + 18, player1.getPos().y + 21);
			break;
		case DIRECTION_DOWN_LEFT:
			ball.updatePos(player1.getPos().x + 8, player1.getPos().y + 21);
			break;
		default:
			break;
		}
	}
	
	//player1 with goal
	if (player1.checkCollison(background.goalColliders)) {
		player1.moveBack();
		player1.shiftColliders();
	}
	
	//player1 with wall
	if (player1.checkCollison(background.mColliders))
	{
		player1.moveBack();
		player1.shiftColliders();
	}
	
	//move with ball player2
	if (ball.checkCollison(player2.mColliders) && !ball.shotFlag)
	{
		int direction = player2.getDirection();
		switch (direction)
		{
		case DIRECTION_UP:
			ball.updatePos(player2.getPos().x + 8, player2.getPos().y - 1);
			break;
		case DIRECTION_DOWN:
			ball.updatePos(player2.getPos().x + 12, player2.getPos().y + 21);
			break;
		case DIRECTION_LEFT:
			ball.updatePos(player2.getPos().x - 1, player2.getPos().y + 8);
			break;
		case DIRECTION_RIGHT:
			ball.updatePos(player2.getPos().x + 21, player2.getPos().y + 8);
			break;
		case DIRECTION_UP_LEFT:
			ball.updatePos(player2.getPos().x + 8, player2.getPos().y - 1);
			break;
		case DIRECTION_UP_RIGHT:
			ball.updatePos(player2.getPos().x + 18, player2.getPos().y - 1);
			break;
		case DIRECTION_DOWN_RIGHT:
			ball.updatePos(player2.getPos().x + 18, player2.getPos().y + 21);
			break;
		case DIRECTION_DOWN_LEFT:
			ball.updatePos(player2.getPos().x + 8, player2.getPos().y + 21);
			break;
		default:
			break;
		}
	}
	
	//player2 with goal
	if (player2.checkCollison(background.goalColliders)) {
		player2.moveBack();
		player2.shiftColliders();
	}
	
	//player2 with wall
	if (player2.checkCollison(background.mColliders))
	{
		player2.moveBack();
		player2.shiftColliders();
	}
	

	//move with ball goalKeeper1
	if (ball.checkCollison(goalKeeper1.mColliders) )
	{
		resetLocationRed();
	}

	//goalKeeper1 with goal
	if (goalKeeper1.checkCollison(background.goalColliders)) {
		goalKeeper1.moveBack();
		goalKeeper1.shiftColliders();
	}

	//goalKeeper1 with wall
	if (goalKeeper1.checkCollison(background.mColliders))
	{
		goalKeeper1.moveBack();
		goalKeeper1.shiftColliders();
	}

	//move with ball goalKeeper2
	if (ball.checkCollison(goalKeeper2.mColliders))
	{
		resetLocationBlue();
	}

	//goalKeeper2 with goal
	if (goalKeeper2.checkCollison(background.goalColliders)) {
		goalKeeper2.moveBack();
		goalKeeper2.shiftColliders();
	}

	//goalKeeper2 with wall
	if (goalKeeper2.checkCollison(background.mColliders))
	{
		goalKeeper2.moveBack();
		goalKeeper2.shiftColliders();
	}

	//ball with wall
	int checkBalltoWall = ball.checkCollison(background.mColliders);
	if ((checkBalltoWall != -1) && ball.shotFlag)
	{
		int direction = ball.getDirection();
		int x = ball.velocity.x;
		int y = ball.velocity.y;
		switch (direction)
		{
		case DIRECTION_UP:
			ball.setVelocity(Vector2f(x,-y));
			break;
		case DIRECTION_DOWN:
			ball.setVelocity(Vector2f(x, -y));
			break;
		case DIRECTION_LEFT:
			ball.setVelocity(Vector2f(-x, y));
			break;
		case DIRECTION_RIGHT:
			ball.setVelocity(Vector2f(-x, y));
			break;
		case DIRECTION_UP_LEFT :
			if(checkBalltoWall == 0)
				ball.setVelocity(Vector2f(x, -y));
			else if (checkBalltoWall == 2)
				ball.setVelocity(Vector2f(-x, y));
			break;
		case DIRECTION_UP_RIGHT:
			if (checkBalltoWall == 0)
				ball.setVelocity(Vector2f(x, -y));
			else if (checkBalltoWall == 3)
				ball.setVelocity(Vector2f(-x, y));
			break;
		case DIRECTION_DOWN_RIGHT:
			if (checkBalltoWall == 1)
				ball.setVelocity(Vector2f(x, -y));
			else if (checkBalltoWall == 3)
				ball.setVelocity(Vector2f(-x, y));
			break;
		case DIRECTION_DOWN_LEFT:
			if (checkBalltoWall == 1)
				ball.setVelocity(Vector2f(x, -y));
			else if (checkBalltoWall == 2)
				ball.setVelocity(Vector2f(-x, y));
			break;
		default:
			break;
		}
	}
	
	//ball with goal
	int checkBallCollison = ball.checkCollison(background.goalColliders);
	if ((checkBallCollison != -1) && ball.shotFlag)
	{
		std::cout << checkBallCollison << std::endl;
		int direction = ball.getDirection();
		int x = ball.velocity.x;
		int y = ball.velocity.y;
		switch (checkBallCollison)
		{
		case 0:
			ball.setVelocity(Vector2f(-x, y));
			break;
		case 1:
			if (ball.mCollider.y < background.goalColliders[1].y) {
				ball.setVelocity(Vector2f(x, -y));
			}
			else {
				ball.setVelocity(Vector2f(-x, y));
			}
				break;
		case 2:
			if (ball.mCollider.y > background.goalColliders[2].y) {
				ball.setVelocity(Vector2f(x, -y));
			}
			else {
				ball.setVelocity(Vector2f(-x, y));
			}
			break;
		case 3:
			ball.setVelocity(Vector2f(-x, y));
			break;
		case 4:
			if (ball.mCollider.y < background.goalColliders[4].y) {
				ball.setVelocity(Vector2f(x, -y));
			}
			else {
				ball.setVelocity(Vector2f(-x, y));
			}
			break;
		case 5:
			if (ball.mCollider.y < background.goalColliders[5].y) {
				ball.setVelocity(Vector2f(x, -y));
			}
			else {
				ball.setVelocity(Vector2f(-x, y));
			}
			break;
		default:
			break;
		}
	}
	
	//ball with PointArea
	if (ball.checkCollison(getPointArea1))
	{
		point2++;
		gameState = 0;
	}
	if (ball.checkCollison(getPointArea2))
	{
		point1++;
		gameState = 0;
	}
	

	ball.update();
	player1.update();
	player2.update();
	goalKeeper1.update();
	goalKeeper2.update();
	if(player1.isActive)
		updateArrowPosition(arrow1, player1);
	else if (goalKeeper1.isActive)
		updateArrowPosition(arrow1, goalKeeper1);
	if (player2.isActive)
		updateArrowPosition(arrow2, player2);
	else if (goalKeeper2.isActive)
		updateArrowPosition(arrow2, goalKeeper2);
}

void graphics()
{
	window.clear();
	window.render(background);
	/*SDL_SetRenderDrawColor(window.renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(window.renderer, &getPointArea1);
	SDL_RenderDrawRect(window.renderer, &getPointArea2);
	for (int i = 0; i < background.goalColliders.size(); i++) {
		SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(window.renderer, &background.goalColliders[i]);
	}*/
	window.render(player2);
	window.render(player1);

	window.render(goalKeeper1);
	window.render(goalKeeper2);

	window.render(arrow1);
	window.render(arrow2);

	window.render(ball);


	//Display score
	std::string scoreText = "score: " + std::to_string(point1) + " - " + std::to_string(point2);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Pixel, &scoreText[0], White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(window.renderer, surfaceMessage);
	window.render(600, 550, Message);

	window.display();
}

void game()
{
	if (gameState == 0)
	{
		resetLocation();
		gameState = 1;
	}
	else if (gameState == 1) {
		update();
		graphics();
	}
}

int main(int argc, char* args[])
{
	int scrollingOffset = 0;
	while (gameRunning)
	{	
		startLoop = SDL_GetTicks();
		game();
		delayTimeLoop();
	}
	window.cleanUp();
	TTF_Quit();
	return 0;
}