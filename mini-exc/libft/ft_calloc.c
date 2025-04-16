/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:27:49 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:19 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	space;
	void	*buff;

	space = count * size;
	if ((count != 0) && ((space / count) != size))
	{
		return (NULL);
	}
	buff = malloc(space);
	if (buff == NULL)
		return (NULL);
	ft_bzero(buff, space);
	return (buff);
}
/*
#include <stdio.h>
#include <string.h>

void test_case(size_t count, size_t size) {
    printf("Testing calloc with count = %zu, size = %zu\n", count, size);

    // Using standard calloc
    void *std_ptr = calloc(count, size);
    if (!std_ptr) {
        printf("Standard calloc failed to allocate %zu bytes.\n", count * size);
    } else {
        printf("Standard calloc: allocated %zu bytes.\n", count * size);
    }

    // Using ft_calloc
    void *ft_ptr = ft_calloc(count, size);
    if (!ft_ptr) {
        printf("ft_calloc failed to allocate %zu bytes.\n", count * size);
    } else {
        printf("ft_calloc: allocated %zu bytes.\n", count * size);
    }

    // Compare results if both allocations were successful
    if (std_ptr && ft_ptr) {
        if (memcmp(std_ptr, ft_ptr, count * size) == 0) {
            printf("Success: Both allocations are 
			identical and zero-initialized.\n");
        } else {
            printf("Error: Allocations differ or are not zero-initialized.\n");
        }
    }

    free(std_ptr);
    free(ft_ptr);
    printf("\n");
}

int main() {
    // Case 1: Zero count and size
    test_case(0, 0);

    // Case 2: Zero count, non-zero size
    test_case(0, 5);

    // Case 3: Non-zero count, zero size
    test_case(5, 0);

    // Case 4: Small allocation (1 element of 1 byte)
    test_case(1, 1);

    // Case 5: Medium allocation
    test_case(10, 10);

    // Case 6: Large allocation
    test_case(1000, 1000);

    return 0;
}*/
