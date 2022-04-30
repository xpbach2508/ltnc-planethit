#include "headers/SDL_ultils.h"

void Game_Over()
{

}

void RenderNumber(SDL_Renderer* renderer, SDL_Texture* texture, int kind, const int & score)
{
    SDL_Rect num[10];
    for (int i = 0; i < 10; ++i)
        num[i] = {i * 20, 0, 20, 20};
    string _highscore = GetHighScoreFromFile("high_score.txt");
    string _score = to_string(score);
    if(kind == 2) {
        for (int i = 0; i < _score.length(); ++i)
        {
            SDL_Rect dRect = {SCORE_GAMEPX+ i*20, SCORE_GAMEPY, 20, 20};
            SDL_RenderCopy(renderer, texture, &num[_score[i]-'0'],&dRect);
        }
        for(int i = 0; i < _highscore.length(); ++i)
        {
            SDL_Rect dRect = {HIGH_SCORE_GAMEPX+ i*20, HIGH_SCORE_GAMEPY, 20, 20};
            SDL_RenderCopy(renderer, texture, &num[_highscore[i]-'0'],&dRect);
        }
    }
    if(kind == 1) {
        int start = HIGH_SCORE_MENUPX - _highscore.length()/2*20;
        for(int i = 0; i < _highscore.length(); i++)
        {
            SDL_Rect dRect = {start+ i*20, HIGH_SCORE_MENUPY,20 ,20};
            SDL_RenderCopy(renderer, texture, &num[_highscore[i]-'0'],&dRect);
        }
    }
}
//highscore
std::string GetHighScoreFromFile(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}
void UpdateHighScore(std::string path, const int& score, const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

//CheckCollision
bool CheckCollision(SDL_FRect& a, SDL_FRect& b)
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == nullptr)
        std::cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << std::endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface);
        if( newTexture == nullptr) std::cout << "Unable to create texture from " << path << "SDL Error:"
                                << SDL_GetError() << std::endl;
//        else {
//            Width = loadedSurface->w;
//            Height = loadedSurface->h;
//        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
