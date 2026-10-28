/********************************************************
 * Program: C-reverse_polish_notation_calculator.       *
 * About  : . The porgram is an implementation of the   *
 *            reverse polish notation in a calculator   *
 *            using the stack concept of LiFo.          *
 *          . The operators we have is +, -, *, /.      *
 *          . We accept only one digits operands.       *
 *          . Division by 0 not allowed and variables   *
 *            int variables so there is no fractions!   *
 * Author : Ammar MULLAOGLU                             *
 * Date   : 28.10.2026                                  *
 ********************************************************/

//Preprocessor MACROS
/////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_LENGTH 100
/////////////////////////

//Global variables
/////////////////////////
int stack[STACK_LENGTH];
int top = 0;
/////////////////////////

//Functions prototypes:
/////////////////////////
void push(int operand);             //Push element into the stack.
int pop(void);                      //Pop element out of the stack.
void clear(void);                   //Clear the stack and set top(index of stack) to 0.

bool is_empty(void);                //Check if stack is empty => top == 0.
bool is_full(void);                 //Check if stack is full  => top == STACK_LENGTH

void overflow(void);                //Print a message, terminate.
void underflow(void);               //Print a message, terminate.

void read_input(void);              //Read input.
void calculate(char operators);     //Calculate the result of operands from stack.
void print_output(void);            //Print output.
/////////////////////////

int main(void){
    system("title C-reverse_polish_notation_calculator"); //Set program title in Windows OS.
    printf("/*******************************************************************\n"
            "*      Program: C-reverse_polish_notation_calculator.              *\n"
            "*      About  : . The porgram is an implementation of the          *\n"
            "*                 reverse polish notation in a calculator          *\n"
            "*                 using the stack concept of LiFo.                 *\n"
            "*               . The operators we have is +, -, *, /.             *\n"
            "*               . We accept only one digits operands.              *\n"
            "*               . Division by 0 not allowed and variables          *\n"
            "*                 are int variables so there is no fractions!      *\n"
            "*               . To EXIT the program enter a character that is    *\n"
            "*                 not a number, an operand or a space.             *\n"
            "*                                                                  *\n"
            "*      Author : Ammar MULLAOGLU                                    *\n"
            "*      Date   : 28.10.2026                                         *\n"
            "*******************************************************************/\n\n\n");
    for(;;){
        printf("Enter an RPN expression: ");
        read_input();
    }
}

/****************************************
 * push(operand): Takes operand, checks *
 * if the stack is full, if so we have  *
 * overflow, if no we store the operand *
 * in the stack, increase the stack's   *
 * index by 1 which is top.             *
 ****************************************/
void push(int operand){
    if(is_full()){
        overflow();
    }else{
        stack[top] = operand;
        top++;
    }
}
/****************************************
 * int pop(): Check if we have an empty *
 * stack, if yes we have underflow, if  *
 * no, we reduce the index by 1 and     *
 * return the value that we popped back *
 ****************************************/
int pop(void){
    if(is_empty())
        underflow();
    else{
        top--;
        return stack[top];
    }
}
/****************************************
 * clear(): set the index of stack to 0 *
 ****************************************/
void clear(void){
    top = 0;
}
/****************************************
 * bool is_empty(): Check if stack's    *
 * index is equal to zero.              *
 ****************************************/
bool is_empty(void){
    return top == 0;
}
/****************************************
 * bool is_full(): Check if stack's     *
 * index is equal to STACK_LENGTH       *
 ****************************************/
bool is_full(void){
    return top == STACK_LENGTH;
}
/****************************************
 * overflow(): print an error message   *
 * and terminate.                       *
 ****************************************/
void overflow(void){
    printf("Expression is too complex!\n");
    exit(EXIT_FAILURE);
}
/****************************************
 * underflow(): print an error message  *
 * and terminate.                       *
 ****************************************/
void underflow(void){
    printf("Not enough operands in expression!\n");
    exit(EXIT_FAILURE);
}
/*****************************************************************************
 * read_input(): Get user input character by character.                      *
 * If the character is space or newline ignore.                              *
 * If the character is a number store this operand using push() function.    *
 * If the character is operator call calculate() function.                   *
 * If the character is equal sign then call print_output() to show result.   *
 * If we have anything else we terminate.                                    *
 *****************************************************************************/
void read_input(void){
    char user_input;

    while(1){
        user_input = getchar();
        if(user_input == ' ' || user_input == '\n')
            continue;

        if(user_input >= '0' && user_input <= '9')
            push(user_input - 48);
        else if(user_input == '+' || user_input == '-' || user_input == '*' || user_input == '/')
            calculate(user_input);
        else if(user_input == '=')
            print_output();
        else
            exit(EXIT_SUCCESS);
    }
    return;
}
/*****************************************************************************
 * calculate(operators): It does two calls to pop() in order to get operand 1*
 * and operand 2.                                                            *
 * It checks what is the operator throw switch, and checks if we division by *
 * Zero, in case we have we are going to terminate the program.              *
 * It calculate the result and push() it back to the stack                   *
 *****************************************************************************/
void calculate(char operators){
    int operand1, operand2;
    int result = 0;

    operand2 = pop();  //The first pop gets stack[top - 1] which is the second operand.
    operand1 = pop();  //The second pop gets stack[top - 2] which is the second operand.
    switch(operators){
    case '+': result = operand1 + operand2; break;
    case '-': result = operand1 - operand2; break;
    case '*': result = operand1 * operand2; break;
    case '/': if(operand2 == 0){
                printf("Invalid division by 0!\n");
                exit(EXIT_FAILURE);
              }else{
                result = operand1 / operand2;
              }
    }
    push(result);
    return;
}
/*****************************************************************************
 * print_output(): Pop() what we have in stack's index, print the result.    *
 * Clear the stack and return.                                               *
 *****************************************************************************/
void print_output(){
    int result;
    result = pop();
    clear();
    printf("result = %d\n\n", result);
    return;
}
