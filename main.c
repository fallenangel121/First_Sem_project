#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int text_count = 0;

int tab_count = 0;
int space_after_count = 0;
int space_before_count = 0;
int capital_letter_count = 0;
int special_symbol_count = 0;
int multiple_spaces_count = 0;

int entire_tab_count = 0;
int entire_space_after_count = 0;
int entire_space_before_count = 0;
int entire_capital_letter_count = 0;
int entire_special_symbol_count = 0;
int entire_multiple_spaces_count = 0;

char* AddTab(char* text) { // sled vseki abzac izrechenieto zapochva s 1 tabulaciq navutre

	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char)); //*
	int i;

	for (i = 0; i < strlen(text); i++) {

		if (i == 0 || text[i] == '\n') {
			strncat(tmpText, "\t", 1);
			entire_tab_count++;
		}
		strncat(tmpText, &text[i], 1);
	}
	return tmpText;
}

char* AddSpaceAfter(char* text) {  //sled vseki prepinatelen znak funkciqta dobavq po 1 shpaciq

	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char));
	int i;

	for (i = 0; i < strlen(text); i++) {

		if (text[i] == '.' || text[i] == '?' || text[i] == ',' || text[i] == '!' || text[i] == ';' || text[i] == ':' || text[i] == '"') {

			strncat(tmpText, &text[i], 1);
			strncat(tmpText, " ", 1);

			entire_space_after_count++;

		}
		else {
			strncat(tmpText, &text[i], 1);
		}
	}
	return tmpText;
}

char* AddSpaceBefore(char* text) {    // funkciqta dobavq shpaciq predi lqvata skoba
	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char));
	int i;

	for (i = 0; i < strlen(text); i++) {
		if (text[i] == '(')
		{
			strncat(tmpText, " (", 2);
			entire_space_before_count++;
			continue;
		}
		strncat(tmpText, &text[i], 1);
	}
	return tmpText;
}

char* SentenceToUpper(char* text) { // vsqko izrechenie zapochva s glavna bukva

	int isNewSentence = 0;

	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char));
	int i;

	for (i = 0; i < strlen(text); i++) {

		if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
			strncat(tmpText, &text[i], 1);
			strncat(tmpText, " ", 1);
			isNewSentence = 1;
			continue;
		}

		if (isNewSentence == 1) {

			char temp = toupper(text[i]);

			strncat(tmpText, &temp, 1);
			isNewSentence = 0;

			entire_capital_letter_count++;
		}
		else {
			strncat(tmpText, &text[i], 1);
		}
	}
	return tmpText;
}


char* RemoveSpecialChars(char* text) {    //vseki simvol sys stoynost po-golqma ot 127 biva premahvan
	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char));

for (int i = 0; i < strlen(text); i++) {
		int variab = text[i];

		if (text[i] > '~' || text[i] < 0) {
			entire_special_symbol_count++;
			strncat(tmpText, &text[i], 0);
		}
		else if ((text[i] == '?')){
                text[i] == ' ';
		}else
		{
		    strncat(tmpText, &text[i], 1);
		}
	}
	return tmpText;
}

char* RemoveMultipleSpaces(char* text) {   //prazni razstoqniq po-golemi ot 1 shpaciq bivat namaleni do 1
	char* tmpText = (char*)calloc(strlen(text) * 2, sizeof(char));
	int i;

	for (i = 0; i < strlen(text) - 1; i++) {

		if (text[i] == ' ' && text[i + 1] == ' ')
		{
			entire_multiple_spaces_count++;

		}
		else {
			strncat(tmpText, &text[i], 1);
		}
	}
	return tmpText;
}


int main()
{
	while (true) {
		char text[2000];

		printf("Enter text:\n");
		fflush(stdin);
		fgets(text, 1000, stdin);

		char* editedText = (char*)malloc(sizeof(char) * 2000);
		text_count++;

		strcpy(editedText, RemoveSpecialChars(text));
		strcpy(editedText, SentenceToUpper(editedText));
		strcpy(editedText, AddSpaceAfter(editedText));
		strcpy(editedText, AddTab(editedText));
		strcpy(editedText, AddSpaceBefore(editedText));
		strcpy(editedText, RemoveMultipleSpaces(editedText));


		float averageTabs = entire_tab_count / text_count;
		float averageSpacesBefore = entire_space_before_count / text_count;
		float averageSpacesAfter = entire_space_after_count / text_count;
		float averageCapitalLetters = entire_capital_letter_count / text_count;
		float averageSpecialSymbols = entire_special_symbol_count / text_count;
		float averageMultipleSpaces = entire_multiple_spaces_count / text_count;

		printf("\nFormatted text:\n%s\n", editedText);
		printf("\nAdded tabs: %d (Average: %.2f)\n", entire_tab_count, averageTabs);
		printf("Added spaces before char: %d (Average: %.2f)\n", entire_space_before_count, averageSpacesBefore);
		printf("Added spaces after char: %d (Average: %.2f)\n", entire_space_after_count, averageSpacesAfter);
		printf("Changed letters to upper case: %d (Average: %.2f)\n", entire_capital_letter_count, averageCapitalLetters);
		printf("Removed special symbols: %d (Average: %.2f)\n", entire_special_symbol_count, averageSpecialSymbols);
		printf("Removed multiple spaces: %d (Average: %.2f)\n", entire_multiple_spaces_count, averageMultipleSpaces);

	}
	return 0;
}
