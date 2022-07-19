#include "Game.h"
#define GRAVITY 400.0f
using namespace Valzuroid::Pinball;

void Valzuroid::Pinball::Game::InitializeSplashScreen(int seconds)
{
    float timeLeft = seconds;
    while(timeLeft >= 0)
    {
        interface.clear();
        interface.drawBackground();
        interface.drawLogo(timeLeft / seconds);
        sf::sleep(sf::milliseconds(10));
        timeLeft -= 0.01;
        interface.display();
    }
}

Valzuroid::Pinball::Game::Game(): manager(0,3), audioManager(true,("Audio/NEFFEX - Dangerous [Copyright Free].ogg"))
{
    last_frame = high_resolution_clock::now();
    exit = left = right = space = false;
}

Valzuroid::Pinball::Game::~Game()
{
    for (int i = 0; i < BallsNo; i++)
    {
        delete pBalls[i];
    }
    delete[] pBalls;

    for (int i = 0; i < ObstaclesNo; i++)
    {
        delete pObstacles[i];
    }
    delete[] pObstacles;
    delete[] pDrawn;

}

void Valzuroid::Pinball::Game::readInterfaceInput()
{
    interface.getControls(exit, left, right, space);

    if(currentMode == GameMode::MainMenu)
    {
        mainMenuUI.onMouseClickEvent(sf::Mouse::getPosition(interface.GetWindow()));
        return;
    }

    if (currentMode != GameMode::Ingame) return;
    manager.MouseClickEvent(sf::Mouse::getPosition(interface.GetWindow()));
    hudManager.onMouseClickEvent(sf::Mouse::getPosition(interface.GetWindow()));
}

void Valzuroid::Pinball::Game::StartAll()
{
    for (int i = 0; i < BallsNo; i++)
    {
        pBalls[i]->start();
    }

    for (int i = 0; i < ObstaclesNo; i++)
    {
        pObstacles[i]->start();
    }

    manager.Start();
    vfxManager.start();
}

void Valzuroid::Pinball::Game::Callback(int eventNo)
{
    cout << "Event No: " << eventNo << endl;

    if(eventNo == 0)
    {
        StartGame();
    }
}

void Valzuroid::Pinball::Game::StartGame()
{
    currentMode = GameMode::Ingame;
}

void Valzuroid::Pinball::Game::Initialize()
{
    InitializeSplashScreen(1);
    interface.LoadGraphics();
    InstantiateObstacles();
    StartAll();
}

void Valzuroid::Pinball::Game::simulate()
{
    // Measuring time elapsed in-between frames
    high_resolution_clock::time_point this_frame = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(this_frame - last_frame);
    last_frame = this_frame;
    double delta_time = time_span.count();  // Delta time in seconds

    //Update fps
    interface.setFPS("FPS: " + to_string(1.0/delta_time));
    if (currentMode == GameMode::MainMenu)
    {
        mainMenuUI.updateTick();
        return;
    }


    if (currentMode != GameMode::Ingame) return;

    ActivateBalls(space);
    FlippersMotion(left, right, delta_time);
    CollisionCheck(delta_time,manager);
    MoveBalls(delta_time);
    
    manager.UpdateTimer(delta_time);
    manager.Update(delta_time);

    vfxManager.updateTick(delta_time);
}

void Valzuroid::Pinball::Game::updateInterfaceOutput()
{
    interface.clear();

    if (currentMode == GameMode::MainMenu)
    {
        mainMenuUI.draw(interface);
    }

    if (currentMode == GameMode::Ingame)
    {
        //Load things
        interface.drawBackground();

        manager.Updategame(interface);
        DrawDrawables();
        vfxManager.draw(interface);
        UIElements(interface);
    }

    if (currentMode == GameMode::GameOver) 
    {
        manager.EndGame(interface);
    }
    interface.display();
}

bool Valzuroid::Pinball::Game::exited()
{
    return exit;
}

void Valzuroid::Pinball::Game::GameOver(bool lost) {
    Lost = lost;
    currentMode = GameMode::GameOver;
}

