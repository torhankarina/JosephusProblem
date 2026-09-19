//***************************************************************************
//
// Karina Torhan
// Z2111032
// CSCI 340 -OPE1 20268
// Assignment 04 The Josephus Problem
// Due Date: 9/22/26, 5:00 PM
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************
#include "josephus.h"
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>

// print the underlined message heading for the list
void print_underlined_string(const std::string &message)
{
    std::cout << message << std::endl;
    std::cout << std::string(message.length(), '-') << std::endl;
}

// print the collection of remaining people in formatted columns
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols)
{
    if (eliminations == 0)
    {
        print_underlined_string("Initial group of people");
    }
    else
    {
        std::ostringstream oss;
        oss << "After eliminating " << eliminations << " people";
        print_underlined_string(oss.str());
    }

    int count = 0;
    for (auto it = collection.begin(); it != collection.end(); ++it)
    {
        std::cout << *it;
        ++count;

        if (count == num_cols)
        {
            std::cout << std::endl;
            count = 0;
        }
        else if (std::next(it) != collection.end())
        {
            std::cout << ", ";
        }
    }
    if (count != 0)
    {
        std::cout << std::endl;
    }
    // only print a trailing newline if this is NOT the final survivor print
    if (collection.size() > 1)
    {
        std::cout << std::endl;
    }
}

/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of prople with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line

    // generate the initial list of people using the generator class
    std::list<std::string> people;
    std::generate_n(std::back_inserter(people), num_people, SEQ(num_people));

    // print the starting group
    print_list(people, 0, num_cols);

    auto it = people.begin();
    unsigned eliminations = 0;

    // loop and eliminate people until only one remains
    while (people.size() > 1)
    {
        // advance the iterator by the modulus count
        for (unsigned count = 1; count < modulus; ++count)
        {
            ++it;
            if (it == people.end())
            {
                it = people.begin();
            }
        }

        // erase the chosen person and update iterator to the next valid position
        it = people.erase(it);
        if (it == people.end())
        {
            it = people.begin();
        }

        ++eliminations;

        // print state check based on frequency
        if (eliminations % print_frequency == 0)
        {
            print_list(people, eliminations, num_cols);
        }
    }

    // print the final surviving survivor
    std::cout << "Eliminations Completed" << std::endl;
    print_list(people, eliminations, num_cols);

  return 0;
}