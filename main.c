#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int     fd;
	char    *line;

	fd = open("test.txt", O_RDONLY); // Открываем файл
	if (fd < 0)
	{
		perror("Ошибка при открытии файла");
		return (1);
	}
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // Освобождаем память после каждого вызова
	}
	close(fd); // Закрываем файл
	return (0);
}