# Lexical Analyzer Demo

The source code comprises a program designed to take in a source file named code.psi and generate a text file called code.lex. This resulting file contains a sequential listing of all the tokens extracted from code.lex.

# Lexical Rules for the Demo

1- Identifiers:  
•	Maximum identifier size is 30 characters. If an identifier larger than that is used, the lexical analyzer issues an error message.  
•	The demo language is not case sensitive and all the identifier names are standardized as lower case.  
•	Identifiers start with an alphabetic character (a letter) and are composed of one or more letters/digits/_ (underscore).  
•	Example Token: Identifier(my_var_1)  

2- Integer Constants:  
•	Maximum integer size is 10 digits. If you use an integer value longer than that, the lexical analyzer issues an error message.  
•	Negative values are not supported.  
•	Example Token: IntConst(1290)  

3- Operators:  
•	Valid operators of the language are +,-,*,/,++,--,:=  
•	Example Token: Operator(++)  

4- Brackets:  
•	LeftPar: (  
• RightPar: )  
•	RightSquareBracket: ]  
• LeftSquareBracket: [  
•	LeftCurlyBracket:  {  
• RightCurlyBracket:  }  
•	Example Token: LeftCurlyBracket  

5- String Constants:  
•	String constants of the language are delimited by double quotes (ASCII code 34)as in “this is a string”.  
•	String constants have unlimited size.  
•	String constants cannot contain the double quote character. when you reach one, the string terminates.  
•	If a string constant cannot terminate before the file end, a lexical error is issued.  

6- Keywords:  
•	Keywords are: break,case,char,const,continue,do,else,enum,float,for,goto,if,int,
long,record,return,static,while.  
•	The demo language is not case sensitive and all the keywords are standardized as lower case.  
•	Example Token: Keyword(while)  

7- End of Line:  
• EndOfLine: ;  
•	Example Token: EndOfLine  

8- Comments:  
• Anything between /* and */ is a comment.  
•	If a comment cannot terminate before the file end, a lexical error is issued.  
•	Comments are just like blank space and they provide no tokens.  

# Example

If code.psi contains:  

  hi:=hello+25; /*addition*/  
  hello++; /*increment*/  
  "test_7+8:=9" + [1234} -:= break / ELSE;  

code.lex would be:  

  Identifier(hi)  
  Operator(:=)  
  Identifier(hello)  
  Operator(+)  
  IntConst(25)  
  EndOfLine  
  Identifier(hello)  
  Operator(++)  
  EndOfLine  
  StringConst(test_7+8:=9)  
  Operator(+)  
  LeftSquareBracket  
  IntConst(1234)  
  RightCurlyBracket  
  Operator(-)  
  Operator(:=)  
  Keyword(break)  
  Keyword(else)  
  EndOfLine  
