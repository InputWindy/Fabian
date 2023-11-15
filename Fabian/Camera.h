#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    
    glm::mat4 GetViewMatrixnz()
    {
        return glm::lookAt(Position, Position + Front, -Up);
    }
    glm::mat4 GetViewMatrixpz()
    {
        return glm::lookAt(Position, Position - Front, -Up);
    }
    glm::mat4 GetViewMatrixpx()
    {
        return glm::lookAt(Position, Position + Right, -Up);
    }
    glm::mat4 GetViewMatrixnx()
    {
        return glm::lookAt(Position, Position - Right, -Up);
    }
    glm::mat4 GetViewMatrixpy()
    {
        return glm::lookAt(Position, Position + Up, -Front);
    }
    glm::mat4 GetViewMatrixny()
    {
        return glm::lookAt(Position, Position - Up, Front);
    }
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    

    // processes input received from a mouse input system. Expects the offset value in both the ;x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
    

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
    
};

#pragma region Transform
class Transform
{
public:
    Transform() = default;
    Transform(glm::vec3 pos, glm::vec3 scal, glm::vec3 rot) :
        position(pos), scale(scal), rotation(rot)
    {
        update();
    };
    Transform(const Transform& t) :position(t.position), scale(t.scale), rotation(t.rotation) {
        update();
    }
    ~Transform() = default;

    void setPosition(glm::vec3 pos) {
        position = pos;
        update();
    }
    void setScale(glm::vec3 scal) {
        scale = scal;
        update();
    }
    void setRotation(glm::vec3 rot) {
        rotation = rot;
        update();
    }

    glm::vec3& getPosition() {
        return position;
    }
    glm::vec3& getScale() {
        return scale;
    }
    glm::vec3& getRotation() {
        return rotation;
    }

    glm::mat4 getModelMatrix() {
        return model;
    }
private:
    void update() {
        model = glm::mat4(1.0f);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, position);
        /*model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(10.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));*/
    }
public:

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    glm::mat4 model;
};

#pragma endregion

#endif