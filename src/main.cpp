#include <raylib.h> 
#include <box2d.h>
#include <Sprite.h>
#include <loadtmx.hpp>
#include <TilePalette.h>
#include <TileMapLayer.h>
#include <CursorController.h>

using namespace std;

static float posx = 0.0f;
static float posy = 0.0f;
static float speed = 100.0f;
static float jumpVelocity = 400.0f;

void checkControllerInput(b2Vec2* velocity) {
    if(IsGamepadAvailable(0)){
        // cout << "Gamepad available: " << IsGamepadAvailable(0) << endl;
        // cout << "Gamepad Name: " << GetGamepadName(0) << endl;
        // cout << "Gamepad Axis Count: " <<  GetGamepadAxisCount(1) << endl;
        // cout << "Button Pressed: " << GetGamepadButtonPressed() << endl;
        // cout << "Axis 0 Movement:" << GetGamepadAxisMovement(0,0) << endl;
        // cout << "Gamepad L Button: " << IsGamepadButtonPressed(1,GAMEPAD_AXIS_LEFT_X) << endl;
        // cout << "Gamepad R Button: " << IsGamepadButtonPressed(1,GAMEPAD_AXIS_LEFT_Y) << endl;
        const float leftStickDeadzoneX = 0.1f;
        const float leftStickDeadzoneY = 0.1f;
        const float rightStickDeadzoneX = 0.1f;
        const float rightStickDeadzoneY = 0.1f;
        const float leftTriggerDeadzone = -0.9f;
        const float rightTriggerDeadzone = -0.9f;

        // Get axis values
        float leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float rightStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y);
        float leftTrigger = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER);
        float rightTrigger = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Calculate deadzones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
        if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX) rightStickX = 0.0f;
        if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY) rightStickY = 0.0f;
        if (leftTrigger < leftTriggerDeadzone) leftTrigger = -1.0f;
        if (rightTrigger < rightTriggerDeadzone) rightTrigger = -1.0f;

        // cout << "Left Stick X: " << leftStickX << endl;
        // cout << "left Stick Y: " << leftStickY << endl;
        // cout << "Right Stick X: " << rightStickX << endl;
        // cout << "Right Stick Y: " << rightStickY << endl;

        // Dpads
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)){
            // cout << "DPAD UP PRESSED" << endl;
        }
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
            // cout << "DPAD DOWN PRESSED" << endl;
        }
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || leftStickX <= -0.7f){
            // cout << "DPAD LEFT PRESSED" << endl;
            velocity->x += -speed;
        }
        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || leftStickX >= 0.7f){
            // cout << "DPAD RIGHT PRESSED" << endl;
            velocity->x += speed;
        }

        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
            // cout << "X BUTTON PRESSED" << endl;
            velocity->x *= 2;
        }

        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
            // cout << "A BUTTON PRESSED" << endl;
            velocity->y = -jumpVelocity;
        }

        
    }
    if(IsGamepadAvailable(1)){
        // cout << "Gamepad available: " << IsGamepadAvailable(0) << endl;
        // cout << "Gamepad Name: " << GetGamepadName(0) << endl;
        // cout << "Gamepad Axis Count: " <<  GetGamepadAxisCount(1) << endl;
        // cout << "Button Pressed: " << GetGamepadButtonPressed() << endl;
        // cout << "Axis 0 Movement:" << GetGamepadAxisMovement(0,0) << endl;
        // cout << "Gamepad L Button: " << IsGamepadButtonPressed(1,GAMEPAD_AXIS_LEFT_X) << endl;
        // cout << "Gamepad R Button: " << IsGamepadButtonPressed(1,GAMEPAD_AXIS_LEFT_Y) << endl;
        const float leftStickDeadzoneX = 0.1f;
        const float leftStickDeadzoneY = 0.1f;
        const float rightStickDeadzoneX = 0.1f;
        const float rightStickDeadzoneY = 0.1f;
        const float leftTriggerDeadzone = -0.9f;
        const float rightTriggerDeadzone = -0.9f;

        // Get axis values
        float leftStickX = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y);
        float rightStickX = GetGamepadAxisMovement(1, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(1, GAMEPAD_AXIS_RIGHT_Y);
        float leftTrigger = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_TRIGGER);
        float rightTrigger = GetGamepadAxisMovement(1, GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Calculate deadzones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
        if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX) rightStickX = 0.0f;
        if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY) rightStickY = 0.0f;
        if (leftTrigger < leftTriggerDeadzone) leftTrigger = -1.0f;
        if (rightTrigger < rightTriggerDeadzone) rightTrigger = -1.0f;

        // cout << "Left Stick X: " << leftStickX << endl;
        // cout << "left Stick Y: " << leftStickY << endl;
        // cout << "Right Stick X: " << rightStickX << endl;
        // cout << "Right Stick Y: " << rightStickY << endl;


        // Dpads
        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_UP)){
            // cout << "DPAD UP PRESSED" << endl;
        }
        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
            // cout << "DPAD DOWN PRESSED" << endl;
        }
        
        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || leftStickX <= -0.7f){
            // cout << "DPAD LEFT PRESSED" << endl;
            velocity->x += -speed;
        }
        
        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || leftStickX >= 0.7f){
            // cout << "DPAD RIGHT PRESSED" << endl;
            velocity->x += speed;
        }

        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
            // cout << "X BUTTON PRESSED" << endl;
            velocity->x *= 2;
        }

        if (IsGamepadButtonDown(1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
            // cout << "A BUTTON PRESSED" << endl;
            velocity->y = -jumpVelocity;
        }
        
        
    }else{
        // cout << "No gamepad available." << endl;
    }
}

