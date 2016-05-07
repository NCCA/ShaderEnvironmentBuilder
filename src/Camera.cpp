#include "Camera.h"

//----------------------------------------------------------------------------------------------------------------------
// Camera settings
Camera::Camera()
{
    m_fov=60.0;
    m_cameraIndex = 0;
    m_cameraRoll = 0.00;
    m_cameraYaw = 0.00;
}

//----------------------------------------------------------------------------------------------------------------------
// Creates a vector of cameras with different perspectives.
std::vector<ngl::Camera> Camera::createCamera()
{
    ngl::Camera Pcam;
    ngl::Camera Tcam;
    ngl::Camera Bcam;
    ngl::Camera Lcam;
    ngl::Camera Rcam;

    ngl::Vec3 perspEye(2.0f, 0.5f,2.0f);
    ngl::Vec3 perspLook(0,0,0);
    ngl::Vec3 perspUp(0.0f,1.0f,0.0f);

    ngl::Vec3 topEye(0.0f,1.0f,0.0f);
    ngl::Vec3 topLook=(0,0,0);
    ngl::Vec3 topUp(0.0f,0.0f,1.0f);

    ngl::Vec3 bottomEye(0.0f,-1.0f,0.0f);
    ngl::Vec3 bottomLook=(0,0,0);
    ngl::Vec3 bottomUp(0.0f,0.0f,1.0f);

    ngl::Vec3 leftEye(0.0f,0.0f,-3.0f);
    ngl::Vec3 leftLook=(0,0,0);
    ngl::Vec3 leftUp(0.0f,1.0f,0.0f);

    ngl::Vec3 rightEye(0.0f,0.0f,3.0f);
    ngl::Vec3 rightLook=(0,0,0);
    ngl::Vec3 rightUp(0.0f,1.0f,0.0f);

    Pcam.set(perspEye,perspLook, perspUp);
    Pcam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    m_cameras.push_back(Pcam);

    Tcam.set(topEye,topLook,topUp);
    Tcam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    m_cameras.push_back(Tcam);

    Bcam.set(bottomEye,bottomLook,bottomUp);
    Bcam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    m_cameras.push_back(Bcam);

    Lcam.set(leftEye,leftLook,leftUp);
    Lcam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    m_cameras.push_back(Lcam);

    Rcam.set(rightEye,rightLook,rightUp);
    Rcam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    m_cameras.push_back(Rcam);
    m_mainCamera = m_cameras[m_cameraIndex];
    return m_cameras;
}

ngl::Camera Camera::setShapeCam()
{
  m_mainCamera.setShape(m_fov, m_aspect, m_nearClip, m_farClip);
  return m_mainCamera;
}

//----------------------------------------------------------------------------------------------------------------------
// Camera Roll settings
void Camera::cameraYaw(double _cameraYaw)
{
    m_mainCamera.yaw(-m_cameraYaw);
    m_cameraYaw = _cameraYaw;
    m_mainCamera.yaw(_cameraYaw);
    emit updateSignal();
}


//----------------------------------------------------------------------------------------------------------------------
// Camera Roll settings
void Camera::cameraPitch(double _cameraPitch)
{
    m_mainCamera.pitch(-m_cameraPitch);
    m_cameraPitch = _cameraPitch;
    m_mainCamera.pitch(_cameraPitch);
    emit updateSignal();
}


//----------------------------------------------------------------------------------------------------------------------
// Camera Roll settings
void Camera::cameraRoll(double _cameraRoll)
{
    m_mainCamera.roll(-m_cameraRoll);
    m_cameraRoll = _cameraRoll;
    m_mainCamera.roll(_cameraRoll);
    emit updateSignal();
}

//----------------------------------------------------------------------------------------------------------------------
// Signal passed from the UI to set the camera FOV
void Camera::setCameraFocalLength(int _focalLength)
{
    m_fov= _focalLength;
    m_mainCamera.setShape(m_fov, m_aspect, 0.5f, 150.0f);
    emit updateSignal();
}

void Camera::setCameraShape(QString _view)
{
  string view = _view.toStdString();

  map<string, int> camViewMap;
  camViewMap["Persp"]=0;
  camViewMap["Top"]=1;
  camViewMap["Bottom"]=2;
  camViewMap["Left"]=3;
  camViewMap["Right"]=4;

  m_cameraIndex = camViewMap[view];
  m_mainCamera = m_cameras[m_cameraIndex];
  std::cout<<view<<std::endl;
  emit updateSignal();
}


//----------------------------------------------------------------------------------------------------------------------
// Set camera near clipping plane
void Camera::setCamNearClip(double _nearClip)
{
    m_nearClip= _nearClip;
    emit updateSignal();
}

//----------------------------------------------------------------------------------------------------------------------
// Set camera far clipping plane
void Camera::setCamFarClip(double _farClip)
{
    m_farClip= _farClip;
    emit updateSignal();
}




void updateSignal()
{
    ;
}
