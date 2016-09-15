In order to run you must have flex and yacc installed (ubuntu/debian):  
 **sudo apt-get install flex**  
 **sudo apt-get install byacc**  

After that you just need to run the Makefile:  
 **make**

This software makes lexical, syntactic and semantic analysis based of a file provided.
It will print any error found. 

In order to run:  
 **./etapa4  entry_file **  

A file named entry containing semantic errors is provided.

==================================================  
To understand the syntactic criteria, please go to the work definition (in portuguese):    
[Work description: syntactic analysis](https://bitbucket.org/bpsilva/compiler-02_syntactic_analysis/raw/ca77046c56d9f7fafab516dc0e3f3a504c5a924e/definition.pdf)  

To understand the semantic criteria, please go to the work definition (in portuguese):    
[Work description: syntactic analysis](https://bitbucket.org/bpsilva/compiler-03_semantic_analysis/raw/ca77046c56d9f7fafab516dc0e3f3a504c5a924e/definition.pdf)  


See the previous stages of the project too:  
[First stage: lexical analysis](https://bitbucket.org/bpsilva/compiler-01_lexical_analysis)  
[Second stage: syntactic analysis](https://bitbucket.org/bpsilva/compiler-02_syntactic_analysis/)  
[Third stage: abstract syntax tree generation](https://bitbucket.org/bpsilva/compiler-03_abstract_syntax_tree)