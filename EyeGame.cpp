#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include "Circle.h"
#include "Button.h"
#include <string>
#include "Texture.h"
#include "EyeInterface.h"

int WIDTH = 1080;
int HEIGHT = 720;
int RADIUS = 25;

char programName[] = "EyeGame";
EyeInterface * eye;
Circle ball(0,HEIGHT,RADIUS);

char *mainBg = "Images/mainScreen.pam";
char *playgroundImage = "Images/playgroundWindow.pam";
char *playgroundStatic = "Images/playgroundStatic.pam";
char *playgroundHover = "Images/playgroundHover.pam";
char *playgroundClicked = "Images/playgroundClicked.pam";
char *ballGameStatic = "Images/ballGameStatic.pam";
char *ballGameHover = "Images/ballGameHover.pam";
char *ballGameClicked = "Images/ballGameClicked.pam";
char *mazeGameStatic = "Images/mazeGameStatic.pam";
char *mazeGameHover = "Images/mazeGameHover.pam";
char *mazeGameClicked = "Images/mazeGameClicked.pam";
char *aboutGameStatic = "Images/aboutGameStatic.pam";
char *aboutGameHover = "Images/aboutGameHover.pam";
char *aboutGameClicked = "Images/aboutGameClicked.pam";
char *aboutGameImage = "Images/aboutGameWindow.pam";

bool isPlaygroundHover = false;
bool isPlaygroundClicked = false;
bool isBallGameHover = false;
bool isBallGameClicked = false;
bool isAboutGameHover = false;
bool isAboutGameClicked = false;
bool isMazeGameHover = false;
bool isMazeGameClicked = false;
bool isBackButtonClicked = false;
bool isBackButtonHover = false;

double playgroundPos[] = {15,275,250,100};
double ballGamePos[] = {280,275,250,100};
double mazeGamePos[] = {545,275,250,100};
double aboutGamePos[] = {810,275,250,100};
double backButtonPos[] = {15,15,75,75};

char *ballGameImage = "Images/ballGameScreen.pam";
char *backButtonStatic = "Images/backButtonStatic.pam";
char *backButtonHover = "Images/backButtonHover.pam";
char *backButtonClicked = "Images/backButtonClicked.pam";

char *mazeGameLevel1 = "Images/mazeGameLevel1.pam";
char *mazeGameLevel2 = "Images/mazeGameLevel2.pam";
char *mazeGameLevel3 = "Images/mazeGameLevel3.pam";
char *afterMazeWindow = "Images/afterMazeWindow.pam";

int mainBgTextureId, playgroundTextureId, ballGameTextureId, mazeGameLevel1TextureId, mazeGameLevel2TextureId, mazeGameLevel3TextureId, afterMazeWindowTextureId, backButtonStaticId, backButtonHoverId, backButtonClickedId, aboutGameTextureId;

int startWindowId = 0, playgroundWindowId = 0, ballGameWindowId = 0, mazeGameLevel1WindowId = 0, mazeGameLevel2WindowId = 0, mazeGameLevel3WindowId = 0, afterMazeWindowId = 0, aboutGameWindowId = 0;

int * WindowId[] = {&startWindowId, &playgroundWindowId, &ballGameWindowId, &mazeGameLevel1WindowId, &mazeGameLevel2WindowId, &mazeGameLevel3WindowId, &afterMazeWindowId, &aboutGameWindowId};

int numWindows = 8;

int playgroundStaticId, playgroundHoverId, playgroundClickedId, ballGameStaticId, ballGameHoverId, ballGameClickedId, mazeGameStaticId, mazeGameHoverId, mazeGameClickedId, aboutGameStaticId, aboutGameHoverId, aboutGameClickedId;

int * buttonsID[] = {&playgroundStaticId, &playgroundHoverId, &playgroundClickedId, &ballGameStaticId, &ballGameHoverId, &ballGameClickedId, &mazeGameStaticId, &mazeGameHoverId, &mazeGameClickedId, &aboutGameStaticId, &aboutGameHoverId, &aboutGameClickedId };

