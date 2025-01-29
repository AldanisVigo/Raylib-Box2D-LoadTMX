#include "Sprite.h"
#include <math.h>

Sprite::Sprite(){

}

Sprite::Sprite(b2Vec2 pos, b2Vec2 size, b2Rot rot, int zIdx, Color c, b2BodyType bodType, string nm, b2WorldId* worldId) {
    color = c;
    name = nm;
    position = pos;
    rotation = rot;
    zIndex = zIdx;
    textured = false;
    animated = false;

    // Creating a box shape with half-width and half-height
    box = b2MakeBox(size.x / 2, size.y / 2);
    bodyDefinition = b2DefaultBodyDef();
    bodyDefinition.type = bodType;
    bodyDefinition.position = pos;
    bodyDefinition.rotation = rot;  // Apply rotation to body definition
    bodyId = b2CreateBody(*worldId, &bodyDefinition);

    shapeDefinition = b2DefaultShapeDef();
    shapeId = b2CreatePolygonShape(bodyId, &shapeDefinition, &box);
}

/*
    Constructor used to create tiles for the TileGrid in the TileMapLayer
*/
Sprite::Sprite(char* tileTexturePath,b2Vec2 pos,int tileSize,int zIdx,string tileName,b2WorldId* wrldId){
    texture = LoadTexture(tileTexturePath);
    position = pos;
    size = b2Vec2{
        (float)tileSize,
        (float)tileSize
    };
    
    zIndex = zIdx;
    name = tileName;
    worldId = *wrldId;
    animated = false;
    textured = true;
}

// Constructor using float pointers (unchanged)
Sprite::Sprite(float x, float y, b2Vec2 sz, b2Rot rot, int zIdx, Color c, b2BodyType bodType, string nm, b2WorldId* worldId) {
    color = c;
    name = nm;
    b2Vec2 newPos = b2Vec2_zero;
    newPos.x = x + sz.x / 2;
    newPos.y = y + sz.y / 2;
    position = newPos;
    textured = false;
    animated = false;

    size = sz;
    rotation = rot;
    zIndex = zIdx;

    // Creating a box shape with half-width and half-height
    box = b2MakeBox(sz.x / 2, sz.y / 2);
    bodyDefinition = b2DefaultBodyDef();
    bodyDefinition.type = bodType;
    bodyDefinition.position = newPos;
    bodyDefinition.rotation = rot;  // Apply rotation to body definition
    bodyId = b2CreateBody(*worldId, &bodyDefinition);

    shapeDefinition = b2DefaultShapeDef();
    shapeId = b2CreatePolygonShape(bodyId, &shapeDefinition, &box);
}

Sprite::Sprite(b2Vec2 p, b2Rot rot, int zIdx, Color clr, b2BodyType bType, string nm, b2WorldId* wrldId, Animation* anim){
    worldId = *wrldId;
    color = clr;
    name = nm;
    position = p;
    float w =  anim->atlas.width / float(anim->num_frames);
    float h =  (float)anim->atlas.height;
    size = b2Vec2{
       w,
       h
    };
    rotation = rot;
    zIndex = zIdx;

    // Creating a box shape with half-width and half-height
    box = b2MakeBox(size.x / 2, size.y / 2);
    bodyDefinition = b2DefaultBodyDef();
    bodyDefinition.type = bType;
    bodyDefinition.position = p;
    bodyDefinition.rotation = rot;  // Apply rotation to body definition
    bodyId = b2CreateBody(*wrldId, &bodyDefinition);

    shapeDefinition = b2DefaultShapeDef();
    shapeId = b2CreatePolygonShape(bodyId, &shapeDefinition, &box);

    animation = anim;
    animated = true;
    textured = false; 
}

