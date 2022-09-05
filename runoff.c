#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }


    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }




    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) //vote (i, j, name)
{
    //if ranked name that voter gives = one of candidate options, then set preferences[voter][rank], with the rank being the index
    //of the candidate voted for in candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //For each voter (preferences[voter][0]), if name matches one in candidate struct
    //**Only update votes for candidates in race (use eliminate bool)
    //**For candidates not in race look at second preference, or third
    for (int i = 0; i < voter_count; i++)
    {
        //If a candidate isn't eliminated, get voter's first preference counted towards candidates vote
        if (candidates[preferences[i][0]].eliminated == false)
        {
            candidates[preferences[i][0]].votes++;
        }

        //get highest preference possible for a candidate still in the running
        else if (candidates[preferences[i][0]].eliminated == true)
        {
            //Look at index of second preference, and if that candidate still in the running, add 1 to this candidates vote total
            //check to see if each candidate is eliminated, i
            for (int j = 1; j < candidate_count; j++)
            {
                if (candidates[preferences[i][j]].eliminated == false)
                {
                    candidates[preferences[i][j]].votes++;
                    break;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //if a candidate has more than half the votes, declare winner, else return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minNum = voter_count;
    //find the candidate with the least number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < minNum && candidates[i].eliminated == false)
        {
            minNum = candidates[i].votes;
        }
    }
    //printf("min:%i",minNum);
    return minNum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int counter = 0;
    int elimCounter = 0;
    //see if all candidates have the same number of MIN votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            counter++;
        }

        //keep track eliminated candidates
        else if (candidates[i].eliminated == true)
        {
            elimCounter++;
        }
    }

    if (counter == (candidate_count - elimCounter))
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //set candidates[].eliminated == true if has min votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}