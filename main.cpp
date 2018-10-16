//
// Created by Tripp Gordon on 11/7/17.
//


#include <vector>
#include <map>

#include "LaserBullet.h"
#include "Player.h"
#include "Alien.h"
#include "graphics.h"

/*
 * Requires: Nothing
 * Modifies: Nothing
 * Effects: Global function to save and retrieve scores based on username input.
 *          Then asks user to start a new game. Returns true if they do.
 */
bool openingScreen();

/*
 * Requires: Nothing
 * Modifies: Nothing
 * Effects: Global function to display high scores.
 */
void displayHighScores();

/*
 * Requires: Nothing
 * Modifies: Nothing
 * Effects: Global function to allow user to search for a previous score by username.
 */
void displaySearchedScore();



/*
 * Function to hold all testing outside of main()
 */
void testing();


int main(int argc, char** argv) {

        graphicsPlay(argc, argv);

    return 0;
}

bool openingScreen() {
    // initialize variables
    char yesOrNo;
    string nameFromUserInput;
    string nameFromFile;

    // display the three highest scores
    cout << "Would you like to see the first 3 scores? (Y/N)" << endl;
    cin >> yesOrNo;
    if (yesOrNo == 'Y' or yesOrNo == 'y') {
        displayHighScores();
    }

    // display a score
    cout << "Would you like to search for a score? (Y/N)" << endl;
    cin >> yesOrNo;
    if (yesOrNo == 'Y' or yesOrNo == 'y') {
        displaySearchedScore();
    }

    //
    cout << "Would you like to play a new game? (Y/N)" << endl;
    cin >> yesOrNo;
    if (yesOrNo == 'Y' or yesOrNo == 'y') {
        return true;
    } else {
        return false;
    }

}

void displayHighScores() {

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
        organizedHighScoresFile.seekg( 0 );

        // concatinate the top 3 scores into a string called scoreOutput
        for (int i = 0; i < 3 && i < lineCount; ++i) {
            organizedHighScoresFile >> nameFromFile >> scoreFromFile;
            scoreOutput += nameFromFile + '\t' + to_string(scoreFromFile) + '\n';

        }
        organizedHighScoresFile.close();

        // display the scores
        if (lineCount >= 3) {
            cout << scoreOutput;
        } else if (lineCount > 0) {
            cout << "There are less than three scores, but here they are: "
                 << endl << scoreOutput << endl;
        } else {
            cout << "There are no scores saved." << endl;
        }
    }
}

void displaySearchedScore() {

    // initialize variables
    string nameFromUserInput;
    string nameFromFile;
    int scoreFromFile;
    string line;
    int lineCount = 0;

    // get name from user
    cout << "Please enter the player name who's score you want." << endl;
    while (!(cin >> nameFromUserInput)) {
        cin.clear();
        string junk;
        cin >> junk;
        cout << "Invalid input. Please re-enter the name: ";
    }

    // open file
    ifstream highScoreFile("high_score.txt");
    if (!highScoreFile) {
        cout << "File not found. " << endl;
    } else {

        // get lineCount
        while (getline(highScoreFile, line)) {
            ++lineCount;
        }
        highScoreFile.clear();
        highScoreFile.seekg( 0 );

        // search file and output results to user
        bool found = false;
        string userOutput = nameFromUserInput + "'s past scores: \n";
        for (int i = 0; i < lineCount; ++i) {
            highScoreFile >> nameFromFile >> scoreFromFile;
            if (nameFromFile == nameFromUserInput) {
                userOutput += nameFromFile + "     \t" + to_string(scoreFromFile) + "\n";
                found = true;
            }
        }
        if (found == false) {
            cout << "Player not found." << endl;
        } else {
            cout << userOutput;
        }
        highScoreFile.close();
    }
}



