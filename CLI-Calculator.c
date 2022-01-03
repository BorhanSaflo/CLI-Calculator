//Include the libraries that will be needed for the program.
#include <stdio.h>
#include <math.h>
#include <ctype.h>

//Declaring Global Variables and Functions
float a = 0, b = 0, c = 0, d = 0, e = 0, memory[100];
int memorySize=0, memorySelectedItem, firstTimeMenu=1;
char clearMemoryConfirmation;
char getItem(char mode);
char getOperation(char item);
float getNum(char type, char operation, char item);
float binaryOperations(float num1, float num2, char operation);
float unaryOperations(float num, char operation);
void advancedOperations(char advancedItem, char item);
void setVariables(char operation,float num);
int memorySelection();
void viewMemory();
void eraseMemory();
void addToMemory(float result);

//Initiate the main function of the program.
int main(void) {
    //Declaring variables in the main function scope
    char item, advancedItem, operation;
    float num1, num2, result;

    //Display the welcome messages to the user
    puts("Welcome to my Command-Line Calculator (CLC)");
    puts("Developer: Borhan Saflo");
    puts("Version: 3, Assignment 3");
    puts("Date: Wednesday, Dec 1, 2021");
    puts("-----------------------------------------------------------");

    //A do while loop that will continue to loop as long as the selected item is not X.
    do {
        //The getItem function will be executed, allowing the user to select an item from the main menu.
        item= getItem('M');
        //A switch statement that will handle the item options.
        switch (item) {
            case 'B':
                num1= getNum('1',operation,item);
                operation= getOperation(item);
                num2= getNum('2', operation,item);
                result= binaryOperations(num1, num2, operation);
                printf("The result is:\t%.2f\n", result);
                break;

            case 'U':
                operation= getOperation(item);
                num1= getNum('U',operation,item);
                result= unaryOperations(num1, operation);
                printf("The result is:\t%.2f\n", result);
                break;

            case 'A':
                firstTimeMenu=1;
                do {
                    advancedItem= getItem('A');
                    advancedOperations(advancedItem, item);
                } while (advancedItem != 'X');
                break;

            case 'V':
                operation= getOperation(item);
                num1= getNum('V',operation,item);
                setVariables(operation,num1);
                break;

            case 'M':
                viewMemory();
                break;

            case 'R':
                eraseMemory();
                break;

            case 'X':
                //Print goodbye message
                puts("Thanks for using my Simple Calculator. Hope to see you soon again, Goodbye!");
                break;
        }

    } while (item != 'X');
}

//The getItem function is called anytime an item is required, and it displays the appropriate menu and scans for an item based on the value passed in the parameter.
char getItem(char mode) {
    char item = ' ';
    if(mode=='M') {
        if(firstTimeMenu == 1) {
            puts("Select one of the following items: ");
            puts("B) - Binary Mathematical Operations, such as addition and subtraction.");
            puts("U) - Unary Mathematical operations, such as square root, and log.");
            puts("A) - Advances Mathematical Operations, using variables, arrays.");
            puts("V) - Define variables and assign them values.");
            puts("M) - See the memory");
            puts("R) - Erase memory");
            puts("X) - Exit");
            firstTimeMenu=0;
        }
        else puts("Select your option ( B (Binary operation), U (Unary operation) , A (Advanced), V (Variables), M (Memory), R (Erase Memory), X (Exit))");

        while (1) {
            scanf(" %c", &item);
            item=toupper(item);
            if(item=='B' || item=='U' || item=='A' || item=='V' || item=='M' || item=='R' || item=='X') break;
            puts("Invalid input, select your option ( B (Binary operation), U (Unary operation) , A (Advanced), V (Variables), M (Memory), R (Erase Memory), X (Exit))");
            fflush(stdin);
        }
    }
    else if(mode=='A') {
        if(firstTimeMenu == 1) {
            puts("Select one of the following items:");
            puts("B) - Binary Mathematical Operations, such as addition and subtraction.");
            puts("U) - Unary Mathematical Operations, such as square root, and log.");
            puts("X) - Exit and back to the main menu");
            firstTimeMenu=0;
        }
        else puts("Select your option ( B (Binary operation), U (Unary operation), X (Exit and back to the main menu))");

        while (1) {
            scanf(" %c", &item);
            item=toupper(item);
            if(item=='B' || item=='U' || item=='X') break;
            puts("Invalid input, select your option ( B (Binary operation), U (Unary operation), X (Exit and back to the main menu))");
            fflush(stdin);
        }
    }
    return item;
}

