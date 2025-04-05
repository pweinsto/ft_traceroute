# ft_traceroute

ft_traceroute tracks the route packets taken from an IP network on their way to a given host. It utilizes the IP protocol's time to live (TTL) field and attempts to elicit an ICMP TIME_EXCEEDED response from each gateway along the path to the host. ft_traceroute works with either UDP or ICMP requests.
ft_traceroute is fully compatible with IPV4 and IPV6 adresses and handles DNS resolution.
