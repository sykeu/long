#ifndef LONG_H
#define LONG_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define BUFFER_SIZE 1

int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, size_t len);
char	**ft_split(char *s, char c);


#endif
