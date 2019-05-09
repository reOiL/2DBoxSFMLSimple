#include <iostream>
#include "SFML/Graphics.hpp"
#include "Box2D.h"

#define PIX_TO_MET(x) 30.f / x
#define MET_TO_PIX(x) 30.f * x
#define RAD_TO_GRAD(x) x * 57.f

int main() {
    //Box2D
    b2Vec2 kGravity(0.f, 9.8f);
    b2World kWorld(kGravity);
    //SFML
    sf::RenderWindow kWnd(sf::VideoMode(800, 600), "Simple 2D box");
    kWnd.setFramerateLimit(60);

    sf::Image kImage;
    if (!kImage.loadFromFile("img/ball.png"))
    {
        std::cout << "Not found textures!\n";
        return 0;
    }
    sf::Texture BallTexture;
    BallTexture.loadFromImage(kImage);
    BallTexture.setSmooth(true);

    const unsigned short BallCount = 1;
    std::vector<sf::Sprite> Balls;
    for (int i = 0; i < BallCount; ++i)
    {
        sf::Sprite kTempSprite(BallTexture);
        kTempSprite.setOrigin(50, 50); // texture size 100x100 so we make center at 50 50
        kTempSprite.setTextureRect(sf::IntRect(0, 0, 100, 100)); // add collider react
        Balls.push_back(kTempSprite);
    }

    //Set Wall
    const char *BallName = "Ball";
    for (auto it: Balls)
    {
        b2PolygonShape kPolygonShape;
        kPolygonShape.SetAsBox(PIX_TO_MET(100),
                               PIX_TO_MET(100)); // dived by 30 that because Box2D default in meter not a pixel

        b2BodyDef kBodyDef;
        kBodyDef.type = b2_dynamicBody;
        kBodyDef.position.Set(PIX_TO_MET(10), PIX_TO_MET(10)); // set Ball position

        b2Body *body = kWorld.CreateBody(&kBodyDef);
        body->CreateFixture(&kPolygonShape, 2);
        body->SetUserData((void *) BallName);
    }

    while (kWnd.isOpen())
    {
        sf::Event kEvent;
        while (kWnd.pollEvent(kEvent))
        {
            if (kEvent.type == sf::Event::Closed)
                kWnd.close();
        }

        //Box 2D
        kWorld.Step(1 / 60.f, 8, 3);
        //
        kWnd.clear(sf::Color::Black);
        for (auto it: Balls)
        {
            for (auto jt = kWorld.GetBodyList(); jt != nullptr; jt = jt->GetNext())
            {
                if (jt->GetUserData() == (void *) BallName)
                {
                    b2Vec2 pos = jt->GetPosition();
                    it.setPosition(MET_TO_PIX(pos.x), MET_TO_PIX(pos.y));
                    it.setRotation(RAD_TO_GRAD(jt->GetAngle()));
                    kWnd.draw(it);
                }
            }
        }
        kWnd.display();
    }

    return 0;
}