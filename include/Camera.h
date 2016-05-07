#ifndef CAMERA_H
#define CAMERA_H

#include <unordered_map>
#include <ngl/Camera.h>
#include <map>
#include <iostream>
//#include <QOpenGLWidget>
//#include "NGLScene.h"
#include "vector"
#include "QString"
#include "QWidget"
#include <QObject>
//#include <QOpenGLWidget>
//#include <QGLWidget>

//------------------------------------------------------------------------------------------------------------------------
/// @file Camera.h
/// @brief Creates the persp, top, bottom and side view cameras and adjusts settings such as roll, yaw.
/// @author Ellie Ansell
/// @version 1.0
/// @date 03/05/16
//------------------------------------------------------------------------------------------------------------------------

using namespace std;

class Camera : public QObject
{
Q_OBJECT        // must include this if you use Qt signals/slots
public:
    Camera(); // {connect(this, &Camera::someSignal, this, &Camera::someSlot);}

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
    //int setCameraShape(QString _view);
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


    ngl::Camera setShapeCam();
    ngl::Camera m_mainCamera;
    float m_nearClip;
    float m_farClip;

    void someSlot(const QVariant &);
public slots:
    //----------------------------------------------------------------------------
    /// @brief Function to set camera FOV
    /// @param[in] _focalLength the FOV value to set
    //----------------------------------------------------------------------------
    void setCameraFocalLength(int _focalLength);
    void setCameraShape(QString _view);

    //----------------------------------------------------------------------------
    /// @brief Sets camera Pitch
    /// @param[in] _cameraRoll the new pitch value
    //----------------------------------------------------------------------------
    void cameraRoll(double _cameraRoll);
    //----------------------------------------------------------------------------
    /// @brief Sets camera Pitch
    /// @param[in] _cameraPitch the new pitch value
    //----------------------------------------------------------------------------
    void cameraPitch(double _cameraPitch);
    //----------------------------------------------------------------------------
    /// @brief Sets camera Yaw
    /// @param[in] _cameraYaw the new yaw value
    //----------------------------------------------------------------------------
    void cameraYaw(double _cameraYaw);
    //----------------------------------------------------------------------------------------------------------------------
    // Set camera near clipping plane
    void setCamNearClip(double _nearClip);

    //----------------------------------------------------------------------------------------------------------------------
    // Set camera far clipping plane
    void setCamFarClip(double _farClip);



    signals:
    void updateSignal();
};

#endif // CAMERA_H
