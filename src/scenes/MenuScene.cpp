/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#include "MenuScene.hpp"
#include "ServiceLocator.hpp"
#include "MusicManager.hpp"
#include <filesystem>

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

std::string Indie::MenuScene::getFileName(std::string const &filepath)
{
    std::string filename(filepath.c_str());
    const size_t last_slash_id = filename.find_last_of("\\/");

    if (std::string::npos != last_slash_id)
        filename.erase(0, last_slash_id + 1);
    const size_t period_id = filename.rfind('.');
    if (std::string::npos != period_id)
        filename.erase(period_id);
    return (filename);
}

void Indie::MenuScene::saveHighScoreMap(std::string mapPath, int score)
{
    MasterInfo *info = this->getMasterInfo();
    bool isExist = false;

    for (auto &HighScoredMap : info->scores_map) {
        if (getFileName(mapPath) == HighScoredMap.first) {
            if (score > HighScoredMap.second) {
                isExist = true;
                HighScoredMap.second = score;
                break;
            }
        }
    }
    if (isExist == false)
        info->scores_map.insert(std::pair<std::string, int>(getFileName(mapPath), score));
}
