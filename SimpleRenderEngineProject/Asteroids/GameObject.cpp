#include "GameObject.h"

GameObject::GameObject(
	sre::Sprite sprite_laser,
	sre::Sprite sprite_asteroid_lg
)
{
	this->sprite_laser = sprite_laser;
	this->sprite_asteroid_lg = sprite_asteroid_lg;

	for (int i = 0; i < 5; i++) spawn_asteroid();

	int asteroids_destroyed_count = 0;
}

bool key_down_w = false;
bool key_down_a = false;
bool key_down_d = false;
bool key_down_space = false;

void GameObject::ProcessEvents(SDL_Event &event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		key_down_w = event.type == SDL_KEYDOWN;
		break;
	case SDLK_a:
		key_down_a = event.type == SDL_KEYDOWN;
		break;
	case SDLK_d:
		key_down_d = event.type == SDL_KEYDOWN;
		break;
	case SDLK_SPACE:
		key_down_space = event.type == SDL_KEYDOWN;
		break;
	}
}

void GameObject::Update(float deltaTime)
{
	if (key_down_a)
		spaceshit->rotate_cw(deltaTime);
	if (key_down_d)
		spaceshit->rotate_ccw(deltaTime);
	if (key_down_w)
		spaceshit->move_forward();
	if (key_down_space)
		lasers.push_back(std::pair<glm::vec2, glm::vec2>(spaceshit->pos, spaceshit->vel));

	for (auto& laser : lasers) {
		std::get<0>(laser) = coord_mod(std::get<0>(laser) + std::get<1>(laser));
	}

	for (auto& asteroid : asteroids) {
		std::get<0>(asteroid) = coord_mod(std::get<0>(asteroid) + std::get<1>(asteroid));
	}

	// asteroid/laser collision
	int collision_count = 0;
	for (auto l = lasers.begin(); l != lasers.end(); l++) {
		for (auto a = asteroids.begin(); a != asteroids.end(); a++) {
			auto laser = *l;
			auto asteroid = *a;

			if (glm::distance(std::get<0>(laser), std::get<0>(asteroid)) < 50) {
				a = asteroids.erase(a);
				a--;
				l = lasers.erase(l);
				l--;
				collision_count++;
			}
			
			if (glm::distance(spaceshit->pos, std::get<0>(asteroid)) < 50) {
				spaceshit->vel = rotate_vec(spaceshit->vel, 90);
			}
		}
	}

	for (int i = 0; i < collision_count*(asteroids_destroyed_count+1); i++) {
		spawn_asteroid();
	}
	

	// asteroid/spaceshit collision
	for (auto a = asteroids.begin(); a != asteroids.end(); a++) {
		auto asteroid = *a;
		if (glm::distance(spaceshit->pos, std::get<0>(asteroid)) < 100) {
			spaceshit->vel = rotate_vec(spaceshit->vel, 90);
		}
	}

	asteroids_destroyed_count += collision_count;
}

void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	for (auto& laser : lasers) {
		sprite_laser.setPosition(std::get<0>(laser));
		sprite_laser.setRotation(vec2_to_degrees(std::get<1>(laser))-90);
		spriteBatchBuilder.addSprite(sprite_laser);
	}

	for (auto& asteroid : asteroids) {
		sprite_asteroid_lg.setPosition(std::get<0>(asteroid));
		sprite_asteroid_lg.setRotation(vec2_to_degrees(std::get<1>(asteroid))-90);
		spriteBatchBuilder.addSprite(sprite_asteroid_lg);
	}

	spaceshit->Render(spriteBatchBuilder);
}

void GameObject::spawn_asteroid()
{
	auto posx = rand() % 1000;
	auto posy = 0;
	if (rand()%2==0)
		std::swap(posx, posy);
	auto maxvel = 5;
	auto velx = (rand() % maxvel*2) - maxvel;
	auto vely = (rand() % maxvel*2) - maxvel;
	auto pos = glm::vec2(posx, posy);
	auto vel = glm::vec2(velx, vely);
	this->asteroids.push_back(std::tuple<glm::vec2, glm::vec2, float>(pos, vel, 5));
}