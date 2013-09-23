#include <stdio.h>
#include <string.h>

unsigned char ballots[1000][20];
unsigned char names[20][81];
long votes[20];
unsigned long validNames = 0;

void ProcessCase();

int main()
{
	char achBuf[1024];
	char* line;
	unsigned long cases = 0;

	line = gets(achBuf);
	sscanf(line, "%ul", &cases);

	// Empty line before each case, but only read it once since we'll
	// later use this as a case separator.
	gets(achBuf);

#ifdef DEBUG
	printf("Processing %d cases.\n", cases);
#endif
	while (cases--)
	{
		ProcessCase();
		if (cases)
		{
			printf("\n");
		}
	}
}

void ProcessCase()
{
	char achBuf[1024];
	char* line;
	unsigned long candidates = 0;
	unsigned long ballotCount = 0;

	// Read in the count of candidates
	line = gets(achBuf);
	sscanf(line, "%ul", &candidates);

#ifdef DEBUG
	printf("Processing %d candidates.\n", candidates);
#endif

	// Read in the candidates themselves.
	validNames = 0;
	while(candidates--)
	{
		line = gets(achBuf);
		strcpy(names[validNames++], line);

#ifdef DEBUG
		printf("Reading in candidate %s.\n", names[validNames-1]);
#endif
	}

	// Read in the ballots
	line = gets(achBuf);
	while (line != NULL && line[0] != '\0')
	{
		char seps[] = " ";
		unsigned long choice = 0;
		char* tok = strtok(line, seps);
		while (tok != NULL)
		{
			ballots[ballotCount][choice++] = atoi(tok) - 1;
			tok = strtok(NULL, seps);
		}
		ballotCount++;
		line = gets(achBuf);
	}

#ifdef DEBUG
	printf("Read in %d ballots.\n", ballotCount);
#endif

	// Our basic structures for knowing valid candidates will be a bitmask of their ordinal.
	// As each candidate is removed from the race we'll modify the bitmask.
	{
		unsigned long validCandidateMask = (1 << validNames) - 1;

		// Process the ballots
		while (1)
		{
			unsigned long currentBallot = 0;
			unsigned long currentCandidate = 0;

			long maxVotes = -1;
			long maxVotesCandidate = -1;
			long maxVotesTie = -1;

			unsigned long minVotes = (unsigned long)-1;
			long minVotesCandidate = -1;

			// First count the ballots
			memset(votes, 0, sizeof(votes));
			for (;currentBallot < ballotCount; currentBallot++)
			{
				votes[ballots[currentBallot][0]]++;
			}

			// Second find the max of the current ballot takers.
			for (currentCandidate = 0; currentCandidate < validNames; currentCandidate++)
			{
				if (votes[currentCandidate] > maxVotes)
				{
					maxVotesCandidate = currentCandidate;
					maxVotes = votes[currentCandidate];
				}
			}
#ifdef DEBUG
			printf("Found max vote candidate %d.\n", maxVotesCandidate);
#endif

			// Third find a tie of the max.
			for (currentCandidate = 0; currentCandidate < validNames; currentCandidate++)
			{
				if (votes[currentCandidate] == maxVotes && currentCandidate != maxVotesCandidate)
				{
					maxVotesTie = currentCandidate;
					break;
				}
			}

			// If there was no tie then we can output the winner now
			if (maxVotesTie == -1)
			{
				printf("%s\n", names[maxVotesCandidate]);
				return;
			}
			else
			{
#ifdef DEBUG
				printf("Found max vote tie candidate %d.\n", maxVotesTie);
#endif
			}

			// 4. If there was a tie then find someone to eliminate
			for (currentCandidate = 0; currentCandidate < validNames; currentCandidate++)
			{
				if (validCandidateMask & (1 << currentCandidate))
				{
					if (votes[currentCandidate] < maxVotes && votes[currentCandidate] < minVotes)
					{
						minVotesCandidate = currentCandidate;
						minVotes = votes[currentCandidate];
					}
				}
			}

			// We must be tied print all winners
			if (minVotesCandidate == -1)
			{
				unsigned long currentName = 0;
#ifdef DEBUG
				printf("Full tie print all winners %x.\n", validCandidateMask);
#endif
				while (validCandidateMask > 0)
				{
					if (validCandidateMask & 1)
					{
						printf("%s\n", names[currentName]);
					}
					currentName++;
					validCandidateMask >>= 1;
				}
				return;
			}
			else
			{
				for (currentCandidate = 0; currentCandidate < validNames; currentCandidate++)
				{
					if (validCandidateMask & (1 << currentCandidate))
					{
						if (minVotes == votes[currentCandidate])
						{
							minVotesCandidate = currentCandidate;
#ifdef DEBUG
							printf("Eliminating candidate %d.\n", minVotesCandidate);
#endif
							// Mask out the loser
							validCandidateMask &= ~(1 << minVotesCandidate);

							// Eliminate the loser
							for (currentBallot = 0;currentBallot < ballotCount; currentBallot++)
							{
								if (ballots[currentBallot][0] == minVotesCandidate)
								{
									unsigned long nextOffset = 1;
									long nextCandidate = -1;
									// while (ballots[currentBallot][nextOffset] == minVotesCandidate)
									while (!(1 << ballots[currentBallot][nextOffset] & validCandidateMask))
									{
										nextOffset++;
									}

									// Smear all the way to the left erasing the previous candidate
									nextCandidate = ballots[currentBallot][nextOffset];
									while (nextOffset--)
									{
										ballots[currentBallot][nextOffset] = nextCandidate;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}