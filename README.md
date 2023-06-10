This is a program for parsing CSS
_________________________________________________________________________________________

Specifically, it was written as part of university course. Goal of the project is to write a program, that would parse CSS and then browse through it using following commands:

???? - stop parsing CSS, start executing commands
? - print number of CSS blocks parsed so far
<i>,S,? - print number of selectors for block i
<i>,A,? - print number of attributes for block i
<i>,S,<j> - print j-th selector for block i
<i>,A,<n> - print value of n attribute for block i
<n>,A,? - print total number of occurences of attribute n
<z>,S,? - print total number of occurences of selectior z
<z>,E,<n> - print value of attribute n of selector z (in case of being more than one take the last one)
<i>,D,* - delete block i, print "deleted"
<i>,D,<n> - delete attribute n from block i, print "deleted", in case of it being the last attribute in the block - delete it
**** - continue parsing CSS


Program input is composed of CSS code and commands, as follows:

#breadcrumb 
{
	width: 80%;
	font-size: 9pt;
}

h1, body {
	min-width: 780px;
	margin: 0;
	padding: 0;
	font-family: "Trebuchet MS", "Lucida Grande", Arial;
	font-size: 85%;
	color: #666666;
}

h1, h2, h3, h4, h5, h6 {color: #0066CB;}
????
?
1,S,?
1,S,1
1,A,?
2,A,font-family
h1,S,?
color,A,?
h1,E,color
1,A,padding
1,D,*
?
2,D,color
?

****
h1, h2, h3, h4, h5, h6 {color: #0066FF;}
????
?

Output for this would be:

? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D, color == deleted
? == 1
? == 2



Implementation details
_________________________________________________________________________________________

Parsed CSS is stored in a list of segments, each containing 8 CSS blocks. 
All data structures in this code are custom-implemented (no default std data structures, like vector, were used).



Tests
_________________________________________________________________________________________

There are six tests for this program attached in the "tests" folder.
*.io files contain input and *.out files contain desired output.



Final notes
_________________________________________________________________________________________

All code files in this repository are written by me. 
However I am not an autor of attached tests and the example above.
Those were made by my university.
