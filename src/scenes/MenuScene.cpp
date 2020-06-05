/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#include "MenuScene.hpp"
#include "ServiceLocator.hpp"

const std::string Indie::MenuScene::filepaths[5] = {
    "../ressources/images/bg_boxes.png",
    "../ressources/images/clouds.png",
    "../ressources/images/mountains.png",
    "../ressources/images/trees.png",
    "../ressources/images/ground.png"
};

const irr::core::vector2df Indie::MenuScene::velocities[5] = {
    irr::core::vector2df((irr::f32)10.f, (irr::f32)10.f),
    irr::core::vector2df((irr::f32)15.f, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)20.f, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)25.f, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)30.f, (irr::f32)0.000)
};

Indie::MenuScene::MenuScene(ContextManager &context)
    : context(context)
    , masterInfo(std::make_unique<Indie::MasterInfo>())
{
    this->loadMasterInfo();
}

Indie::MenuScene::~MenuScene()
{
    parallax.clear();
}

void Indie::MenuScene::setColor(irr::video::SColor color)
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i]->setColor(color);
}

void Indie::MenuScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);

    for (size_t i = 0; i < 5; i++) {
        std::unique_ptr<Parallax> tmp = std::make_unique<Parallax>(context);
        tmp->init(this->context, this->filepaths[i], POS(1280, 720), this->velocities[i]);
        this->parallax.push_back(std::move(tmp));
    }
}

void Indie::MenuScene::reset()
{
    parallax.clear();
    init();
}

void Indie::MenuScene::update(irr::f32 ticks)
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i]->update(ticks);
}

void Indie::MenuScene::renderPre3D()
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i]->draw();
}

void Indie::MenuScene::renderPost3D() {}


Indie::MasterInfo *Indie::MenuScene::getMasterInfo(void) const
{
    return this->masterInfo.get();
}

void Indie::MenuScene::setMasterInfo(const Indie::MasterInfo &masterInfo)
{
    this->masterInfo = std::make_unique<Indie::MasterInfo>(masterInfo);
}

void Indie::MenuScene::loadMasterInfo(void)
{
    MasterInfo info;

    try {
        std::vector<std::vector<std::string>> parsedData = ServiceLocator::getInstance().get<CSVParser>().parse("../ressources/.saves/xp.txt");

        if (parsedData.size() != 2)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/xp.txt\" corrupted.");
        for (auto data : parsedData) {
            if (data.size() != 2)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/xp.txt\" corrupted.");
            std::string nameType = data.at(0);
            int nbXp = stoi(data.at(1));
            if (nameType != "LVL" && nameType != "XP")
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/xp.txt\" corrupted.");
            if (nbXp < 0)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/xp.txt\" corrupted.");
            if (nameType == "LVL")
                info.lvl = nbXp;
            if (nameType == "XP")
                info.xp = nbXp;
        }
    } catch (const std::exception &e) {
        info.lvl = 0;
        info.xp = 0;
        std::cout << e.what() << std::endl;
    }
    try {
        std::vector<std::vector<std::string>> parsedData = ServiceLocator::getInstance().get<CSVParser>().parse("../ressources/.saves/highscoremap.txt");

        // Maybe check if the map exist ?
        for (auto data : parsedData) {
            if (data.size() != 2)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/highscoremap.txt\" corrupted.");
            std::string mapName = data.at(0);
            int highScore = stoi(data.at(1));
            if (highScore < 0)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/highscoremap.txt\" corrupted.");
            info.scores_map.insert(std::pair<std::string, int>(mapName, highScore));
        }
    } catch (const std::exception &e) {
        info.scores_map = {};
        std::cout << e.what() << std::endl;
    }
    this->setMasterInfo(info);
}