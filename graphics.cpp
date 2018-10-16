//
// Created by William Soccorsi on 11/29/17.
//

#include "stdlib.h"
#include "Player.h"
#include "Alien.h"
#include "Shape.h"
#include "Button.h"


#include <vector>
#include <map>



enum screen_type {start, game, score, end};

GLdouble width, height;
int wd;
vector<Circle> star(100);
vector<Circle> flames(50);
vector<Circle> explosions(20);

/*
 * Requires: Nothing
 * Modifies: Nothing
 * Effects: Global function to create a custom player based on user input
 */
Player customizePlayer();
void initializeAliens();

// initialize objects
screen_type screen;
bool levelUp;
bool paused = false;
int levelCount = 0;
Player player;
Block block1;
Block block2;
Block block3;
Button gameButton;
Button scoreButton;
Button backButton;
Button quitButton;
vector<Button> scoreSquares(10);
vector<LaserBullet> playerBullets(10);
vector<LaserBullet> alienBullets(10);
vector<Alien> aliens(5);
int playerBulletCount = 0;
int alienBulletCount = 0;
int alienMoveCount = 0;
int alienCount = 0;

void init() {
    screen = start;

    width = boardWidth;
    height = boardHeight;

    srand(time(0));

    /**
     * set values for buttons
     */
    //game button
    gameButton.setPosition(175, 180 - 24);
    gameButton.setHeight(30);
    gameButton.setWidth(120);
    gameButton.setFill(white);

    //make score button
    scoreButton.setPosition(170, 180 - 24 + 100);
    scoreButton.setHeight(30);
    scoreButton.setWidth(150);
    scoreButton.setFill(white);

    //make back button
    backButton.setPosition(boardWidth/2, boardHeight - 50);
    backButton.setHeight(30);
    backButton.setWidth(80);
    backButton.setFill(white);

    //make quit button
    quitButton.setPosition(boardWidth/2-40, boardHeight/2-15);
    quitButton.setHeight(30);
    quitButton.setWidth(80);
    quitButton.setFill(white);

    //make score squares
    for (int i = 0; i < scoreSquares.size(); ++i) {
        scoreSquares[i].setPosition(100, 30 + i * 40);
        scoreSquares[i].setHeight(30);
        scoreSquares[i].setWidth(300);
        scoreSquares[i].setFill(white);
    }


    levelUp = true;

    /**
     * set values for player
     */

    player = customizePlayer();
    player.setPosition(15,height/2 -player.getHeight()/2);

    /**
     * set values for blocks
     */

    block1.setPosition(100, 160*0 + 50);


    block2.setPosition(100, 160*1 + 50);


    block3.setPosition(100, 160*2 + 50);


    /**
     * set values for bullets
     */
//    // playerbullets
//    for (int i = 0; i < playerBullets.size(); ++i) {
//
//        playerBullets[i].setDirection(Direction::right);
//    }
//    // alienbullets
//    for (int i = 0; i < alienBullets.size(); ++i) {
//
//        alienBullets[i].setDirection(Direction::left);
//    }

    /**
     * set values for Aliens
     */
    initializeAliens();

    /**
     * set values for Stars
     */

    for (int i = 0; i < star.size(); ++i) {
        star[i] = Circle(rand() % 3 + 1,
                         {1, 1, 1},
                         {rand() % (int) width, rand() % (int) height});
    }
    for (int i = 0; i < flames.size(); ++i) {
        flames[i] = Circle(rand() % 7 + 4,
                           {1, 0, 0},
                           {rand() % (int) width, rand() % (int) height});
    }

    for (int i = 0; i < flames.size(); ++i) {
        flames[i].set_position(player.getX(), player.getY() + 25);
    }
    for (int i = 0; i < explosions.size(); ++i) {
        explosions[i] = Circle(rand() % 7 + 6,
                           {1, 0, 0},
                           {-20, -20});
    }

}



/* Initialize OpenGL Graphics */
void InitGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display_start() {

    gameButton.draw();
    string startMessage = "Start Game";
    glColor3f(.3, .3, .3);
    glRasterPos2i(180, 180);
    for (int i = 0; i < startMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, startMessage[i]);
    }

    scoreButton.draw();
    string scoreMessage = "High Scores";
    glColor3f(.3, .3, .3);
    glRasterPos2i(180, 180 + 100);
    for (int i = 0; i < scoreMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreMessage[i]);
    }

}

