#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#define C4 261
#define D4 294
#define E4 329
#define F4 349
#define G4 392
#define A4 440
#define B4 493

void play_note(int frequency, int duration) {
    Beep(frequency, duration);
}

int get_note_for_char(char c) {
    c = tolower(c);  

    switch (c) {
        case 'c': return C4; 
        case 'd': return D4; 
        case 'e': return E4; 
        case 'f': return F4; 
        case 'g': return G4; 
        case 'a': return A4; 
        case 'b': return B4; 
        
		default: return -1;   
    }
}

int main() {
    char input[100];  

    printf("------------------------- ~Piano Simulator~ -------------------------\n");
    printf("Enter a sequence of characters to play corresponding piano notes:[a-g]\n");
    printf("Press 'exit' to quit the program.\n");
	printf("----------------------------------------------------------------------\n");
    
    while (1) {
        printf("\nEnter input: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            printf("Exiting Piano Simulator.....\nThank you.....");
            break;
        }
        
		for (int i = 0; input[i] != '\0'; i++) {
            char c = input[i];
            int frequency = get_note_for_char(c);
            
            if (frequency != -1) {
                play_note(frequency, 500);  //in milliseconds
            }
        }
    }

    return 0;
}