double * Buttons[] = {playgroundPos, ballGamePos, mazeGamePos, aboutGamePos, backButtonPos};
int BUTTON_SIZE = 5;

bool * hoverButton[] = {&isPlaygroundHover, &isBallGameHover, &isMazeGameHover, &isAboutGameHover, &isBackButtonHover};

bool * clickedButton[] = {&isPlaygroundClicked, &isBallGameClicked, &isMazeGameClicked, &isAboutGameClicked};

char *zero = "Images/0.pam";
char *one = "Images/1.pam";
char *two = "Images/2.pam";
char *three = "Images/3.pam";
char *four = "Images/4.pam";
char *five = "Images/5.pam";
char *six = "Images/6.pam";
char *seven = "Images/7.pam";
char *eight = "Images/8.pam";
char *nine = "Images/9.pam";

int zeroTextureId, oneTextureId, twoTextureId, threeTextureId, fourTextureId, fiveTextureId, sixTextureId, sevenTextureId, eightTextureId, nineTextureId ;
int score = 0;

int createNewWindow(const char* title, int Window);
void mouse_motion(int x, int y);
void keyboard(unsigned char c, int x, int y);
void keyboard2(unsigned char c, int x, int y);
void mouse(int mouseButton, int state, int x, int y);
void mouse2(int mouseButton, int state, int x, int y);
void createMazeGameLevel1Window();
void createMazeGameLevel2Window();
void createMazeGameLevel3Window();
void createAfterMazeWindow();


void drawStartWindow() { 
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(mainBgTextureId,0,0,1080,720);
	Button playground;
	playground.drawButton(playgroundPos);
	if (isPlaygroundClicked) drawTexture(playgroundClickedId, playgroundPos);
	else if (isPlaygroundHover) drawTexture(playgroundHoverId, playgroundPos);
	else drawTexture(playgroundStaticId, playgroundPos);
	Button ballGame;
	ballGame.drawButton(ballGamePos);
	if (isBallGameClicked) drawTexture(ballGameClickedId, ballGamePos);
	else if (isBallGameHover) drawTexture(ballGameHoverId, ballGamePos);
	else drawTexture(ballGameStaticId, ballGamePos);
	Button mazeGame;
	mazeGame.drawButton(mazeGamePos);
	if (isMazeGameClicked) drawTexture(mazeGameClickedId, mazeGamePos);
	else if (isMazeGameHover) drawTexture(mazeGameHoverId, mazeGamePos);
	else drawTexture(mazeGameStaticId, mazeGamePos);
	Button aboutGame;
	aboutGame.drawButton(aboutGamePos);
	if (isAboutGameClicked) drawTexture(aboutGameClickedId, aboutGamePos);
	else if (isAboutGameHover) drawTexture(aboutGameHoverId, aboutGamePos);
	else drawTexture(aboutGameStaticId, aboutGamePos);  
	glutSwapBuffers();
}


void createStartWindow() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	startWindowId = createNewWindow("Eye Game",1);
	glutDisplayFunc(drawStartWindow);
	glutKeyboardFunc(keyboard);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);

	mainBgTextureId = loadTexture(mainBg);

	playgroundStaticId = loadTexture(playgroundStatic);
	playgroundHoverId = loadTexture(playgroundHover);
	playgroundClickedId = loadTexture(playgroundClicked);

	ballGameStaticId = loadTexture(ballGameStatic);
	ballGameHoverId = loadTexture(ballGameHover);
	ballGameClickedId = loadTexture(ballGameClicked);

	mazeGameStaticId = loadTexture(mazeGameStatic);
	mazeGameHoverId = loadTexture(mazeGameHover);
	mazeGameClickedId = loadTexture(mazeGameClicked);

	aboutGameStaticId = loadTexture(aboutGameStatic);
	aboutGameHoverId = loadTexture(aboutGameHover);
	aboutGameClickedId = loadTexture(aboutGameClicked); 

	glutPostWindowRedisplay(startWindowId);
	glutSetWindow(startWindowId);
}