void Valzuroid::Pinball::Game::InstantiateObstacles() {
    file.open("Configurations/Obstacles.txt");
    if(file.is_open()){
        string Choice="0";
        while(Choice!="END") {
            file >> Choice;
            if (Choice=="PORTAL") {
                ReadPortals(file);
            } else if (Choice=="BALL") {
                ReadBalls(file);
            } else if (Choice=="FLIPPER") {
                ReadFlippers(file);
            } else if (Choice=="KICKER") {
                ReadKickers(file);
            } else if (Choice=="BUMPER"){
                ReadBumpers(file);
            } else if (Choice=="MAGNET"){
                ReadMagnets(file);
            } else if (Choice=="KICKER"){
                ReadKickers(file);
            } else if (Choice=="SWITCH"){
                ReadSwitchs(file);
            } else if (Choice=="COLLECTABLE"){
                ReadCollectables(file);
            } else if (Choice=="SPEEDBOOSTER"){
                ReadSpeedBoosters(file);
            } else if (Choice=="GATE"){
                ReadGates(file);
            } else if(Choice=="LANE"){
                ReadLanes(file);
            } else if(Choice=="RAMP"){
                ReadRamps(file);
            } else if(Choice=="SCOREMULTIPLIER"){
                ReadScoreMultipliers(file);
            } else if(Choice=="BULLSEYE"){
                ReadBullseyes(file);
            } else if(Choice=="WALL"){
                ReadWalls(file);
            }
        }
        file.close();
    }else{
        cout << "Error, unable to open Obstacles file!" << endl;
    }
}

void Valzuroid::Pinball::Game::AddObstacle(Obstacle *obstacle) {
    Obstacle** pTemp = new Obstacle* [ObstaclesNo+1];
    //Everything is copied onto a temporary array
    for (int i = 0; i < ObstaclesNo; i++) {
        pTemp[i] = pObstacles[i];
    }
    pTemp[ObstaclesNo] = obstacle;
    ObstaclesNo++;
    pObstacles = new Obstacle*[ObstaclesNo];
    for (int j = 0; j < ObstaclesNo; j++) {
        pObstacles[j] = pTemp[j];
    }

    delete[] pTemp;
}

void Valzuroid::Pinball::Game::ReadBalls(fstream &file) {
    Vector2D velocity, center;
    string IsMain, Trash;
    double radius;
    int BallsNo;
    file >> BallsNo;
    for (int i = 0; i < BallsNo; ++i) {
        //Center first
        file >> Trash;
        file >> center.x;
        file >> center.y;
        //Radius second
        file >> Trash;
        file >> radius;
        //Velocity third
        file >> Trash;
        file >> velocity.x;
        file >> velocity.y;
        //If main last
        file >> Trash;
        file >> IsMain;
        if (IsMain == "YES") {
            AddBall(new Ball( center, radius, velocity, true));
            AddDrawable(pBalls[i]);
        } else if (IsMain == "NO") {
            AddBall(new Ball( center, radius, velocity, false));
            AddDrawable(pBalls[i]);
        }
    }
}

void Valzuroid::Pinball::Game::ReadFlippers(fstream &file) {
    int FlippersNo = 0;
    file >> FlippersNo;

    for (int i = 0; i < FlippersNo; i++) {
        Vector2D Center;
        string Flippertype, Trash;
        double length, angle, MajorRadius, MinorRadius, NormalAngle, ExtendedAngle, Velocity;
        file >> Trash;
        file >> Flippertype;
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> length;
        file >> Trash;
        file >> angle;
        file >> Trash;
        file >> MajorRadius;
        file >> Trash;
        file >> MinorRadius;
        file >> Trash;
        file >> NormalAngle;
        file >> Trash;
        file >> ExtendedAngle;
        file >> Trash;
        file >> Velocity;

        if (Flippertype == "RIGHT") {
            AddObstacle(new Flipper(FlipperType::RIGHT, Center, length, angle, MajorRadius, MinorRadius, NormalAngle,
                                    ExtendedAngle, Velocity));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        } else if (Flippertype == "LEFT") {
            AddObstacle(new Flipper(FlipperType::LEFT, Center, length, angle, MajorRadius, MinorRadius, NormalAngle,
                                    ExtendedAngle, Velocity));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        }
    }
}

void Valzuroid::Pinball::Game::ReadBumpers(fstream &file) {
    Vector2D position;
    double radius;
    int bumpersNo, type;
    string trash;
    file >> bumpersNo;
    for (int i = 0; i < bumpersNo; i++) {
        file >> trash;
        file >> position.x;
        file >> position.y;
        file >> trash;
        file >> radius;
        file >> trash;
        file >> type;
        if (type == 0) {
            AddObstacle(new PopBumper(position, radius));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        } else if (type == 1) {
            AddObstacle(new ThrustBumper(position, radius));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        } else if (type == 2) {
            AddObstacle(new VibraniumBumper(position, radius));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        } else if (type == 3) {
            AddObstacle(new ScoreMultiplier(position, radius));
            AddDrawable(pObstacles[ObstaclesNo-1]);
        }
    }
}

