#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
using namespace std;

int main() {
	int pipefd[2], pipefd1[2];
	char buffer[100], buffer1[100];
	char inputString[100];

	pipe(pipefd);
	pipe(pipefd1);

	pid_t pid = fork();

	if(pid > 0) {
		while(inputString[0] != 'Q'){
			close(pipefd[0]);
			close(pipefd1[1]);
			cout << "Enter what parent wanna say: ";
			cin >> inputString;
			write(pipefd[1], inputString, sizeof(inputString));
			read(pipefd1[0], buffer1, sizeof(buffer1));
			cout << "Child says: " << buffer1 << endl;
		}
	}

	else if (pid == 0) {
		while(inputString[0] != 'Q'){
			close(pipefd[1]);
			close(pipefd1[0]);
			read(pipefd[0], buffer, sizeof(buffer));
			cout << "Parent Says: " << buffer << endl;
			cout << "Enter what child wanna say: ";
			cin >> inputString;
			write(pipefd1[1], inputString, sizeof(inputString));
		}
	}

	else {
		cout << "Fork Failed" << endl;
	}
}