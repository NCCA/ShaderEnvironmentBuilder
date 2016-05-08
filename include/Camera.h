#ifndef CAMERA_H
#define CAMERA_H

// Library  includes
#include <iostream>
#include <QString>
#include <QWidget>
#include <QObject>
#include <unordered_map>
#include <ngl/Camera.h>
#include <vector>

//------------------------------------------------------------------------------
/// @file Camera.h
/// @brief Creates the camera used for NGLScene.
/// @author Ellie Ansell
/// @version 1.0
/// @date 05/05/16
//------------------------------------------------------------------------------

class Camera : public QObject
{
Q_OBJECT
public:
    //----------------------------------------------------------------------------
    /// @brief _Cstor class
    //----------------------------------------------------------------------------
    Camera();
    //----------------------------------------------------------------------------
    /// @brief A vector containing the ngl cameras
    //----------------------------------------------------------------------------
    std::vector <ngl::Camera > m_cameras;
    //----------------------------------------------------------------------------
    /// @brief An index to access the cameras
    //----------------------------------------------------------------------------
    int m_cameraIndex;
    //----------------------------------------------------------------------------
    /// @brief fov value for the camera
    //----------------------------------------------------------------------------
    int m_fov;
    //----------------------------------------------------------------------------
    /// @brief aspect ratio of the camera
    //----------------------------------------------------------------------------
    float m_aspect;
    //----------------------------------------------------------------------------
    /// @brief Near clipping plane of the camera
    //----------------------------------------------------------------------------
    float m_nearClip;
    //----------------------------------------------------------------------------
    /// @brief Far clipping plane of the camera
    //----------------------------------------------------------------------------
    float m_farClip;
    //----------------------------------------------------------------------------
    /// @brief camera yaw value
    //----------------------------------------------------------------------------
    double m_cameraYaw;
    //----------------------------------------------------------------------------
    /// @brief camera roll value
    //----------------------------------------------------------------------------
    double m_cameraRoll;
    //----------------------------------------------------------------------------
    /// @brief camera pitch value
    //----------------------------------------------------------------------------
    double m_cameraPitch;
    //----------------------------------------------------------------------------
    /// @brief Active camera used by NGLScene.
    //----------------------------------------------------------------------------
     ngl::Camera m_mainCamera;
    //----------------------------------------------------------------------------
    /// @brief Creates a vector of ngl cameras and sets their shapes
    //----------------------------------------------------------------------------
    void createCameras();
    //----------------------------------------------------------------------------
    /// @brief Sets the camera shape and returns the new camera to NGLScene.
    //----------------------------------------------------------------------------
    ngl::Camera setShapeCam();

public slots:
    //----------------------------------------------------------------------------
    /// @brief Function to set camera FOV
    /// @param[in] _focalLength the FOV value to set
    //----------------------------------------------------------------------------
    void setCameraFocalLength(int _focalLength);
    //----------------------------------------------------------------------------
    /// @brief Sets the new camera shape
    /// @param[in] _view The camera view set (persp, top, bottom, left, right).
    //----------------------------------------------------------------------------
    void setCameraShape(QString _view);
    //----------------------------------------------------------------------------
    /// @brief Sets camera roll
    /// @param[in] _cameraRoll the new roll value
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
    //----------------------------------------------------------------------------
    /// @brief Sets near clipping frame
    /// @param[in] _nearClip the near clipping plane value
    //----------------------------------------------------------------------------
    void setCamNearClip(double _nearClip);
    //----------------------------------------------------------------------------
    /// @brief Sets far clipping frame
    /// @param[in] _farClip the far clipping plane value
    //----------------------------------------------------------------------------
    void setCamFarClip(double _farClip);

    signals:
    //----------------------------------------------------------------------------
    /// @brief Signal sent to NGLScene update() function to update the scene with the new camera.
    //----------------------------------------------------------------------------
    void updateSignal();
};

#endif // CAMERA_H
