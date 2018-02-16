/* lab1.c
 * Feb 02,2018
 * Titi Asrat
 * Purpose:  practice working with files in C.
 */
#include <stdio.h>
#include <string.h>


#define STR_SIZE 256	/* size of a string */

#define TRUE 1
#define FALSE 0

//debug macro
#if 0
    #define PRINT printf
#else
    #define PRINT (void)
#endif

struct stack
{
    char stk[STR_SIZE];
    int top;
}st;
typedef struct stack STACK;

STACK s;


char push(char);

char  pop(void);

char peek(void);


int main(void)
{
    int i=0;			// loop counter
    char filename[STR_SIZE]="";	// filename to open
    FILE *infile=NULL;		// file pointer
    char buffer[STR_SIZE]="";	// string used to process file
    char peek_return = 'a'; //
    int in_comment = FALSE;

    st.top = -1;

    /* prompt the user for a filename */
    printf("Enter name of file to open: ");
    fgets(buffer, sizeof(buffer), stdin);

    /* clean up the input, since c stores the enter key */
    sscanf(buffer, "%s", filename);  // no & since filename is a string

    /* open file, for reading */
    infile = fopen(filename, "r");
    if (infile == NULL)
    {  printf("Error opening file: %s\n", filename); /*error handling*/
        return 1;  // exit with error
    }

    /* read through file, and print (){} */
    while(fgets(buffer, sizeof(buffer), infile))
    {
        for(i = 0; i < strlen(buffer); i++)
        {
            //process comments, if comment then ignore
            if ((buffer[i] == '/') && (i < strlen(buffer) -1) && (buffer[i+1] == '*'))
            {
                //found a comment
                in_comment = TRUE;

            } //end of if
            else if ((buffer[i] == '*') && (i < strlen(buffer) -1) && (buffer[i+1] == '/'))
            {
                //end of comment
                in_comment = FALSE;

            } //end of else if
            //if not in comment, process each character
            if(!in_comment)
            {
                if(buffer[i] == '(' )
                {
                   // PRINT("buffer %s\n", buffer); //debugging print statement
                   // PRINT("buffer_i is %c and i is %d\n ", buffer[i], i); //debugging print statement
                    //push on the stack
                    push(buffer[i]);
                }
                else if (buffer[i] == ')')
                {
                    peek_return = peek();
                    if (peek_return == '(')
                    {
                        printf("found a ), popping now. buffer is %s\n", buffer); //debugging print statement
                        pop();
                        continue;
                    }
                    else
                    {
                        printf("buffer is %s\n", buffer); //debugging print statement
                        printf("Error: missing ) on line %d \n", i);
                    }
                }
                else if (buffer[i] == '{')
                {
                    push(buffer[i]);
                }
                else if (buffer[i] ==  '}')
                {
                    peek_return = peek();
                    if (peek_return == '{')
                    {
                        printf("found a }, popping now. buffer is %s\n", buffer); //debugging print statement
                        pop();
                        continue;
                    }
                    else
                    {
                        printf("buffer is %s\n", buffer); //debugging print statement
                        printf("Error: missing } on line %d \n", i);
                    }
                }
                else if (buffer[i] == '[')
                {
                   push(buffer[i]);
                }

                else if (buffer[i] == ']')
                {
                    peek_return = peek();
                    if (peek_return == '[')
                    {
                        printf("found a ], popping now. buffer is %s\n", buffer); //debugging print statement
                        pop();
                        continue;
                    }
                    else
                    {
                        printf("buffer is %s\n", buffer); //debugging print statement
                        printf("Error: missing ] on line %d \n", i);
                    }
                }
                else
                {
                    continue; //if not one of the characters listed above, then continue looping
                }
            }//end of else
        } //end for
    }  // loop will exit when we reach end of file, end while
    printf("\n");
    /* close file and exit */
    fclose(infile);
    return 0;
} //end main



/*  Function to add an element to the stack */

char push (char character)
{
    st.top++;
    st.stk[st.top] = character;
    return character;

}

/*  Function to delete an element from the stack */

char pop ()
{
    char charac = 'b';

    if (st.top == - 1)
    {
        PRINT ("Stack is Empty\n"); //debugging print statement
       // return (s.top);
    }

    else
    {
        charac = s.stk[s.top];
        //printf ("poped element is = %dn", s.stk[s.top]);
        st.top = s.top - 1;
    }

    return(charac);
}

char peek ()
{
    return st.stk[st.top];  //to see what is on the top of the stack
}
