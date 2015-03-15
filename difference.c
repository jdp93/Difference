//Joseph Pallansch
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

//compares two files and writes differences to two seperate files
int main(int argc, char **argv){
	//checks for appropriate number of arguments
	if(argc !=3){
		printf("This program takes two file names as input\n");
		printf("Check your arguments and try again\n");
		exit(0);
	}
	
	int fd1, fd2, fd3, fd4;
	int size, size1, size2;
	char *diffone = "diffone";
	char *difftwo = "difftwo";
	
	//used to measure time methods take
	struct timeval start;
	struct timeval finish;
	int difference;
	
	//buffers to read one at a time
	char buffer1[1] = {0};
	char buffer2[1] = {0};

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(diffone, O_CREAT | O_RDWR, 0666);
	fd4 = open(difftwo, O_CREAT | O_RDWR, 0666);
	
	//detects if problem with input
	if(fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0){
		printf("Error opening your input files, diffone, or difftwo\n");
		printf("Check your files and try again\n");
		exit(0);
	}
	//if diffone or difftwo already exists the program will overwrite part
	//or all of the file starting at the beginning

	//determines size of the input files
	size1 = lseek(fd1, 0, SEEK_END);
	size2 = lseek(fd2, 0, SEEK_END);

	//resets cursor to the beginning
	lseek(fd1, 0, SEEK_SET);
	lseek(fd2, 0, SEEK_SET);

	//determines the size of the smallest file
	if(size1 <= size2){
		size = size1;
	}
	else{
		size = size2;
	}

	gettimeofday(&start, NULL);

	//looks for differences and writes them to diffone
	int n = 1;
	while(n < size){
		read(fd1, buffer1, 1);
		read(fd2, buffer2, 1);
		if(!(buffer1[0] == buffer2[0])){
			write(fd3, buffer1, 1);
		}
		n++;
	}
	//writes all additional bytes from the first file if it's larger
	while(n < size1){
		read(fd1, buffer1, 1);
		write(fd3, buffer1, 1);
		n++;
	}

	gettimeofday(&finish, NULL);
	difference =  finish.tv_usec - start.tv_usec;
	printf("First method took %d microseconds\n", difference);

	//reset the cursor
	lseek(fd1, 0, SEEK_SET);
	lseek(fd2, 0, SEEK_SET);
	
	gettimeofday(&start, NULL);

	//creates dynamic memory
	char *p;
	char *s;
	char *t;
	p = (char *) malloc(size1);
	s = (char *) malloc(size2);
	t = (char *) malloc(size2);
	free(p);
	free(s);
	free(t);

	read(fd1, p, size1);
	read(fd2, s, size2);
	
	//looks for differences in files and writes them to difftwo
	int i = 0;
	int count = 0;
	while(i < size){
		if(p[i] != s[i]){
			t[count] = s[i];
			count++;
		}
		i++;
	}
	//writes additional bytes from second file if it's larger
	while(i < size2){
		t[count] = s[i];
		count++;
		i++;
	}	
	write(fd4, t, count);

	gettimeofday(&finish, NULL);
	difference = finish.tv_usec - start.tv_usec;
	printf("The second method took %d microseconds\n", difference);

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);

	return 0;
}
