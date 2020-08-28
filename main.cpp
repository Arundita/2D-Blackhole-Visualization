
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
using namespace sf;
using namespace std;

int main(int, char const**)
{
    //system("pwd");
    // Create the main window
    VideoMode vm(800,600);
    RenderWindow window(vm,"blackhole",Style::Fullscreen);
    
    const int c = 3;                        //speed of light
    const int G = 5;                                //universal gravitation constant
    const int M = 200;                                //mass of blackhole
    const int rs = (2 * G * M)/(c*c);            //Schwarzschild raduis
   
    SoundBuffer bgMusicBuffer;
    bgMusicBuffer.loadFromFile("sound/.wav");
    Sound bgmusic;
    bgmusic.setBuffer(bgMusicBuffer);
    
    SoundBuffer wooshSoundBuffer;
    wooshSoundBuffer.loadFromFile("sound/woosh.wav");
    Sound wooshSound;
    wooshSound.setBuffer(wooshSoundBuffer);
    
    SoundBuffer lightSoundBuffer;
    lightSoundBuffer.loadFromFile("sound/laser.wav");
    Sound lightSound;
    lightSound.setBuffer(lightSoundBuffer);
    
    
    //creating the background
    Texture textureBg;
    textureBg.loadFromFile("graphics/bg.png");
    Vector2u textureSize;  //Added to store texture size.
    textureSize = textureBg.getSize();
    Vector2u windowSize;   //Added to store window size
    windowSize = window.getSize();
    Sprite spriteBg;
    spriteBg.setTexture(textureBg);
    float ScaleX = (float) windowSize.x / textureSize.x;
    float ScaleY = (float) windowSize.y / textureSize.y;     //Calculate scale.
    spriteBg.setScale(ScaleX, ScaleY);
    
    //parameters for asteroid
    double speed = 0.12;//constants and start values
    long double angle = 90;
    const double rad = 57.2957795;
    double ang = 0;
    
    //parameters for the photon in the red orbit
    double speed_ro = 0.18;//constants and start values
    long double angle_ro = 90;
    const double rad_ro = 57.2957795;
    double ang_ro = 0;
    
    //parameters for the photon in the accretion region
    double speed_par = 0.11;//constants and start values
    long double angle_par = 90;
    const double rad_par = 57.2957795;
    double ang_par = 0;
    
    //parameters for the debree 1 in the accretion region
    double speed_deb1 = 0.12;//constants and start values
    long double angle_deb1 = 90;
    const double rad_deb1 = 57.2957795;
    double ang_deb1 = 0;
    
    //parameters for the debree 2 in the accretion region
    double speed_deb2 = 0.12;//constants and start values
    long double angle_deb2 = 90;
    const double rad_deb2 = 57.2957795;
    double ang_deb2 = 0;
    
    //parameters for the debree 3 in the accretion region
    double speed_deb3 = 0.12;//constants and start values
    long double angle_deb3 = 90;
    const double rad_deb3 = 57.2957795;
    double ang_deb3 = 0;
    
    //create the rectangle shape to mirror black hole - white
    RectangleShape blackHoleMirror;
    blackHoleMirror.setSize((Vector2f(50,580)));
    blackHoleMirror.setFillColor(Color(250,250,250,150));
    blackHoleMirror.setPosition(1500, 715);
    
    //create the rectangle shape to mirror the event horizon - pink
    RectangleShape eventHorizonMirror;
    eventHorizonMirror.setSize((Vector2f(300,150)));
    eventHorizonMirror.setFillColor(Color(250,350,250,150));
    eventHorizonMirror.setPosition(1290, 915);
    
    //create the rectangle shape to mirror the place where the red_orbit photon collides - red square
    RectangleShape redOrbitMirror;
    redOrbitMirror.setSize((Vector2f(30,30)));
    redOrbitMirror.setFillColor(Color(250,20,20,150));
    redOrbitMirror.setPosition(1300, 1045);
    
    //create the rectangle shape to mirror to intersect withthe photon flying out of the blackhole - henna
    RectangleShape spiralOutMirror;
    spiralOutMirror.setSize((Vector2f(320,50)));
    spiralOutMirror.setFillColor(Color(80,50,20,100));
    spiralOutMirror.setPosition(1240, 1000);
    
    //create the rectangle shape to mirror the accretion region - green
    RectangleShape accRegionMirror;
    accRegionMirror.setSize((Vector2f(50,800)));
    accRegionMirror.setFillColor(Color(50,160,60,50));
    accRegionMirror.setPosition(1490, 700);
    
    //create the rectangle shape to mirror the debris 1 region - yellow
    RectangleShape deb1Mirror;
    deb1Mirror.setSize((Vector2f(30,50)));
    deb1Mirror.setFillColor(Color(250,240,160,150));
    deb1Mirror.setPosition(1550, 1320);
    
    //create the rectangle shape to mirror the debris 2 region - yellow
    RectangleShape deb2Mirror;
    deb2Mirror.setSize((Vector2f(30,50)));
    deb2Mirror.setFillColor(Color(250,240,160,150));
    deb2Mirror.setPosition(1500, 450);
    
    //create the rectangle shape to mirror the debris 3 region - yellow
    RectangleShape deb3Mirror;
    deb3Mirror.setSize((Vector2f(70,30)));
    deb3Mirror.setFillColor(Color(250,240,160,150));
    deb3Mirror.setPosition(1400, 1400);
    
    /*--------------------------------------------OBJECTS------------------------------------------*/
    //create the accretion disk
    CircleShape accretionDisk;
    accretionDisk.setRadius(2.5*rs);
    accretionDisk.setFillColor(Color(128,128,128,100));
    accretionDisk.setPosition(920, 420);
    
    //create a blackhole
    CircleShape blackhole;
    blackhole.setRadius(rs);
    blackhole.setOutlineColor(Color(255,0,0,170));                     //photon orbit = 1.5*rs
    blackhole.setOutlineThickness(.6*rs);
    blackhole.setFillColor(Color(0,0,0,250));
    blackhole.setPosition(1250, 750);
    Vector2f origin_of_bh = blackhole.getOrigin();
    FloatRect lb_bh = blackhole.getLocalBounds();

    
    //blackhole image
    Texture bht;
    bht.loadFromFile("graphics/blackhole_1.png");
    Sprite bhsprite;
    bhsprite.setTexture(bht);
    bhsprite.setPosition(1040, 603);
    bhsprite.scale(.72,.72);
    
    //photon orbit image
       Texture pot;
       pot.loadFromFile("graphics/photonOrbit.png");
       Sprite posprite;
       posprite.setTexture(pot);
       posprite.setPosition(950, 485);
       posprite.scale(.52,.52);
    
    //creating photons for event horizon
    Texture photonT;
    photonT.loadFromFile("graphics/photon.png");
    const int numOfPhotons_eventHorizon = 10;
    int count = 0;
    Sprite photon_eventHorizon[numOfPhotons_eventHorizon];
    for(int i=0;i<numOfPhotons_eventHorizon;i++){
        photon_eventHorizon[i].setTexture(photonT);
        photon_eventHorizon[i].setPosition(100, 870+count);
        photon_eventHorizon[i].scale(.09,.09);
        count+=20;
    }
    //photons for red orbit
    Sprite photon_redOrbit;
    photon_redOrbit.setTexture(photonT);
    photon_redOrbit.setPosition(100,1260);
    photon_redOrbit.scale(.09,.09);
    
    //photons for accretion region
    Sprite photon_accretionRegion;
    photon_accretionRegion.setTexture(photonT);
    photon_accretionRegion.setPosition(100,1460);
    photon_accretionRegion.scale(.09,.09);
    
    //create asteroid
    Texture ast;
    ast.loadFromFile("graphics/asteroid.png");
    Sprite astSprite;
    astSprite.setTexture(ast);
    astSprite.setPosition(150, 1900);
    astSprite.scale(1.7,1.7);
    
    //create deb1
    Texture deb_1_tex;
    deb_1_tex.loadFromFile("graphics/debris_1.png");
    Sprite debris_1;
    debris_1.setTexture(deb_1_tex);
    debris_1.setPosition(1100, 2700);
    debris_1.scale(.15,.15);
    
    //create deb2
    Texture deb_2_tex;
    deb_2_tex.loadFromFile("graphics/debris_2.png");
    Sprite debris_2;
    debris_2.setTexture(deb_2_tex);
    debris_2.setPosition(2600, -100);
    debris_2.scale(.17,.17);
    
    //create deb3
    Texture deb_3_tex;
    deb_3_tex.loadFromFile("graphics/debris_3.png");
    Sprite debris_3;
    debris_3.setTexture(deb_3_tex);
    debris_3.setPosition(3300, 300);
    debris_3.scale(.27,.27);
    
    //create a planet body that is so big that it gets sucked into the black hole
    //planet
    Texture ground;
    ground.setSmooth(true);
    ground.setRepeated(true);
    ground.loadFromFile("graphics/body.png");

    //float radius = 100;
    RectangleShape planet;
    planet.setTexture(&ground);
    planet.setSize((Vector2f(550,550)));
    planet.setPosition(200, 270);
    
    //astronaut
    Texture astronautTexture;
    astronautTexture.setSmooth(true);
    astronautTexture.setRepeated(true);
    astronautTexture.loadFromFile("graphics/astronaut.png");

    RectangleShape astronaut;
    astronaut.setTexture(&astronautTexture);
    astronaut.setSize((Vector2f(200,150)));
    astronaut.setPosition(3000, 100);
    
    //trailing lights
    Texture trailingLightTexture;
    trailingLightTexture.setSmooth(true);
    trailingLightTexture.setRepeated(true);
    //trailingLightTexture.loadFromFile("graphics/trailingLight.png");

    RectangleShape trailingLight;
    trailingLight.setTexture(&trailingLightTexture);
    trailingLight.setFillColor(Color(250,250,250,0));
    trailingLight.setSize((Vector2f(5,5)));
    trailingLight.rotate(-27);
    trailingLight.setPosition(1260,1200);
       
    
   //variables
    Time dt;
    Clock clock;
    bool paused = true;
    bool orbitRegion = true;
    bool accretionRegion = true;
    bool accretionRegion_photon = true;
    bool loopGoesOn = true;
    bool stretchPlanet = false;
    bool absorbPlanet = false;
    bool stretchAstronaut = false;
    bool absorbAstronaut = false;
    bool accretionRegion_deb1 = true;
    bool accretionRegion_deb2 = true;
    bool accretionRegion_deb3 = true;
    float velocityOfPhotons = 0.0f;
    float intersectOfPhotonSpiralingOut;
    
    Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                 window.close();
             }
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){
                paused = false;
            }
        }
       
        if(!paused){
            //bgmusic.play();
            clock.restart();
                for(int i=0;i<numOfPhotons_eventHorizon;i++){
                    photon_eventHorizon[i].move(5,0);
                }
        
            if(orbitRegion){
                photon_redOrbit.move(5,0);
            }
         //case2: the photons that fall in the red area, should orbit and eventually fall,
                if(!orbitRegion){
                        if (angle_ro > 360)//if angle exceeds 360
                                angle_ro -= 360;//reset it
                    angle_ro += speed_ro;//angle in degrees
                        ang_ro = angle_ro/rad_ro;//angle in radians
                        photon_redOrbit.move(sin(ang_ro),cos(ang_ro));//move on a circular path
                    
                    speed_ro += 0.00001; //spiral in
                    
                    //if touches even horizon, hide it
                    if(photon_redOrbit.getGlobalBounds().intersects(redOrbitMirror.getGlobalBounds())){
                        wooshSound.play();
                        photon_redOrbit.setPosition(3000,3000);
                    }
                  
                }
            //case 3 - asteroid
            if(accretionRegion){
                astSprite.move(1.6,-.5);
                //astSprite.move(.16,-.05);
            }
            if(!accretionRegion){
                if (angle > 360)//if angle exceeds 360
                        angle -= 360;//reset it
                angle += speed;//angle in degrees
                ang = angle/rad;//angle in radians
                astSprite.move(sin(ang),cos(ang));//move on a circular path
            }
            
            //case 3 - debris 1
            if(accretionRegion_deb1){
                debris_1.move(.25,-.9);
            }
            if(!accretionRegion_deb1){
                if (angle_deb1 > 360)//if angle exceeds 360
                        angle_deb1 -= 360;//reset it
                angle_deb1 += speed_deb1;//angle in degrees
                ang_deb1 = angle_deb1/rad_deb1;//angle in radians
                debris_1.move(sin(ang_deb1),cos(ang_deb1));//move on a circular path
            }
            
            //case 3 - debris 2
            if(accretionRegion_deb2){
                debris_2.move(-.5,.2);
            }
            if(!accretionRegion_deb2){
                if (angle_deb2 > 360)//if angle exceeds 360
                        angle_deb2 -= 360;//reset it
                angle_deb2 += speed_deb2;//angle in degrees
                ang_deb2 = angle_deb2/rad_deb2;//angle in radians
                debris_2.move(-sin(ang_deb2),-cos(ang_deb2));//move on a circular path
            }
            
            //case 3 - debris 3
            if(accretionRegion_deb3){
                debris_3.move(-.5,.3);
            }
            if(!accretionRegion_deb3){
                if (angle_deb3 > 360)//if angle exceeds 360
                        angle_deb3 -= 360;//reset it
                angle_deb3 += speed_deb3;//angle in degrees
                ang_deb3 = angle_deb3/rad_deb3;//angle in radians
                debris_3.move(-sin(ang_deb3),cos(ang_deb3));//move on a circular path
            }
            
            
            
            
            
            
            
            if(accretionRegion_photon){
                photon_accretionRegion.move(5,0);
                //photon_accretionRegion.move(-3,0);
            }
            if(!accretionRegion_photon){
                if(!loopGoesOn){
                    photon_accretionRegion.move(4,9);
                    trailingLight.setFillColor(Color(250,250,250,250));
                    trailingLight.setSize(trailingLight.getSize() + Vector2f(0,9));
                    if(photon_accretionRegion.getPosition().y > 3000){
                        trailingLight.setFillColor(Color(250,250,250,0));
                    }
                }
                if(photon_accretionRegion.getGlobalBounds().intersects(spiralOutMirror.getGlobalBounds())){
                    lightSound.play();
                    loopGoesOn = false;
                    trailingLight.setSize(trailingLight.getSize() + Vector2f(0,-9));
                    //photon_accretionRegion.move(5,7);
                }
                if(loopGoesOn){
                    if (angle_par > 360)//if angle exceeds 360
                        angle_par -= 360;//reset it
                    angle_par += speed_par;//angle in degrees
                    ang_par = angle_par/rad_par;//angle in radians
                    photon_accretionRegion.move(sin(ang_par),cos(ang_par));//move on a circular path
                    speed_par += 0.00001;
                    trailingLight.setFillColor(Color(250,250,250,0));
                }
               
            }
            //case 4
            if(!stretchPlanet){
                planet.move(.05,.05);
            }
            
            if(stretchPlanet){
                planet.move(.05,.05);
                planet.setSize(planet.getSize() + Vector2f(0.25,-0.08));
            }
            if(absorbPlanet){
                //test.setOrigin(-test.getGlobalBounds().width, test.getGlobalBounds().height);
                planet.move(5,.15);
                planet.setPosition(3000, 3000);
            }
            
            
            
            if(!stretchAstronaut){
                astronaut.move(-.20,.1);
            }
            
            if(stretchAstronaut){
                astronaut.move(-.20,.1);
                astronaut.setSize(astronaut.getSize() + Vector2f(0.20,0));
            }
            if(absorbAstronaut){
                //test.setOrigin(-test.getGlobalBounds().width, test.getGlobalBounds().height);
                astronaut.move(-5,.15);
                astronaut.setPosition(3000, 3000);
            }
            
            
            
            
                //case 1: if the light falls inside th event horizon, light particles should get ablsorb by theblackhole without curving
            for(int i=0;i<numOfPhotons_eventHorizon;i++){
                if(photon_eventHorizon[i].getGlobalBounds().intersects(eventHorizonMirror.getGlobalBounds())){
                    wooshSound.play();
                    photon_eventHorizon[i].setPosition(3000, 3000);
                }
            }
            //case2: the photons that fall in the red area, should orbit and eventually fall,
            /*if (photon_redOrbit.getPosition().x < blackhole.getPosition().x + 0.9*rs){
                  orbitRegion = false;
          }*/
            if (photon_redOrbit.getGlobalBounds().intersects(blackHoleMirror.getGlobalBounds())){
                orbitRegion = false;
            }
            
            //the matter falling in the red area should get sucked in instantly.
            //if the mass is bigger, the gravitationalpull is gonna be bigger, in that case, the asteroid or matter will enter the red region and as soon as it enters thered region it is going to sucked into the event horizon as matter cwont spiral in the red region
            

                
            
            //case 3: the photons and matter that fall in the grey area should keep orbiting
         
            if(photon_accretionRegion.getGlobalBounds().intersects(accRegionMirror.getGlobalBounds())){
                intersectOfPhotonSpiralingOut = photon_accretionRegion.getGlobalBounds().intersects(accRegionMirror.getGlobalBounds());
                accretionRegion_photon = false;
            }
           
            if(astSprite.getGlobalBounds().intersects(accRegionMirror.getGlobalBounds())){
                    accretionRegion = false;
            }
            
            if(debris_1.getGlobalBounds().intersects(deb1Mirror.getGlobalBounds())){
                    accretionRegion_deb1 = false;
            }
            
            if(debris_2.getGlobalBounds().intersects(deb2Mirror.getGlobalBounds())){
                    accretionRegion_deb2 = false;
            }
            
            if(debris_3.getGlobalBounds().intersects(deb3Mirror.getGlobalBounds())){
                    accretionRegion_deb3 = false;
            }
            
            //case 4: stretch a planet
            if(planet.getGlobalBounds().intersects(accretionDisk.getGlobalBounds())){
                stretchPlanet = true;
            }
            //absorb the planet
            if(planet.getGlobalBounds().intersects(blackHoleMirror.getGlobalBounds())){
                wooshSound.play();
                absorbPlanet = true;
            }
            
            //stretch an astronaut
            if(astronaut.getGlobalBounds().intersects(accretionDisk.getGlobalBounds())){
                stretchAstronaut = true;
            }
            //absorb the astronaut
            if(astronaut.getGlobalBounds().intersects(blackHoleMirror.getGlobalBounds())){
                wooshSound.play();
                absorbAstronaut = true;
            }
            
        }
        
        
        
        
        //planet.rotate(.025);
        
        window.clear();
        window.draw(spriteBg);
        window.draw(accretionDisk);
        window.draw(blackhole);
        //window.draw(bhsprite);
        window.draw(astSprite);
        for(int i=0;i<numOfPhotons_eventHorizon;i++){
            window.draw(photon_eventHorizon[i]);
        }
        window.draw(trailingLight);
        window.draw(photon_redOrbit);
        window.draw(photon_accretionRegion);
       // window.draw(bodySprite);
        window.draw(debris_1);
        window.draw(debris_2);
        window.draw(debris_3);
        window.draw(planet);
        window.draw(astronaut);
        //window.draw(blackHoleMirror);
       // window.draw(eventHorizonMirror);
        //window.draw(accRegionMirror);
       // window.draw(spiralOutMirror);
       // window.draw(redOrbitMirror);
        //window.draw(deb1Mirror);
        //window.draw(deb2Mirror);
        //window.draw(deb3Mirror);
        window.display();
        }

    return EXIT_SUCCESS;
}
