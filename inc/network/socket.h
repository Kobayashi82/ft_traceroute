/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:11:17 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 20:28:31 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <unistd.h>
	#include <sys/socket.h>
	#include <netinet/in.h>

#pragma endregion

#pragma region "Methods"

	int socket_create(int domain, int type, int protocol, int reusable, int ip_hdrincl);
	int socket_close(int sockfd);
	int socket_bind(int sockfd, const struct sockaddr *addr, socklen_t len);
	int socket_listen(int sockfd, int backlog);
	int socket_connect(int sockfd, const struct sockaddr *addr, socklen_t len);
	int socket_accept(int sockfd, struct sockaddr *addr, socklen_t *len);
	int	socket_setopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

#pragma endregion
