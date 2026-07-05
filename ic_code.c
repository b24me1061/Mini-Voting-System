#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int voters;
    printf("Enter Total Voters: ");
    scanf("%d", &voters);

    char **userId = (char**)malloc(voters * sizeof(char*));
    for (int i = 0; i < voters; i++) {
        userId[i] = (char*)malloc(15 * sizeof(char)); 
        sprintf(userId[i], "User%d", i + 1);
    }

    int no_of_party;
    printf("Number of Parties: ");
    scanf("%d", &no_of_party);

    char **Party_Name = (char**)malloc(no_of_party * sizeof(char*));
    for (int i = 0; i < no_of_party; i++) {
        Party_Name[i] = (char*)malloc(20 * sizeof(char)); 
        printf("Party name %d: ", i + 1);
        scanf("%s", Party_Name[i]);
    }
    
    int *total_vote = (int*)calloc(no_of_party, sizeof(int));

    int *has_voted = (int*)calloc(voters, sizeof(int));

    FILE *file=fopen("record.txt","a");
    if(file==NULL) {
        printf("Error while opening file \n");
        return 1;
    }
    int total_votes_cast = 0;
    while (total_votes_cast < voters) {
        char user_vote_id[15];
        char party_name[20];
        
        printf("Enter User ID to vote (e.g., User1, User2, ...): ");
        scanf("%s", user_vote_id);

        int user_index = -1;
        for (int i = 0; i < voters; i++) {
            if (strcmp(user_vote_id, userId[i]) == 0) {
                user_index = i;
                break;
            }
        }

        if (user_index == -1) {
            printf("Invalid User ID. Please try again.\n");
            continue;
        }

        if (has_voted[user_index] == 1) {
            printf("This user has already voted. Please choose another user.\n");
            continue;
        }

        printf("%s, enter the party name you want to vote for: ", user_vote_id);
        scanf("%s", party_name);

        int found = 0;
        for (int j = 0; j < no_of_party; j++) {
            if (strcmp(party_name, Party_Name[j]) == 0) {
                total_vote[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid party name entered. Please try again.\n");
            continue;
        }
        
        fprintf(file,"User: %s , Party whom voted : %s \n",user_vote_id,party_name);

        has_voted[user_index] = 1;
        total_votes_cast++;

        printf("%s has successfully voted for party %s.\n\n", user_vote_id, party_name);
    }

    printf("\nVote Results:\n");
    for (int j = 0; j < no_of_party; j++) {
        printf("Total votes for Party %s: %d\n", Party_Name[j], total_vote[j]);
    }

    int max = total_vote[0];
    int winner_index = 0;
    for (int j = 1; j < no_of_party; j++) {
        if (total_vote[j] > max) {
            max = total_vote[j];
            winner_index = j;
        }
    }

    printf("\nCongrats! The winning party is %s with %d votes.\n", Party_Name[winner_index], max);

    for (int i = 0; i < voters; i++) {
        free(userId[i]);
    }
    free(userId);

    for (int i = 0; i < no_of_party; i++) {
        free(Party_Name[i]);
    }
    free(Party_Name);
    free(total_vote);
    free(has_voted);
    fclose(file);
    return 0;
}
