#include<stdio.h>
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<stdlib.h>
extern int errno; 
void main()
{
    int ch1;
    char ch2,ch3;
    char name[20],buffer[102];
    int fd=0,val;
    while(1)
    {
        printf("1. I/O Calls\n");
        printf("2. Process Calls\n");
        printf("3. Exit.\n");
        printf("Enter your choice:");
        scanf(" %d",&ch1);
        switch(ch1)
        {
             
            case 1:
            {
                while(1)
                {
                    printf("I/O calls.\n");
                    if(fd>0)
                        printf("**A file is open.**\n\n");
                    printf("a. Create/Open file.\n");
                    printf("b. Close file.\n");
                    printf("c. Read file.\n");
                    printf("d. Write in file.\n");
                    printf("e. Exit.\n");
		    printf("Enter your choice:");
                    scanf(" %c",&ch2);
                    switch(ch2)
                    {
                        case 'a':
                        {
                            if(fd>0)
                                printf("A file is already open. Close it first to create/open a new file.\n");
                            else
                            {
                                printf("Enter the name of the file to create/open (20 characters):");
				scanf(" %s", name);
				//strcpy(name,"rew");				
				printf("%s*\n",name);
                                fd = open(name, O_RDWR | O_EXCL | O_CREAT, 0777);
				if(fd<0)
					fd=open(name, O_RDWR,0);
				if(fd<0)
					fd=open(name,O_RDWR | O_EXCL,0);
                                if(fd>0)
                                    printf("%s File creation/opening successful.\n",name);
                                else  
                                    printf("Error Number % d\n", errno);            
                            }
                        }
                        break;
                        case 'b':
                        {
                            if(fd>0)
                            {
                                if(close(fd)==0)
                                { 
                                    printf("File closed successfully.\n");
                                    fd=0;
                                }
                                else
                                    printf("File closing unsuccessful.\n");
                            }
                            else
                                printf("No file is currently open.\n");
                        }
                        break;
                        case 'c':
                        {
                            if(fd>0)
                            {
                                if(read(fd,buffer,100)<0)
                                    printf("File reading error.\n");
                                else
                                {
                                    printf("First 100 characters in the file is :\n");

                                    printf("%s\n",buffer);
                                }
                            }
                            else
                                printf("Open a file first to read from.\n");
                        }
                        break;
                        case 'd':
                        {
                            if(fd>0)
                            {
                                printf("Enter what you want to write to file (max 100 characters): ");
				scanf(" %s", buffer);
                               	//fgets(buffer,100,stdin);
				strcat(buffer,"\n");
                                if(write(fd,buffer, strlen(buffer))<0)
                                    printf("Writing to file error.\n");
                                else
                                    printf("Writing to file is successful.\n");
                            }
                            else
                                printf("Open a file first to write to.\n");
                        }
                        break;
                        case 'e':
                        break;
                        default:
                            printf("Enter correct choice.\n");
                    }
                    if(ch2=='e')
                        break;
                }
            }
            break;
            case 2:
            {
                while(1)
                {
                    printf("Process Calls.\n");
                    printf("i. fork()\n");
                    printf("j. exec()\n");
                    printf("k. exit.\n");
		    printf("Enter your choice:");
                    scanf(" %c",&ch3);
                    switch(ch3)
                    {
                        case 'i':
                        {
                            printf("Executing fork system call.\n");
                            val=fork();
                            if(val==0)
                            {
                                printf("This string is printed from the child process.\nAnd the child process will terminate now.\n");
                                exit(1);
                            }
                            else
                                printf("This string is printed from the current/parent process.\nThe parent process will continue.\n");
                        }
                        break;
                        case 'j':
                        {
                            printf("Executing exec system call will terminate this program.\nDo you want to continue(y/n):");
                            scanf(" %c",&ch2);
			    //ch2='y';
                            if(ch2=='y'||ch2=='Y')
                            {
                                printf("Executing exec system call to execute ls function to print all the files in the current directory.\n\n");
                                execl("/bin/ls", "ls", 0);
                            }
                            else
                                printf("exec system call cancelled.\n");
                        }
                        break;
                        case 'k':
                        break;
                        default:
                            printf("Enter correct choice.\n");
                    }
                    if(ch3=='k')
                        break;
                    
                }
            }
            break;
            case 3:
                exit(1);
            break;
            default:
                printf("Please enter a valid choice\n");
        }
    }
}
