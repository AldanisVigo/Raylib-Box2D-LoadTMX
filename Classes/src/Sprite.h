#ifndef SPRITE_H
#define SPRITE_H
#include <iostream>
#include <raylib.h>
#include <box2d.h>
#include "Animation.h"

using namespace std;

class Sprite {
    public:
        Sprite();
        Sprite(b2Vec2,b2Rot,int,Color,b2BodyType,string,b2WorldId*,Animation*);
        Sprite(b2Vec2,b2Vec2, b2Rot,int,Color,b2BodyType,string,b2WorldId*);
        Sprite(float,float,b2Vec2,b2Rot,int,Color,b2BodyType,string,b2WorldId*);
        Sprite(char*,b2Vec2,int,int,string,b2WorldId*);
        b2Vec2 position;
        b2Vec2 size;
        b2Rot rotation;
        bool rotationLocked = false;
        int zIndex;
        string name;
        vector<string> groups;
        b2Polygon box;
        b2BodyDef bodyDefinition;
        b2BodyType bodyType;
        b2BodyId bodyId;
        b2ShapeDef shapeDefinition;
        b2ShapeId shapeId;
        Color color = RED;
        void draw();
        void drawPaletteTileSprite(int,int);
        void drawGridTileSprite(int tileSize,Vector2 pos,int tileId);
        b2WorldId worldId;
        void Move(b2Vec2);
        bool animated = false;
        bool textured = false;
        Animation* animation;
        Texture2D texture;
        bool debug = false;
        void updateCurrentAimation();
        bool flip;
        void drawCurrentAnimation();
};

#endif