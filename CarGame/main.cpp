#include "afx.h"

void Setup();
void Display();
void Reshape(int width, int height);
void Update();

void KeyPressed(unsigned char key, int x, int y);
void KeyReleased(unsigned char key, int x, int y);
void KeyOperations();

void SpecialKeyPressed(int key, int x, int y);
void SpecialKeyReleased(int key, int x, int y);
void SpecialKeyOperations();

void MouseInput(int x, int y);

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Camera* camera = new Camera();
GameTime* gameTime = new GameTime();
GLfloat deltaTime = 0;

GLuint basicShader;
GLuint lightingShader;

int currentModelNumber = 0;

bool wireframeMode = false;

vector<GameObject*>m_nModels;

Scene* gameScene = new Scene();

Terrain* terrain = new Terrain("Terrain.png", "HeightMap.raw", 256, 256);
Skybox* skybox = new Skybox();

Car* car = new Car();
Wheel* flWheel = new Wheel();
Wheel* frWheel = new Wheel();
Wheel* rlWheel = new Wheel();
Wheel* rrWheel = new Wheel();
Crate* crate = new Crate();
Crate* crate1 = new Crate();

std::map <string, glm::vec3>m_nCams;

string rearCam = "RearCam";
string rightCam = "RightCam";
string frontCam = "FrontCam";
string leftCam = "LeftCam";
string topCam = "TopCam";

string currentCamera = rearCam;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);

	int hWnd = glutCreateWindow("ModelLoader");

	glewInit();

	if (MessageBoxA(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) != IDNO)
	{
		glutFullScreen();
	}

	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	glutSpecialFunc(SpecialKeyPressed);
	glutSpecialUpFunc(SpecialKeyReleased);
	glutPassiveMotionFunc(MouseInput);

	Setup();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Update);

	glutMainLoop();
}

void Setup()
{ 
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	camera->node->SetParent(car->node);

	//terrain->Initialize();
	skybox->Initialize();

	car->node->SetNodeName("CarNode");
	flWheel->node->SetNodeName("FL_Wheel Node");
	frWheel->node->SetNodeName("FR_Wheel Node");
	rlWheel->node->SetNodeName("RL_Wheel Node");
	rrWheel->node->SetNodeName("RR_Wheel Node");
	crate->node->SetNodeName("Crate Node");
	crate1->node->SetNodeName("Crate1 Node");

	camera->node->SetNodeName("CamNode");

	car->node->m_vPosition = glm::vec3(0, 1.7f, 0);
	flWheel->node->m_vPosition = glm::vec3(1.4f, -1.0f, 3.0f);
	frWheel->node->m_vPosition = glm::vec3(-1.4f, -1.0f, 3.0f);
	rlWheel->node->m_vPosition = glm::vec3(1.5f, -1.0f, -2.6f);
	rrWheel->node->m_vPosition = glm::vec3(-1.5f, -1.0f, -2.6f);

	crate->node->m_vPosition = glm::vec3(0, 100, 10);
	crate->node->m_vSize = glm::vec3(5);

	crate1->node->m_vPosition = glm::vec3(0, 200, 10);
	crate1->node->m_vSize = glm::vec3(5);

	//Camera Initial Pos
	m_nCams[rearCam] = glm::vec3(0, 5, -10);
	m_nCams[rightCam] = glm::vec3(-10, 5, 0);
	m_nCams[frontCam] = glm::vec3(0, 5, 10);
	m_nCams[leftCam] = glm::vec3(10, 5, 0);
	m_nCams[topCam] = glm::vec3(0, 20, -5);

	camera->node->m_vPosition = m_nCams[rearCam];

	gameScene->GetRootNode()->AddChild(terrain->node);
	gameScene->GetRootNode()->AddChild(car->node);
	car->node->AddChild(flWheel->node);
	car->node->AddChild(frWheel->node);
	car->node->AddChild(rlWheel->node);
	car->node->AddChild(rrWheel->node);
	gameScene->GetRootNode()->AddChild(crate->node);
	gameScene->GetRootNode()->AddChild(crate1->node);
	
	//Camera is the child of car
	car->node->AddChild(camera->node);

	//Setting mass of Objects
	car->node->m_fMass = 10.0f;
	crate->node->m_fMass = 0.1f;
	crate1->node->m_fMass = 0.1f;

	//Seting friction on objects
	car->node->SetFriction(glm::vec3(0.5f));
	crate->node->SetFriction(glm::vec3(0.1f));
	crate1->node->SetFriction(glm::vec3(0.1f));

	//Enabling gravity
	car->node->gravity = true;
	crate->node->gravity = true;
	crate1->node->gravity = true;

	glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	SceneManager::GetInstance()->SetCurrentScene(gameScene);
	ShaderManager::GetInstance()->Initialize(); 
	TextureManager::GetInstance()->LoadAllTextures();
	
	basicShader = ShaderManager::GetInstance()->ProgramId("Basic");
	lightingShader = ShaderManager::GetInstance()->ProgramId("Lighting");

	car->node->shaderID = lightingShader;
	flWheel->node->shaderID = lightingShader;
	frWheel->node->shaderID = lightingShader;
	rlWheel->node->shaderID = lightingShader;
	rrWheel->node->shaderID = lightingShader;
	camera->node->shaderID = lightingShader;
	terrain->node->shaderID = lightingShader;
	crate->node->shaderID = lightingShader;
	crate1->node->shaderID = lightingShader;

	printf("Crate Parent : %s", crate->node->GetParent()->GetNodeName());
	printf("Crate1 Parent : %s", crate1->node->GetParent()->GetNodeName());

	glEnable(GL_PROGRAM_POINT_SIZE);
}

