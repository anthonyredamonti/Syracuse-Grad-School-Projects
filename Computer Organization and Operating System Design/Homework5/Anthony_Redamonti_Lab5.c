// Anthony Redamonti
// 12-26-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// Run the following: 
// cd libfuse
// git checkout fuse-2.9.7
// cd example
// gcc -Wall Anthony_Redamonti_Lab5.c `pkg-config fuse --cflags --libs` -o Anthony_Redamonti_Lab5
// mkdir /tmp/mnt
// ./Anthony_Redamonti_Lab5 /tmp/mnt
// cat Anthony_Redamonti_Lab5
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
//

#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>

// array of pointers (array of arrays)
char* file_names[10];
int names_index = 0;

// array of pointers (array of arrays)
char* file[10];
int file_index = 0;

// copy array1 into array2
void copy_array(const char* array1, int size_of_array1, char* array2, int size_of_array2){
    if(size_of_array1 > size_of_array2){
        printf("array1 is bigger than array2 and therefore cannot be copied.\n");
        return;
    }
    for(int i = 0; i < size_of_array1; i++){
        array2[i] = array1[i];
    }
}

static int lab5_addfile(const char* file_name, const char* path)
{
    path++; // get rid of '/' character
    
    // check if there is room. Arbitrarily chose 10 as max number of files.
    if(names_index == 10){
        printf("Max file count exceeded.\n");
        return 0;
    }

    // get the size of the name
    int name_size = sizeof(file_name)/sizeof(file_name[0]);
    if(name_size > 4096){
        printf("File name is greater than 4096 bytes. Too large.\n");
        return 0;
    }

    // store the name in heap
    char* temp_name = (char*)(malloc(name_size*sizeof(char)));
    copy_array(file_name, name_size, temp_name, name_size);
    file_names[names_index] = temp_name;
    names_index++;

    // allocate memory for the file
    file[file_index] = (char*)(malloc(4096*sizeof(char)));
    file_index++;
    return 1;
}

int same_file(const char* file1, const char* file2){
    int size1 = sizeof(file1)/sizeof(file1[0]);
    int size2 = sizeof(file2)/sizeof(file2[0]);
    if(size1 != size2){
        return 0;
    }
    for(int i = 0; i < size1; i++){
        if(file1[i] != file2[i]){
            return 0;
        }
    }
    return 1;
}

int find_index(const char* path){
    path = path + 1; // remove "/" character
    printf("Looking for path: %s\n", path);
    for(int i = 0; i < names_index; i++){
        if(same_file(path, file_names[i]) == 1){
           return i; 
        }
    }
    printf("Path not found.\n");
    return -123; // file does not exist
}

static int lab5_unlink(const char *path)
{
    int index = find_index(path);
    if(index == -123){
        return 0;
    }
    free(file[index]);
    free(file_names[index]);
    while (index < 9){
        file[index] = file[index+1];
        file_names[index] = file_names[index+1];
        index++;
    }
    names_index--;
    file_index--;
	int	result = unlink(path);
	if (result == -1)
    {
		return -errno;
    }
	return 0;
}

static int lab5_open(const char *path, struct fuse_file_info *fi)
{
    int index = find_index(path);
    if(index == -123){
        return 0;
    }
	int result = open(path, fi->flags);
	if (result == -1)
		return -errno;
	close(result);
	return 0;
}

static int lab5_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int index = find_index(path);
    if(index == -123){
        return 0;
    }
    int bytes_read = readlink(path, buf, size - 1);
	buf[bytes_read] = '\0';
    return 1;
}

static int lab5_write(const char *path, const char* new_data, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int index = find_index(path);
    if(index == -123){
        return 0;
    }
    int original_file_size = strlen(file[index]);
    if(original_file_size + size > 4096){
        printf("Cannot write more than 4096 bytes to a file\n");
        return 0;
    }
    int error = 0;
    int fd = open(path, error);
    pwrite(fd, new_data, size, offset);
    return 1;
}

static struct fuse_operations lab5_oper = {
	.open		= lab5_open,
	.read		= lab5_read,
    .write      = lab5_write,
    .link       = lab5_addfile, // create a file
    .unlink     = lab5_unlink   // delete a file
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &lab5_oper, NULL);
}