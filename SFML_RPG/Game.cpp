#include "Game.h"

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

void Game::init_variables()
{
    this->window = nullptr;

    this->dt = 0.f;
    this->fullScreen = false;
}

void Game::init_window()
{
    std::ifstream ifs("Configs/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

    bool full_screen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned anti_aliasing_level = 0;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> full_screen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> anti_aliasing_level;
    }
    ifs.close();

    this->fullScreen = full_screen;
    this->windowSettings.antialiasingLevel = anti_aliasing_level;

    if (this->fullScreen) {
        this->window = new sf::RenderWindow(window_bounds, title,
            sf::Style::Fullscreen, this->windowSettings);
    }
    else {
        this->window = new sf::RenderWindow(window_bounds, title,
            sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    }

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
    this->states.push(new MainMenuState(this->window, 
        &this->supportedKeys, &this->states));
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
    this->dt = this->dtClk.restart().asSeconds();
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

void Game::end_app()
{
    std::cout << "Closing Application..." << std::endl;
}