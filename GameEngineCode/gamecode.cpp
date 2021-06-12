// GameCode.cpp		
#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"

Game::Game()
{
   // No-op
}

Game::~Game()
{
   // No-op
}

Game Game::instance;    // Singleton instance

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()

{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err=SUCCESS;

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err= Update();
		break;
   case GAMEOVER:
		err = FAILURE;  // Error return causes the window loop to exit
		break;
   case CREDITS:
	   err = Credits(); //Credits page
	   break;
   case WIN:
	   err = Win(); //Win Screen
	   break;
   case LOSE:
	   err = Lose(); //Gameover from losing screen
	   break;
	default:
		// Not a valid state
		err = FAILURE;       // Error return causes the window loop to exit
	}

	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	case CREDITS:
		//Not Needed?
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	case CREDITS:
		//Not Needed?
		break;
	}
}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
   // Any clean up code here 


	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}

//if the player dies, this screen is displayed
ErrorType Game::Lose()
{
	MyDrawEngine::GetInstance()->WriteText(500, 220, L"You Died", MyDrawEngine::LIGHTRED);
	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = { L"Main Menu", L"Quit" };

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::LIGHTBLUE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // Resume
		{
			ChangeState(MENU);  // Go back to running the game
		}
		if (m_menuOption == 1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(GAMEOVER);     // Go back to the menu
		}

	}

	return SUCCESS;
}

//When the win condition of killing all enemies is met this screen is displayed
ErrorType Game::Win()
{
	MyDrawEngine::GetInstance()->WriteText(500, 220, L"You Defeated the Boss and Won, Congratulations", MyDrawEngine::LIGHTBLUE);
	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = { L"Main Menu", L"Quit" };

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::LIGHTBLUE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // Resume
		{
			ChangeState(MENU);  // Go back to running the game
		}
		if (m_menuOption == 1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(GAMEOVER);     // Go back to the menu
		}

	}

	return SUCCESS;
}


// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::LIGHTBLUE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

   // Display menu options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::LIGHTBLUE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

   // Get user input
	pInputs->SampleKeyboard();

   // Move choice up and down
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // If player chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	//Changes to the title and added the Credits screen to this section
	//MyDrawEngine::GetInstance()->WriteText(500,220, L"You Ever Fight A Squid?", MyDrawEngine::LIGHTBLUE);

	const int NUMOPTIONS = 4;
	 MyDrawEngine::GetInstance()->DrawAt(Vector2D(0,0), MyDrawEngine::GetInstance()->LoadPicture(L"title_screen.bmp") , 1.5f);
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Go Fullscreen",L"Credits" ,L"Exit"};

   // If the window is currently fullscreen, change the second option to read "Go Windowed" instead
	if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
	{
		wcscpy_s( options[1], 15, L"Go Windowed");
	}

   // Display the options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::LIGHTBLUE;
		}
		MyDrawEngine::GetInstance()->WriteText(300,250+50*i, options[i], colour);
	}

   // Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if(m_menuOption ==1)          // Toggle full screen
		{
			if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed();
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen();
			}
		}
		if (m_menuOption == 2)
		{
			ChangeState(CREDITS);
		}
		if(m_menuOption ==3)          //Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}