int main(){
    const int screenWidth = 1024, screenHeight = 780;
    InitWindow(screenWidth, screenHeight, "Raylib + Box2D + LoadTMX");

    //Initialize the cursor controller here
    CursorController* cursorController = new CursorController();

    InitAudioDevice();      // Initialize audio device
    Music music = LoadMusicStream("../sounds/background.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music,1.0f);
    SetTargetFPS(61);
    b2SetLengthUnitsPerMeter(256);
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 256.0f * 1.0f;
    b2WorldId worldId = b2CreateWorld(&worldDef);
    b2Rot spriteRot;
    spriteRot.c = cos(0.0f); 
    spriteRot.s = sin(0.0f); 
    Sprite mySprite = Sprite(posx,posy,b2Vec2{20.0f,80.0f},spriteRot,1,BLUE,b2BodyType::b2_staticBody,"Character",&worldId);
    mySprite.rotationLocked = true;
    b2Body_SetGravityScale(mySprite.bodyId,7.0f);
    Sprite platformOne = Sprite(0.0f,350.0f,b2Vec2{700.0f,10.0f},spriteRot,1,RED,b2BodyType::b2_staticBody,"Floor",&worldId);
    Sprite platformTwo = Sprite(700.0f, 250.0f,b2Vec2{700.0f,10.0f},spriteRot,1,RED,b2BodyType::b2_staticBody,"Floor",&worldId);
    // b2Body_SetGravityScale(platformOne.bodyId,0);

    Texture2D susieAtlasTexture = LoadTexture("../sprites/susie.png");
    // Texture2D texture = LoadTexture("assets/my_texture.png");
    if (susieAtlasTexture.id == 0) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
   
    Animation idleAnim = Animation{
        "Idle",
        susieAtlasTexture,
        17,
        1,
        4,
        0.0f,
        1,
        0.4f
    };

    Animation walkAnim = Animation{
        "Walk",
        susieAtlasTexture,
        17,
        13,
        17,
        0.0f,
        13,
        0.1f,
    };

    
    Sprite susie = Sprite(b2Vec2{10.0f,0.0f},spriteRot,0,RED,b2BodyType::b2_dynamicBody,"susie",&worldId,&walkAnim);
    b2Body_SetGravityScale(susie.bodyId,3.0f);
    susie.rotationLocked = true;
    susie.debug = false;
    //b2Vec2 p, b2Vec2 sz, b2Rot rot, int zIdx, Color clr, b2BodyType bType, string nm, b2WorldId * wrldId, Animation * anim
   
    Camera2D camera;
    camera.zoom = 2.0f;
    camera.target.x = (float)(susie.position.x);
    camera.target.y = (float)(susie.position.y);
    
    
    // Create a tile palette area
    TilePalette* tp = new TilePalette(&worldId,cursorController,Vector2{(float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2});
    tp->worldId = &worldId;
    // Set the position of the tile palette
    tp->position = Vector3{
        0.0f,
        0.0f,
        0.0f
    };

    TileMapLayer* tilemapLayer = new TileMapLayer(Vector2{0,0},16.0,100,100,tp,&camera);
    tilemapLayer->palette = tp;

    

    while (!WindowShouldClose())
    { 
        HideCursor();
        UpdateMusicStream(music);
        float dt = GetFrameTime();
        b2World_Step(worldId, dt, 8);

        b2Vec2 velocity = b2Body_GetLinearVelocity(susie.bodyId);

        if (IsKeyDown(KEY_D) || IsGamepadButtonPressed(0,2)) {
            velocity.x = speed;  
            // susie.animation = &walkAnim;
            susie.flip = false;
        } else if (IsKeyDown(KEY_A) || IsGamepadButtonPressed(0,4)) {
            velocity.x = -speed; 
            susie.flip = true;
            // susie.animation = &walkAnim;
        } else {
            velocity.x = 0.0f;  
            susie.flip = false;
            // susie.animation = &idleAnim;
        }
        

        if (IsKeyDown(KEY_SPACE)){
            velocity.y = -jumpVelocity;
        }

        checkControllerInput(&velocity);

        if(velocity.x >= speed * 2 || velocity.x <= -speed * 2){
            walkAnim.frame_length = 0.05f;
        }else{
            walkAnim.frame_length = 0.1f;
        }

        if(velocity.x > 0.1f || velocity.x < -0.1f){
            susie.animation = &walkAnim;
            if(velocity.x < -0.1f){
                susie.flip = true;
            }else if(velocity.x > 0.1f){
                susie.flip = false;
            }
        }else if(velocity.y > 0.1f || velocity.y < -0.1f){
            // Switch for falling anim
            susie.animation = &idleAnim;
        }else{
            susie.animation = &idleAnim;
        }

        // b2Body_SetLinearVelocity(mySprite.bodyId, velocity);
        susie.Move(velocity);
       
        b2Vec2 playerPos = b2Body_GetPosition(susie.bodyId);
        camera.target = (Vector2){playerPos.x, playerPos.y}; 

        camera.offset.x = (float)screenWidth / 2.0f;
        camera.offset.y = (float)screenHeight / 2.0f;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        
        
        BeginMode2D(camera);
            tilemapLayer->draw();
            mySprite.draw();  
            platformOne.draw();    
            platformTwo.draw();
            susie.draw();
            
        EndMode2D();

        // Draw the tile palette window
        tp->draw();
        cursorController->draw();


        EndDrawing();


        // Check for collisions here
        b2ContactData contactData;
        b2Body_GetContactData(susie.bodyId,&contactData,10);
        b2ShapeId shapeAID = contactData.shapeIdA;
        b2ShapeId shapeBID = contactData.shapeIdB;

        if(contactData.manifold.pointCount > 0){
            b2BodyId bodyA = b2Shape_GetBody(shapeAID);
            b2BodyId bodyB = b2Shape_GetBody(shapeBID);
            if(bodyA.index1 == susie.bodyId.index1 || bodyB.index1 == susie.bodyId.index1){
                // cout << "Susie colliding with object." << endl;

                if(bodyA.index1 == susie.bodyId.index1){
                    if(bodyB.index1 == platformOne.bodyId.index1 || bodyB.index1 == platformTwo.bodyId.index1){
                        // cout << "Susie colliding with floor" << endl;
                    }
                }else if(bodyB.index1 == susie.bodyId.index1){
                    if(bodyA.index1 == platformOne.bodyId.index1){
                        // cout << "Susie colliding with floor" << endl;
                    }
                }
            }else{
                // cout << "Susie not colliding." << endl;
            }
        }else{
            // cout << "No Collisions being detected." << endl;
        }
        
        contactData = b2ContactData();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    b2DestroyShape(mySprite.shapeId,true);
    b2DestroyBody(mySprite.bodyId);
    b2DestroyShape(platformOne.shapeId,true);
    b2DestroyBody(platformOne.bodyId);
    b2DestroyShape(platformTwo.shapeId,true);
    b2DestroyBody(platformTwo.bodyId);
    b2DestroyWorld(worldId);
    CloseWindow();
    return 0;
}