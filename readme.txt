1. Describe the state of your program, exactly what works and what does not work. 
All transactions in sample command work properly. However, I do not figure out how to display Unknown client / unsuccessful transaction first before all other history display. That is I show "Unknown client ID 9999 requested" after the client history for mickey mouse and minnie mouse are shown.

something unexpected: I am so surprised that the number of delete can be more than the number of allocate. It is because I do not create account for the fake clientData object. However, when the whole program is done, it will delete the non-initialized account. So, for the fake constructor for client, it is required to create ten fake account for client.


Furthermore, I am using a window machine. And I also follow the instruction to put an additional empty line right after the last command data. However, when I do this, it shows "Unknown transaction type '=' requested". Even though my command data file is empty, "Unknown transaction type '=' requested" is still showing. However, when I remove the additional empty line, it works. It makes me confused on how the end of line character works.

 
2. Describe anything you are particularly proud of ... 
I am proud of there's no memory leak for the whole program. Although it shows more than 1000 errors in the behinning when I run valgrind. I fixed all of that and get rid of the memory leak.