ErrorType Game::Credits()
{

	MyDrawEngine::GetInstance()->WriteText(500, 220, L"Credits", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteText(500, 320, L"Base Engine: Chris Rook", MyDrawEngine::BLUE);
	MyDrawEngine::GetInstance()->WriteText(500, 420, L"Programmed by: Michael Stringer", MyDrawEngine::RED);
	MyDrawEngine::GetInstance()->WriteText(500, 520, L"Art By: Tereza Filousova", MyDrawEngine::DARKGREEN);

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (pInputs->NewKeyPressed(DIK_ESCAPE))
	{
		ChangeState(MENU);
	}

	return SUCCESS;
}

// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
   // Code to set up your game *********************************************
   // **********************************************************************

	gt.mark();
	gt.mark();

	//My Code


	//Set Camera to 0,0 where the first room will be located
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D (0, 0));

	//Create rooms

	//Create Room 1 - Starting Room
	GameObject* pRoom1 = builder.buildRoom(Vector2D(0, 0));
	objectManager.addObject(pRoom1);

	//Create Room 2 - Turret Room
	GameObject* pRoom2 = builder.buildRoom(Vector2D(0, -2100));
	objectManager.addObject(pRoom2);

	//Create Room 3 - Shark + Turret room
	GameObject* pRoom3 = builder.buildRoom(Vector2D(0, -4200));
	objectManager.addObject(pRoom3);

	//Create Room 4 (Boss Room)
	GameObject* pRoom4 = builder.buildRoom(Vector2D(0, -6300));
	objectManager.addObject(pRoom4);

	//Create Doors and add them to both the Object Manager and Room manager to be handled by Room Manager
	//Room 1 Door 1 (North)
	GameObject* pDoor1 = builder.buildDoor(Vector2D(0, -900), pRoom2, Vector2D(0, -1500));
	objectManager.addObject(pDoor1);
	roomManager.addDoor(pDoor1);

	//Room 2 Door 1 (South)
	GameObject* pDoor2 = builder.buildDoor(Vector2D (0, -1300), pRoom1, Vector2D(0, -600));
	objectManager.addObject(pDoor2);
	roomManager.addDoor(pDoor2);

	//Room 2 Door 2 (North)
	GameObject* pDoor3 = builder.buildDoor(Vector2D(0, -3000), pRoom3, Vector2D(0, -3600));
	objectManager.addObject(pDoor3);
	roomManager.addDoor(pDoor3);

	//Room 3 Door 1 (South)
	GameObject* pDoor4 = builder.buildDoor(Vector2D(0, -3400), pRoom2, Vector2D(0, -2600));
	objectManager.addObject(pDoor4);
	roomManager.addDoor(pDoor4);

	//Room 3 Door 2 (North)
	GameObject* pDoor5 = builder.buildDoor(Vector2D(0, -5100), pRoom4, Vector2D(0, -5600));
	objectManager.addObject(pDoor5);
	roomManager.addDoor(pDoor5);


	//Create The Player Character
	GameObject* pSquid = builder.buildSquidPlayer(Vector2D(0, 500), &objectManager);
	objectManager.addObject(pSquid);

	//Add Objects To Rooms

	//Room 1
	//Enemies
	GameObject* pGoldFish = builder.buildGoldFish(Vector2D(500, -250), Vector2D(-350, 0), pSquid); 
	objectManager.addObject(pGoldFish);		 

	//Enemy Trigger Zones
	GameObject* pGoldfishTrigger = builder.buildEnemyTriggerZone(pGoldFish, 500);
	objectManager.addObject(pGoldfishTrigger);

	//Rocks
	GameObject* pRock1 = builder.buildRock(Vector2D(-420, 350), 0);
	objectManager.addObject(pRock1);
	GameObject* pRock2 = builder.buildRock(Vector2D(600, 650), 1);
	objectManager.addObject(pRock2);
	GameObject* pRock3 = builder.buildRock(Vector2D(700, 200), 2);
	objectManager.addObject(pRock3);
	GameObject* pRock4 = builder.buildRock(Vector2D(-500, -450), 2);
	objectManager.addObject(pRock4);
	GameObject* pRock5 = builder.buildRock(Vector2D(240, -650), 1);
	objectManager.addObject(pRock5);
	GameObject* pRock6 = builder.buildRock(Vector2D(350, -60), 2);
	objectManager.addObject(pRock6);

	//Particle Effects
	GameObject* pBubblesCrack = builder.buildBubbles(Vector2D(-240, -360), &objectManager);
	objectManager.addObject(pBubblesCrack);

	//Health Pickups
	GameObject* pHeartPickup1 = builder.buildHeartPickup(Vector2D(120, -600));
	objectManager.addObject(pHeartPickup1);

	//Room 2
	//Enemies
	GameObject* pGoldFish2 = builder.buildGoldFish(Vector2D(500, -2400), Vector2D(-350, 0), pSquid); 
	objectManager.addObject(pGoldFish2);
	GameObject* pTurret1 = builder.buildTurret(Vector2D(-600, -2700), pSquid, &objectManager);
	objectManager.addObject(pTurret1);
	GameObject* pTurret2 = builder.buildTurret(Vector2D(600, -2700), pSquid, &objectManager);
	objectManager.addObject(pTurret2);
	
	//Enemy Trigger Zones
	GameObject* pGoldfishTrigger2 = builder.buildEnemyTriggerZone(pGoldFish2,500);
	objectManager.addObject(pGoldfishTrigger2);
	GameObject* pTurretTrigger1 = builder.buildEnemyTriggerZone(pTurret1, 700);
	objectManager.addObject(pTurretTrigger1);
	GameObject* pTurretTrigger2 = builder.buildEnemyTriggerZone(pTurret2, 700);
	objectManager.addObject(pTurretTrigger2);

	//Rocks
	GameObject* pRock7 = builder.buildRock(Vector2D(-200, -2600), 1);
	objectManager.addObject(pRock7);
	GameObject* pRock8 = builder.buildRock(Vector2D(200, -2600), 1);
	objectManager.addObject(pRock8);
	GameObject* pRock9 = builder.buildRock(Vector2D(-175, -2200), 1);
	objectManager.addObject(pRock9);
	GameObject* pRock10 = builder.buildRock(Vector2D(175, -2200), 1);
	objectManager.addObject(pRock10);
	GameObject* pRock11 = builder.buildRock(Vector2D(-650, -1600), 0);
	objectManager.addObject(pRock11);
	GameObject* pRock12 = builder.buildRock(Vector2D(650, -1600), 0);
	objectManager.addObject(pRock12);

	//Health Pickups
	GameObject* pHeartPickup2 = builder.buildHeartPickup(Vector2D(520, -2600));
	objectManager.addObject(pHeartPickup2);
	
	//Room 3
	//Rocks
	GameObject* pRock13 = builder.buildRock(Vector2D(-650, -4000), 1);
	objectManager.addObject(pRock13);
	GameObject* pRock14 = builder.buildRock(Vector2D(650, -4000), 1);
	objectManager.addObject(pRock14);
	GameObject* pRock15 = builder.buildRock(Vector2D(-650, -4400), 0);
	objectManager.addObject(pRock15);
	GameObject* pRock16 = builder.buildRock(Vector2D(650, -4400), 0);
	objectManager.addObject(pRock16);

	//Enemies
	GameObject* pShark = builder.buildShark(Vector2D(0, -4200));
	objectManager.addObject(pShark);

	GameObject* pTurret3 = builder.buildTurret(Vector2D(-500, -4700), pSquid, &objectManager);
	objectManager.addObject(pTurret3);
	GameObject* pTurretTrigger3 = builder.buildEnemyTriggerZone(pTurret3, 700);
	objectManager.addObject(pTurretTrigger3);
	GameObject* pTurret4 = builder.buildTurret(Vector2D(500, -4700), pSquid, &objectManager);
	objectManager.addObject(pTurret4);
	GameObject* pTurret5 = builder.buildTurret(Vector2D(0, -4500), pSquid, &objectManager);
	objectManager.addObject(pTurret5);

	//Enemy Triggers
	GameObject* pSharkTrigger = builder.buildEnemyTriggerZone(pShark, 300);
	objectManager.addObject(pSharkTrigger);
	GameObject* pTurretTrigger4 = builder.buildEnemyTriggerZone(pTurret4, 700);
	objectManager.addObject(pTurretTrigger4);
	GameObject* pTurretTrigger5 = builder.buildEnemyTriggerZone(pTurret5, 700);
	objectManager.addObject(pTurretTrigger5);

	//Health Pickups
	GameObject* pHeartPickup3 = builder.buildHeartPickup(Vector2D(320, -4400));
	objectManager.addObject(pHeartPickup3);
	GameObject* pHeartPickup4 = builder.buildHeartPickup(Vector2D(-220, -3600));
	objectManager.addObject(pHeartPickup4);


	//Boss Room
	//Shot Speed Increase Pickup
	GameObject* pShotSpeedPickup = builder.buildShotSpeedPowerUp(Vector2D(500, -6300));
	objectManager.addObject(pShotSpeedPickup);

	//Enemies
	GameObject* pBoss = builder.buildBossHead();
	objectManager.addObject(pBoss);
	GameObject* pBossLeftArm = builder.buildBossArm(Vector2D(-600, -6850), 1, pSquid, &objectManager);
	objectManager.addObject(pBossLeftArm);
	GameObject* pBossRightArm = builder.buildBossArm(Vector2D(600, -6850), 0, pSquid, &objectManager);
	objectManager.addObject(pBossRightArm);

	//Enemy Triggers
	GameObject* pBossTriggerLeft = builder.buildEnemyTriggerZone(pBossLeftArm, 1800);
	objectManager.addObject(pBossTriggerLeft);
	GameObject* pBossTriggerRight = builder.buildEnemyTriggerZone(pBossRightArm, 1800);
	objectManager.addObject(pBossTriggerRight);

	return SUCCESS;
}


// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// Check for entry to pause menu
	static bool escapepressed = true;
	if (KEYPRESSED(VK_ESCAPE))
	{
		if (!escapepressed)
			ChangeState(PAUSED);
		escapepressed = true;
	}
	else
		escapepressed = false;

	
	// Your code goes here *************************************************
	// *********************************************************************
	
	gt.mark();

	//My Code

	//Update, render and check collisions of objects
	objectManager.updateAll(float(gt.mdFrameTime));
	objectManager.renderAll();
	objectManager.checkAllCollisions();

	//get number of objects with the Enemy Type to send to the room manager, its then used in handling doors
	int numberOfEnemies = objectManager.getNumberofType(ObjectType::ENEMY);
	roomManager.updateRoom(numberOfEnemies);
	
	//If the player dies there will be zero squids trigger the loss condition, to Win all enemies must be killed
	if (objectManager.getNumberofType(ObjectType::SQUID) == 0)
	{
		ChangeState(LOSE);
	}
	if (numberOfEnemies == 0)
	{
		ChangeState(WIN);
	}
	//Delete anything marked for deletion
	objectManager.deleteInactive();
	
	//
   // *********************************************************************
   // *********************************************************************

	return SUCCESS;
}

// Called when the player ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
   // Add code here to tidy up ********************************************
   // *********************************************************************
	
	//Delete all objects
	objectManager.deleteAll();

	return SUCCESS;
}