void testing() {
//    Position position;
//    position.xCoord = 1;
//    position.yCoord = 1;
//
//    /*
//     * Testing all LaserBullet constructors and methods
//     */
//
//    LaserBullet bullet;
//    cout << "Expecting 0000000:\n"
//         << bullet.getPosition().xCoord
//         << bullet.getPosition().yCoord << bullet.getX() << bullet.getY()
//         << endl << endl;
//
//    LaserBullet bullet2;
//    cout << "Expecting 1100000:\n"
//         << bullet.getPosition().xCoord
//         << bullet.getPosition().yCoord << bullet.getX() << bullet.getY() << endl << endl;
//
//    LaserBullet bullet3(position);
//    cout << "Expecting 1101111:\n"
//          << bullet3.getPosition().xCoord
//         << bullet3.getPosition().yCoord << bullet3.getX() << bullet3.getY() << endl << endl;
//
//    //bullet.setFill(yellow);
//    bullet.setPosition(position);
//    cout << "Expecting 1101111:\n"
//         << bullet.getPosition().xCoord
//         << bullet.getPosition().yCoord << bullet.getX() << bullet.getY()
//         << endl << endl;
//
//  //  bullet.setFill(1,1,1);
//    bullet.setPosition(2,2);
//    cout << "Expecting 1112222:\n"
//         << bullet.getPosition().xCoord
//         << bullet.getPosition().yCoord << bullet.getX() << bullet.getY()
//         << endl << endl;
//
//    bullet.move(2,2);
//    cout << "Expecting 1114444:\n"
//         << bullet.getPosition().xCoord
//         << bullet.getPosition().yCoord << bullet.getX() << bullet.getY()
//         << endl << endl;
//
//    /*
//     * Testing all blaster methods
//     */
////    Blaster blaster;
////    cout << "Expecting 0000:\n" << blaster.getFiringRate()
////         << blaster.getFiringSpeed() << blaster.getDirection()
////         << blaster.getBullet().getX()
////         << endl << endl;
////
////    blaster.setFiringRate(9);
////    blaster.setFiringSpeed(8);
////    blaster.setDirection(Direction::left);
////    blaster.setBullet(bullet3);
////    cout << "Expecting 9821:\n" << blaster.getFiringRate()
////         << blaster.getFiringSpeed() << blaster.getDirection()
////         << blaster.getBullet().getX()
////         << endl << endl;
////
////    Blaster blaster2(2,3,Direction::right,bullet);
////    cout << "Expecting 2334:\n" << blaster2.getFiringRate()
////         << blaster2.getFiringSpeed() << blaster2.getDirection()
////         << blaster2.getBullet().getX()
////         << endl << endl;
//
//
//    /*
//     * Testing all Player constructors and methods
//     */
//
//    Player player;
//    cout << "Expecting Unknown0010000000:\n" << player.getName() << player.getScore()
//         << player.getBlaster().getFiringSpeed() << player.getHealthPoints()
//
//         << player.getPosition().xCoord
//         << player.getPosition().yCoord << player.getX() << player.getY()
//         << endl << endl;
//
//    player.setName("Tripp");
//    player.setScore(3);
//    player.setBlaster(blaster);
//    player.setHealthPoints(6);
//
//    player.setPosition(position);
//    cout << "Expecting Tripp3861101111:\n" << player.getName() << player.getScore()
//         << player.getBlaster().getFiringSpeed() << player.getHealthPoints()
//
//         << player.getPosition().xCoord
//         << player.getPosition().yCoord << player.getX() << player.getY()
//         << endl << endl;
//
//
//    player.setPosition(5,5);
//    cout << "Expecting Tripp3861115555:\n" << player.getName() << player.getScore()
//         << player.getBlaster().getFiringSpeed() << player.getHealthPoints()
//         << player.getPosition().xCoord
//         << player.getPosition().yCoord << player.getX() << player.getY()
//         << endl << endl;
//
//    Player player2(position,blaster,3,"Corso");
//    player2.incrementScore(2);
//    cout << "Expecting Corso2831011111:\n" << player2.getName() << player2.getScore()
//         << player2.getBlaster().getFiringSpeed() << player2.getHealthPoints()
//         << player2.getPosition().xCoord
//         << player2.getPosition().yCoord << player2.getX() << player2.getY()
//         << endl << endl;
//
//    /*
//     * Testing all Alien constructors and methods
//     */
//
//    Alien alien;
//    cout << "Expecting 010000000:\n"
//         << alien.getBlaster().getFiringSpeed() << alien.getHealthPoints()
//         << alien.getPosition().xCoord
//         << alien.getPosition().yCoord << alien.getX() << alien.getY()
//         << endl << endl;
//
//    alien.setBlaster(blaster);
//    alien.setHealthPoints(6);
//   // alien.setFill(yellow);
//    alien.setPosition(position);
//    cout << "Expecting 861101111:\n"
//         << alien.getBlaster().getFiringSpeed() << alien.getHealthPoints()
//         << alien.getPosition().xCoord
//         << alien.getPosition().yCoord << alien.getX() << alien.getY()
//         << endl << endl;
//
//  //  alien.setFill(1,1,1);
//    alien.setPosition(5,5);
//    cout << "Expecting 861115555:\n"
//         << alien.getBlaster().getFiringSpeed() << alien.getHealthPoints()
//         << alien.getPosition().xCoord
//         << alien.getPosition().yCoord << alien.getX() << alien.getY()
//         << endl << endl;
//
//    Alien alien2(position,blaster,3);
//    cout << "Expecting 831011111:\n"
//         << alien2.getBlaster().getFiringSpeed() << alien2.getHealthPoints()
//         << alien2.getPosition().xCoord
//         << alien2.getPosition().yCoord << alien2.getX() << alien2.getY()
//         << endl << endl;
//
//    /*
//     * Score output testing
//     */
//
//    // report 7 players with random scores
//    vector<string> randomNames = {"tripp", "corso", "will", "bob", "joe", "john", "bill"};
//    srand(time(0));
//    for (int i = 0; i < 7; ++i) {
//        player.setScore(rand() %10);
//        player.setName(randomNames[i]);
//        player.reportScore();
//    }
}