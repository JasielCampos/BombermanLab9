#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/StageScene.h"

// ++increment for menu id
MenuItem& operator++(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) + 1);
    if(c == MenuItem::Last)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
    return c;
}

// --decrement for menu id
MenuItem& operator--(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) - 1);
    if(c == MenuItem::None)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItem operator++(MenuItem& c, int)
{
    MenuItem result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItem operator--(MenuItem& c, int)
{
    MenuItem result = c;
    --c;
    return result;
}

MenuScene::MenuScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(Texture::MenuBack), gameManager->getRenderer());
    
    background->setPosition(30, 20);
    
    background->setSize(gameManager->getWindowWidth() - 60,  static_cast<int>(gameManager->getWindowHeight() / 1.5f) - 20);
    addObject(background);

    // start menu
   /* startText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "INICIO");
    startText->setColor(colorPressed);
    startText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f), background->getHeight() + 60);
    addObject(startText);*/

    startCartoonText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CARTOON");
    startCartoonText->setColor(colorPressed);
    startCartoonText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startCartoonText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startCartoonText->getWidth() / 2.0f), 380);
    addObject(startCartoonText);

    startClasicText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CLASIC");
    startClasicText->setColor(colorStandard);
    startClasicText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startClasicText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startCartoonText->getWidth() / 2.0f), 420);
    addObject(startClasicText);
   
    startCustomText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CUSTOM");
    startCustomText->setColor(colorStandard);
    startCustomText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startCustomText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startClasicText->getWidth() / 2.0f), 460);
    addObject(startCustomText);

    startRealisticText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "REALIST");
    startRealisticText->setColor(colorStandard);
    startRealisticText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startRealisticText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startCustomText->getWidth() / 2.0f), 500);
    addObject(startRealisticText);

    // exit menu
    exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "SALIR");
    exitText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    exitText->setPosition(startCartoonText->getPositionX(), 550);
    addObject(exitText);

    gameManager->getSceneManager()->addScene("gameover", std::make_shared<GameOverScene>(gameManager));
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MainMenu));
}

void MenuScene::onEnter()
{
    menuMusic->play();
}

void MenuScene::onExit()
{
    menuMusic->stop();
}

void MenuScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.scancode)
        {
            // we should select next menu item
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                currentSelectedMenu++;
                onMenuItemSelect();
                break;
            // we should select prev menu item
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                currentSelectedMenu--;
                onMenuItemSelect();
                break;
            // enter in menu item
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_RETURN:
                onMenuItemPress();
                break;
            default:
                break;
        }
    }
}

void MenuScene::onMenuItemSelect()
{
    // reset menu items color
    startCartoonText->setColor(colorStandard);
    startClasicText->setColor(colorStandard);
    startCustomText->setColor(colorStandard);
    startRealisticText->setColor(colorStandard);

    exitText->setColor(colorStandard);
    // change color of selected menu item
    switch(currentSelectedMenu)
    {
        case MenuItem::StartCartoon:
            startCartoonText->setColor(colorPressed);
            break;
        case MenuItem::StartClasic:
            startClasicText->setColor(colorPressed);
            break;
        case MenuItem::StartCustom:
            startCustomText->setColor(colorPressed);
            break;
        case MenuItem::StartRealistic:
            startRealisticText->setColor(colorPressed);
            break;
        case MenuItem::Exit:
            exitText->setColor(colorPressed);
            break;
        default:
            break;
    }
}

int MenuScene::onMenuItemPress()
{
    switch(currentSelectedMenu)
    {
        case MenuItem::StartCartoon:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0, 1));
            gameManager->getSceneManager()->activateScene("stage");
            return 1;
            break;
        case MenuItem::StartClasic:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0, 2));
            gameManager->getSceneManager()->activateScene("stage");
            return 2;
            break;
        case MenuItem::StartCustom:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0, 3));
            gameManager->getSceneManager()->activateScene("stage");
            return 3;
            break;
        case MenuItem::StartRealistic:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0, 4));
            gameManager->getSceneManager()->activateScene("stage");
            return 4;
            break;
        case MenuItem::Exit:
            // stop gameManager loop
            gameManager->stop();
            break;
        default:
            break;
    }
}