void Valzuroid::Pinball::Game::CollisionCheck(double collision_time, GameManager & manager) {
    for (int i = 0; i < BallsNo; i++) {
        pBalls[i]->setAcceleration({0, 400});
        for (int j = 0; j <ObstaclesNo; j++) {
            CollisionResponse response = pObstacles[j]->collideWith(*pBalls[i], collision_time, manager);
            if (response.ballSpeed == Vector2D::zero) continue;
            cout << "VFX?" << endl;
            vfxManager.AddHitVFX(response.collisionPoint);
            pBalls[i]->setCenter(response.ballPosition);
            pBalls[i]->setAcceleration(pBalls[i]->getAcceleration()+ response.ballSpeed);
        }
        //With other balls as well.
        for (int k = 0; k <BallsNo; k++) {
            pBalls[i]->setAcceleration(pBalls[i]->getAcceleration()+pBalls[k]->collideWith(*pBalls[i],collision_time,manager));
        }
    }
}

void Valzuroid::Pinball::Game::DrawDrawables()
{
    for (int i = 0; i < DrawablesNo; i++) 
    {
        pDrawn[i]->draw(interface);
    }

    hudManager.draw(interface);
}

void Valzuroid::Pinball::Game::ActivateBalls(bool space) {
    for (int i = 0; i <BallsNo ;i++) {
        if(pBalls[i]->getisMain())
            pBalls[i]->Activate(space);
    }
}

void Valzuroid::Pinball::Game::FlippersMotion(bool left, bool right, double delta_time) {
    Flipper *pFlipper;
    for (int i = 0; i <ObstaclesNo; i++) {
        pFlipper = dynamic_cast<Flipper*>(pObstacles[i]);
        if(pFlipper!=NULL){
            pFlipper->MoveFlipper(left, right, delta_time);
        }
    }
}

void Valzuroid::Pinball::Game::ReadWalls(fstream &file) {
    string Trash,Choice;
    int WallsNo;
    Vector2D Center;
    bool isVertical=false;

    file >> WallsNo;
    for (int i = 0; i <WallsNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> Choice;
        if(Choice=="YES"){
            isVertical=true;
        }else if(Choice=="NO"){
            isVertical=false;
        }

        AddObstacle(new Wall(isVertical,Center));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }

}

