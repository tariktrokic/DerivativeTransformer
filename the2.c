#include <stdio.h>
#include <stdlib.h>

int main()
{
    char operatorStack[100];
    /*R for random, just to not have a garbage value*/
    char operator= 'R';
    char prevOperator;
    int operatorCount = 0;
    char *postfixString = malloc(300 * sizeof(char));
    char *postfixStringFree = postfixString;
    int wasLastOperatorNumber = 0;
    int numberCount = 0;
    int numbersPassed = 0;
    int numberStartPoints[100];
    int exponentNumbers[100];
    int exponentCount = 0;
    int exponentBase = 0;
    int exponent = 1;
    char *derivativeStack[100];
    char *infixStack[100];
    char *evaluatedString = NULL;
    char *firstOperand = NULL;
    char *secondOperand = NULL;
    char *thirdOperand = NULL;
    char *forthOperand = NULL;
    int forthOperandInt = 0;
    int firstOperandLength = 0;
    int secondOperandLength = 0;
    int thirdOperandLength = 0;
    int forthOperandLength = 0;
    int charCount = 0;
    int charsReadCount = 0;
    int i = 0;

    while (operator!= EOF)
    {
        operator= getchar();
        if (operator== ' ' ||
            operator== '\t' ||
            operator== '\n' ||
            operator== EOF)
        {
            continue;
        }
        if (operator== '+' ||
            operator== '-' ||
            operator== '*' ||
            operator== '/' ||
            operator== '^' ||
            operator== '(' ||
            operator== ')')
        {
            wasLastOperatorNumber = 0;
            while (1)
            {
                if (operatorCount > 0)
                {
                    prevOperator = operatorStack[operatorCount - 1];
                    if (operator== ')')
                    {
                        while (prevOperator != '(')
                        {
                            postfixString[charCount++] = prevOperator;
                            operatorCount--;
                            prevOperator = operatorStack[operatorCount - 1];
                        }
                        operatorCount--;
                        break;
                    }
                    else if (operator== '(' || prevOperator == '(')
                    {
                        operatorStack[operatorCount++] = operator;
                        break;
                    }
                    else if (operator== '^')
                    {
                        operatorStack[operatorCount++] = operator;
                        break;
                    }
                    else if ((operator== '*' || operator== '/') &&
                             (prevOperator == '+' || prevOperator == '-'))
                    {
                        operatorStack[operatorCount++] = operator;
                        break;
                    }
                    else
                    {
                        postfixString[charCount++] = prevOperator;
                        operatorCount--;
                    }
                }
                else
                {
                    operatorStack[operatorCount++] = operator;
                    break;
                }
            }
        }
        else
        {
            if (operator>= '0' && operator<= '9')
            {
                if (!wasLastOperatorNumber)
                {
                    numberStartPoints[numberCount++] = charCount;
                    wasLastOperatorNumber = 1;
                }
            }
            else
            {
                wasLastOperatorNumber = 0;
            }
            postfixString[charCount++] = operator;
        }
    }

    for (i = operatorCount - 1; i >= 0; i--)
    {
        postfixString[charCount++] = operatorStack[i];
        operatorCount--;
    }

    while (charsReadCount < charCount)
    {
        operator= * postfixString++;
        charsReadCount++;
        if (operator== '+' || operator== '-' || operator== '*' || operator== '/' || operator== '^')
        {
            firstOperand = infixStack[operatorCount - 2];
            secondOperand = infixStack[operatorCount - 1];
            for (i = 0; firstOperand[i] != '\0'; i++)
                ;
            firstOperandLength = i;
            for (i = 0; secondOperand[i] != '\0'; i++)
                ;
            secondOperandLength = i;
            evaluatedString = malloc((firstOperandLength + secondOperandLength + 4) * sizeof(char));
            evaluatedString[0] = '(';
            for (i = 0; firstOperand[i] != '\0'; i++)
            {
                evaluatedString[i + 1] = firstOperand[i];
            }
            evaluatedString[firstOperandLength + 1] = operator;
            for (i = 0; secondOperand[i] != '\0'; i++)
            {
                evaluatedString[i + firstOperandLength + 2] = secondOperand[i];
            }
            evaluatedString[secondOperandLength + firstOperandLength + 2] = ')';
            evaluatedString[secondOperandLength + firstOperandLength + 3] = '\0';
            if (operator!= '*' && operator!= '/' && operator!= '^')
            {
                free(firstOperand);
                free(secondOperand);
            }
            operatorCount -= 2;
            infixStack[operatorCount] = evaluatedString;

            operatorCount += 2;
            if (operator== '+' || operator== '-')
            {
                firstOperand = derivativeStack[operatorCount - 2];
                secondOperand = derivativeStack[operatorCount - 1];
                for (i = 0; firstOperand[i] != '\0'; i++)
                    ;
                firstOperandLength = i;
                for (i = 0; secondOperand[i] != '\0'; i++)
                    ;
                secondOperandLength = i;
                evaluatedString = malloc((firstOperandLength + secondOperandLength + 4) * sizeof(char));
                evaluatedString[0] = '(';
                for (i = 0; firstOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + 1] = firstOperand[i];
                }
                evaluatedString[firstOperandLength + 1] = operator;
                for (i = 0; secondOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + firstOperandLength + 2] = secondOperand[i];
                }
                evaluatedString[secondOperandLength + firstOperandLength + 2] = ')';
                evaluatedString[secondOperandLength + firstOperandLength + 3] = '\0';
                free(firstOperand);
                free(secondOperand);
                operatorCount -= 2;
                derivativeStack[operatorCount++] = evaluatedString;
            }
            else if (operator== '*')
            {
                thirdOperand = derivativeStack[operatorCount - 2];
                forthOperand = derivativeStack[operatorCount - 1];
                for (i = 0; thirdOperand[i] != '\0'; i++)
                    ;
                thirdOperandLength = i;
                for (i = 0; forthOperand[i] != '\0'; i++)
                    ;
                forthOperandLength = i;
                evaluatedString = malloc((firstOperandLength + secondOperandLength + thirdOperandLength + forthOperandLength + 6) * sizeof(char));
                evaluatedString[0] = '(';
                for (i = 0; thirdOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + 1] = thirdOperand[i];
                }
                evaluatedString[thirdOperandLength + 1] = '*';
                for (i = 0; secondOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + thirdOperandLength + 2] = secondOperand[i];
                }
                evaluatedString[secondOperandLength + thirdOperandLength + 2] = '+';
                for (i = 0; forthOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + secondOperandLength + thirdOperandLength + 3] = forthOperand[i];
                }
                evaluatedString[forthOperandLength + secondOperandLength + thirdOperandLength + 3] = '*';
                for (i = 0; firstOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + forthOperandLength + secondOperandLength + thirdOperandLength + 4] = firstOperand[i];
                }
                evaluatedString[firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 4] = ')';
                evaluatedString[firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 5] = '\0';
                free(firstOperand);
                free(secondOperand);
                free(thirdOperand);
                free(forthOperand);
                operatorCount -= 2;
                derivativeStack[operatorCount++] = evaluatedString;
            }
            else if (operator== '/')
            {
                thirdOperand = derivativeStack[operatorCount - 2];
                forthOperand = derivativeStack[operatorCount - 1];
                for (i = 0; thirdOperand[i] != '\0'; i++)
                    ;
                thirdOperandLength = i;
                for (i = 0; forthOperand[i] != '\0'; i++)
                    ;
                forthOperandLength = i;
                evaluatedString = malloc((firstOperandLength + 2 * secondOperandLength + thirdOperandLength + forthOperandLength + 13) * sizeof(char));
                evaluatedString[0] = '(';
                evaluatedString[1] = '(';
                for (i = 0; thirdOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + 2] = thirdOperand[i];
                }
                evaluatedString[thirdOperandLength + 2] = '*';
                for (i = 0; secondOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + thirdOperandLength + 3] = secondOperand[i];
                }
                evaluatedString[secondOperandLength + thirdOperandLength + 3] = '-';
                for (i = 0; forthOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + secondOperandLength + thirdOperandLength + 4] = forthOperand[i];
                }
                evaluatedString[forthOperandLength + secondOperandLength + thirdOperandLength + 4] = '*';
                for (i = 0; firstOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + forthOperandLength + secondOperandLength + thirdOperandLength + 5] = firstOperand[i];
                }
                evaluatedString[firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 5] = ')';
                evaluatedString[firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 6] = '/';
                evaluatedString[firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 7] = '(';
                for (i = 0; secondOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + firstOperandLength + forthOperandLength + secondOperandLength + thirdOperandLength + 8] = secondOperand[i];
                }
                evaluatedString[secondOperandLength + firstOperandLength + thirdOperandLength + secondOperandLength + forthOperandLength + 8] = '^';
                evaluatedString[secondOperandLength + firstOperandLength + thirdOperandLength + secondOperandLength + forthOperandLength + 9] = '2';
                evaluatedString[secondOperandLength + firstOperandLength + thirdOperandLength + secondOperandLength + forthOperandLength + 10] = ')';
                evaluatedString[secondOperandLength + firstOperandLength + thirdOperandLength + secondOperandLength + forthOperandLength + 11] = ')';
                evaluatedString[secondOperandLength + firstOperandLength + thirdOperandLength + secondOperandLength + forthOperandLength + 12] = '\0';
                free(firstOperand);
                free(secondOperand);
                free(thirdOperand);
                free(forthOperand);
                operatorCount -= 2;
                derivativeStack[operatorCount++] = evaluatedString;
            }
            else
            {
                thirdOperand = derivativeStack[operatorCount - 2];
                forthOperand = derivativeStack[operatorCount - 1];
                free(forthOperand);
                if (exponentCount == 0)
                {
                    sscanf(secondOperand, "%i", &forthOperandInt);
                    forthOperandInt--;
                    if (firstOperand[0] >= '0' && firstOperand[0] <= '9')
                    {
                        sscanf(firstOperand, "%i", &i);
                        exponentBase = i;
                        exponent = 1;
                        for (i = forthOperandInt; i >= 0; i--)
                        {
                            exponent *= exponentBase;
                        }
                        exponentNumbers[exponentCount++] = exponent - 1;
                    }
                }
                else
                {
                    forthOperandInt = exponentNumbers[--exponentCount];
                    if (firstOperand[0] >= '0' && firstOperand[0] <= '9')
                    {
                        sscanf(firstOperand, "%i", &i);
                        exponentBase = i;
                        exponent = 1;
                        for (i = forthOperandInt; i >= 0; i--)
                        {
                            exponent *= exponentBase;
                        }
                        exponentNumbers[exponentCount++] = exponent - 1;
                    }
                }
                i = forthOperandInt;
                forthOperandLength = 0;
                if (i == 0)
                {
                    forthOperandLength = 1;
                }
                while (i != 0)
                {
                    i /= 10;
                    ++forthOperandLength;
                }
                forthOperand = malloc((forthOperandLength + 1) * sizeof(char));
                sprintf(forthOperand, "%i", forthOperandInt);
                forthOperand[forthOperandLength] = '\0';
                for (i = 0; thirdOperand[i] != '\0'; i++)
                    ;
                thirdOperandLength = i;
                evaluatedString = malloc((firstOperandLength + secondOperandLength + thirdOperandLength + forthOperandLength + 9) * sizeof(char));
                evaluatedString[0] = '(';
                for (i = 0; secondOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + 1] = secondOperand[i];
                }
                evaluatedString[secondOperandLength + 1] = '*';
                evaluatedString[secondOperandLength + 2] = '(';
                for (i = 0; firstOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + secondOperandLength + 3] = firstOperand[i];
                }
                evaluatedString[firstOperandLength + secondOperandLength + 3] = '^';
                for (i = 0; forthOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + firstOperandLength + secondOperandLength + 4] = forthOperand[i];
                }
                evaluatedString[forthOperandLength + secondOperandLength + firstOperandLength + 4] = ')';
                evaluatedString[forthOperandLength + secondOperandLength + firstOperandLength + 5] = '*';
                for (i = 0; thirdOperand[i] != '\0'; i++)
                {
                    evaluatedString[i + forthOperandLength + secondOperandLength + firstOperandLength + 6] = thirdOperand[i];
                }
                evaluatedString[thirdOperandLength + forthOperandLength + secondOperandLength + firstOperandLength + 6] = ')';
                evaluatedString[thirdOperandLength + forthOperandLength + secondOperandLength + firstOperandLength + 7] = '\0';
                free(firstOperand);
                free(secondOperand);
                free(thirdOperand);
                free(forthOperand);
                operatorCount -= 2;
                derivativeStack[operatorCount++] = evaluatedString;
            }
        }
        else
        {
            if ((operator== 's' && * postfixString == 'i') || operator== 't')
            {
                if (operator== 's')
                {
                    evaluatedString = malloc(4 * sizeof(char));
                    evaluatedString[0] = 'c';
                    evaluatedString[1] = 'o';
                    evaluatedString[2] = 's';
                    evaluatedString[3] = '\0';
                    derivativeStack[operatorCount] = evaluatedString;
                }
                else
                {
                    evaluatedString = malloc(10 * sizeof(char));
                    evaluatedString[0] = '(';
                    evaluatedString[1] = 't';
                    evaluatedString[2] = 'a';
                    evaluatedString[3] = 'n';
                    evaluatedString[4] = '^';
                    evaluatedString[5] = '2';
                    evaluatedString[6] = '+';
                    evaluatedString[7] = '1';
                    evaluatedString[8] = ')';
                    evaluatedString[9] = '\0';
                    derivativeStack[operatorCount] = evaluatedString;
                }
                evaluatedString = malloc(4 * sizeof(char));
                evaluatedString[0] = operator;
                i = 1;
                while (i < 3)
                {
                    operator= * postfixString++;
                    charsReadCount++;
                    evaluatedString[i++] = operator;
                }
                evaluatedString[3] = '\0';
                infixStack[operatorCount++] = evaluatedString;
            }
            else if (operator== 's' || operator== 'c' || operator== 'l')
            {
                if (operator== 's')
                {
                    evaluatedString = malloc(3 * sizeof(char));
                    evaluatedString[0] = 'c';
                    evaluatedString[1] = 'h';
                    evaluatedString[2] = '\0';
                    derivativeStack[operatorCount] = evaluatedString;
                }
                else if (operator== 'c')
                {
                    evaluatedString = malloc(3 * sizeof(char));
                    evaluatedString[0] = 's';
                    evaluatedString[1] = 'h';
                    evaluatedString[2] = '\0';
                    derivativeStack[operatorCount] = evaluatedString;
                }
                else
                {
                    evaluatedString = malloc(6 * sizeof(char));
                    evaluatedString[0] = '(';
                    evaluatedString[1] = '1';
                    evaluatedString[2] = '/';
                    evaluatedString[3] = 'X';
                    evaluatedString[4] = ')';
                    evaluatedString[5] = '\0';
                    derivativeStack[operatorCount] = evaluatedString;
                }
                evaluatedString = malloc(3 * sizeof(char));
                evaluatedString[0] = operator;
                operator= * postfixString++;
                charsReadCount++;
                evaluatedString[1] = operator;
                evaluatedString[2] = '\0';
                infixStack[operatorCount++] = evaluatedString;
                operator= *(postfixString - 1);
            }
            else if (operator>= '0' && operator<= '9')
            {
                evaluatedString = NULL;
                i = 0;
                while (operator>= '0' && operator<= '9')
                {
                    if (evaluatedString != NULL)
                    {
                        evaluatedString = realloc(evaluatedString, (2 + i) * sizeof(char));
                    }
                    else
                    {
                        evaluatedString = malloc(2 * sizeof(char));
                    }
                    evaluatedString[i] = operator;
                    if (!(numbersPassed == (numberCount - 1)) && (i + charsReadCount - 1) == numberStartPoints[numbersPassed + 1])
                    {
                        break;
                    }
                    operator= postfixString[i++];
                    if (i >= (charCount - charsReadCount))
                    {
                        break;
                    }
                }
                numbersPassed++;
                postfixString += (i - 1);
                charsReadCount += (i - 1);
                evaluatedString[i] = '\0';
                infixStack[operatorCount] = evaluatedString;
                evaluatedString = malloc(2 * sizeof(char));
                evaluatedString[0] = '0';
                evaluatedString[1] = '\0';
                derivativeStack[operatorCount++] = evaluatedString;
            }
            else
            {
                evaluatedString = malloc(2 * sizeof(char));
                evaluatedString[0] = operator;
                evaluatedString[1] = '\0';
                infixStack[operatorCount] = evaluatedString;
                evaluatedString = malloc(2 * sizeof(char));
                evaluatedString[0] = '1';
                evaluatedString[1] = '\0';
                derivativeStack[operatorCount++] = evaluatedString;
            }
        }
    }
    printf("%s\n", derivativeStack[0]);
    free(derivativeStack[0]);
    free(infixStack[0]);
    free(postfixStringFree);
    return 0;
}