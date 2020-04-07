/* The aim of the project is to create a program that emulates
a simplified algorithm for searching contacts entered using
a sequence of digits. The program input is a sequence of digits.
The output of the program will contain a list of contacts
that match the specified numeric filter.


$ ./proj1 <contacts.txt
petr dvorak, 603123456
jana novotna, 777987654
bedrich smetana ml., 541141120

$ ./proj1 12 <contacts.txt
petr dvorak, 603123456
bedrich smetana ml., 541141120

$ ./proj1 686 <seznam.txt
jana nOVOtna, 777987654
(OVO only for demonstration)

*/

/******************************************************/
/* * *                  Project #1                * * */
/* * *                                            * * */
/* * *                   Version: 1               * * */
/* * *                                            * * */
/* * *          Maksimov Danil (xmaksi01)         * * */
/* * *                 October 2019               * * */
/******************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100 // task condition for string size
#define MAX_TEMPLATES_COUNT 10000 // max number of combinations for name searching
#define STR_SIZE 20  // max string size for searching

typedef struct contact{
  char name[SIZE];
  char number[SIZE];
  int number_mathes;
  int name_mathes;
} list;


// Knuth–Morris–Pratt algorithm for searching matches

int check_KMP(char obr[], char str[]){
  int pi[strlen(obr)];
  pi[0]=0;

      int l = strlen(obr);

      for (l=1; obr[l]; l++) {
         int j = pi[l-1];
         while ((j > 0) && (obr[l] != obr[j]))
             j = pi[j-1];
         if (obr[l] == obr[j])
             j++;
         pi[l] = j;
      }
      int j=0;

      for (int k=0; str[k]; k++) {
        while ((j > 0) && (str[k] != obr[j]))

            j = pi[j-1];

        if (str[k] == obr[j])
            j++;
        if (j==l){
          return l;
        }

     }
     return 0;
}

// function generate keybord like in smartphones and then
// generate all avalible combinations of letters
void generate_templates(char *template, char *str, int index, char templates[MAX_TEMPLATES_COUNT][STR_SIZE], int *size) {
	if (!strlen(template)) {
		strcpy(templates[*size], str);
		*size = *size + 1;

		return;
	}

	int buttons[26] = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9 };

	int button = template[0] - '0';

	for (int i = 0; i < 26; i++) {
		if (buttons[i] == button) {
			str[index] = 'a' + i;
			generate_templates(template + 1, str, index + 1, templates, size);
		}
	}
}
//  function checks name and pass varible to KMP algorithm
int check_name(int i, char *argv[], list contact[]){

    char *template = argv[1];
    char templates[MAX_TEMPLATES_COUNT][STR_SIZE];
    char str[STR_SIZE];
    int size = 0; // qty of combinations

    generate_templates(template, str, 0, templates, &size);


    for(int k = 0; k < size; k++){
      contact[i].name_mathes = check_KMP(templates[k], contact[i].name);
        if(contact[i].name_mathes > 0)
          break;
    }

return 0;
}

// case-insensitive based on ASCII table
void lower_register(int counter_for_name, list contact[]){
          for(int i = 0; i < counter_for_name; i++){
                for(int k = 0; k < SIZE; k++){
                    if(contact[i].name[k] < '[' && contact[i].name[k] > '@')
            contact[i].name[k] = contact[i].name[k] + ' ';
                }
          }
}

int input_check(char argv[]){
  int l = strlen(argv);
  for(int i = 0; i < l; i++){
    if(argv[i] > '9' || argv[i] < '1'){
      printf("INCORRECT INPUT\n");
      return 1;
    }
  }
  return 0;
}


void printf_result(char *argv[], list contact[], int counter_for_name, int counter_for_number){

  int not_found_trigger = 0;

   for(int i = 0; i < counter_for_number; i++){
   contact[i].number_mathes = check_KMP(argv[1], contact[i].number);
   }

   for(int i = 0; i < counter_for_name; i++){
     check_name(i,argv,contact);
   }

      for(int i = 0; i < counter_for_name; i++){

       if((contact[i].name_mathes == contact[i].number_mathes) && contact[i].number_mathes > 0 && contact[i].name_mathes > 0 )
           contact[i].number_mathes++; // priority by number with the same number of matches

       if(contact[i].number_mathes > contact[i].name_mathes)
         printf("%s, %s\n", contact[i].name, contact[i].number);

       else if(contact[i].name_mathes > contact[i].number_mathes)
         printf("%s, %s\n", contact[i].name, contact[i].number);

       else if(contact[i].number_mathes == 0 && contact[i].name_mathes == 0)
         not_found_trigger++;

     }

     if (not_found_trigger == counter_for_name){
       printf("Not found\n");
     }
}

int main(int argc, char* argv[]){

  list contact[42]; // "The program must support at least 42 contacts."

  char buffer[SIZE];
  int i = 0;
  int counter_for_name = 0;
  int counter_for_number = 0;

  while(fgets(buffer, SIZE, stdin) != NULL){
    i++;
      for(int j = 0; j < SIZE; j++)
        if(buffer[j] == '\n' || (buffer[j] == ' ' && buffer[j+1] == ' '))
          buffer[j] ='\0';

// even iterations of cycle => even string => even line => number of contact
      if(i%2 == 0){
        strncpy(contact[counter_for_number].number, buffer, SIZE);
        counter_for_number++;
      }
// odd iterations of cycle => name of contact
      else{

        strncpy(contact[counter_for_name].name,buffer,SIZE);
        counter_for_name++;
      }
  }
// calling case-insensitive function
  lower_register(counter_for_name, contact);


    if(argc == 1){
      for(int i = 0; i < counter_for_name; i++){
        printf("%s, %s\n", contact[i].name, contact[i].number);
      }
    }

    else if(argc ==2){
        int check = input_check(argv[1]); // checking the string for the contents of numbers

        if(check == 1)
          return 0;
        else
          printf_result(argv, contact, counter_for_name, counter_for_number);

    }

    else if(argc > 2){
      printf("Incorrect input\n");
    }



  return 0;
}
