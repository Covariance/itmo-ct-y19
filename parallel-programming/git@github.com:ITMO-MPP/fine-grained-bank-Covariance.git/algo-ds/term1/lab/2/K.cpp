#include <iostream>

const long long LENGTH = 1000000000000000000;
long long first, x, m, answer;

long long query(long long q) {
    long long retval;
    std::cout << "? " << q << std::endl;
    std::cin >> retval;
    return retval;
}

int main() {
	std::cin >> x >> m;
	std::cout << "? 1" << std::endl;
	std::cin >> first;

	long long r = std::min((LENGTH + x - first) % LENGTH + 1, LENGTH - m);
	long long mid;
	long long l = std::max(1ll, r - m);

	while (l <= r) {
		mid = l + (r - l)/2;
        answer = query(mid);

		if (answer == x) {
			std::cout << "! " << mid << std::endl;
			return 0;
		}

		if (x < first) {
			if (answer > first || answer < x) {
                l = mid + 1;
			} else {
			    r = mid - 1;
			}
		} else {
			if (answer > first && answer < x) {
                l = mid + 1;
			} else {
			    r = mid - 1;
			}
		}
	}

	std::cout << "! -1" << std::endl;
	return 0;
}