void drawPlaygroundWindow() {
	glutSetWindow(playgroundWindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(playgroundTextureId, 0, 0, WIDTH, HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId,backButtonPos);
	else if (isBackButtonHover) drawTexture(backButtonHoverId,backButtonPos);
	else drawTexture(backButtonStaticId, backButtonPos);
	eye->update();
	ball.x += (eye->x-ball.x) * 0.016;
	ball.y += (eye->y-ball.y) * 0.016;

	if (ball.x > WIDTH) ball.x = 0;
	if (ball.x < 0) ball.x = WIDTH;
	if (ball.y > HEIGHT) ball.y = 0;
	if (ball.y < 0) ball.y = HEIGHT;

	ball.draw();

	glutSwapBuffers();
}

void updatePlayground() {
	if(playgroundWindowId){
		eye->update();
		drawPlaygroundWindow();
	}
	
}

void createPlaygroundWindow() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	playgroundWindowId = createNewWindow("Playground", 4);
	glutDisplayFunc(drawPlaygroundWindow);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	playgroundTextureId = loadTexture(playgroundImage);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(playgroundWindowId);
	glutSetWindow(playgroundWindowId);
	glutIdleFunc(updatePlayground);
}

void drawBallGameWindow() {

	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(ballGameTextureId, 0, 0, WIDTH, HEIGHT);
	
	if (score == 0) drawTexture(zeroTextureId, 480, 50, 100, 250);
	if (score == 1) drawTexture(oneTextureId, 480, 50, 100, 250);
	if (score == 2) drawTexture(twoTextureId, 480, 50, 100, 250);
	if (score == 3) drawTexture(threeTextureId, 480, 50, 100, 250);
	if (score == 4) drawTexture(fourTextureId, 480, 50, 100, 250);
	if (score == 5) drawTexture(fiveTextureId, 480, 50, 100, 250);
	if (score == 6) drawTexture(sixTextureId, 480, 50, 100, 250);
	if (score == 7) drawTexture(sevenTextureId, 480, 50, 100, 250);
	if (score == 8) drawTexture(eightTextureId, 480, 50, 100, 250);
	if (score == 9) drawTexture(nineTextureId, 480, 50, 100, 250); 
	if (score == 10) {
		drawTexture(oneTextureId, 480, 50, 100, 250); 
		drawTexture(zeroTextureId, 560, 50, 100, 250);
		glutDestroyWindow(ballGameWindowId);
		ballGameWindowId = 0;
		createMazeGameLevel1Window();
	}

	if (isBackButtonClicked) drawTexture(backButtonClickedId, backButtonPos); 
	else if (isBackButtonHover) drawTexture(backButtonHoverId, backButtonPos); 
	else drawTexture(backButtonStaticId, backButtonPos); 
	eye->update();
	
	ball.x += (eye->x-ball.x) * 0.016;
	ball.y += (eye->y-ball.y) * 0.016;
  	
	if (ball.x > WIDTH) ball.x = 0;
	if (ball.x < 0) ball.x = WIDTH;
	if (ball.y > HEIGHT) ball.y = 0;
	if (ball.y < 0) ball.y = HEIGHT;
	if (ball.x > 700 && ball.x < 800 && ball.y > 200 && ball.y < 250) {ball.x = 0; ball.y = 720; ++ score;}

	ball.draw();

	glutSwapBuffers();

}

void updateBall() {
	if(ballGameWindowId){
		eye->update();
		drawBallGameWindow();
	}
	
}

