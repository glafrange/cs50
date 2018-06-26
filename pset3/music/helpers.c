// Helper functions for music

#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // separate the string fraction into it's numerator and denominator as ints
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';

    while (denominator != 8)
    {
        // multiply the entire fraction by 2 until it represents eighth notes
        if (denominator < 8)
        {
            denominator = denominator * 2;
            numerator *= 2;
        }
    }
    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // An array of musical notes with only sharps
    string NOTES_SHARP[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    // An array of musical notes with only flats
    string NOTES_FLAT[] = {"C", "Db", "D", "Eb", "E", "F",
                           "Gb", "G", "Ab", "A", "Bb", "B"
                          };
    float f;
    // If the 2nd index of note is the end of the string it is a natural note
    bool isAccidental = note[2] != '\0' ? true : false;
    // create a new string with just the note name, using isAccidental to decide the 1 index
    char noteName[] = {note[0], isAccidental == true ? note[1] : '\0', '\0'};
    int octave = isAccidental == true ? note[2] - '0' : note[1] - '0';
    // distance needs to be a float to do the math required in finding the frequency
    float distance;
    for (int i = 0; i < 12; i++)
    {
        // each array of notes has an enharmonic note at every index
        if (strcmp(noteName, NOTES_SHARP[i]) == 0 || strcmp(noteName, NOTES_FLAT[i]) == 0)
        {
            // finding distance by adding the distance from the octave 4 multiplied by 12(1 for each note) and the distance of i(current note) from 9(A in the array)
            distance = (octave - 4) * 12 + (i - 9);
        }
    }
    f = round(pow(2, distance / 12) * 440);
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