void Valzuroid::Pinball::Game::ReadPortals(fstream &file) {
    string Trash;
    double radius;
    Vector2D Pos1,Pos2;
    int PortalsNo;
    file >> PortalsNo;
    for (int i = 0; i <PortalsNo; i++) {
        file >> Trash;
        file >> Pos1.x;
        file >> Pos1.y;
        file >> Trash;
        file >> Pos2.x;
        file >> Pos2.y;
        file >> Trash;
        file >> radius;
        AddObstacle(new Portal(Pos1,Pos2,radius));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::MoveBalls(double time) {
    for (int i = 0; i <BallsNo; i++) {
        pBalls[i]->move(time,manager,Lost);
        pBalls[i]->UpdateBoost(time);
    }
}

void Valzuroid::Pinball::Game::AddDrawable(Drawn *drawn){
    Drawn **pTemp = new Drawn*[DrawablesNo+1];
    //Everything is copied onto a temporary array
    for (int i = 0; i <DrawablesNo; i++) {
        pTemp[i]=pDrawn[i];
    }
    pTemp[DrawablesNo]=drawn;
    DrawablesNo++;
    pDrawn = new Drawn*[DrawablesNo];
    for (int j = 0; j <DrawablesNo; j++) {
        pDrawn[j] = pTemp[j];
    }

    delete[]pTemp;
}

void Valzuroid::Pinball::Game::AddBall(Ball *ball) {
    Ball **pTemp = new Ball*[BallsNo+1];
    //Everything is copied onto a temporary array
    for (int i = 0; i <BallsNo; i++) {
        pTemp[i] = pBalls[i];
    }
    pTemp[BallsNo] = ball;
    BallsNo++;
    pBalls = new Ball*[BallsNo];
    for (int j = 0; j <BallsNo; j++) {
        pBalls[j]=pTemp[j];
    }
    delete[]pTemp;
}

void Valzuroid::Pinball::Game::ReadMagnets(fstream& file) {
    string Trash;
    Vector2D Position;
    double MagnetRadius,radius;
    int MagnetNo;
    file >> MagnetNo;
    for (int i = 0; i <MagnetNo; i++)
    {
        file >> Trash;
        file >> Position.x;
        file >> Position.y;
        file >> Trash;
        file >> MagnetRadius;
        file >> Trash;
        file >> radius;
        AddObstacle(new Magnet(Position,MagnetRadius,radius));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadGates(fstream& file){
    string Trash;
    double length,width;
    int GatesNo;
    Vector2D Center;

    file >> GatesNo;
    for (int i = 0; i <GatesNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> length;
        file >> Trash;
        file >> width;
        AddObstacle(new Gate(Center,length,width));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }

}

void Valzuroid::Pinball::Game::ReadKickers(fstream &file)
{
    string Trash;
    double x1,y1,x2,y2,x3,y3;
    int NoFrame=0;
    file >> NoFrame;
    for (int i = 0; i <NoFrame; i++) {
        file >> Trash;
        file >> x1;
        file >> Trash;
        file >> y1;
        file >> Trash;
        file >> x2;
        file >> Trash;
        file >> y2;
        file >> Trash;
        file >> x3;
        file >> Trash;
        file >> y3;
        AddObstacle(new Kicker(x1, x2, x3, y1, y2, y3));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadSwitchs(fstream &file) {
    Vector2D position;
    string trash;
    int SwitchNo;
    double Length;

    file >> SwitchNo;
    for (int i = 0; i <SwitchNo; i++) {
        file >> trash;
        file >> position.x;
        file >> position.y;
        file >> trash;
        file >> Length;

        AddObstacle(new Switch(position,Length));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadCollectables(fstream &file) {
    string Letter,Trash;
    double radius;
    int CollectablesNo;
    Vector2D Center;

    file >> CollectablesNo;
    for (int i = 0; i <CollectablesNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> radius;
        file >> Letter;
        AddObstacle(new Collectable(radius,Letter,Center));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadSpeedBoosters(fstream &file) {
    string Trash;
    int BoostersNo;
    double radius;
    Vector2D Center;

    file >> BoostersNo;
    for (int i = 0; i <BoostersNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> radius;
        AddObstacle(new SpeedBooster(radius,Center));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::DebugMode(Interface & interface) {
    //Debug
    for (int i = 0; i < BallsNo; i++) {
        if(pBalls[i]->getisMain()){
            Debug="X: " + to_string(pBalls[i]->GetCenter().x) + " Y: " + to_string(pBalls[i]->GetCenter().y);
        }
    }
    interface.drawText(Debug, 24, {GAME_WIDTH+1,GAME_HEIGHT/2.0});

    //FPS UPDATE
    interface.drawFPS();
}

void Valzuroid::Pinball::Game::UIElements(Interface& interface) {
    //Black background
    interface.drawUIBackground();
    //Debug
    //DebugMode(interface);
    manager.Updategame(interface);
}

void Valzuroid::Pinball::Game::ReadLanes(fstream &file) {
    double Length;
    Vector2D Center;
    int LanesNo;
    string Trash;

    file >> LanesNo;

    for (int i = 0; i <LanesNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> Length;
        AddObstacle(new Lane(Length, Center));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadRamps(fstream &file) {
    double Angle;
    string Trash;
    int RampsNo;
    Vector2D Size,Center;

    file >> RampsNo;
    for (int i = 0; i <RampsNo; i++) {
        file >> Trash;
        file >> Size.x;
        file >> Size.y;
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> Angle;

        AddObstacle( new Ramp(Size,Center,Angle));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }

}

void Valzuroid::Pinball::Game::ReadScoreMultipliers(fstream &file) {
    Vector2D Center;
    string Trash;
    int ScoreMultipliersNo;
    double Radius;

    file >> ScoreMultipliersNo;
    for (int i = 0; i <ScoreMultipliersNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> Radius;

        AddObstacle( new ScoreMultiplier(Center,Radius));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}

void Valzuroid::Pinball::Game::ReadBullseyes(fstream &file) {
    string Trash,Choice;
    Vector2D Center;
    double Length;
    bool isVertical=false;
    int BullseyeNo;

    file >> BullseyeNo;
    for (int i = 0; i <BullseyeNo; i++) {
        file >> Trash;
        file >> Center.x;
        file >> Center.y;
        file >> Trash;
        file >> Length;
        file >> Choice;

        if(Choice== "YES"){
            isVertical=true;
        }else if(Choice=="NO"){
            isVertical=false;
        }

        AddObstacle( new Bullseye(Center,Length,isVertical));
        AddDrawable(pObstacles[ObstaclesNo-1]);
    }
}