// Drawing the sprite (updated)
void Sprite::draw() {
    b2Vec2 p;
    
    if(b2Body_IsValid(bodyId)){
        // Get the position of the body from Box2D
        p = b2Body_GetPosition(bodyId);
    }else{
        p = b2Vec2{
            position.x,
            position.y
        };
    }
    
    Rectangle rec;
    // Create a Rectangle for rendering in Raylib
    rec.x = p.x; // Center the rectangle on the body position (adjust by half the width)
    rec.y = p.y; // Center the rectangle on the body position (adjust by half the height)
    rec.width = size.x;
    rec.height = size.y;

    float r = 0.0f * (180.0f / M_PI);

    if (!rotationLocked) {
        // Get rotation in radians
        r = b2Rot_GetAngle(b2Body_GetRotation(bodyId));
    }else{
        b2Body_SetFixedRotation(bodyId,true);
    }

    if(debug){
        DrawRectangleLines(
            p.x - size.x / 2,
            p.y - size.y / 2,
            size.x,
            size.y,
            GREEN
        );
    }

    if(!textured && !animated){
        // Draw the rectangle with proper adjustment
        DrawRectanglePro(rec, Vector2{size.x / 2, size.y / 2}, r * (180.0f / M_PI), color);
        // Debug Draw the collider
    }else if(textured && !animated){
        // sDraw texture
        DrawTexture(texture,position.x,position.y,WHITE);
    }else if(animated && !textured){
        drawCurrentAnimation();
    }else{
        animated = false;
        textured = true;
        // Just display a texture
    }
    updateCurrentAimation();
}

void Sprite::drawPaletteTileSprite(int tileId,int tS){
    DrawTextureRec(texture,Rectangle{
        float(tileId * tS),
        0,
        (float)tS,
        (float)tS
    }, Vector2{position.x,position.y}, WHITE);            
}

void Sprite::drawGridTileSprite(int tileSize,Vector2 pos,int tileId){
    // DrawTexture(texture,pos.x,pos.y,WHITE);
    DrawTextureRec(texture,Rectangle{
        float(tileId * tileSize),
        0,
        (float)tileSize,
        (float)tileSize
    }, Vector2{pos.x,pos.y}, WHITE);  
     
    // DrawRectangleLines(
    //     pos.x,
    //     pos.y,
    //     tileSize,
    //     tileSize,
    //     RED
    // );
    // DrawRectanglePro(Rectangle{
    //     pos.x,
    //     pos.y,
    //     (float)tileSize,
    //     (float)tileSize
    // },Vector2{0,0},0.0f,RED);
}

// Moving the sprite (updated for velocity)
void Sprite::Move(b2Vec2 velocity) {
    // Apply velocity to the sprite (simpler than using forces)
    b2Body_SetLinearVelocity(bodyId, velocity);
}

void Sprite::updateCurrentAimation(){
    if(!animated) return;
    if(animation == nullptr || animation == NULL) {
        // cout << "Animation is null" << endl;
    }else{
        if (animation->frame_timer > animation->frame_length) {
            animation->current_frame++;
            animation->frame_timer -= animation->frame_length;
            if (animation->current_frame >= animation->end_frame - animation->start_frame) {
                animation->current_frame = 0;  // Reset to the first frame
            }
        }
    }
}

void Sprite::drawCurrentAnimation(){
    animation->frame_timer += GetFrameTime();
    float frame_x = (animation->start_frame + animation->current_frame) * (animation->atlas.width / animation->num_frames);
    float frame_y = 0.0f;
    float frame_width = animation->atlas.width / animation->num_frames / 2;
    float frame_height = animation->atlas.height;  
    Rectangle sourceRectangle = Rectangle{
        frame_x, 
        frame_y,
        frame_width * 2,
        frame_height
    };

    if(flip){
        sourceRectangle.width = -sourceRectangle.width;
    }

    b2Vec2 pos = b2Body_GetPosition(bodyId);

    Rectangle destinationRectangle = Rectangle{
        pos.x + frame_width,
        pos.y + frame_height / 2,
        frame_width * 2,
        frame_height
    };
    
    DrawTexturePro(animation->atlas, sourceRectangle, destinationRectangle, {destinationRectangle.width,destinationRectangle.height}, 0,WHITE);
}