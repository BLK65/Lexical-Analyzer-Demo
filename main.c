#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Checks for delimiters to separate the substrings.
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == ':' || ch == '"' || ch == '\n'|| ch == '\0')
        return (true);
    return (false);
}

// Returns true if the substring is an IDENTIFIER.
bool isIdentifier(char* str)
{
    int len = strlen(str);
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

// Returns "true" if the substring is an INTEGER CONSTANT.
bool isIntegerConstant(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return(false);

    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9')
            return (false);
    }
    return(true);
}

// Returns "true" if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return(true);
    return(false);
}

// Returns "true" if the character is the first half of an OPERATOR.
bool isOperator2(char ch)
{
    if (ch == ':')
        return(true);
    return(false);
}

// Returns "true" if the substring is a STRING CONSTANT.
bool isStringConstant(char* str)
{
    int lastIndex = strlen(str) -1;
    if (str[0] == '"' && str[lastIndex] == '"')
        return(true);
    return(false);
}


// Returns "true" if the character is END OF LINE.
bool isEndOfLine(char ch)
{
    if (ch == ';')
        return(true);
    return(false);
}

// Returns "true" if the substring is a KEYWORD.
bool isKeyword(char* str)
{
    if (!strcasecmp(str, "break") || !strcasecmp(str, "case") || !strcasecmp(str, "char") || !strcasecmp(str, "const") || !strcasecmp(str, "continue") || !strcasecmp(str, "do") ||
        !strcasecmp(str, "else") || !strcasecmp(str, "enum") || !strcasecmp(str, "float") || !strcasecmp(str, "for") || !strcasecmp(str, "goto") || !strcasecmp(str, "if") ||
        !strcasecmp(str, "int") || !strcasecmp(str, "long") || !strcasecmp(str, "record") || !strcasecmp(str, "return") || !strcasecmp(str, "static") || !strcasecmp(str, "while"))
        return(true);
    return(false);
}

char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left+2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void parse(char* str, FILE* fPointerIn, FILE* fPointerOut)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right)
    {
        if (isDelimiter(str[right]) == false)
            right++;
        if (isDelimiter(str[right]) == true && left == right)
        {

            if (isEndOfLine(str[right]) == true)
                fprintf(fPointerOut, "EndOfLine\n");

            else if (isDelimiter(str[right]) == true)
                if (str[right] == '(')
                    fprintf(fPointerOut, "LeftPar\n");
                else if (str[right] == ')')
                    fprintf(fPointerOut, "RightPar\n");
                else if (str[right] == '[')
                    fprintf(fPointerOut, "LeftSquareBracket\n");
                else if (str[right] == ']')
                    fprintf(fPointerOut, "RightSquareBracket\n");
                else if (str[right] == '{')
                    fprintf(fPointerOut, "LeftCurlyBracket\n");
                else if (str[right] == '}')
                    fprintf(fPointerOut, "RightCurlyBracket\n");

            else if (str[right] == '"')
            {
                int x = right + 1;
                while (!(str[x] == '"') && x < strlen(str))
                    x++;
                if (x == strlen(str))
                {
                    printf("Error. String constant couldn't terminate before the file end.");
                    //exit(1);
                }
                char* subStr = subString(str, right + 1, x - 1);
                right = x; // might be broken
                fprintf(fPointerOut, "StringConst(%s)\n", subStr);
            }

            else if (isOperator(str[right]) == true)
                if (str[right] == '/')
                {
                    if (str[right+1] == '*')
                    {
                        int x = right + 2;
                        while (!(str[x] == '*' && str[x+1] == '/') && x < strlen(str))
                            x++;
                        if (x == strlen(str))
                        {
                            printf("Error. Comment couldn't terminate before the file end.");
                            //exit(1);
                        }
                        right = x+1;
                    }
                }

                else if (str[right] == '+' && str[right+1] == '+')
                {
                    fprintf(fPointerOut, "Operator(++)\n");
                    right++;
                }
                else if (str[right] == '-' && str[right+1] == '-')
                {
                    fprintf(fPointerOut, "Operator(--)\n");
                    right++;
                }
                else
                    fprintf(fPointerOut, "Operator(%c)\n", str[right]);

            else if (isOperator2(str[right]) == true)
                if (str[right+1] == '=')
                {
                    fprintf(fPointerOut, "Operator(:=)\n");
                    right++;
                }

            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
        {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                fprintf(fPointerOut, "Keyword(%s)\n", strlwr(subStr));

            else if (isIntegerConstant(subStr) == true)
                if (strlen(subStr) < 11)
                    fprintf(fPointerOut, "IntConst(%s)\n", subStr);
                else
                {
                    printf("Error. Integer Constant is too large.\n");
                    //exit(1);
                }

            else if (isIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
                if (strlen(subStr) < 31)
                    fprintf(fPointerOut, "Identifier(%s)\n", strlwr(subStr));
                else
                {
                    printf("Error. Identifier is too large.\n");
                    //exit(1);
                }

            left = right;
        }
    }
    return;
}

int main()
{
    char str[1000];

    FILE *fPointerIn, *fPointerOut;

    fPointerIn = fopen("code.psi", "r");
    fPointerOut = fopen("code.lex", "w");

    if (fPointerIn == NULL){
        printf("Encountered an error while opening code.psi.");
        exit(1);
    }

    if (fPointerOut == NULL){
        printf("Encountered an error while opening code.lex.");
        exit(1);
    }

    while (fscanf(fPointerIn, "%s", str) != EOF)
        {
            parse(str,fPointerIn,fPointerOut);
        }

    fclose(fPointerIn);
    fclose(fPointerOut);

    return (0);
}