void createBallGameWindow() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	ballGameWindowId = createNewWindow("Basketball Game",2);
	glutDisplayFunc(drawBallGameWindow);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	ballGameTextureId = loadTexture(ballGameImage);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);

	zeroTextureId = loadTexture(zero);
	oneTextureId = loadTexture(one);
	twoTextureId = loadTexture(two);
	threeTextureId = loadTexture(three);
	fourTextureId = loadTexture(four);
	fiveTextureId = loadTexture(five);
	sixTextureId = loadTexture(six);
	sevenTextureId = loadTexture(seven);
	eightTextureId = loadTexture(eight);
	nineTextureId = loadTexture(nine);


	glutPostWindowRedisplay(ballGameWindowId);
	glutSetWindow(ballGameWindowId);	
	glutIdleFunc(updateBall);
}

bool collideWithWallLevel1() {
	if (ball.x > WIDTH - RADIUS || ball.x < 0 + RADIUS|| ball.y > HEIGHT - RADIUS|| ball.y < 0 + RADIUS || (ball.x < 270 + RADIUS && ball.x > 0 + RADIUS && ball.y > 540 - RADIUS && ball.y < 550 + RADIUS) || (ball.x > 270 - RADIUS && ball.x < 540 + RADIUS && ball.y > 360 - RADIUS && ball.y < 370 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 550 + RADIUS && ball.y > 180 - RADIUS && ball.y < 540 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < 820 + RADIUS && ball.y > 360 - RADIUS && ball.y < 540 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < WIDTH - RADIUS && ball.y > 360 - RADIUS && ball.y < 370 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < 810 + RADIUS && ball.y > RADIUS && ball.y < 180 + RADIUS))
		return true;
	return false;
}

void drawMazeGameLevel1Window() {
	glutSetWindow(mazeGameLevel1WindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(mazeGameLevel1TextureId, 0, 0, WIDTH, HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId, backButtonPos); 
	else if (isBackButtonHover) drawTexture(backButtonHoverId, backButtonPos); 
	else drawTexture(backButtonStaticId, backButtonPos); 
	eye->update();

	ball.x += (eye->x-ball.x) * 0.016;
	ball.y += (eye->y-ball.y) * 0.016;

	if (collideWithWallLevel1()) {
		ball.x = 135;
		ball.y = 90;
	}

	if (ball.x > 900 && ball.x < 1000 && ball.y > 400 && ball.y < 500) {
		glutDestroyWindow(mazeGameLevel1WindowId);
		mazeGameLevel1WindowId = 0;
		ball.x = 50; ball.y = 350;
		createMazeGameLevel2Window();
 	}

	ball.draw();


	glutSwapBuffers();
}

void updateMazeLevel1() {
	if (mazeGameLevel1WindowId) {
		eye->update();
		drawMazeGameLevel1Window();
	}
}

void createMazeGameLevel1Window() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	mazeGameLevel1WindowId = createNewWindow("Maze Game",3);
	glutDisplayFunc(drawMazeGameLevel1Window);
	glutMouseFunc(mouse2);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	mazeGameLevel1TextureId = loadTexture(mazeGameLevel1);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(mazeGameLevel1WindowId);
	glutSetWindow(mazeGameLevel1WindowId);
	glutIdleFunc(updateMazeLevel1);
}

bool collideWithWallLevel2() {
	if (ball.x > WIDTH - RADIUS || ball.x < 0 + RADIUS|| ball.y > HEIGHT - RADIUS|| ball.y < 0 + RADIUS || (ball.x > 270 - RADIUS && ball.x < 280 + RADIUS && ball.y > RADIUS && ball.y < 360 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 550 + RADIUS && ball.y > 360 - RADIUS && ball.y < 540 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < 820 + RADIUS && ball.y > 180 - RADIUS && ball.y < 360 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < 820 + RADIUS && ball.y > 540 - RADIUS && ball.y < HEIGHT - RADIUS) || (ball.x > 270 - RADIUS && ball.x < 540 + RADIUS && ball.y > 540 - RADIUS && ball.y < 550 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 810 + RADIUS && ball.y > 360 - RADIUS && ball.y < 370 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 550 + RADIUS && ball.y > RADIUS && ball.y < 180 + RADIUS)) 
		return true;
	return false;
}

