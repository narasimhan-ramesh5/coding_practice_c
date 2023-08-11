#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// To execute C, please define "int main()"

#define NUM_TESTS 6

char *testStr[NUM_TESTS] = {
  "         leading and trailing spaces   ",
  "trailing and  in  between spaces",
  "      leading and in between      spaces",
  "nospaces",
  "        ",
  "",
};

void remove_trailing_spaces(char *input_str, int len, int *new_len)
{
    /* This is going to involve a lot of memory moves.
       Ideally, we want to minimize the number of memmove operaitons.
       Therefore, we shall move one word at a time to its right location */

    int i = 0, num_trailing_spaces =0;

    for(i = len - 1; i > 0; i--)
    {
       if(input_str[i] == ' ')
       {
          num_trailing_spaces++;
       }
       else 
       {
          break;
       }
    }

    *new_len = len - num_trailing_spaces;
    input_str[*new_len] = '\0';

    return;
}


void str_rev(char *result_str, int len)
{
  int i = 0, j = len - 1;
  char temp;
  while(i < j)
  {
     temp = result_str[i];
     result_str[i] = result_str[j];
     result_str[j] = temp;
     i+=1;j-=1;
  }
}

void reverse_words_in_str(char *result_str, int len)
{
   int word_start = 0, word_count = 0, word_end = 0, word_len = 0;
   int current_index = 0, i = 0, j= 0, k= 0;
   char temp = 0;
   int updated_len = len, num_extra_spaces = 0;

   while(current_index < len)
   {
      i = current_index;

      /* Find next word */
      while(result_str[i] == ' ' && i < len) {
        i += 1;
      } 

      if(i == len)
      {
        printf("Reached end of string\n");
        break;
      }

      word_count++;

      word_start = i;

      i += 1;
      while(result_str[i] != ' ' && i < len){
        i += 1;
      }
      word_end = i - 1;

      printf("Word starts at index %d and ends at %d\n", word_start, word_end);

      /* Reverse each word */
      j = word_start;
      k = word_end;
      while(j < k)
      {
         temp = result_str[j];
         result_str[j] = result_str[k];
         result_str[k] = temp;
         j+=1;k-=1;
      }

      word_len = word_end - word_start + 1;

      /* Remove additional spaces - 
         This logic covers the leading spaces and in-between spaces */
      if(word_count == 1)
      {
         num_extra_spaces = word_start - current_index;
         memmove(&result_str[current_index], &result_str[word_start], word_len);
      }
      else 
      {
         num_extra_spaces = word_start - current_index - 1;
         memmove(&result_str[current_index + 1], &result_str[word_start], word_len);
      }

      printf("Found %d extra spaces\n", num_extra_spaces);

      for(k = word_end; k > word_end - num_extra_spaces; k--)
      {
         result_str[k] = ' ';
      }

      if(i == len)
      {
         printf("Reached end of string\n");
         break;
      }
      current_index = i - num_extra_spaces;
   }

   if(!word_count)
   {
      result_str[0] = '\0';
   }
   else 
   {
      /* 
       * We took care of leading and in-between spaces, 
       * now remove trailing spaces.
       */
      remove_trailing_spaces(result_str, len, &updated_len);
      //result_str = realloc(result_str, updated_len + 1);
      str_rev(result_str, updated_len);
   }
}


int main() {
  char *result_str = NULL;
  int i = 0, input_str_size = 0;

  for(i = 0; i < NUM_TESTS; i++)
  {
      printf("*** Iteration %d ***\n", i);
      printf("Input string is : \"%s\"\n", testStr[i]);

      input_str_size = strlen(testStr[i]);
      
      /* 'result_str' is the buffer where we perform the in-place word reversal */
      result_str = malloc(input_str_size + 1); /* One extra for string terminator */
      if(!result_str)
      {
         printf("Couldn't allocate memory for result string \n");
         break;
      }

      strncpy(result_str, testStr[i], input_str_size);
      result_str[input_str_size] = '\0';

      reverse_words_in_str(result_str, input_str_size);

      printf("Result is \"%s\"\n", result_str);

      free(result_str);
      printf("\n\n\n");
  }

  printf("This program implements an in-place word reversal within a string.\
    It also removes extra spaces that either lead, trail or occur in between\n");
  
  return 0;
}
