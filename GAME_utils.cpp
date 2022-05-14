#include "headers/GAME_ultils.h"


std::vector<int> LoadSetting(std::string path)
{
    std::vector<int> Settingg;
    int temp;
    std::fstream SettingFile;
    std::string number;
    SettingFile.open(path, std::ios::in);
    while(!SettingFile.eof()) {
        std::getline(SettingFile, number);
        std::stringstream ConvertToInt(number);
        ConvertToInt >> temp;
        Settingg.push_back(temp);
    }
    return Settingg;
}

void UpdateSetting(std::string path, const int& ship, const int& bullet, const int& planet)
{
    std::fstream SettingFile;
    std::string number;
    SettingFile.open(path, std::ios::out);
    number = std::to_string(ship) + "\n" + std::to_string(bullet) + "\n" + std::to_string(planet);
    SettingFile << number;
    //std::cout << number << std::endl;
    SettingFile.close();

}
void renderText(const std::string& text, TTF_Font* font,SDL_Renderer* renderer)
{
    SDL_Color fontColor = {255,255,255};
    SDL_Surface* surface = TTF_RenderText_Blended(font,text.c_str(),fontColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_Rect scRect;
    SDL_Rect dsRect;
    TTF_SizeText(font,text.c_str(), &scRect.w, &scRect.h);
    scRect.x = 0;
    scRect.y = 0;
    dsRect.x = 195;
    dsRect.y = 639;
    dsRect.w = scRect.w;
    dsRect.h = scRect.h;
    SDL_RenderCopy(renderer,texture,&scRect,&dsRect);
    freeTexture(texture);
}
void renderHealth(SDL_Renderer* renderer, SDL_Texture* texture, int& health)
{
    //Set rect of health texture, first is colored health
    SDL_Rect sRect = {0,0, 259, 226};
    for(int i = 0; i < health; i++) {
        SDL_Rect dRect = {HEALTH_POSX+30*i,HEALTH_POSY,30,30};
        SDL_RenderCopy(renderer,texture,&sRect,&dRect);
    }
    sRect = {260,0, 259, 226};
    for(int i = 0; i < 5-health; i++) {
        SDL_Rect dRect = {HEALTH_POSX+30*(i+health),HEALTH_POSY,30,30};
        SDL_RenderCopy(renderer,texture,&sRect,&dRect);
    }
}

void RenderNumber(SDL_Renderer* renderer, SDL_Texture* texture, int kind, const int& score)
{
    SDL_Rect num[10];
    for (int i = 0; i < 10; ++i)
        num[i] = {i * 20, 0, 20, 20};
    std::string _highscore = GetHighScoreFromFile("high_score.txt");
    std::string _score = std::to_string(score);
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
	std::getline(HighScoreFile,highscore);
	HighScoreFile.close();

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
	HighScoreFile.close();
}

//CheckCollision
double distanceSquared( float x1, float y1, float x2, float y2 )
{
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}
bool checkCollision1( Circle& a, SDL_FRect& b, int degree)
{
    //Closest point on collision box
    float cX, cY;

    //Find closest x offset
    if( a.x < b.x )
    {
        cX = b.x;
    }
    else if( a.x > b.x + b.w*cos(degree*Pi/180) )
    {
        cX = b.x + b.w*cos(degree*Pi/180);
    }
    else
    {
        cX = a.x;
    }
      //Find closest y offset
    if( a.y < b.y )
    {
        cY = b.y;
    }
    else if( a.y > b.y + b.h*sin(degree*Pi/180) )
    {
        cY = b.y + b.h*sin(degree*Pi/180);
    }
    else
    {
        cY = a.y;
    }

    //If the closest point is inside the circle
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
    {
        //This box and the circle have collided
        return true;
    }

    //If the shapes have not collided
    return false;
}
bool checkCollision2( Circle& a, Circle& b )
{
    //Calculate total radius squared
    float totalRadiusSquared = a.r + b.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) )
    {
        //The circles have collided
        return true;
    }

    //If not
    return false;
}

void freeTexture(SDL_Texture* texture)
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
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
    //Init Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Initialize the truetype font API.
    if (TTF_Init() < 0)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
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
    TTF_Quit();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
