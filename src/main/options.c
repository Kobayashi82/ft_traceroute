/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:45 by vzurera-          #+#    #+#             */
/*   Updated: 2025/08/11 17:27:51 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "main/options.h"

#pragma endregion

#pragma region "Strtoul"

	static int ft_strtoul(char **argv, const char *optarg, size_t *value, size_t max_value, bool allow_zero) {
		char *endptr;
		*value = strtoul(optarg, &endptr, 0);

		if (*endptr)							{ fprintf(stderr, "%s: invalid value (`%s' near `%s')\n", argv[0], optarg, endptr);	return (1); }
		if (!*value && !allow_zero)				{ fprintf(stderr, "%s: option value too small: %s\n", argv[0], optarg);				return (1); }
		if (max_value && *value > max_value)	{ fprintf(stderr, "%s: option value too big: %s\n", argv[0], optarg);				return (1); }

		return (0);
	}

#pragma endregion

#pragma region "Help"

	static int help() {
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "  ft_traceroute [ -dFITnrUV ] [ -f first_ttl ] [ -i device ] [ -m max_ttl ] [ -N squeries ] [ -p port ] [ -t tos ] [ -w MAX,HERE,NEAR ] [ -q nqueries ] [ -s src_addr ] [ -z sendwait ] host [ packetlen ]\n");
		fprintf(stderr, "Options:\n");
		fprintf(stderr, "  -d  --debug                 Enable socket level debugging\n");
		fprintf(stderr, "  -f first_ttl  --first=first_ttl\n");
		fprintf(stderr, "                              Start from the first_ttl hop (instead from 1)\n");
		fprintf(stderr, "  -I  --icmp                  Use ICMP ECHO for tracerouting\n");
		fprintf(stderr, "  -T  --tcp                   Use TCP SYN for tracerouting (default port is 80)\n");
		fprintf(stderr, "  -i device  --interface=device\n");
		fprintf(stderr, "                              Specify a network interface to operate with\n");
		fprintf(stderr, "  -m max_ttl  --max-hops=max_ttl\n");
		fprintf(stderr, "                              Set the max number of hops (max TTL to be\n");
		fprintf(stderr, "                              reached). Default is 30\n");
		fprintf(stderr, "  -N squeries  --sim-queries=squeries\n");
		fprintf(stderr, "                              Set the number of probes to be tried\n");
		fprintf(stderr, "                              simultaneously (default is 16)\n");
		fprintf(stderr, "  -n                          Do not resolve IP addresses to their domain names\n");
		fprintf(stderr, "  -p port  --port=port        Set the destination port to use. It is either\n");
		fprintf(stderr, "                              initial udp port value for \"default\" method\n");
		fprintf(stderr, "                              (incremented by each probe, default is 33434), or\n");
		fprintf(stderr, "                              initial seq for \"icmp\" (incremented as well,\n");
		fprintf(stderr, "                              default from 1), or some constant destination\n");
		fprintf(stderr, "                              port for other methods (with default of 80 for\n");
		fprintf(stderr, "                              \"tcp\", 53 for \"udp\", etc.)\n");
		fprintf(stderr, "  -t tos  --tos=tos           Set the TOS (IPv4 type of service)\n");
		fprintf(stderr, "  -w MAX,HERE,NEAR  --wait=MAX,HERE,NEAR\n");
		fprintf(stderr, "                              Wait for a probe no more than HERE (default 3)\n");
		fprintf(stderr, "                              times longer than a response from the same hop,\n");
		fprintf(stderr, "                              or no more than NEAR (default 10) times than some\n");
		fprintf(stderr, "                              next hop, or MAX (default 5.0) seconds (float\n");
		fprintf(stderr, "                              point values allowed too)\n");
		fprintf(stderr, "  -q nqueries  --queries=nqueries\n");
		fprintf(stderr, "                              Set the number of probes per each hop. Default is\n");
		fprintf(stderr, "                              3\n");
		fprintf(stderr, "  -r                          Bypass the normal routing and send directly to a\n");
		fprintf(stderr, "                              host on an attached network\n");
		fprintf(stderr, "  -s src_addr  --source=src_addr\n");
		fprintf(stderr, "                              Use source src_addr for outgoing packets\n");
		fprintf(stderr, "  -z sendwait  --sendwait=sendwait\n");
		fprintf(stderr, "                              Minimal time interval between probes (default 0).\n");
		fprintf(stderr, "                              If the value is more than 10, then it specifies a\n");
		fprintf(stderr, "                              number in milliseconds, else it is a number of\n");
		fprintf(stderr, "                              seconds (float point values allowed too)\n");
		fprintf(stderr, "  --fwmark=num                Set firewall mark for outgoing packets\n");
		fprintf(stderr, "  -U  --udp                   Use UDP to particular port for tracerouting\n");
		fprintf(stderr, "                              (instead of increasing the port per each probe),\n");
		fprintf(stderr, "                              default port is 53\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "  -V  --version               Print version info and exit\n");
		fprintf(stderr, "  --help                      Read this help and exit\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Arguments:\n");
		fprintf(stderr, "+     host          The host to traceroute to\n");
		fprintf(stderr, "      packetlen     The full packet length (default is the length of an IP\n");
		fprintf(stderr, "                    header plus 40). Can be ignored or increased to a minimal\n");
		fprintf(stderr, "                    allowed value\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Report bugs to <kobayashi82@outlook.com>.\n");

		return (1);
	}

#pragma endregion

#pragma region "Usage"

	static int usage() {
		fprintf(stderr, "Usage: ft_traceroute [-c NUM, --count=NUMBER] [-i NUM, --interval=NUM]\n");
		fprintf(stderr, "                     [-w NUM, --timeout=NUM]  [-W NUM, --linger=NUM]\n");
		fprintf(stderr, "                     [-s NUM, --size=NUM]     [-p PATTERN, --pattern=PATTERN]\n");
		fprintf(stderr, "                     [-T NUM, --tos=NUM]      [-r, --ignore-routing] [--ttl=NUM]\n");
		fprintf(stderr, "                     [-d, --debug] [-n, --numeric] [-v, --verbose] [-q, --quiet]\n");
		fprintf(stderr, "                     [-h?, --help] [-u, --usage]   [-V, --version]\n");
		fprintf(stderr, "                     HOST ...\n");

		return (1);
	}

#pragma endregion

#pragma region "Version"

	static int version() {
		fprintf(stderr, "ft_traceroute 1.0 (based on traceroute 2.1.5).\n");
		fprintf(stderr, "Copyright (C) 2025 Kobayashi Corp ⓒ.\n");
		fprintf(stderr, "License WTFPL: DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE.\n");
		fprintf(stderr, "This is free software: you are free to change and redistribute it.\n");
		fprintf(stderr, "There is NO WARRANTY, to the extent permitted by law.\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Written by Kobayashi82 (vzurera-).\n");

		return (1);
	}

#pragma endregion

#pragma region "Invalid"

	static int invalid() {
		fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
		return (2);
	}

#pragma endregion

#pragma region "Validate Host"

	static int validate_host(t_options *options, const char *hostname) {
		struct addrinfo hints, *res;

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_RAW;
		hints.ai_flags = AI_CANONNAME;

		if (getaddrinfo(hostname, NULL, &hints, &res)) return (1);

		memcpy(&options->sockaddr, res->ai_addr, res->ai_addrlen);
		snprintf(options->hostname, sizeof(options->hostname), "%s", res->ai_canonname ? res->ai_canonname : hostname);

		inet_ntop(AF_INET, &options->sockaddr.sin_addr, options->host, INET_ADDRSTRLEN);
		freeaddrinfo(res);

		return (0);
	}

#pragma endregion

#pragma region "Parse"

	int parse_options(t_options *options, int argc, char **argv) {
		memset(options, 0, sizeof(t_options));
		options->size = SIZE_MAX;
		struct option long_options[] = {
			{"count",			required_argument,	0, 'c'},	// [-c, --count=NUM]
			{"debug",			no_argument,		0, 'd'},	// [-d, --debug]	
			{"interval",		required_argument,	0, 'i'},	// [-i, --interval=NUM]
			{"numeric",			no_argument,		0, 'n'},	// [-n, --numeric]	
			{"ignore-routing",	no_argument,		0, 'r'},	// [-r, --ignore-routing]
			{"ttl",				required_argument,	0, 'L'},	// [	--ttl=N]	
			{"tos",				required_argument,	0, 'T'},	// [-T, --tos=NUM]
			{"verbose",			no_argument,		0, 'v'},	// [-v, --verbose]
			{"timeout",			required_argument,	0, 'w'},	// [-w, --timeout=N]
			{"linger",			required_argument,	0, 'W'},	// [-W, --linger=N]
			{"pattern",			required_argument,	0, 'p'},	// [-p, --pattern=PATTERN]
			{"quiet",			no_argument,		0, 'q'},	// [-q, --quiet]
			{"size",			required_argument,	0, 's'},	// [-s, --size=NUM]
			{"help",			no_argument,		0, 'h'},	// [-h?, --help]
			{"usage",			no_argument,		0, 'u'},	// [	--usage]
			{"version",			no_argument,		0, 'V'},	// [-V, --version]
			{0, 0, 0, 0}
		};

		options->pid = getpid();

		int opt;
		while ((opt = getopt_long(argc, argv, "c:di:nrT:vw:W:p:qs:h?uV", long_options, NULL)) != -1) {
			switch (opt) {
				case 'c':	if (ft_strtoul(argv, optarg, &options->count, 0, true))						return (2);					break;
				case 'L':	if (ft_strtoul(argv, optarg, &options->ttl, 255, false))					return (2);					break;
				case 'T':	if (ft_strtoul(argv, optarg, &options->tos, 255, true))						return (2);					break;
				case 'w':	if (ft_strtoul(argv, optarg, &options->timeout, INT_MAX, false))			return (2);					break;
				case 'W':	if (ft_strtoul(argv, optarg, &options->linger, INT_MAX, false))				return (2);					break;
				case 's':	if (ft_strtoul(argv, optarg, &options->size, MAX_SIZE, true))				return (2);					break;
				case 'i': {
					char *endptr;
					double value = strtod(optarg, &endptr);
					if (*endptr) {
						fprintf(stderr, "ft_ping: invalid value (`%s' near `%s')\n", optarg, endptr);
						invalid(); return (2);
					}
					options->options |= OPT_INTERVAL;
					options->interval = value * 1000;
					if (options->interval < 100) { fprintf(stderr, "%s: option value too small: %s\n", argv[0], optarg); return (2); }
					break;
				}
				case 'p': {
					int i, c, off;
					options->pattern_len = MAX_PATTERN;
					for (i = 0; *optarg && i < options->pattern_len; ++i) {
						if (sscanf(optarg, "%2x%n", &c, &off) != 1) { fprintf(stderr, "%s: error in pattern near %s\n", argv[0], optarg); return (2); }
						optarg += off;
						options->pattern[i] = c;
					}
					options->pattern_len = i;
					break;
				}
				case 'd':	options->socket_type |= OPT_DEBUG;																break;
				case 'r':	options->socket_type |= OPT_DONTROUTE;															break;
				case 'n':	options->options |= OPT_NUMERIC;																break;
				case 'v':	options->options |= OPT_VERBOSE;																break;
				case 'q':	options->options |= OPT_QUIET;																	break;
				case '?':	if (!strcmp(argv[optind - 1], "-?"))															return (help());	return (invalid());
				case 'h':																									return (help());
				case 'u':																									return (usage());
				case 'V':																									return (version());
			}
		}

		if (optind >= argc) {
			fprintf(stderr, "ft_ping: missing host operand\n");
			invalid(); return (2);
		}

		if (validate_host(options, argv[optind])) { fprintf(stderr, "%s: unknown host\n", argv[0]); return (2); }

		return (0);
	}

#pragma endregion
