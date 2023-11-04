#include <io.h>
#include <windows.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define PROT_READ     0x1
#define PROT_WRITE    0x2

#ifdef FILE_MAP_EXECUTE
#define PROT_EXEC     0x4
#else
#define PROT_EXEC        0x0
#define FILE_MAP_EXECUTE 0
#endif

#define MAP_SHARED    0x01
#define MAP_PRIVATE   0x02
#define MAP_ANONYMOUS 0x20
#define MAP_ANON      MAP_ANONYMOUS
#define MAP_FAILED    ((void *) -1)

#ifdef __USE_FILE_OFFSET64
# define DWORD_HI(x) (x >> 32)
# define DWORD_LO(x) ((x) & 0xffffffff)
#else
# define DWORD_HI(x) (0)
# define DWORD_LO(x) (x)
#endif

static char *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
{
	if (prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC))
		return MAP_FAILED;
	if (fd == -1) {
		if (!(flags & MAP_ANON) || offset)
			return MAP_FAILED;
	} else if (flags & MAP_ANON)
		return MAP_FAILED;

	DWORD flProtect;
	if (prot & PROT_WRITE) {
		if (prot & PROT_EXEC)
			flProtect = PAGE_EXECUTE_READWRITE;
		else
			flProtect = PAGE_READWRITE;
	} else if (prot & PROT_EXEC) {
		if (prot & PROT_READ)
			flProtect = PAGE_EXECUTE_READ;
		else if (prot & PROT_EXEC)
			flProtect = PAGE_EXECUTE;
	} else
		flProtect = PAGE_READONLY;

	off_t end = length + offset;
	HANDLE mmap_fd, h;
	if (fd == -1)
		mmap_fd = INVALID_HANDLE_VALUE;
	else
		mmap_fd = (HANDLE)_get_osfhandle(fd);
	h = CreateFileMapping(mmap_fd, NULL, flProtect, DWORD_HI(end), DWORD_LO(end), NULL);
	if (h == NULL)
		return MAP_FAILED;

	DWORD dwDesiredAccess;
	if (prot & PROT_WRITE)
		dwDesiredAccess = FILE_MAP_WRITE;
	else
		dwDesiredAccess = FILE_MAP_READ;
	if (prot & PROT_EXEC)
		dwDesiredAccess |= FILE_MAP_EXECUTE;
	if (flags & MAP_PRIVATE)
		dwDesiredAccess |= FILE_MAP_COPY;
	char *ret = MapViewOfFile(h, dwDesiredAccess, DWORD_HI(offset), DWORD_LO(offset), length);
	if (ret == NULL) {
		CloseHandle(h);
		ret = MAP_FAILED;
	}
	return ret;
}

static char munmap(char *addr, size_t length)
{
	UnmapViewOfFile(addr);
}

int main()
{
    const char *filepath = "inter.txt";
    FILE *fptr1;
    fptr1 = fopen(filepath, "w");
    fclose( fptr1 );

    int fd = open(filepath, O_RDONLY, (mode_t)0600);

    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    struct stat fileInfo = {0};

    do{
        if (fstat(fd, &fileInfo) == -1)
        {
            perror("Error getting the file size");
            exit(EXIT_FAILURE);
        }
    }while (fileInfo.st_size == 0);

    printf("File size is %ji\n", (intmax_t)fileInfo.st_size);

    char *map = mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    char a;

    time_t start = clock();

    for (off_t i = 0; i < fileInfo.st_size; i++)
    {
        a = map[i];
    }

    printf("mmap time: %f seconds\n", (double)(clock() - start)/CLOCKS_PER_SEC);

    if (munmap(map, fileInfo.st_size) == -1)
    {
        close(fd);
        perror("Error un-mmapping the file");
        exit(EXIT_FAILURE);
    }

    close(fd);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    FILE *fptr;
    char c = NULL;
    int i = 0;

    fptr = fopen("inter1.txt", "w");
    fclose( fptr );
    fptr = fopen("inter1.txt", "r");

    do{
        c=getc(fptr);

    }while(c == -1 );

    start = clock();

    long sz = 0;
    do{
        fseek(fptr, 0L, SEEK_END);
        sz = ftell(fptr);
    }while(sz < 5471304);

    printf("fopen to start: %f seconds\n", (double)(clock() - start)/CLOCKS_PER_SEC);

    fseek(fptr, 0L, SEEK_SET);
    while((c=getc(fptr))!=EOF)
    {
        a = c;
    }

    printf("fopen time: %f seconds\n", (double)(clock() - start)/CLOCKS_PER_SEC);

    return 0;
}

#undef DWORD_HI
#undef DWORD_LO