void display_end() {
    quitButton.draw();
    string quitMessage = "QUIT";
    glColor3f(.3,.3,.3);
    glRasterPos2i(boardWidth/2-30, boardHeight/2+5);
    for (int i = 0; i < quitMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quitMessage[i]);
    }

    string scoreMessage = "Score: " + to_string(player.getScore());
    glColor3f(.3,.3,.5);
    glRasterPos2i(boardWidth/2-40, boardHeight/2+50);
    for (int i = 0; i < scoreMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreMessage[i]);
    }
}


void display_game() {
    if (levelUp == true) {
        ++levelCount;
        initializeAliens();
        levelUp = false;
    }
    //display level
    string startMessage = "Level: " + to_string(levelCount);
    glColor3f(1, 0, 0);
    glRasterPos2i(180 + 180, 50);
    for (int i = 0; i < startMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, startMessage[i]);
    }

    if (paused){
        //display level
        string pausedMessage = "Paused";
        glColor3f(1, 1, 1);
        glRasterPos2i((boardWidth/2) - 40, boardHeight/2);
        for (int i = 0; i < pausedMessage.length(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pausedMessage[i]);
        }
    }

    //blocks with playerbullets
    for (int i = 0; i < playerBullets.size(); ++i) {
        //block1
        if (block1.isOverlapping(playerBullets[i])) {
            if (playerBullets[i].getIsDrawn()) {
                block1.collide(playerBullets[i]);
                playerBullets[i].collide();
            }
        }
        //block2
        if (block2.isOverlapping(playerBullets[i])) {
            if (playerBullets[i].getIsDrawn()) {
                block2.collide(playerBullets[i]);
                playerBullets[i].collide();
            }
        }
        //block3
        if (block3.isOverlapping(playerBullets[i])) {
            if (playerBullets[i].getIsDrawn()) {
                block3.collide(playerBullets[i]);
                playerBullets[i].collide();
            }
        }
        //aliens with playerbullet collisions
        for (int j = 0; j < aliens.size(); ++j) {
            if (aliens[j].isOverlapping(playerBullets[i])) {
                if (playerBullets[i].getIsDrawn() && aliens[j].getIsDrawn()) {
                    explosions[i].set_position(aliens[j].getX(), aliens[j].getY() + 10);
                    explosions[i].orange2Red();
                    aliens[j].collide(playerBullets[i]);
                    playerBullets[i].collide();
                    player.incrementScore(10);
                }
            }
        }
    }




    //block with alienbullets
    for (int i = 0; i < alienBullets.size(); ++i) {
        //block1
        if (block1.isOverlapping(alienBullets[i])) {
            if (alienBullets[i].getIsDrawn()) {
                block1.collide(alienBullets[i]);
                alienBullets[i].collide();
            }
        }
        //block2
        if (block2.isOverlapping(alienBullets[i])) {
            if (alienBullets[i].getIsDrawn() && block2.getIsDrawn()) {
                block2.collide(alienBullets[i]);
                alienBullets[i].collide();
            }
        }
        //block3
        if (block3.isOverlapping(alienBullets[i])) {
            if (alienBullets[i].getIsDrawn() && block3.getIsDrawn()) {
                block3.collide(alienBullets[i]);
                alienBullets[i].collide();
            }
        }

        //player with alienbullet collisions
        if (player.isOverlapping(alienBullets[i])) {
            if (alienBullets[i].getIsDrawn() && player.getIsDrawn()) {
                if (alienBullets[i].getDirection() == Direction::left) {
                    player.collide(alienBullets[i]);
                    alienBullets[i].collide();
                }
            }
        }
    }





    //block draw
    if (block1.getIsDrawn()) {
        block1.draw();
    }
    if (block2.getIsDrawn()) {
        block2.draw();
    }
    if (block3.getIsDrawn()) {
        block3.draw();
    }

    //player draw
    if (player.getIsDrawn()) {
        player.draw();
    } else {
        screen = screen_type::end;
    }

    //player bullet draw
    for (int i = 0; i < playerBullets.size(); ++i) {
        if (playerBullets[i].getIsDrawn() == true) {
            playerBullets[i].draw();
        }
    }

    //alien bullet draw
    for (int i = 0; i < alienBullets.size(); ++i) {
        if (alienBullets[i].getIsDrawn() == true) {
            alienBullets[i].draw();
        }
    }

    //alien draw
    alienCount = 0;
    for (int i = 0; i < aliens.size(); ++i) {
        if (aliens[i].getIsDrawn()) {
            aliens[i].draw();
            ++alienCount;
        }
    }
    if (alienCount == 0) {
        levelUp = true;
    }


}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */

    // draw the stars
    for (int i = 0; i < star.size(); ++i) {
        star[i].draw();
    }





    switch(screen) {
        case start: display_start();
            break;
        case game: display_game();
            //drawing flames
            for (int i = 0; i < flames.size(); ++i) {
                flames[i].draw();
            }
            for (int i = 0; i < explosions.size(); ++i) {
                explosions[i].draw();
                explosions[i].set_position(-30,-30);

            }
            break;
        case score: display_score();
            break;
        case screen_type::end: display_end();
            break;
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        player.reportScore();
        glutDestroyWindow(wd);
         exit(0);
    }
    if (!paused) {
        if (key == 32) {
            //player
            player.shoot();
            if (playerBulletCount > 9) {
                playerBulletCount = 0;
            } else {
                ++playerBulletCount;
            }
            player.shoot();
            playerBullets[playerBulletCount] = player.getBullet();

        }
    }

    if (key == 'p'){
        paused = !paused;

    }
    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        if (!paused) {
            case GLUT_KEY_DOWN:
                player.move(0, 10);
            break;
            case GLUT_KEY_LEFT:
                break;
            case GLUT_KEY_RIGHT:
                break;
            case GLUT_KEY_UP:
                player.move(0, -10);
            break;
        }
    }
    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {

    if (screen == start && gameButton.isOverlapping(x,y)) {
        gameButton.setFill(purple);
    } else {
        gameButton.setFill(white);
    }

    if (screen == start && scoreButton.isOverlapping(x,y)) {
        scoreButton.setFill(purple);
    } else {
        scoreButton.setFill(white);
    }

    if (screen == score && backButton.isOverlapping(x,y)) {
        backButton.setFill(purple);
    } else {
        backButton.setFill(white);
    }

    if (screen == screen_type::end && quitButton.isOverlapping(x,y)) {
        quitButton.setFill(purple);
    } else {
        quitButton.setFill(white);
    }

    for (int i = 0; i < scoreSquares.size(); ++i) {
        if (screen == score && scoreSquares[i].isOverlapping(x,y)) {
            scoreSquares[i].setFill(purple);
        } else {
            scoreSquares[i].setFill(white);
        }
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == start && gameButton.isOverlapping(x,y)) {
        screen = game;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == start && scoreButton.isOverlapping(x,y)) {
        screen = score;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == score && backButton.isOverlapping(x,y)) {
        screen = start;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == screen_type::end && quitButton.isOverlapping(x,y)) {
        player.reportScore();
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void timer(int extra) {
    if (!paused) {
        //move aliens
        if (alienMoveCount < 100) {
            //move each alien down
            for (int i = 0; i < aliens.size(); ++i) {
                if (aliens[i].getIsDrawn()) {
                    aliens[i].move(0, 2);
                }
            }
            ++alienMoveCount;
            //glutPostRedisplay();
        } else if (alienMoveCount < 200) {
            //move each alien up
            for (int i = 0; i < aliens.size(); ++i) {
                if (aliens[i].getIsDrawn()) {
                    aliens[i].move(0, -2);
                }
            }
            ++alienMoveCount;
            //glutPostRedisplay();
        } else if (alienMoveCount >= 200) {
            alienMoveCount = 0;
        }

        //alien random shoot
        if (alienMoveCount == 50 || alienMoveCount == 125) {
            for (int i = 0; i < levelCount; ++i) {
            int randInt = rand() % aliens.size();
                if (aliens[randInt].getIsDrawn()) {
                    ++alienBulletCount;
                    if (alienBulletCount > 9) {
                        alienBulletCount = 0;
                    }
                    aliens[randInt].shoot();
                    alienBullets[alienBulletCount] = aliens[randInt].getBullet();
                }
            }
        }

        //move player bullets
        for (int i = 0; i < playerBullets.size(); ++i) {
            if (playerBullets[i].getIsDrawn() == true) {
                playerBullets[i].move(10, 0);
            }
        }

        //move alien bullets
        for (int i = 0; i < alienBullets.size(); ++i) {
            if (alienBullets[i].getIsDrawn() == true) {
                alienBullets[i].move(-10, 0);
            }
        }

        //stars
        for (int i = 0; i < star.size(); ++i) {
            star[i].move(star[i].get_radius() / -2, 0);
            // if the star went off the left side of the screen
            // move it to the right side at a random y location
            if (star[i].get_x() < 0) {
                star[i].set_position(500, rand() % (int) height);
            }
        }
        //flames
        for (int i = 0; i < flames.size(); ++i) {
            flames[i].move(flames[i].get_radius() / -2, 0);
            // if the star went off the left side of the screen
            // move it to the right side at a random y location
            if (flames[i].get_x() < 0) {
                flames[i].set_position(player.getX(), player.getY() + 25);
            }
        }
        //explosions
        for (int i = 0; i < explosions.size(); ++i) {
           explosions[i].move(rand() % 20 + (-10), 0);
        }


    }
        glutPostRedisplay();
        glutTimerFunc(30, timer, 0);
    }




/* Main function: GLUT runs as a console application starting at main()  */
int graphicsPlay(int argc, char** argv) {

    init();


    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("A Blast From The Past" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    InitGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

void initializeAliens() {
    /**
     * set values for Aliens
     */
    aliens.clear();
    aliens.resize(levelCount*5);
    alienMoveCount = 0;


    int heightInc;
    int widthInc;
    heightInc = 0;
    widthInc = 0;
    for (int i = 0; i < aliens.size(); ++i) {
        aliens[i].setIsDrawn(true);
        //set dimensions, fill, and blaster
        aliens[i].setWidth(20);
        aliens[i].setHeight(20);
//        aliens[i].setBullet(alienBullets[0]);

        //set position
        if (i == 0) {
            aliens[i].setPosition((boardWidth-20) - widthInc * 50, heightInc * 40 + 100);
            ++heightInc;
        } else {
            if (aliens[i - 1].getY() < boardHeight - 250) {
                aliens[i].setPosition((boardWidth-20) - widthInc * 50, heightInc * 40 + 100);
                ++heightInc;
            } else {
                heightInc = 0;
                ++widthInc;
                aliens[i].setPosition((boardWidth-20) - widthInc * 50, heightInc * 40 + 100);
                ++heightInc;
            }
        }
    }
}


Player customizePlayer() {
    // initialize variables
    Player player;
    string playerName;

    // get user input for name
    cout << "Please enter your name: " << endl;
    while (!(cin >> playerName))
    {
        cin.clear();
        string junk;
        cin >> junk;
        cout << "Invalid input. Please re-enter your name: ";
    }
    player.setName(playerName);

    cout << "Hello " << player.getName() << "! Enjoy the game!" << endl;

    return player;


}


void display_score() {
    // initialize variables
    string nameFromFile;
    int scoreFromFile;
    string scoreOutput;
    int lineCount = 0;
    string line;

    // open organized_high_scores.txt for read
    organizeScores();
    ifstream organizedHighScoresFile("organized_high_scores.txt");
    if (!organizedHighScoresFile) {
        cout << "File not found" << endl;
    } else {

        // get lineCount
        while (getline(organizedHighScoresFile, line)) {
            ++lineCount;
        }
        organizedHighScoresFile.clear();
        organizedHighScoresFile.seekg(0);

        // output top 10
        for (int i = 0; i < scoreSquares.size(); ++i) {
            scoreSquares[i].draw();
        }
        for (int i = 0; i < 10 && i < lineCount; ++i) {
            getline(organizedHighScoresFile, line);
            glColor3f(.3,.3,.3);
            glRasterPos2i(180, 50 + i * 40);
            for (int j = 0; j < line.length(); ++j) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, line[j]);
            }
        }
        organizedHighScoresFile.close();
    }

    //display back button
    backButton.draw();
    string backMessage = "Back";
    glColor3f(.3,.3,.3);
    glRasterPos2i(boardWidth/2 + 10, boardHeight - 30);
    for (int i = 0; i < backMessage.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, backMessage[i]);
    }

}


void organizeScores() {

    // initialize variables
    string nameFromFile;
    int scoreFromFile;
    multimap <int, string> scoreMap;
    int lineCount = 0;
    string line;

    // open file for read
    ifstream highScoreFile("high_score.txt");
    if (!highScoreFile) {
        cout << "File not found" << endl;
    } else {

        // get lineCount
        while (getline(highScoreFile, line)) {
            ++lineCount;
        }

        highScoreFile.clear();
        highScoreFile.seekg(0);

        // add the scores and names to the map
        for (int i = 0; i < lineCount; ++i) {
            highScoreFile >> nameFromFile >> scoreFromFile;
            scoreMap.insert(pair<int, string>(scoreFromFile, nameFromFile));
        }

        // create a new file with the ordered scores
        ofstream organizedHighScoresFile("organized_high_scores.txt", ios::out);
        if (organizedHighScoresFile) {
            multimap<int, string>::iterator it;
            it = --scoreMap.end();
            bool whileLoopBroken;
            while (!(it == scoreMap.begin())) {
                organizedHighScoresFile << it->second << "     \t"
                                        << it->first << endl;
                --it;
            }
            //do it one more time because while loop is whack
            organizedHighScoresFile << it->second << "     \t"
                                    << it->first << endl;
        }
        organizedHighScoresFile.close();
    }
}