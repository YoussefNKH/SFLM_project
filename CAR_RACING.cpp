#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>
//les includes 
using namespace std;
using namespace sf;
//initialistaion des constant du jeux
const double larg = 800;
const double longe = 600;
const int borderLeft = 140;
const int borderRight = 660;
const int racerWidth = 40;
const int racerHeight = 70;
string stringscore = "";
int score = 0;
double gameSpeed = 0.07;//vitess initiale de voiture
//creation de window
RenderWindow app(VideoMode(larg, longe), "2D CAR RACING");
//Creation entier aleatoire 
int getRandomNumber(int a, int b);
// Creation du gameover
int gameOver();
int main()
{
	//iniatialisation de music du jeux
	SoundBuffer gameSoundBuffer;
	gameSoundBuffer.loadFromFile("audio/Battle_in_the_Stars.ogg");
	Sound GameSound;
	GameSound.setBuffer(gameSoundBuffer);
	//les texture utliser 
	Texture background, racer, obs1, obs2, obs3, obs4, gameover;
	//initialisation des FONT
	Font font;
	font.loadFromFile("Font/xirod.ttf");
	//Imporation des texture avec EXIT_FAILURE si l'imporation ne fait pas
	if (!background.loadFromFile("img/background.png")) return EXIT_FAILURE;
	if (!racer.loadFromFile("img/racer.png")) return EXIT_FAILURE;
	if (!obs1.loadFromFile("img/obs1.png")) return EXIT_FAILURE;
	if (!obs2.loadFromFile("img/obs2.png")) return EXIT_FAILURE;
	if (!obs3.loadFromFile("img/obs3.png")) return EXIT_FAILURE;
	if (!obs4.loadFromFile("img/obs4.png")) return EXIT_FAILURE;
	//creation des Sprite
	Sprite Background(background), Background1(background), Racer(racer), Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4), Gameover(gameover);
	double RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;
	//les postion des objet
	RacerX = larg / 2;
	RacerY = longe - racerHeight;
	Obs1X = getRandomNumber(borderLeft, borderRight);
	Obs2X = getRandomNumber(borderLeft, borderRight);
	Obs3X = getRandomNumber(borderLeft, borderRight);
	Obs4X = getRandomNumber(borderLeft, borderRight);
	Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300;
	double BackgroundY1 = 0;
	double BackgroundY2 = -600;
	SoundBuffer gamest;
	gamest.loadFromFile("audio/sound_start.wav");
	Sound Gamest;
	Gamest.setBuffer(gamest);
	Gamest.play();
	GameSound.play();
	GameSound.setLoop(true);
	
	//BOUCLE DU JEUX
	while (app.isOpen())
	{
		//Init DU SCORE
		stringscore = "SCORE:" + to_string(score);
		Text text(stringscore, font, 15);
		text.setPosition(5, 0);
		//Set OBJ position
		Racer.setPosition(RacerX, RacerY);
		Obs1.setPosition(Obs1X, Obs1Y);
		Obs2.setPosition(Obs2X, Obs2Y);
		Obs3.setPosition(Obs3X, Obs3Y);
		Obs4.setPosition(Obs4X, Obs4Y);
		//creation du mouvement background
		Background.setPosition(0, BackgroundY1);
		Background1.setPosition(0, BackgroundY2);
		if (BackgroundY2 > 0)
		{
			BackgroundY1 = 0;
			BackgroundY2 = BackgroundY1 - 500;
		}
		BackgroundY1 += 0.03;
		BackgroundY2 += 0.03;
		//boucle  des obstacles
		if (Obs1Y > longe)
		{
			Obs1Y = 0; Obs1X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs1Y = Obs1Y + gameSpeed; }
		if (Obs2Y > longe)
		{
			Obs2Y = 0; Obs2X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs2Y = Obs2Y + gameSpeed; }
		if (Obs3Y > longe)
		{
			Obs3Y = 0; Obs3X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs3Y = Obs3Y + gameSpeed; }
		if (Obs4Y > longe)
		{
			Obs4Y = 0; Obs4X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs4Y = Obs4Y + gameSpeed; }
		//les niv lorsque niv ++ vitesse ++
		if (score > 10 && score < 18)
		{
			gameSpeed = 0.1;
		}
		if (score > 18 && score < 25)
		{
			gameSpeed = 0.125;
		}
		if (score > 25 && score < 35)
		{
			gameSpeed = 0.14;
		}
		if (score > 35 && score < 45)
		{
			gameSpeed = 0.16;
		}
		//Creation des event 
		Event event;
		while (app.pollEvent(event))// ecoute
		{
			if (event.type == Event::Closed)
				app.close();
			//ecoute de mouvement 
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					if (RacerX > borderLeft) { RacerX = RacerX - 15; }
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (RacerX < borderRight) { RacerX = RacerX + 15; }
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (RacerY > 0) { RacerY = RacerY - 15; }
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (RacerY < longe - 70) { RacerY = RacerY + 15; }
				}

			}
		}
		//SI un ACCIDENT 
		if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY) <= (Obs1Y + 30)))
		{
			GameSound.stop()  ; gameOver();
		};
		if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY) <= (Obs2Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((RacerX >= (Obs3X - 30)) && (RacerX <= (Obs3X + 30))) && ((RacerY >= (Obs3Y - 30)) && (RacerY) <= (Obs3Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((RacerX >= (Obs4X - 30)) && (RacerX <= (Obs4X + 30))) && ((RacerY >= (Obs4Y - 30)) && (RacerY) <= (Obs4Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		//dessin des Sprite sur l'ecran
		app.clear();
		app.draw(Background);
		app.draw(Background1);
		app.draw(Racer);
		app.draw(Obs1);
		app.draw(Obs2);
		app.draw(Obs3);
		app.draw(Obs4);
		app.draw(text);
		app.display();
	}
	return EXIT_SUCCESS;
}
int gameOver()
{
	Texture gameover, troll;
	if (!gameover.loadFromFile("img/gameover.png")) return EXIT_FAILURE;
	//if (!troll.loadFromFile("img/troll.png")) return EXIT_FAILURE;

	Sprite Gameover(gameover);
	//Sprite Troll(troll);
	//Troll.setPosition(10, 350);
	SoundBuffer gameOver;
	gameOver.loadFromFile("audio/sound_crash.wav");
	Sound GameOver;
	GameOver.setBuffer(gameOver);
	GameOver.play();
	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
		}
		Font myfont;
		myfont.loadFromFile("Font/xirod.ttf");
		stringscore = "YOUR SCORE:" + to_string(score);
		Text text(stringscore, myfont, 30);
		text.setPosition(210, 450);
		//Text text1("PRESS ENTER TO RESTART", myfont, 30);
		//text1.setPosition(350, 250);
		app.clear();
		app.draw(Gameover);
		app.draw(text);
		//app.draw(text1);
		//app.draw(Troll);
		app.display();

	}

}
int getRandomNumber(int a, int b)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	result = (result / 10) * 10;
	return result;
}