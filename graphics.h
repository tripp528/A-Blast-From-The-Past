//
// Created by William Soccorsi on 11/29/17.
//

#ifndef A_BLAST_FROM_THE_PAST_GRAPHICS_H
#define A_BLAST_FROM_THE_PAST_GRAPHICS_H

#ifndef graphics_h
#define graphics_h

#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif


// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
    void init();

// Initialize OpenGL Graphics
    void InitGL(void);

// Callback functions for GLUT */

// Draw the window - this is where all the GL actions are
    void display(void);

// Trap and process alphanumeric keyboard events
    void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
    void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events
    void cursor(int x, int y);

// Calls itself after a specified time
    void timer(int extra);

// Handle mouse button pressed and released events
    void mouse(int button, int state, int x, int y);

    int graphicsPlay(int argc, char *argv[]);


void display_score();

/*
 * Requires: Nothing
 * Modiefies: Nothing
 * Effects: Create a new file with the names and scores
 *          (in order of score from largest to smallest)
 */
void organizeScores();


#endif /* graphics_h */




#endif //A_BLAST_FROM_THE_PAST_GRAPHICS_H
