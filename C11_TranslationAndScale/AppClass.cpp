#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Aedan Frank - acf6919@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 30.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	vector3 tempPos;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	//init the mesh
	m_pMesh = new MyMesh();
	tempPos = vector3(1.0f, 0.0, 0.0f);
	m_pMesh->GenerateCube(1.0f, C_BLACK);

	m_pMesh2 = new MyMesh();
    m_pMesh2->GenerateCube(0.5f, C_BLACK);

	m_pMesh3 = new MyMesh();
	m_pMesh3->GenerateCube(1.5f, C_BLACK);

	m_pMesh4 = new MyMesh();
	m_pMesh4->GenerateCube(0.5f, C_BLACK);
	
	m_pMesh5 = new MyMesh();
	m_pMesh5->GenerateCube(1.0f, C_BLACK);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Create a model matrix out of the arcball quaternion
	matrix4 m4Model = ToMatrix4(m_qArcBall);

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f, 2.0f, 2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	matrix4 m4Translate2 = glm::translate(IDENTITY_M4, vector3(value, 5.0f, 3.0f));
	matrix4 m4Translate3 = glm::translate(IDENTITY_M4, vector3(value, 1.0f, 1.0f));
	matrix4 m4Translate4 = glm::translate(IDENTITY_M4, vector3(value-3.0f, 5.0f, 3.0f));
	matrix4 m4Translate5 = glm::translate(IDENTITY_M4, vector3(value+3.0f, -3.0f, 3.0f));
	value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;
	matrix4 m4Model2 = m4Scale * m4Translate2;
	matrix4 m4Model3 = m4Scale * m4Translate3;
	matrix4 m4Model4 = m4Scale * m4Translate4;
	matrix4 m4Model5 = m4Scale * m4Translate5;

	m_pMesh->Render(m4Projection, m4View, m4Model);
	m_pMesh2->Render(m4Projection, m4View, m4Model2);
	m_pMesh3->Render(m4Projection, m4View, m4Model3);
	m_pMesh4->Render(m4Projection, m4View, m4Model4);
	m_pMesh5->Render(m4Projection, m4View, m4Model5);

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
	SafeDelete(m_pMesh);
	SafeDelete(m_pMesh2);
	//release GUI
	ShutdownGUI();
}