//The getOperation function is called anytime an operation is required. It will ask the user for input by displaying the appropriate message and scanning for the user's input for an operation.
char getOperation(char item) {
    char operation = ' ';
    if(item=='B') {
        puts("Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
        while (scanf(" %c", &operation) == 0 || (operation != '+' && operation != '-' && operation != '*' && operation != '/' && operation != '%' && operation != '^')) {
            puts("Invalid Input, Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
            fflush(stdin);
        }
    }
    else if(item=='U') {
        puts("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ): ");
        while (scanf(" %c", &operation) == 0 || (toupper(operation) != 'S' && toupper(operation) != 'L' && toupper(operation) != 'E' && toupper(operation) != 'C' && toupper(operation) != 'F')) {
            puts("Invalid Input, please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ): ");
            fflush(stdin);
        }
        operation = toupper(operation);
    }
    else if(item=='V') {
        puts("Please enter the name of the variable ( A single character between 'a' to 'e' ):");
        while (scanf(" %c", &operation) == 0 || (toupper(operation) != 'A' && toupper(operation) != 'B' && toupper(operation) != 'C' && toupper(operation) != 'D' && toupper(operation) != 'E')) {
            puts("Invalid Input, Please enter the name of the variable ( A single character between 'a' to 'e' ): ");
            fflush(stdin);
        }
        operation = toupper(operation);
    }

    return operation;
}

//The getNum function is called anytime a number is required; it will ask the user for a number by displaying the appropriate message and scanning for the user's input for a number; it will only accept the allowed numbers for each operation.
float getNum(char type, char operation, char item) {
    float num;
    char input;
    if (type=='1' && item=='A') {
        puts("Please enter the first number or a variable name ('a' to 'e'):");
        while (scanf("%f", &num) == 0 && scanf("%c", &input) == 1) {
            input = toupper(input);
            if (input == 'A') num = a;
            else if (input == 'B') num = b;
            else if (input == 'C') num = c;
            else if (input == 'D') num = d;
            else if (input == 'E') num = e;
            if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
                input = ' ';
                break;
            } else puts("Invalid Input, please enter the first number:");
            fflush(stdin);
        }
    }
    else if(type=='1') {
        puts("Please enter the first number:");
        while (scanf("%f", &num) == 0) {
            puts("Invalid Input, please enter the first number:");
            fflush(stdin);
        }
    }
    else if(type=='2' && item=='A') {
        puts("Please enter the second number or a variable name ('a' to 'e'):");
        while ((scanf("%f", &num) == 0 && scanf("%c", &input) == 1) || (num == 0 && operation == '/')  || (num == 0 && operation == '%')) {
            input = toupper(input);
            if (input == 'A') num = a;
            else if (input == 'B') num = b;
            else if (input == 'C') num = c;
            else if (input == 'D') num = d;
            else if (input == 'E') num = e;
            if (operation == '/' && num == 0) {
                puts("The denominator can't be zero, please enter the second number or a variable name ('a' to 'e'):");
                num=1;
            }
            else if (operation == '%' && num == 0) puts("Invalid Input, please enter the second number or a variable name ('a' to 'e'):");
            else if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
                input = ' ';
                break;
            } else puts("Invalid Input, please enter the second number or a variable name ('a' to 'e'):");
            fflush(stdin);
        }
    }
    else if(type=='2') {
        puts("Please enter the second number:");
        while (scanf("%f", &num) == 0 || (num == 0 && operation == '/')  || (num == 0 && operation == '%')) {
            if (num == 0 && operation == '/') {
                puts("The denominator can't be zero, please enter the second number:");
                num=1;
            }
            else puts("Invalid Input, please enter the second number:");
            fflush(stdin);
        }
    }
    else if(type=='U' && item=='A') {
        if (operation == 'S') puts("Please enter a non-negative number or a variable name ('a' to 'e'):");
        else if (operation == 'L') puts("Please enter a positive number or a variable name ('a' to 'e'):");
        else puts("Please enter a number or a variable name ('a' to 'e'):");
        while ((scanf("%f", &num) == 0 && scanf("%c", &input) == 1) || (operation == 'S' && num < 0) || (operation == 'L' && num <= 0)) {
            input = toupper(input);
            if (input == 'A') num = a;
            else if (input == 'B') num = b;
            else if (input == 'C') num = c;
            else if (input == 'D') num = d;
            else if (input == 'E') num = e;
            if (operation == 'S' && num < 0) {
                puts("Number can't be negative, please enter a non-negative number or a variable name ('a' to 'e'):");
                num=1;
            }
            else if (operation == 'L' && num <= 0) {
                puts("Number can't be 0 or negative, please enter a positive number or a variable name ('a' to 'e'):");
                num=1;
            }
                //if the user selects one of the variables, then break out of the loop.
            else if (input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E') {
                input = ' ';
                break;
            } else puts("Invalid input, please enter a number or a variable name ('a' to 'e'):");
            fflush(stdin);
        }
    }
    else if(type=='U') {
        if (operation == 'S') puts("Please enter a non-negative number:");
        else if (operation == 'L') puts("Please enter a positive number:");
        else puts("Please enter a number:");

        while ((scanf("%f", &num) == 0) || (operation == 'S' && num < 0) || (operation == 'L' && num <= 0)) {
            if (operation == 'S' && num < 0) {
                puts("Number can't be negative, please enter a non-negative number:");
                num=1;
            }
            else if (operation == 'L' && num <= 0) {
                puts("Number can't be 0 or negative, please enter a positive number:");
                num=1;
            }
            else puts("Invalid input, please enter a number:");
            fflush(stdin);
        }
    }
    else if(type=='V') {
        puts("Please enter a value to assign to the variable:");
        while (scanf("%f", &num) != 1) {
            puts("Invalid Input, Please enter a value to assign to the variable:");
            fflush(stdin);
        }
    }
    return num;
}