void drawMazeGameLevel2Window() {
	glutSetWindow(mazeGameLevel2WindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(mazeGameLevel2TextureId, 0, 0, WIDTH, HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId, backButtonPos); 
	else if (isBackButtonHover) drawTexture(backButtonHoverId, backButtonPos); 
	else drawTexture(backButtonStaticId, backButtonPos); 
	eye->update();

	ball.x += (eye->x-ball.x) * 0.016;
	ball.y += (eye->y-ball.y) * 0.016;

	if (collideWithWallLevel2()) {
		ball.x = 50;
		ball.y = 200;
	}

	if (ball.x > 870 && ball.x < 970 && ball.y > 225 && ball.y < 315) {
		glutDestroyWindow(mazeGameLevel2WindowId);
		mazeGameLevel2WindowId = 0;
		ball.x = 135;
		ball.y = 450;
		createMazeGameLevel3Window();
	}

	ball.draw();

	glutSwapBuffers();
}

void updateMazeLevel2() {
	if (mazeGameLevel2WindowId) {
		eye->update();
		drawMazeGameLevel2Window();
	}
}

void createMazeGameLevel2Window() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	mazeGameLevel2WindowId = createNewWindow("Level 2",6);
	glutDisplayFunc(drawMazeGameLevel2Window);
	glutMouseFunc(mouse2);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	mazeGameLevel2TextureId = loadTexture(mazeGameLevel2);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(mazeGameLevel2WindowId);
	glutSetWindow(mazeGameLevel2WindowId);
	glutIdleFunc(updateMazeLevel2);
}

bool collideWithWallLevel3() {
	if (ball.x > WIDTH - RADIUS || ball.x < 0 + RADIUS|| ball.y > HEIGHT - RADIUS|| ball.y < RADIUS || (ball.x > 270 - RADIUS && ball.x < 280 + RADIUS && ball.y > RADIUS && ball.y < 180 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 550 + RADIUS && ball.y > 180 - RADIUS && ball.y < 540 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < 820 + RADIUS && ball.y > 360 - RADIUS && ball.y < 540 + RADIUS) || (ball.x > RADIUS && ball.x < 270 + RADIUS && ball.y > 540 - RADIUS && ball.y < 550 + RADIUS) || (ball.x > 270 - RADIUS && ball.x < 540 + RADIUS && ball.y > 360 - RADIUS && ball.y < 370 + RADIUS) || (ball.x > 540 - RADIUS && ball.x < 810 + RADIUS && ball.y > 180 - RADIUS && ball.y < 190 + RADIUS) || (ball.x > 810 - RADIUS && ball.x < WIDTH - RADIUS && ball.y > 360 - RADIUS && ball.y < 370 + RADIUS))
		return true;
	return false;
}

void drawMazeGameLevel3Window() {
	glutSetWindow(mazeGameLevel3WindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(mazeGameLevel3TextureId, 0, 0, WIDTH, HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId, backButtonPos); 
	else if (isBackButtonHover) drawTexture(backButtonHoverId, backButtonPos); 
	else drawTexture(backButtonStaticId, backButtonPos); 
	eye->update();

	ball.x += (eye->x-ball.x) * 0.016;
	ball.y += (eye->y-ball.y) * 0.016;

	if (collideWithWallLevel3()) {
		ball.x = 135;
		ball.y = 450;
	}

	if (ball.x > 650 && ball.x < 750 && ball.y > 45 && ball.y < 135) {
		glutDestroyWindow(mazeGameLevel3WindowId);
		mazeGameLevel3WindowId = 0;
		createAfterMazeWindow();
	}

	ball.draw();

	glutSwapBuffers();
}

void updateMazeLevel3() {
	if (mazeGameLevel3WindowId) {
		eye->update();
		drawMazeGameLevel3Window();
	}
}

void createMazeGameLevel3Window() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	mazeGameLevel3WindowId = createNewWindow("Level 3",7);
	glutDisplayFunc(drawMazeGameLevel3Window);
	glutMouseFunc(mouse2);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	mazeGameLevel3TextureId = loadTexture(mazeGameLevel3);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(mazeGameLevel3WindowId);
	glutSetWindow(mazeGameLevel3WindowId);
	glutIdleFunc(updateMazeLevel3);
}

