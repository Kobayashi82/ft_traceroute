/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:11:09 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/02 14:25:40 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "network/socket.h"
	#include "utils/utils.h"

	#include <unistd.h>
	#include <netinet/in.h>

#pragma endregion

#pragma region "Create"

	int socket_create(int domain, int type, int protocol, int reusable, int ip_hdrincl) {
		int sockfd = socket(domain, type, protocol);
		if (sockfd < 0) return (-1);

		if (reusable) {
			int value = 1;
			if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0) {
				close(sockfd);
				return (-1);
			}
		}

		if (ip_hdrincl && domain == AF_INET && type == SOCK_RAW) {
			int value = 1;
			if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &value, sizeof(value)) < 0) {
				close(sockfd);
				return (-1);
			}
		}

		return (sockfd);
	}

#pragma endregion

#pragma region "Close"

	int socket_close(int sockfd) {
		return (close(sockfd));
	}

#pragma endregion

#pragma region "Bind"

	int	socket_bind(int sockfd, const struct sockaddr *addr, socklen_t len) {
		return (bind(sockfd, addr, len));
	}

#pragma endregion

#pragma region "Listen"

	int	socket_listen(int sockfd, int backlog) {
		return (listen(sockfd, (backlog <= 0 || backlog > SOMAXCONN) ? SOMAXCONN : backlog));
	}

#pragma endregion

#pragma region "Connect"

	int	socket_connect(int sockfd, const struct sockaddr *addr, socklen_t len) {
		return (connect(sockfd, addr, len));
	}

#pragma endregion

#pragma region "Accept"

	int	socket_accept(int sockfd, struct sockaddr *addr, socklen_t *len) {
		return (accept(sockfd, addr, len));
	}

#pragma endregion

#pragma region "Set Option"

	int	socket_setopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
		return (setsockopt(sockfd, level, optname, optval, optlen));
	}

#pragma endregion