//When a binary operation has to be calculated, the binaryOperations function is called. The function takes three parameters: the first number, the second number, and the operation. The function will then compute and return the result.
float binaryOperations(float num1, float num2, char operation) {
    float result = 0;
    if (operation == '+') result = num1 + num2;
    else if (operation == '-') result = num1 - num2;
    else if (operation == '*') result = num1 * num2;
    else if (operation == '/') result = num1 / num2;
    else if (operation == '%') result = fmodf(num1, num2);
    else if (operation == '^') result = powf(num1, num2);
    addToMemory(result);
    return result;
}

//When a unary operation has to be computed, the unaryOperation function is called. The function will take two parameters: the number and the operation. The function will then compute and return the result.
float unaryOperations(float num, char operation) {
    float result = 0;
    if (operation == 'S') result = sqrtf(num);
    else if (operation == 'L') result = log10f(num);
    else if (operation == 'E') result = expf(num);
    else if (operation == 'C') result = ceilf(num);
    else if (operation == 'F') result = floorf(num);
    addToMemory(result);
    return result;
}

//When the user wants to compute an operation from the calculator's advanced section, the advancedOperations function is called and the function will handle each case.
void advancedOperations(char advancedItem, char item) {
    float num1,num2,result;
    char operation = ' ';
    switch (advancedItem) {
        case 'B':
            num1=getNum('1',operation,item);
            operation=getOperation('B');
            num2=getNum('2',operation,item);
            result= binaryOperations(num1, num2, operation);
            printf("The result is:\t%.2f\n", result);
            break;

        case 'U':
            operation = getOperation('U');
            num1= getNum('U',operation,item);
            result= unaryOperations(num1, operation);
            printf("The result is:\t%.2f\n", result);
            break;

        case 'X':
            break;
    }
}

