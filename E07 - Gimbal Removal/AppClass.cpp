#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Aedab Frank - acf6919@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	m_pModelMngr->LoadModel(m_sSteve);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	// Updates the matrix4 orientation for EACH axis
	matrix4 m4OrientationX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.x), vector3(1.0f, 0.0f, 0.0f));
	matrix4 m4OrientationY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.y), vector3(0.0f, 1.0f, 0.0f));
	matrix4 m4OrientationZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.z), vector3(0.0f, 0.0f, 1.0f));

	// Gets the total orientation by concatenating the matrix4 orientation of each axis
	matrix4 m4Orientation = m4OrientationX * m4OrientationY * m4OrientationZ;

	// Applies the matrix4 orientation to the matrix4 of the actual model
	m_m4Model = glm::toMat4(m_qOrientation);


	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	/*
	* The following line was replaced by the model manager so we can see a model instead of a cone
	*/
	//m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_m4Model));
	m_pModelMngr->AddModelToRenderList(m_sSteve, m_m4Model);


	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}