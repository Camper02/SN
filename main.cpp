#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>
#include <logger.hpp>


using namespace sf;



int main()
{
	ns_log::Logger log;
	const int W = 40;
	RenderWindow window(VideoMode(640, 420), "Test!");
	int stayflag = 0;
	Texture t;
	Texture tileSet;
	Texture BackGround;
	Texture score;
	try
	{
		t.loadFromFile("assets/SNINJA.png");
		if (!t.loadFromFile("assets/SNINJA.png"))
		{
			throw std::runtime_error("Failed to load texture: SNINJA.png");
		}
		tileSet.loadFromFile("assets/blocks.png");
		if (!tileSet.loadFromFile("assets/blocks.png"))
		{
			throw std::runtime_error("Failed to load texture: blocks.png");
		}
		BackGround.loadFromFile("assets/BackGround.png");
		if (!BackGround.loadFromFile("assets/BackGround.png"))
		{
			throw std::runtime_error("Failed to load texture: BackGround.png");
		}
		
	}
	catch (const std::exception& e)
	{
		log.send_message(e.what());
		std::cerr << "An exception occurred: " << e.what() << std::endl;
		return 1;
	}
	float currentFrame = 0;
	PLAYER b(tileSet);
	Sprite tile(tileSet);
	Sprite BG(BackGround);
	PLAYER p(t);
	log.send_message("textures downloaded succesfully");
	

	Clock clock;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 700;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;
			stayflag = 1;
			p.f = true;
			p.direction = true;
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
			stayflag = 1;
			p.f = true;
			p.direction = true;
		}

		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -0.35; p.onGround = false; stayflag = 1;}
		}
		if (stayflag != 1)
		{
			p.f = false;
		}
		
		p.update(time);

		if (p.rect.left > 300 && p.rect.left < 980) offsetX = p.rect.left - 300;
		offsetY = p.rect.top - 200;

		window.clear (Color(107, 140, 255)); 
		window.draw(BG);
		
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'Z') tile.setTextureRect((IntRect(1, 1, 34, 34)));

				if (TileMap[i][j] == 'B') tile.setTextureRect((IntRect(1, 82, 34, 34)));

				if (TileMap[i][j] == '0') tile.setTextureRect((IntRect(241, 80, 33, 33)));

				if (TileMap[i][j] == 'M') tile.setTextureRect((IntRect(1, 305, 33, 33)));

				if (TileMap[i][j] == ' ') continue;

				tile.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(tile);
			}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