void Display()
{
	gameTime->StartTimer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (wireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Object Rendering
	glm::mat4 projectionMatrix = glm::perspective(45.0f, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.1f, 10000.0f);
	glm::mat4 viewMatrix = camera->GetMatrix();

	glUseProgram(lightingShader);

	//Sending camera position to shader
	glUniform3f(glGetUniformLocation(lightingShader, "m_vCamPos"), camera->m_vPosition.x, camera->m_vPosition.y, camera->m_vPosition.z);

	//Lighting properties
	glUniform3f(glGetUniformLocation(lightingShader, "light[0].position"), camera->m_vPosition.x, camera->m_vPosition.y, camera->m_vPosition.z);
	glUniform3f(glGetUniformLocation(lightingShader, "light[0].ambient"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(lightingShader, "light[0].diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(lightingShader, "light[0].specular"), 1.0f, 1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(lightingShader, "projection"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(lightingShader, "view"), 1, GL_FALSE, &viewMatrix[0][0]);

	SceneManager::GetInstance()->Update(deltaTime);

	glUseProgram(0);

	//SkyBox Rendering
	glUseProgram(basicShader);
	glm::mat4 skyboxProjectionMatrix = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, 0.1f, 10000.0f);
	glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->GetMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(basicShader, "projection"), 1, GL_FALSE, glm::value_ptr(skyboxProjectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(basicShader, "view"), 1, GL_FALSE, glm::value_ptr(skyboxViewMatrix));
	skybox->Render(basicShader);
	glUseProgram(0);

	gameTime->StopTimer();
	deltaTime = 1.0f / 60.0f;
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

bool CheckCollision(GameObject* go1, GameObject* go2)
{
	static bool conditionX = false;
	static bool conditionY = false;
	static bool conditionZ = false;

	if (go1->boundingBox.left < go2->boundingBox.right && go1->boundingBox.right > go2->boundingBox.left)
	{
		conditionX = true;
	}
	else
	{
		conditionX = false;
	}

	if (go1->boundingBox.down < go2->boundingBox.up && go1->boundingBox.up > go2->boundingBox.down)
	{
		conditionY = true;
	}
	else
	{
		conditionY = false;
	}

	if (go1->boundingBox.front < go2->boundingBox.back && go1->boundingBox.back > go2->boundingBox.front)
	{
		conditionZ = true;
	}
	else
	{
		conditionZ = false;
	}

	if (conditionX && conditionY && conditionZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CollisionUpdates()
{
	//Collision between car and terrain
	static glm::vec3 carLastPos;
	if (CheckCollision(car, terrain))
	{
		car->node->m_vPosition.y = carLastPos.y;
	}
	else
	{
		carLastPos = car->node->m_vPosition;
		car->node->m_vPosition.y -= 9.8f * deltaTime;
	}

	//Collision between crate and terrain
	static glm::vec3 crateLastPos;
	static bool crateHitGround = false;
	static bool crateHitCrate1 = false;

	if (crateHitGround)
	{
		crate->node->m_vPosition.y = crateLastPos.y;
	}
	else
	{
		crate->node->m_vPosition.y -= 9.8f * deltaTime;
		crateLastPos = crate->node->m_vPosition;
	}

	if (CheckCollision(crate, terrain))
		crateHitGround = true;
	else
		crateHitGround = false;

	//Collision between crate1 and terrain
	static glm::vec3 crate1LastPos;
	static bool crate1HitGround = false;
	static bool crate1Hitcrate = false;

	if (crate1HitGround)
	{
		crate1->node->m_vPosition.y = crateLastPos.y;
	}
	else
	{
		crate1->node->m_vPosition.y -= 9.8f * deltaTime;
		crate1LastPos = crate1->node->m_vPosition;
	}

	if (CheckCollision(crate1, terrain))
		crate1HitGround = true;
	else
		crate1HitGround = false;

	if (CheckCollision(crate, crate1))
	{
		crate1->node->m_vVelocity = crate1->node->m_vVelocity * (crate->node->m_fMass/ crate1->node->m_fMass) * (crate->node->m_vFriction / crate1->node->m_vFriction);
	}

	//Collision between car and crate
	if (CheckCollision(car, crate))
	{
		crate->node->m_vVelocity = (car->node->m_fMass * car->node->m_vVelocity) / crate->node->m_fMass * (car->node->m_vFriction / crate->node->m_vFriction);
	}
	
	//Collision between car and crate1
	if (CheckCollision(car, crate1))
	{
		crate1->node->m_vVelocity = (car->node->m_fMass * car->node->m_vVelocity) / crate1->node->m_fMass * (car->node->m_vFriction / crate1->node->m_vFriction);
	}
}

glm::vec3 carForward = glm::vec3(0, 0, 1);
glm::vec3 carRight = glm::vec3(1, 0, 0);
glm::vec3 carUp = glm::vec3(0, 1, 0);

float carSpeed = 0;

void Update()
{
	CollisionUpdates();

	//Conditions for ReSpawning 
	if (car->node->m_vPosition.y < -20.0f)
	{
		car->node->m_vPosition = glm::vec3(0, 20, 0);
	}

	if (crate->node->m_vPosition.y < -20.0f)
	{
		crate->node->m_vPosition = glm::vec3(0, 20, 0);
	}

	if (crate1->node->m_vPosition.y < -20.0f)
	{
		crate1->node->m_vPosition = glm::vec3(0, 20, 0);
	}

	//Calculation of vectors
	carRight.x = cos(glm::radians(car->node->m_vRotation.y));
	carRight.z = sin(glm::radians(car->node->m_vRotation.y));
	carRight = glm::normalize(carRight);

	carForward.x = sin(glm::radians(car->node->m_vRotation.y));
	carForward.z = cos(glm::radians(car->node->m_vRotation.y));
	carForward = glm::normalize(carForward);

	//Printing vectors
	printf("\nCar Forward : ");
	car->node->PrintVector3(carForward);
	printf("Car Up : ");
	car->node->PrintVector3(carUp);
	printf("Car Right : ");
	car->node->PrintVector3(carRight);

	carSpeed = glm::length(car->node->m_vVelocity);
	printf("Car Speed : %f\n", carSpeed);

	glutPostRedisplay();
	KeyOperations();
	SpecialKeyOperations();

	camera->Update(deltaTime);

	//Camera Lerp
	camera->node->m_vPosition += glm::vec3(m_nCams[currentCamera] - camera->node->m_vPosition) * 0.1f;
}

void KeyPressed(unsigned char key, int x, int y)
{
	InputManager::GetInstance()->keyStates[key] = true;

	if (key == VK_SPACE)
	{
		car->node->SetFriction(glm::vec3(0.01f));
	}

	if (key == VK_ESCAPE)
	{
		exit(0);
	}

	if (key == 't')
	{
		if (wireframeMode)
			wireframeMode = false;
		else
			wireframeMode = true;
	}

	if (key == 'f')
	{
		if (camera->node->GetParent())
			camera->node->SetParent(NULL);
		else
			camera->node->SetParent(car->node);
	}

	if (key == 'h')
	{
		crate->node->m_vPosition.y = 100.0f;
	}
}

void KeyReleased(unsigned char key, int x, int y)
{
	InputManager::GetInstance()->keyStates[key] = false;
	
	if (key == 'w')
	{
		
	}

	if (key == 's')
	{
		
	}

	if (key == 'd')
	{
		
	}

	if (key == 'a')
	{
		
	}

	if (key == VK_SPACE)
	{
		car->node->SetFriction(glm::vec3(0.1f));
	}
}

void KeyOperations()
{
	if (InputManager::GetInstance()->keyStates['r'] == true)
	{
		camera->Reset();
	}
	static float moveDir = 1;

	if (InputManager::GetInstance()->keyStates['w'] == true)
	{
		car->node->ApplyForce(car->node->localAxis.forward * 2500.0f);
	}

	if (InputManager::GetInstance()->keyStates['s'] == true)
	{
		car->node->ApplyForce(car->node->localAxis.forward * -1000.0f);
	}

	static glm::vec3 flWheelRight = glm::vec3(1, 0, 0);
	static glm::vec3 flWheelUp = glm::vec3(0, 1, 0);

	static float steerAngle = 0;

	flWheel->node->m_vRotation.x += glm::length(car->node->m_vVelocity);
	frWheel->node->m_vRotation.x += glm::length(car->node->m_vVelocity);
	rlWheel->node->m_vRotation.x += glm::length(car->node->m_vVelocity);
	rrWheel->node->m_vRotation.x += glm::length(car->node->m_vVelocity);

	if (InputManager::GetInstance()->keyStates['a'] == true)
	{
		if (carSpeed > 1.0f)//When Speed of car is greater than 1.0f then only rotate
		{
			car->node->m_vRotation.y += 1.0f * deltaTime; 
		}

		if (steerAngle > -30.0f)
			steerAngle -= 100.0f * deltaTime;
	}

	if (InputManager::GetInstance()->keyStates['d'] == true)
	{
		if (carSpeed > 1.0f)//When Speed of car is greater than 1.0f then only rotate
		{
			car->node->m_vRotation.y -= 1.0f *deltaTime;
		}

		if (steerAngle < 30.0f)
			steerAngle += 10.0f * deltaTime;
	}
}

void SpecialKeyPressed(int key, int x, int y)
{
	InputManager::GetInstance()->specialKeyStates[key] = true;

	if (key == GLUT_KEY_RIGHT)
	{
		if (currentCamera == rearCam)
		{
			currentCamera = rightCam;
		}
		else if (currentCamera == rightCam)
		{
			currentCamera = frontCam;
		}
		else if (currentCamera == frontCam)
		{
			currentCamera = leftCam;
		}
		else if (currentCamera == leftCam)
		{
			currentCamera = rearCam;
		}
	}

	if (key == GLUT_KEY_LEFT)
	{
		if (currentCamera == rearCam)
		{
			currentCamera = leftCam;
		}
		else if (currentCamera == leftCam)
		{
			currentCamera = frontCam;
		}
		else if (currentCamera == frontCam)
		{
			currentCamera = rightCam;
		}
		else if (currentCamera == rightCam)
		{
			currentCamera = rearCam;
		}
	}

	if (key == GLUT_KEY_UP)
	{
		if (currentCamera != topCam && currentCamera != frontCam)
		{
			currentCamera = topCam;
		}
	}

	if (key == GLUT_KEY_DOWN)
	{
		if (currentCamera == topCam)
		{
			currentCamera = rearCam;
		}
	}
}

void SpecialKeyReleased(int key, int x, int y)
{
	InputManager::GetInstance()->specialKeyStates[key] = false;

	InputManager::GetInstance()->vertical = 0;
	InputManager::GetInstance()->horizontal = 0;
}

void SpecialKeyOperations()
{
	if (InputManager::GetInstance()->specialKeyStates[GLUT_KEY_UP] == true)
	{
		InputManager::GetInstance()->vertical = 1.0f;
	}

	if (InputManager::GetInstance()->specialKeyStates[GLUT_KEY_DOWN] == true)
	{
		InputManager::GetInstance()->vertical = -1.0f;
	}

	if (InputManager::GetInstance()->specialKeyStates[GLUT_KEY_LEFT] == true)
	{
		InputManager::GetInstance()->horizontal = -1.0f;
	}

	if (InputManager::GetInstance()->specialKeyStates[GLUT_KEY_RIGHT] == true)
	{
		InputManager::GetInstance()->horizontal  = 1.0f;
	}
}

void MouseInput(int x, int y)
{
	glutSetCursor(GLUT_CURSOR_NONE);

	static POINT mouseDelta;
	static bool warped = false;

	if (!warped)
	{
		mouseDelta.x = x - WINDOW_WIDTH / 2;
		mouseDelta.y = y - WINDOW_HEIGHT / 2;

		if (camera->m_vRotation.x < 45.0f && mouseDelta.y < 0)
		{
			camera->Pitch(mouseDelta.y * deltaTime);
		}
		else if (camera->m_vRotation.x > -45.0f && mouseDelta.y > 0)
		{
			camera->Pitch(mouseDelta.y * deltaTime);
		}

		camera->Yaw(mouseDelta.x * deltaTime);

		warped = true;
		glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	else
	{
		warped = false;
	}

	glutPostRedisplay();
}