void drawAfterMazeWindow() {
	glutSetWindow(afterMazeWindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(afterMazeWindowTextureId,0,0,WIDTH,HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId,backButtonPos);
	else if (isBackButtonHover) drawTexture(backButtonHoverId,backButtonPos);
	else drawTexture(backButtonStaticId,backButtonPos);
	glutSwapBuffers();
}

void createAfterMazeWindow() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	afterMazeWindowId = createNewWindow("Congratulations!", 8);
	glutDisplayFunc(drawAfterMazeWindow);
	glutMouseFunc(mouse2);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	afterMazeWindowTextureId = loadTexture(afterMazeWindow);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(afterMazeWindowId);
	glutSetWindow(afterMazeWindowId);
}

void drawAboutGameWindow() {
	glutSetWindow(aboutGameWindowId);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture(aboutGameTextureId,0,0,WIDTH,HEIGHT);
	if (isBackButtonClicked) drawTexture(backButtonClickedId,backButtonPos);
	else if (isBackButtonHover) drawTexture(backButtonHoverId,backButtonPos);
	else drawTexture(backButtonStaticId,backButtonPos);
	glutSwapBuffers();
}

void createAboutGameWindow() {
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	aboutGameWindowId = createNewWindow("About Game", 5);
	glutDisplayFunc(drawAboutGameWindow);
	glutMouseFunc(mouse2);
	glOrtho(0.,WIDTH-1,HEIGHT-1,0.,-1.0,1.0);
	aboutGameTextureId = loadTexture(aboutGameImage);
	backButtonStaticId = loadTexture(backButtonStatic);
	backButtonHoverId = loadTexture(backButtonHover);
	backButtonClickedId = loadTexture(backButtonClicked);
	glutPostWindowRedisplay(aboutGameWindowId);
	glutSetWindow(aboutGameWindowId);
}


bool onButton(int x, int y, double * buttonPos) {
	return x >= buttonPos[0] && y >= buttonPos[1] &&
		   x <= buttonPos[0] + buttonPos[2] &&
		   y <= buttonPos[1] + buttonPos[3];
}

