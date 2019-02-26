#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>

sf::RenderWindow mainWindow(sf::VideoMode(800, 500), "Memory Game");
sf::Texture BackgroundTexture;
sf::Texture highScoreTexture;
sf::Sprite background;
sf::Sprite highscoreBackground;

sf::RectangleShape rectNewGame(sf::Vector2f(200, 50));
sf::RectangleShape rectHighScore(sf::Vector2f(200, 50));

sf::RectangleShape rectBack(sf::Vector2f(200, 50));


sf::RectangleShape rect1(sf::Vector2f(100, 100));
sf::RectangleShape rect2(sf::Vector2f(100, 100));
sf::RectangleShape rect3(sf::Vector2f(100, 100));
sf::RectangleShape rect4(sf::Vector2f(100, 100));
sf::RectangleShape rect5(sf::Vector2f(100, 100));
sf::RectangleShape rect6(sf::Vector2f(100, 100));
sf::RectangleShape rect7(sf::Vector2f(100, 100));
sf::RectangleShape rect8(sf::Vector2f(100, 100));
sf::RectangleShape *ALL_RECTANGLES[]=
{
    &rect1,
    &rect2,
    &rect3,
    &rect4,
    &rect5,
    &rect6,
    &rect7,
    &rect8
};

sf::RectangleShape *firstSelectedRectangle;
sf::RectangleShape *secondSelectedRectangle;
bool isFirstRectSelected=false;
bool isFound=false;
bool isClockRestarted=false;


sf::Texture textureRect1;
sf::Texture textureRect2;
sf::Texture textureRect3;
sf::Texture textureRect4;
sf::Texture textureRect5;
sf::Texture textureRect6;
sf::Texture textureRect7;
sf::Texture textureRect8;
sf::Texture cover;
sf::Texture *ALL_TEXTURES[]=
{
    &textureRect1,
    &textureRect2,
    &textureRect3,
    &textureRect4,
    &textureRect5,
    &textureRect6,
    &textureRect7,
    &textureRect8




};

sf::Text textHighScoreScreen;

sf::Text textBack;





sf::RectangleShape rectGameOver(sf::Vector2f(400, 400));
sf::Text textGameOver;


sf::Font font;
sf::Text textNewGame;
sf::Text textHighScore;
sf::Text textCountDown;

sf::Text textScoreGameScreen;
sf::Text textScoreGameOver;

sf::Clock cl;
bool isCovered=false;
bool gameOver = false;
bool gameStarted = false;
bool highScoreWritten = false;


std::string IMAGE_SOURCES[8];
std::string ACTIVE_PAGE = "MAIN_MENU";

int MAX_TIME_IN_SECONDS = 60.0;

int SCORE=0;

