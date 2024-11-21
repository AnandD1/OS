#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
int file_descriptor;
char data_to_write[] = "Hello, System Calls!";
char buffer[100];
ssize_t bytes_read;
file_descriptor = open("example.txt", O_WRONLY | O_CREAT, 0644);
if (file_descriptor == -1) {
perror("open");
exit(1);
}
ssize_t bytes_written = write(file_descriptor, data_to_write,
sizeof(data_to_write) - 1);
if (bytes_written == -1) {
perror("write");
exit(1);
}
printf("Wrote %zd bytes to the file.\n", bytes_written);
if (close(file_descriptor) == -1) {
perror("close");
exit(1);
}
file_descriptor = open("example.txt", O_RDONLY);
if (file_descriptor == -1) {
perror("open");
exit(1);
}
bytes_read = read(file_descriptor, buffer, sizeof(buffer));
if (bytes_read == -1) {
perror("read");
exit(1);
}
buffer[bytes_read] = '\0';
printf("Read from file: %s\n", buffer);
if (close(file_descriptor) == -1) {
perror("close");
exit(1);
}
return 0;
}
