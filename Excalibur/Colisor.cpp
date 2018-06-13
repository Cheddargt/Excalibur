#include "stdafx.h"
#include "Colisor.h"


Colisor::Colisor(sf::RectangleShape& body) : 
	body(body)
{
}


Colisor::~Colisor()
{
}

bool Colisor::CheckCollision(Colisor* other, sf::Vector2f& direcao, float push) //&other e &direcao
{
	sf::Vector2f otherPosition = other->GetPosition();
	sf::Vector2f otherHalfSize = other->GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other->Move(-intersectX * push, 0.0f);

				direcao.x = 1.0f; //direcao->x = 1.0f;
				direcao.y = 0.0f; //direcao->y = 0.0f;
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other->Move(intersectX * push, 0.0f);

				direcao.x = -1.0f; //direcao->x = -1.0f;
				direcao.y = 0.0f; //direcao->y = 0.0f;
			}

		}

		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other->Move(0.0f, -intersectY * push);

				direcao.x = 0.0f; //direcao->x = 0.0f;
				direcao.y = -1.0f; //direcao->y = 0.0f;
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other->Move(0.0f, intersectY * push);

				direcao.x = 0.0f; //direcao->x = 0.0f;
				direcao.y = -1.0f; //direcao->y = 0.0f;
			}
		}
		return true; //caso um projetil inimigo esteja colidindo com o inimigo
	}

	return false; //quando não há colisão acontecendo
}
