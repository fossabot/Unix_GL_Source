
#ifndef __CAMERA__
#define __CAMERA__

#include "ustd.hpp"



namespace OpenGLEngine {

  class Camera {
    public:
    	//////////////////////////////////////////////////////////////////////////////////////////////////////
    	// CONSTRUCTOR/DESTRUCTOR ////////////////////////////////////////////////////////////////////////////
    	//////////////////////////////////////////////////////////////////////////////////////////////////////
    	Camera(const glm::vec3& position, int screenWidth, int screenHeight);
    	Camera(int screenWidth, int screenHeight);
    	~Camera();
    	//////////////////////////////////////////////////////////////////////////////////////////////////////


    	void SetViewport(int x, int y, int width, int height);
    	glm::vec4 GetViewport() const;
    	void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);
    	void ApplyViewMatrix();
    	void SetPosition(const glm::vec3& pos);
    	glm::vec3 GetPosition() const;
    	// Translate the camera by some amount. If local is TRUE (default) then the translation should
    	// be applied in the local-space of the camera. If local is FALSE, then the translation is
    	// applied in world-space.
    	void Translate(const glm::vec3& delta, bool local = true);
    	void SetRotation(const glm::quat& rot);
    	glm::quat GetRotation() const;
    	void SetEulerAngles(const glm::vec3& eulerAngles);
    	glm::vec3 GetEulerAngles() const;

    	// Rotate the camera by some amount.
    	void Rotate(const glm::quat& rot);
    	glm::mat4 GetProjectionMatrix();
    	glm::mat4 GetViewMatrix();
    	float g_Pitch = 0.0f;
    	float g_Yaw = 0.0f;
    	int g_W, g_A, g_S, g_D, g_Q, g_E;
    	bool g_bShift = false;
    	bool g_bAnimate = true;
    	glm::ivec2 g_MousePos;
    	int        g_MouseButton;
    	glm::quat g_Rotation;
    	std::clock_t g_PreviousTicks;
    	std::clock_t g_CurrentTicks;

      glm::vec3 GetDirection();
    	glm::vec3 g_Raycast;

    protected:

    	void UpdateViewMatrix();
    	glm::vec4 m_Viewport;
    	glm::vec3 m_Position;
    	glm::quat m_Rotation;
    	glm::mat4 m_ViewMatrix;
    	glm::mat4 m_ProjectionMatrix;

    private:

    	bool m_ViewDirty;

  };

}


#endif
