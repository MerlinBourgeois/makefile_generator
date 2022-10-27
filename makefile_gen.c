#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(*s1) * (strlen(s1) + strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i] != '\0')
	{
		res[j] = s2[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

int ft_listfile(void)
{
	system("ls *.c | grep -v makefile_gen.c | awk '{ print $0\" /\" }' > cache");
	system("cat cache | tail -n1 | sed 's: /::' > tmp");
	system("sed -i -e '$d' cache; cat tmp >> cache;rm tmp cache-e");
	system("cat cache | tr '/' '\\' > tmp; mv tmp cache");
	return(0);
}

int ft_putstring_file(char *ch, FILE *f)
{
	int i;
	i = 0;
	if(!f)
	{
		printf("%s", "erreur de lecture du ficher");
		return(1);
	}
	while (ch[i])
		fputc(ch[i++], f);
	fclose(f);
	return(0);
}

char *ft_buffer_gen(int boolcompile, char *lib_name)
{
	int i;
	int j;
	char *buffer;
	char joint[100];
	char monobuf[1];
	char *name = "NAME = ";
	char *src = "SRC = ";
	char *obj = "OBJ = ${SRC:.c=.o}";
	char *cflags = "CFLAGS = -Wall -Werror -Wextra";
	char *lib = "LIB  = ar rcs $(NAME)";
	char *remove = "REMOVE = rm -f";
	char *compile = "COMPILE = gcc $(CFLAGS) -o $(NAME) $(OBJ)";
	char *all = "all: $(NAME)";
	char *name_all = "$(NAME):\t$(OBJ)\n\t@$(LIB) $(OBJ)";
	char *clean = "clean:\n\t@$(REMOVE) $(OBJ)";
	char *fclean = "fclean:\tclean\n\t@$(REMOVE) $(NAME)";
	char *re = "re: fclean all";
	char *phony = ".PHONY: all clean fclean re";
	i = 0;

	if (system("find . -name '*.a'") == 0)
	{
		system("find . -name '*.a' | xargs echo -n > tempor");
		int f = open("tempor", O_RDONLY);
		while (read(f, monobuf, 1))
		{
			joint[i] = monobuf[0];
			i++;
		}
		joint[i] = '\0';
		lib = ft_strjoin(lib, ft_strjoin(" ", joint));
		close(f);
		system("rm tempor");
	}
	
	buffer = malloc(30000 * sizeof(char));
	j = 0;
	i = 0;
	ft_listfile();
	while (name[j])
	{
		buffer[i] = name[j];
		i++;
		j++;
	}
	j = 0;
	while (lib_name[j])
	{
		buffer[i] = lib_name[j];
		j++;
		i++;
	}
	j = 0;
	buffer[i++] = '\n';
	while (src[j])
	{
		buffer[i] = src[j];
		j++;
		i++;
	}
	int f = open("cache", O_RDONLY);
	while (read(f, monobuf, 1))
	{
		buffer[i] = monobuf[0];
		i++;
	}
	buffer[i++] = '\n';
	system("rm cache");
	j = 0;
	while (obj[j])
	{
		buffer[i] = obj[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (cflags[j])
	{
		buffer[i] = cflags[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (lib[j])
	{
		buffer[i] = lib[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (remove[j])
	{
		buffer[i] = remove[j];
		i++;
		j++;
	}
	if (boolcompile == 0)
	{
		j = 0;
		buffer[i++] = '\n';
		buffer[i++] = '\n';
		while (compile[j])
		{
			buffer[i] = compile[j];
			i++;
			j++;
		}
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (all[j])
	{
		buffer[i] = all[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (name_all[j])
	{
		buffer[i] = name_all[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (clean[j])
	{
		buffer[i] = clean[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (fclean[j])
	{
		buffer[i] = fclean[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (re[j])
	{
		buffer[i] = re[j];
		i++;
		j++;
	}
	j = 0;
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	while (phony[j])
	{
		buffer[i] = phony[j];
		i++;
		j++;
	}
	return(buffer);
}

int main (void)
{
	char monobuf;
	char polybuf[100];
	char *ch;
	int i;
	int var_bool;
	int x;

	i = 0;
	printf("%c", '\n');
	printf("%s", " +--------------------------------------------------------------------------------+\n");
	printf("%s", " |      Ce délicieux code vous est gracieusement offert par \e[34mBruno et Merlin\e[0m       | \n");
	printf("%s", " +--------------------------------------------------------------------------------+\n");
	printf("%c", '\n');
	printf("%c", '\n');
	printf("%s", "\e[33m                                    ..,,,,...               \n");
	printf("%s", "                              ,,.................,.         \n");
	printf("%s", "                          .*,......................,,*      \n");
	printf("%s", "                        .,,*,,,,,,,,,,,,,,,,,,,,,,,,,*,,    \n");
	printf("%s", "                      .*,****,,,,,****,,,,,***,,,,,,****,*  \n");
	printf("%s", "                     .,**********\e[31;1m##/,,#(*/#/*/#*/\e[33;1m********,* \n");
	printf("%s", "                    .,*********\e[31;1m/#(#\e[30;1m&&&\e[31;1m(//*#\e[30;1m&&&\e[31;1m(/#/\e[33;1m********,*\n");
	printf("%s", "                    *,*********\e[31;1m(#/#\e[30;1m&&%\e[31;1m(((/(\e[30;1m&&&\e[31;1m#/(/\e[33;1m*********,\n");
	printf("%s", "                    *,**********\e[31;1m(#((((((/(#(((#(\e[33;1m***********,\n");
	printf("%s", "                   *,**************************************\n");
	printf("%s", "                    .**********/***************/***********/\n");
	printf("%s", "                     .****\e[31;1m#%%%%%%%%%%%%%%%%%%%%%%%%\e[33;1m/******* \n");
	printf("%s", "                       /********,,,,,,,,,,,,,,**/*********  \n");
	printf("%s", "                        .*******************************    \n");
	printf("%s", "                           *************************/,      \n");
	printf("%s", "                              ./****************/*          \e[0m\n");
	printf("%c", '\n');
	printf("%c", '\n');
	while (i != 1)
	{	
		dprintf(2, "\e[32m\rVoulez vous faire une librairie ou un executable ? (l/e) : \e[0m");
		while (read(0, &monobuf, 1))
		{
			if (monobuf == 'l')
			{
				var_bool = 1;
				i++;
			}
			else if (monobuf == 'e')
			{
				var_bool = 0;
				i++;
			}
			else if (monobuf != 'l' || monobuf != 'e')
			{
				break;
			}
		}
	}
	i = 0;
	while (i != 1)
	{

		dprintf(2, "\e[32m\rNom de votre programe/librairie : \e[0m");
		while (x += read(0, polybuf, 99))
		{
			x = x - 1;
			polybuf[x] = '\0';
			ch = ft_buffer_gen(var_bool, polybuf);
			
			break;
		}
		i = 1;
	}
	FILE *f;
	f = fopen("Makefile", "w");
	ft_putstring_file(ch, f);
	dprintf(2, "\e[34m\rMerci d'avoir géneré votre Makefile avce notre generateur.\e[0m");
}