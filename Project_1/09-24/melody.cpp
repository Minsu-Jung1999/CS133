#include <iostream>
#include "Note.h"
#include "gthread.h"
#include "melody.h"

using namespace std;

Melody::Melody(queue<Note>* song)
{
    // Check if the provided pointer is null
    if (song == nullptr) {
        throw std::invalid_argument("The song pointer is null.");
    }

    // Initialize the Melody with the provided queue of Notes
    songQueue = song;
    originalTotalDuration = getTotalDuration();
}

double Melody::getTotalDuration()
{
    return originalTotalDuration;
}

void Melody::changeTempo(double tempo)
{
    if (tempo < 0.0) {
        throw std::invalid_argument("Tempo cannot be negative.");
    }

    // Adjust the tempo of each note in the song
    while (!songQueue->empty()) {
        Note& note = songQueue->front();
        double newDuration = note.getDuration() * tempo;
        note.setDuration(newDuration);
        songQueue->pop();
        songQueue->push(note);
    }

    originalTotalDuration = getTotalDuration(); // Update total duration
}

void Melody::reverse()
{
    // Reverse the order of notes in the song
    std::stack<Note> tempStack;
    while (!songQueue->empty()) {
        tempStack.push(songQueue->front());
        songQueue->pop();
    }
    while (!tempStack.empty()) {
        songQueue->push(tempStack.top());
        tempStack.pop();
    }
}

void Melody::append(Melody& other)
{
    // Add all notes from the given other song to the end of this song
    while (!other.songQueue->empty()) {
        songQueue->push(other.songQueue->front());
        other.songQueue->pop();
    }
    originalTotalDuration = getTotalDuration(); // Update total duration
}

void Melody::play()
{
    queue<Note> repeateQueue;
    int qsize = songQueue->size();
    bool repeateStart = false;
    bool repeateEnd = false;
    while(qsize>=0)
    {
        Note note = songQueue->front();
        songQueue->pop();
        songQueue->push(note);
        if(note.isRepeat())
        {
            if(repeateStart)
            {
                repeateEnd = true;
                repeateStart = false;
            }
            repeateStart = true;
        }
        if(repeateStart)
        {
            repeateQueue.push(note);
        }
        if(repeateEnd)
        {
            repeateEnd = false;
            while(!repeateQueue.empty())
            {
                Note note = repeateQueue.front();
                repeateQueue.pop();
                note.play();
            }
        }
        note.play();
        qsize--;
    }
}

ostream& operator<< (ostream& out, Melody& song) {
    // Output information about each note to the stream
    // Reflect changes made to the song
    while (!song.songQueue->empty()) {
        out << song.songQueue->front() << std::endl;
        song.songQueue->pop();
    }
    return out;
}