bool isMouseInBoundsOf(sf::RectangleShape r)
{
    return r.getGlobalBounds().contains(sf::Mouse::getPosition().x-mainWindow.getPosition().x,sf::Mouse::getPosition().y-mainWindow.getPosition().y-30);
}
void set_item_positions()
{
    rectNewGame.setPosition(100, 100);
    rectHighScore.setPosition(100, 200);

    textNewGame.setPosition(rectNewGame.getPosition());
    textHighScore.setPosition(rectHighScore.getPosition());


    rect1.setPosition(30, 50);
    rect2.setPosition(150, 50);
    rect3.setPosition(270, 50);
    rect4.setPosition(390, 50);

    rect5.setPosition(30, 250);
    rect6.setPosition(150, 250);
    rect7.setPosition(270, 250);
    rect8.setPosition(390, 250);


    textCountDown.setPosition(250,10);
    textScoreGameScreen.setPosition(550,10);


    rectGameOver.setPosition(100,10);
    textGameOver.setPosition(rectGameOver.getPosition());
    textScoreGameOver.setPosition(rectGameOver.getPosition().x,rectGameOver.getPosition().y+100);


    textHighScoreScreen.setPosition(300,150);

    rectBack.setPosition(0,300);
    textBack.setPosition(rectBack.getPosition());


}
void set_item_fillcolors()
{
    rectHighScore.setFillColor(sf::Color::Red);
    rectNewGame.setFillColor(sf::Color::Red);

    textNewGame.setFillColor(sf::Color::White);
    textHighScore.setFillColor(sf::Color::White);

    rectGameOver.setFillColor(sf::Color::Red);

    rectBack.setFillColor(sf::Color::Red);


}
std::string getHighscore()
{
    std::ifstream in("highscore.txt");
    std::string line;
    in>>line;
    in.close();
    return line;
}
void checkHighscore(int currentScore)
{

    int files_highscore = stoi(getHighscore());
    if(currentScore > files_highscore)
    {
        std::ofstream out("highscore.txt");
        out << currentScore;
        out.close();
    }

}
void draw_items()
{

    if(!gameOver)
    {


        if(ACTIVE_PAGE == "MAIN_MENU")
        {
            mainWindow.draw(background);
            mainWindow.draw(rectNewGame);
            mainWindow.draw(rectHighScore);
            mainWindow.draw(textNewGame);
            mainWindow.draw(textHighScore);

        }

        else if(ACTIVE_PAGE == "GAME_SCREEN")

        {

            mainWindow.draw(background);

            if(!isClockRestarted)
            {
                isClockRestarted=true;
                cl.restart();
                gameStarted=true;

            }



            mainWindow.draw(rect1);
            mainWindow.draw(rect2);
            mainWindow.draw(rect3);
            mainWindow.draw(rect4);
            mainWindow.draw(rect5);
            mainWindow.draw(rect6);
            mainWindow.draw(rect7);
            mainWindow.draw(rect8);

            mainWindow.draw(textCountDown);
            mainWindow.draw(textScoreGameScreen);


        }

        else if (ACTIVE_PAGE == "HIGHSCORE_SCREEN")
        {
            mainWindow.draw(highscoreBackground);

            mainWindow.draw(textHighScoreScreen);

            mainWindow.draw(rectBack);
            mainWindow.draw(textBack);
        }

    }
    else
    {
        mainWindow.draw(rectGameOver);
        mainWindow.draw(textGameOver);
        mainWindow.draw(textScoreGameOver);

        if(!highScoreWritten)
        {
            checkHighscore(SCORE);
            highScoreWritten=true;
        }


    }

}

void initialize_items()
{
    font.loadFromFile("resources/ARCADECLASSIC.ttf");

    textNewGame.setFont(font);
    textHighScore.setFont(font);
    textCountDown.setFont(font);
    textGameOver.setFont(font);

    textScoreGameScreen.setFont(font);
    textScoreGameOver.setFont(font);

    textHighScoreScreen.setFont(font);

    textNewGame.setString("New Game");
    textHighScore.setString("High Score");
    textCountDown.setString("60");
    textGameOver.setString("GAME OVER!!!");

    textScoreGameScreen.setString("SCORE  ");
    textScoreGameOver.setString("SCORE  ");


    textHighScoreScreen.setString("HIGHSCORE  "+getHighscore());




    BackgroundTexture.loadFromFile("resources/main_game.png");
    highScoreTexture.loadFromFile("resources/highscore.png");
    background.setTexture(BackgroundTexture);
    highscoreBackground.setTexture(highScoreTexture);


    textBack.setFont(font);
    textBack.setString("BACK");
}

void load_image_sources_from_file()
{
    std::string all_image_files[] =
    {
        "res/1.jpg",
        "res/2.jpg",
        "res/3.jpg",
        "res/4.jpg",
        "res/5.jpg",
        "res/6.jpg",
        "res/7.jpg",
        "res/8.jpg",
        "res/9.jpg"
    };

    random_shuffle(&all_image_files[0], &all_image_files[8]);

    for(int i=0; i<4; i++)
    {
        IMAGE_SOURCES[i]=IMAGE_SOURCES[i+4]=all_image_files[i];
    }
}

void randomize_image_sources()
{
    random_shuffle(&IMAGE_SOURCES[0], &IMAGE_SOURCES[7]);

}
void load_from_image_source_to_rectangles()
{
    textureRect1.loadFromFile(IMAGE_SOURCES[0]);
    textureRect2.loadFromFile(IMAGE_SOURCES[1]);
    textureRect3.loadFromFile(IMAGE_SOURCES[2]);
    textureRect4.loadFromFile(IMAGE_SOURCES[3]);

    textureRect5.loadFromFile(IMAGE_SOURCES[4]);
    textureRect6.loadFromFile(IMAGE_SOURCES[5]);
    textureRect7.loadFromFile(IMAGE_SOURCES[6]);
    textureRect8.loadFromFile(IMAGE_SOURCES[7]);

    rect1.setTexture( &textureRect1);
    rect2.setTexture( &textureRect2);
    rect3.setTexture( &textureRect3);
    rect4.setTexture( &textureRect4);
    rect5.setTexture( &textureRect5);
    rect6.setTexture( &textureRect6);
    rect7.setTexture( &textureRect7);
    rect8.setTexture( &textureRect8);

}