void mouse_motion(int x, int y) {
	for (int i=0; i < BUTTON_SIZE; ++i) {
		if (onButton(x, y, Buttons[i]))
			*(hoverButton[i]) = true;
		else
			*(hoverButton[i]) = false;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y) {
	int win = glutGetWindow();
	switch(c) {
		case 'q':
		case 'Q':
		case 27:
			glutDestroyWindow(win);
			exit(0);
			break;
		default:
			break;
	}
}

void startMousePressed(int x, int y) {
	if (onButton(x,y,playgroundPos)) {
		isPlaygroundClicked = true;
	} else isPlaygroundClicked = false;

	if (onButton(x,y,ballGamePos)) {
		isBallGameClicked = true;
	} else isBallGameClicked = false;

	if (onButton(x,y,mazeGamePos)) {
		isMazeGameClicked = true;
	} else isMazeGameClicked = false;

	if (onButton(x,y,aboutGamePos)) {
		isAboutGameClicked = true;
	} else isAboutGameClicked = false;

}

void mouse(int mouseButton, int state, int x, int y) {
	if (GLUT_LEFT_BUTTON == mouseButton) {
		if (GLUT_DOWN == state) {
			startMousePressed(x,y);
		} 
		else {
			if (onButton(x,y,playgroundPos) && isPlaygroundClicked) {
				glutDestroyWindow(startWindowId);
				startWindowId = 0;
				createPlaygroundWindow();
				ball.x = 0;
				ball.y = HEIGHT;
			}
 
			if (onButton(x,y,ballGamePos) && isBallGameClicked) {
				glutDestroyWindow(startWindowId);
				startWindowId = 0;
				createBallGameWindow();
				ball.x = 0;
				ball.y = HEIGHT;
			}
			if (onButton(x,y,mazeGamePos) && isMazeGameClicked) {
				if (0 == ballGameWindowId) {
				glutDestroyWindow(startWindowId);
				startWindowId = 0;
				createMazeGameLevel1Window();
				ball.x = 135;
				ball.y = 60;
				//ball.x = 950; ball.y = 450;
				}
			}

			if (onButton(x,y,aboutGamePos) && isAboutGameClicked) {
				glutDestroyWindow(startWindowId);
				startWindowId = 0;
				createAboutGameWindow();
			}

			isPlaygroundClicked = false;
			isBallGameClicked = false;
			isMazeGameClicked = false;
			isAboutGameClicked = false;
		} 
	} else if (GLUT_RIGHT_BUTTON == mouseButton) {

	}
	glutPostRedisplay();
}


void mouse2(int mouseButton, int state, int x, int y) {
	if (GLUT_LEFT_BUTTON == mouseButton) {
		if (GLUT_DOWN == state) {
			if (onButton(x,y,backButtonPos)) {
				isBackButtonClicked = true;
			} else isBackButtonClicked = false;
		} else {
			if (onButton(x,y,backButtonPos) && isBackButtonClicked) {
				if (playgroundWindowId) {
					glutDestroyWindow(playgroundWindowId);
					playgroundWindowId = 0;
				}
				if (ballGameWindowId) {
					glutDestroyWindow(ballGameWindowId);
					ballGameWindowId = 0;
					ball.x = 0; 
					ball.y = HEIGHT;
					score = 0;
					
				}
				if (mazeGameLevel1WindowId) {
					glutDestroyWindow(mazeGameLevel1WindowId);
					mazeGameLevel1WindowId = 0;
				}

				if (mazeGameLevel2WindowId) {
					glutDestroyWindow(mazeGameLevel2WindowId);
					mazeGameLevel2WindowId = 0;
				}

				if (mazeGameLevel3WindowId) {
					glutDestroyWindow(mazeGameLevel3WindowId);
					mazeGameLevel3WindowId = 0;
				}

				if (aboutGameWindowId) {
					glutDestroyWindow(aboutGameWindowId);
					aboutGameWindowId = 0;
				}

				if (afterMazeWindowId) {
					glutDestroyWindow(afterMazeWindowId);
					afterMazeWindowId = 0;
				}

				createStartWindow();
			}

			isBackButtonClicked = false;
		}

	} else if (GLUT_RIGHT_BUTTON == mouseButton) {

	}
	glutPostRedisplay();
}


int createNewWindow(const char* title, int Window) {
	int id = glutCreateWindow(title);
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//start window
	if (Window == 1) {
		glutMouseFunc(mouse);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	//ballGameWindow
	} else if (Window == 2) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	//mazeGameWindow
	} else if (Window == 3) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	//playgroundWindow
	} else if (Window == 4) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	} else if (Window == 5) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	} else if (Window == 6) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	} else if (Window == 7) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);

	} else if (Window == 8) {
		glutMouseFunc(mouse2);
		glutMotionFunc(mouse_motion);
		glutPassiveMotionFunc(mouse_motion);
	}
	return id;
}
void init_gl_window() {
	eye =  new EyeInterface;
	char *argv[] = {programName};
	int argc = sizeof(argv)/sizeof(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	createStartWindow();
	glutMainLoop();
	
}

int main() {
	init_gl_window();
}