//When the user wants to assign a value to a variable, the setVariables function is called. It will accept two parameters and set the selected variable to the desired value.
void setVariables(char operation,float num) {
    if (operation == 'A') a = num;
    else if (operation == 'B') b = num;
    else if (operation == 'C') c = num;
    else if (operation == 'D') d = num;
    else if (operation == 'E') e = num;
    printf("Variable %c is set to: %.2f\n", operation, num);
}

//When the user wishes to see the values stored in memory, viewMemory will be called.
void viewMemory() {
    if(memorySize==1) printf("\nThere is currently 1 item stored in the memory.\n\n");
    else printf("\nThere are currently %d items stored in the memory.\n\n",memorySize);
    if(memorySize==0) return;
    else {
        firstTimeMenu = 1;
        while (1) {
            memorySelectedItem=memorySelection();
            if(memorySelectedItem==-1) break;
            else if(memorySelectedItem==0) {
                printf("\n");
                for (int i = 1; i <= memorySize; ++i) {
                    printf("(%d) %.2f",i, memory[i-1]);
                    if (i!=memorySize) printf(", ");
                }
                printf("\n\n");
            }
            else printf("\nThe value of the item you selected is %.2f\n\n",memory[memorySelectedItem-1]);
        }
    }
}

//The memorySelection function will display the appropriate menu and ask the user to pick a value from the memory to see.
int memorySelection() {
    char input;
    int num;
    if (firstTimeMenu == 1) {
        printf("Select one of the following items:\n");
        puts("0) - Enter 0 to see all the items in the memory.");
        if (memorySize==1) puts("1) - Enter 1 to see the value stored in the memory.");
        else printf("1-%d) - Enter a number from 1 to %d to see its corresponding value in the memory.\n", memorySize,memorySize);
        puts("X) - Exit and back to the main menu");
        firstTimeMenu = 0;
    } else
    if (memorySize==1) puts("Select your option ( 1 (See the value stored in the memory), 0 (All items in the memory), X (Exit and back to the main menu))");
    else printf("Select your option ( 1-%d (See corresponding value in the memory), 0 (All items in the memory), X (Exit and back to the main menu))\n",memorySize);

    while ((scanf("%d", &num) == 0 || num<0 || num>memorySize) && scanf("%c", &input) == 1) {
        input = toupper(input);
        if (input == 'X') {
            num = -1;
            break;
        }
        else if (num>memorySize) puts("Select a number from the allowed range.");
        else if (memorySize==1) puts("Invalid input, select your option ( 1 (See the value stored in the memory), 0 (All items in the memory), X (Exit and back to the main menu))");
        else printf("Invalid input, select your option ( 1-%d (See corresponding value in the memory), 0 (All items in the memory), X (Exit and back to the main menu))\n",memorySize);
        fflush(stdin);
    }
    return num;
}

//The eraseMemory function will prompt the user for confirmation if they are sure they wish to erase the memory. If the user confirms, the memory will be erased.
void eraseMemory() {
    puts("Are you sure you want to clear the memory? [Y/N]");
    while (scanf(" %c", &clearMemoryConfirmation) == 0 || (toupper(clearMemoryConfirmation) != 'Y' && toupper(clearMemoryConfirmation) != 'N')) {
        puts("Invalid input, are you sure you want to clear the memory? [Y/N]");
        fflush(stdin);
    }
    clearMemoryConfirmation=toupper(clearMemoryConfirmation);
    if(clearMemoryConfirmation=='N') return;
    else if(clearMemoryConfirmation=='Y') {
        for (int i = 0; i < memorySize; ++i) memory[i]=0;
        memorySize=0;
        puts("Memory has been cleared.");
    }
}

//When a new value has to be added to the memory, the addToMemory function is called. The function accepts one parameter, and the value passed in the parameter is added to the memory.
void addToMemory(float result) {
    if(memorySize<100) {
        memory[memorySize++]=result;
    } else {
        for (int i = 0; i < 100; ++i) {
            memory[i]=memory[i+1];
        }
        memorySize--;
        memory[memorySize++]=result;
    }
}