void cover_rectangles()
{

    cover.loadFromFile("res/cover.jpg");

    rect1.setTexture( &cover);
    rect2.setTexture( &cover);
    rect3.setTexture( &cover);
    rect4.setTexture( &cover);
    rect5.setTexture( &cover);
    rect6.setTexture( &cover);
    rect7.setTexture( &cover);
    rect8.setTexture( &cover);
}

void highlightFirstSelected()
{
    if(firstSelectedRectangle != nullptr)
        firstSelectedRectangle->setFillColor(sf::Color::Green);}
void highlightSecondSelected()
{
    if(secondSelectedRectangle != nullptr)
        secondSelectedRectangle->setFillColor(sf::Color::Blue);

}
int findIndexOfRect(sf::RectangleShape *r)
{
    for(int i=0; i<8; i++)
    {
        if(ALL_RECTANGLES[i] == r)
            return i;

    }
    return -1;
}
void compareFirstAndSecond()
{
    if(firstSelectedRectangle != nullptr && IMAGE_SOURCES[findIndexOfRect(firstSelectedRectangle)] == IMAGE_SOURCES[findIndexOfRect(secondSelectedRectangle)] && !isFound &&firstSelectedRectangle->getPosition() !=secondSelectedRectangle->getPosition() )
    {
        std::cout<<"found\n";
        SCORE += 100;

        isFound=true;
    }
    else if(gameStarted&& !isFirstRectSelected&&firstSelectedRectangle != nullptr && secondSelectedRectangle != nullptr&&!isFound )
    {
        gameOver=true;
    }


}

void cover_if_time_passed(int s)
{
    sf::Time t = sf::seconds(s);

    if(gameStarted&&cl.getElapsedTime() > t && !isCovered)
    {
        cover_rectangles();
        isCovered = true;
    }


}

void update_counter()
{
    textCountDown.setString("COUNTDOWN  "+std::to_string(int(MAX_TIME_IN_SECONDS - cl.getElapsedTime().asSeconds())));

}

void update_score_text()
{
    textScoreGameOver.setString("SCORE  "+std::to_string(SCORE));
    textScoreGameScreen.setString("SCORE  "+std::to_string(SCORE));

}

void check_if_time_is_up()
{
    if(int(MAX_TIME_IN_SECONDS - cl.getElapsedTime().asSeconds() < 0) && gameStarted)
    {
        gameOver = true;

    }
}
int main()
{
    cl.restart();


    initialize_items();

    load_image_sources_from_file();
    randomize_image_sources();
    load_from_image_source_to_rectangles();


    while(mainWindow.isOpen())
    {
        sf::Event event;

        while(mainWindow.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                mainWindow.close();
                break;

            case sf::Event::MouseButtonReleased:
                if(ACTIVE_PAGE == "MAIN_MENU")
                {
                    if(isMouseInBoundsOf(rectNewGame))
                    {
                        ACTIVE_PAGE="GAME_SCREEN";

                    }
                    else if(isMouseInBoundsOf(rectHighScore))
                        ACTIVE_PAGE="HIGHSCORE_SCREEN";

                }
                else if(ACTIVE_PAGE == "GAME_SCREEN")
                {


                    for(int i =0; i<8; i++)
                    {
                        sf::RectangleShape *currentRectangle = ALL_RECTANGLES[i];
                        if(isMouseInBoundsOf(*currentRectangle))
                        {
                            isFound=false;

                            currentRectangle->setTexture(ALL_TEXTURES[i]);


                            if(!isFirstRectSelected)
                            {
                                firstSelectedRectangle=currentRectangle;
                                isFirstRectSelected=true;

                            }
                            else
                            {
                                secondSelectedRectangle=currentRectangle;
                                isFirstRectSelected=false;
                            }

                        }



                    }


                }
                else if(ACTIVE_PAGE == "HIGHSCORE_SCREEN"){
                    if(isMouseInBoundsOf(rectBack))
                    {
                        ACTIVE_PAGE = "MAIN_MENU";

                    }


                }

            }
        }
        mainWindow.clear();
//happens every frame

        set_item_positions();
        set_item_fillcolors();

        cover_if_time_passed(1);



        highlightFirstSelected();
        highlightSecondSelected();

        compareFirstAndSecond();
        update_counter();
        update_score_text();
        check_if_time_is_up();

        draw_items();




        mainWindow.display();
    }
}
