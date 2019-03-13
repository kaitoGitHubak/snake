#include<iostream>
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<random>
#include<cstdio>
#include<GL/glut.h>

const unsigned fildSize=32;
const unsigned cellSize=20;
using coord=std::pair<unsigned, unsigned>;

std::vector<coord> snake;
coord feed;

enum Direction{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

unsigned dir=RIGHT;

bool isOut();
bool isBody();

void moveDir();
void eatFeed();

coord randomPair();
void putFeed();
void printFeed();

void printFild();
void printSnake();

void snakeInits();

void inits();
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void display();
void timer(int value);

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("Snake");
	inits();
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	return 0;
}

bool isOut(){
	const coord obj=snake.at(snake.size()-1);
	if(obj.first<=0||obj.first>fildSize)
		return true;
	if(obj.second<=0||obj.second>fildSize)
		return true;
	return false;
}

bool isBody(){
	const coord obj=snake.at(snake.size()-1);
	const auto result=std::find(snake.begin(), snake.end()-1, obj);
	if(result!=snake.end()-1)
		return true;
	return false;
}

void moveDir(){
	coord obj=snake.at(snake.size()-1);
	snake.erase(snake.begin());
	
	switch(dir){
	case UP:
		obj.second--;
		break;
	case DOWN:
		obj.second++;
		break;
	case RIGHT:
		obj.first++;
		break;
	case LEFT:
		obj.first--;
		break;
	default:
		break;
	}
	
	snake.push_back(obj);
}

void eatFeed(){
	coord obj=snake.at(snake.size()-1);
		
	switch(dir){
	case UP:
		obj.second--;
		break;
	case DOWN:
		obj.second++;
		break;
	case RIGHT:
		obj.first++;
		break;
	case LEFT:
		obj.first--;
		break;
	default:
		break;
	}

	if(obj==feed){
		snake.push_back(feed);
		putFeed();
	}

}

coord randomPair(){
	std::random_device rnd;
	std::mt19937_64 mt(rnd());
	std::uniform_int_distribution<> rand(1,fildSize);
	const unsigned rand_x=rand(mt);
	const unsigned rand_y=rand(mt);
	coord random=std::make_pair(rand_x, rand_y);
	return random;
}

void putFeed(){
	static const coord center1=std::make_pair(1, 1);
	static const coord center2=std::make_pair(1, fildSize);
	static const coord center3=std::make_pair(fildSize, 1);
	static const coord center4=std::make_pair(fildSize, fildSize);
	const std::vector<coord> center={center1, center2, center3, center4};
	coord obj;
	
	while(1){
		obj=randomPair();
		auto result1=std::find(snake.begin(), snake.end(), obj);
		auto result2=std::find(center.begin(), center.end(), obj);
		if(result1==snake.end()&&result2==center.end()){
			feed=obj;
			return;
		}
	}
}

void printFeed(){
	const unsigned val=cellSize/2;
	
	const unsigned feed_x=feed.first;
	const unsigned feed_y=feed.second;
	
	static const int pointSize=20;
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex2i(val+cellSize*(feed_x-1), val+cellSize*(feed_y-1));
	glEnd();
}

void printFild(){
	static const unsigned lineSize=1;
	
	glColor3f(0.0f, 1.0f, 0.0);
	glLineWidth(lineSize);
	glBegin(GL_LINES);
	
	for(int i=0;i<=fildSize;i++){
		glVertex2i(cellSize*i, 0);
		glVertex2i(cellSize*i, cellSize*fildSize);

		glVertex2i(0, cellSize*i);
		glVertex2i(cellSize*fildSize, cellSize*i);
	}
	glEnd();
}

void printSnake(){
	const unsigned val=cellSize/2;
	
	const unsigned head_x=snake.at(snake.size()-1).first;
	const unsigned head_y=snake.at(snake.size()-1).second;

	static const int pointSize=20;
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex2i(val+cellSize*(head_x-1), val+cellSize*(head_y-1));
	glEnd();

	if(snake.size()==1)  return;

	unsigned body_x;
	unsigned body_y;
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	std::for_each(snake.begin(), snake.end()-1, [&](auto& obj){
			body_x=obj.first;
			body_y=obj.second;
			glVertex2i(val+cellSize*(body_x-1), val+cellSize*(body_y-1));
		});
	glEnd();
}

void snakeInits(){
	snake.clear();
	coord body=std::make_pair(1,2);
	snake.push_back(body);
	coord head=std::make_pair(2, 2);
	snake.push_back(head);
	
	putFeed();
}

void inits(){
	static const unsigned WindowSizeWight=800;
	static const unsigned WindowSizeHeight=800;

	static const unsigned WindowPossitionWight=100;
	static const unsigned WindowPossitionHeight=100;

	gluOrtho2D(0, 100, 100, 0);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(WindowPossitionWight, WindowPossitionHeight);
	glutInitWindowSize(WindowSizeWight, WindowSizeHeight);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	snakeInits();
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-0.5, (GLdouble)w-0.5, (GLdouble)h-0.1, -0.5, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'q':
	case 'Q':
	case '\033':
		std::exit(0);
		break;
	default:
		break;
	}
}

void special(int key, int x, int y){
	unsigned val;
	coord obj=snake.at(snake.size()-1);
	
	switch(key){
	case GLUT_KEY_UP:
		val=UP;
		obj.second--;
		break;
	case GLUT_KEY_DOWN:
		val=DOWN;
		obj.second++;
		break;
	case GLUT_KEY_RIGHT:
		val=RIGHT;
		obj.first++;
		break;
	case GLUT_KEY_LEFT:
		val=LEFT;
		obj.first--;
		break;
	default:
		return;
	}
	if(snake.size()!=1&&obj==snake.at(snake.size()-2))
		return;
	dir=val;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	printFild();
	printSnake();
	printFeed();
	glutSwapBuffers();
	glFlush();
}

void timer(int value){
	static const unsigned speed=70;
	eatFeed();
		moveDir();
	if(isOut()||isBody()){
		while(1){
			glutKeyboardFunc(keyboard);
			glutMainLoop();
		}
	}
	glutPostRedisplay();
	glutTimerFunc(speed, timer, 0);
}

