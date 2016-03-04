
#include "camera.hpp"


namespace OpenGLEngine {


  Camera::Camera(int screenWidth, int screenHeight) {
    m_ViewDirty = false;
  	g_PreviousTicks = std::clock();
  	g_A = g_W = g_S = g_D = g_Q = g_E = 0;

  	this->SetPosition(glm::vec3(0.0, 0.0, 0.0));
  	this->SetRotation(glm::quat());

  	this->SetViewport(0, 0, screenWidth, screenHeight);
  	this->SetProjectionRH(70.0f, screenWidth / (float)screenHeight, 0.01f, 50000.0f);

    speed = 0.02f;
    smoothnessX = smoothnessY = 0.05f;
  }

  Camera::Camera(const glm::vec3& position, int screenWidth, int screenHeight) {

    m_ViewDirty = false;
  	g_PreviousTicks = std::clock();
  	g_A = g_W = g_S = g_D = g_Q = g_E = 0;

  	this->SetPosition(position);
  	this->SetRotation(glm::quat());

  	this->SetViewport(0, 0, screenWidth, screenHeight);
  	this->SetProjectionRH(70.0f, screenWidth / (float)screenHeight, 0.01f, 50000.0f);

    speed = 0.02f;
    smoothnessX = smoothnessY = 0.05f;
  }

  Camera::~Camera()
  {

  }


  void Camera::SetViewport(int x, int y, int width, int height)
  {
  	m_Viewport = glm::vec4(x, y, width, height);
  	glViewport(x, y, width, height);
  }

  glm::vec4 Camera::GetViewport() const
  {
  	return m_Viewport;
  }

  void Camera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar)
  {
  	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
  }

  void Camera::ApplyViewMatrix()
  {
  	UpdateViewMatrix();
  }

  void Camera::SetPosition(const glm::vec3& pos)
  {
  	m_Position = pos;
  	m_ViewDirty = true;
  }

  glm::vec3 Camera::GetPosition() const
  {
  	return m_Position;
  }

  void Camera::Translate(const glm::vec3& delta, bool local /* = true */)
  {
  	if (local)
  	{
  		m_Position += m_Rotation * delta;
  	}
  	else
  	{
  		m_Position += delta;
  	}
  	m_ViewDirty = true;
  }

  void Camera::SetRotation(const glm::quat& rot)
  {
  	m_Rotation = rot;
  	m_ViewDirty = true;
  }

  glm::quat Camera::GetRotation() const
  {
  	return m_Rotation;
  }

  void Camera::SetEulerAngles(const glm::vec3& eulerAngles)
  {
  	m_Rotation = glm::quat(glm::radians(eulerAngles));
  }

  glm::vec3 Camera::GetEulerAngles() const
  {
  	return glm::degrees(glm::eulerAngles(m_Rotation));
  }

  void Camera::Rotate(const glm::quat& rot)
  {
  	m_Rotation = m_Rotation * rot;
  	m_ViewDirty = true;
  }

  glm::mat4 Camera::GetProjectionMatrix()
  {
  	return m_ProjectionMatrix;
  }

  glm::mat4 Camera::GetViewMatrix()
  {
  	UpdateViewMatrix();
  	return m_ViewMatrix;
  }

  void Camera::UpdateViewMatrix()
  {
  	if (m_ViewDirty)
  	{
  		glm::mat4 translate = glm::translate(-m_Position);
  		// Since we know the rotation matrix is orthonormalized, we can simply
  		// transpose the rotation matrix instead of inversing.
  		glm::mat4 rotate = glm::transpose(glm::toMat4(m_Rotation));

  		m_ViewMatrix = rotate * translate;

  		m_ViewDirty = false;
  	}
  }

  glm::vec3 Camera::GetDirection() {
    return g_Raycast;
  }


  void Camera::setMouseDown(bool what) {
    isMouseDown = what;
  }

  void Camera::updateLocation(double deltaTime) {

    Translate(glm::vec3(g_D - g_A, g_Q - g_E, g_S - g_W) * (float)speed);

  }

  void Camera::updateDirection(double relativeMouseMotionX, double relativeMouseMotionY) {

    if(isMouseDown) {
      g_Pitch -= relativeMouseMotionY * smoothnessY;
      g_Yaw -= relativeMouseMotionX * smoothnessX;

      g_Pitch = glm::clamp(g_Pitch, -80.0f, 80.0f);
      g_Yaw = fmod(g_Yaw, 360.0f);

      glm::quat cameraRotation = glm::quat(glm::eulerAngleYX(glm::radians(g_Yaw), glm::radians(g_Pitch)));
      SetRotation(cameraRotation);

      g_Raycast = cameraRotation * glm::vec3(0.0, 0.0, 1.0);
    }

  }

  void Camera::startMovingForward() {
    g_W = 1;
  }

  void Camera::startMovingBackward() {
    g_S = 1;
  }

  void Camera::startMovingRight() {
    g_D = 1;
  }

  void Camera::startMovingLeft() {
    g_A = 1;
  }

  void Camera::stopMovingForward() {
    g_W = 0;
  }

  void Camera::stopMovingBackward() {
    g_S = 0;
  }

  void Camera::stopMovingRight() {
    g_D = 0;
  }

  void Camera::stopMovingLeft() {
    g_A = 0;
  }
}
