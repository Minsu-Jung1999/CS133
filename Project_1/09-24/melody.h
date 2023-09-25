// Write your Melody header code here

#define MELODY_H
#include <iostream>
#include <queue>
#include <stack>
#include "Note.h"
using namespace std;

class Melody
{
private:
    // Pointer to a queue of Notes.
    queue<Note>* songQueue;
    double originalTotalDuration;
public:
    // Initializes the melody to store the passed in pointer to a queue of Notes.
    // It throws a string exception if the queue is null.
    Melody(queue<Note>* song);

    // Returns the total length of the song in seconds.
    // If the song includes a repeated section the length should include that repeated section twice.
    double getTotalDuration();

    // Changes the tempo of each note to be tempo percent of what it formerly was.
    // Passing a tempo of 1.0 will make the tempo stay the same. tempo of 2.0 will make each note twice as long.
    void changeTempo(double tempo);

    // Reverses the order of notes in the song,
    // so that future calls to the play member function will play the notes in the opposite of the order they were in before reverse was called.
    void reverse();

    // Adds all notes from the given other song to the end of this song.
    void append(Melody& other);

    // Plays the song by calling each note's play member function.
    // The notes should be played from the beginning of the queue ...
    // to the end unless there are notes that are marked as being the beginning or end of a repeated section.
    // When the first note that is a beginning or end of a repeated section is found it creates a second queue.
    // It should then get notes from the original queue until it sees another marked as being the beginning or end of a repeat.
    // As it gets these notes it should play them and then place them back in both queues.
    // Once it hits a second marked as beginning or end of a repeat it should play everything in your secondary queue and ...
    // then return to playing from the main queue.
    //  It is possible to call this member function multiple times and get the same result.
    void play();

    // Outputs information about each note to the passed in stream.
    // Each note should be on its own line and output using its << operator.
    // An example file is displayed on page 1.
    // A << reflects the changes that have been made to the song by calling other member functions.
    friend ostream& operator<< (ostream& out, Melody& song);
};


