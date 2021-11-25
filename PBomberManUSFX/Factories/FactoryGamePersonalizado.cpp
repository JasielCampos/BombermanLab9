#include "FactoryGamePersonalizado.h"
FactoryGamePersonalizado::FactoryGamePersonalizado() {
    gameManager = GameManager::instance;
    scaledTileSize = 32;
}

std::shared_ptr<GameObject> FactoryGamePersonalizado::CreatePlayer(const int _positionX, const int _positionY)
{
    // spawn player
    auto player = std::make_shared<ClasicoPlayer>(gameManager->getAssetManager()->getTexture(Texture::Player1), gameManager->getRenderer());
    player->setPosition(_positionX, _positionY);
    player->setSize(scaledTileSize, scaledTileSize);
    player->setClip(tileSize, tileSize, tileSize * 4, 0);

    return dynamic_pointer_cast<GameObject>(player);
}


std::shared_ptr<GameObject> FactoryGamePersonalizado::CreateEnemy(AIType _type, const int _positionX, const int _positionY)
{
    //shared_ptr<GameObject> enemy(nullptr);
    auto enemy = std::make_shared<ClasicoEnemy>(gameManager->getAssetManager()->getTexture(Texture::Enemy1), gameManager->getRenderer());
    enemy->setPosition(_positionX, _positionY);
    enemy->setSize(scaledTileSize, scaledTileSize);
    enemy->setAIType(_type);

    return dynamic_pointer_cast<GameObject>(enemy);
}
