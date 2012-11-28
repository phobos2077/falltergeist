#include "States/NewGameState.h"
#include "Engine/Game.h"
#include "Engine/ResourceManager.h"
#include "UI/ImageButton.h"
#include "UI/TextArea.h"
#include "Engine/SurfaceSet.h"
#include "Fallout/GcdFileType.h"
#include "Fallout/BioFileType.h"
#include <iostream>
#include <sstream>

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::init()
{
    State::init();
    _isFullscreen = true;
    // background
    add(ResourceManager::getSurface("art/intrface/pickchar.frm"));

    // Begin game button
    ImageButton * beginGameButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 322);

    // Edit character button
    ImageButton * editButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 436, 319);

    // Create character button
    ImageButton * createButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 424);

    // Back to mainmenu button
    ImageButton * backButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 461, 424);
    backButton->onLeftButtonClick((EventHandler) &NewGameState::onBackButtonClick);

    // Previous character button
    ImageButton * prevCharacterButton = new ImageButton("art/intrface/slu.frm", "art/intrface/sld.frm", 292, 320);
    prevCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    ImageButton * nextCharacterButton = new ImageButton("art/intrface/sru.frm", "art/intrface/srd.frm", 318, 320);
    nextCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onNextCharacterButtonClick);

    // Characters images
    _selectedCharacter = 0;
    _characterImages = new SurfaceSet(27,23);
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/combat.frm"));
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/stealth.frm"));
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/diplomat.frm"));

    // Character data textarea

    //std::cout <<    ;

    GcdFileType * gcd = ResourceManager::getGcdFileType("premade/combat.gcd");

    std::stringstream ss;
    ss   << _t(100,"text/english/game/stat.msg") << " " << (gcd->strength < 10 ? "0" : "") << gcd->strength << "\r\n"
         << _t(101,"text/english/game/stat.msg") << " " << (gcd->perception < 10 ? "0" : "") << gcd->perception << "\r\n"
         << _t(102,"text/english/game/stat.msg") << " " << (gcd->endurance < 10 ? "0" : "") << gcd->endurance << "\r\n"
         << _t(103,"text/english/game/stat.msg") << " " << (gcd->charisma < 10 ? "0" : "") << gcd->charisma << "\r\n"
         << _t(104,"text/english/game/stat.msg") << " " << (gcd->intelligence < 10 ? "0" : "") << gcd->intelligence << "\r\n"
         << _t(105,"text/english/game/stat.msg") << " " << (gcd->agility < 10 ? "0" : "") << gcd->agility << "\r\n"
         << _t(106,"text/english/game/stat.msg") << " " << (gcd->luck < 10 ? "0" : "") << gcd->luck << "\r\n" ;





    _textStats1 = new TextArea("",300,100);
    _textStats1->setText((char *)ss.str().c_str());
    _textStats1->setFont("font1.aaf");
    _textStats1->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    //_textArea1->border(0xFF0000FF);
    _textBio = new TextArea("",450,50);
    _textBio->setText(ResourceManager::getBioFileType("premade/combat.bio")->getText());
    //_textBio->setText("aasdas\r\n\r\nasdfasdf\r\nasdfasdf\r\n");
    _textBio->setFont("font1.aaf");




    add(beginGameButton);
    add(editButton);
    add(createButton);
    add(backButton);
    add(prevCharacterButton);
    add(nextCharacterButton);

    add(_characterImages);
    add(_textStats1);
    add(_textBio);
}

void NewGameState::think()
{
}

void NewGameState::onBackButtonClick()
{
    _game->popState();
}

void NewGameState::onPrevCharacterButtonClick()
{
    if (_selectedCharacter > 0)
    {
        _selectedCharacter--;
    }
    else
    {
        _selectedCharacter = 2;
    }
    _characterImages->currentSurface = _selectedCharacter;
}

void NewGameState::onNextCharacterButtonClick()
{
    if (_selectedCharacter < 2)
    {
        _selectedCharacter++;
    }
    else
    {
        _selectedCharacter = 0;
    }
    _characterImages->currentSurface = _selectedCharacter;
}

}