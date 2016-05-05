#ifndef CAMERA_H
#define CAMERA_H

#include <unordered_map>
#include <ngl/Camera.h>
#include <map>

#include "vector"
#include "QString"
#include <iostream>

//------------------------------------------------------------------------------------------------------------------------
/// @file Camera.h
/// @brief Creates the persp, top, bottom and side view cameras and adjusts settings such as roll, yaw.
/// @author Ellie Ansell
/// @version 1.0
/// @date 03/05/16
//------------------------------------------------------------------------------------------------------------------------

using namespace std;

class Camera
{
public:
    Camera();

    //---------------------------------------------------------------------------------------------------------------------
    /// @brief A vector containing the ngl cameras
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <ngl::Camera > m_cameras;
    //---------------------------------------------------------------------------------------------------------------------
    /// @brief An index to access the cameras
    //----------------------------------------------------------------------------------------------------------------------
    int m_cameraIndex;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief fov value for the camera
    //----------------------------------------------------------------------------------------------------------------------
    int m_fov;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief aspect ratio of the camera
    //----------------------------------------------------------------------------------------------------------------------
    float m_aspect;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief camera yaw value
    //----------------------------------------------------------------------------------------------------------------------
    double m_cameraYaw;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief camera roll value
    //----------------------------------------------------------------------------------------------------------------------
    double m_cameraRoll;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief camera pitch value
    //----------------------------------------------------------------------------------------------------------------------
    double m_cameraPitch;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the view of the camera (perso, top, bottom, side)
    //----------------------------------------------------------------------------------------------------------------------
    int setCameraShape(QString _view);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Creates a vector of ngl cameras and sets their shapes
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <ngl::Camera > createCamera();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets camera yaw
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Camera cameraYaw(ngl::Camera _cam, double _cameraYaw);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets camera roll
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Camera cameraRoll(ngl::Camera _cam, double _cameraRoll);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets camera pitch
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Camera cameraPitch(ngl::Camera _cam, double _cameraPitch);

};

#endif // CAMERA_H
