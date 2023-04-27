#include "Game.h"

void Game::init_window()
{
    std::ifstream ifs("Configs/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::init_keys()
{
    std::ifstream ifs("Configs/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
       
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();
}

void Game::init_states()
{
    this->states.push(new GameState(this->window, &this->supportedKeys));
}

Game::Game()
{
    this->init_window();
    this->init_keys();
    this->init_states();
    
}

Game::~Game()
{
	delete this->window;
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::end_app()
{

}

// Functions
void Game::update_SFML_events()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::update()
{
    this->update_SFML_events();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);

        if (this->states.top()->get_quit()) {
            this->states.top()->end_state();
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->end_app();
        this->window->close();
    }
}

void Game::update_dt()
{
    // Updates the dt variable with the time it takes to update and render one frame    
    this->dt = this->dtClk.getElapsedTime().asSeconds();
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update_dt();
        this->update();
        this->render();
    }
}
