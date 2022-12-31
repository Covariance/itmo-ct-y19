//
// Created by covariance on 12/30/22.
//

#ifndef NO_SPEED
// 'Now I am become Death, the destroyer of worlds' -- R. Oppenheimer
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")
#endif

#include <bitset>
#include <cassert>
#include <chrono>
#include <iostream>
#include <optional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace mask {
    constexpr size_t SIZE = 256;
    using t = std::bitset<SIZE>;
    using vector = std::vector<t>;

    t read(size_t n) {
        t result;
        bool tmp;
        for (size_t i = 0; i != n; ++i) {
            std::cin >> tmp;
            result.set(i, tmp);
        }
        return result;
    }

    void print(size_t n, const t &t) {
        for (size_t i = 0; i != n; ++i) {
            std::cout << t[i] << ' ';
        }
#ifdef DEBUG
        // Flush the output
        std::cout << std::endl;
#endif
    }
}

namespace poly {
    size_t deg(const mask::t &mask) {
        // std::bitset is good, but it doesn't support iterators (for find) or __builtin_clzl
        size_t i = mask::SIZE;
        while (--i > 0 && !mask.test(i)) {
            // no-op
        }
        return i;
    }

    mask::t mul(mask::t a, mask::t b) {
        auto res = mask::t();
        while (b != 0) {
            if (b.test(0)) {
                res ^= a;
            }
            a <<= 1;
            b >>= 1;
        }
        return res;
    }

    mask::t rem(mask::t a, const mask::t &b) {
        uint64_t a_deg = deg(a) + 1;
        uint64_t b_deg = deg(b) + 1;
#ifdef DEBUG
        // Catches incorrect usage of rem
        assert (a_deg >= b_deg);
#endif
        for (size_t i = a_deg; i >= b_deg; --i) {
            if (a.test(i - 1)) {
                a ^= b << (i - b_deg);
            }
        }
        return a;
    }
}

namespace galois_field {
    /* I thank higher Powers for getting this right. And, actually, this articles: 
        1) https://habr.com/ru/post/279197/
        2) https://en.wikipedia.org/wiki/Finite_field_arithmetic

⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⠀⠀⠀⠀⠀⠀⢀⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⠀⠀⠀⠀⠀⠀⢸⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⡆⠀⢀⣠⠤⠦⢼⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣷⠟⠛⠓⠒⠛⠉⠙⢿⣿⠤⢤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠴⠚⣿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠄⠀⠈⠓⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠃⠀⡼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠀⠀⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡟⠁⢀⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡀⠀⠈⠻⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠀⢠⠏⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⡀⠀⢀⡀⠀⢹⡀⠀⠀⢹⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡟⠀⢠⡞⠀⠀⠀⠀⠀⠀⠀⣠⡾⠀⠀⠀⠀⠀⢣⠀⠀⢇⢠⠀⢷⡀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢞⡿⠁⠀⡼⠀⠀⠀⠀⠀⠀⢀⡴⢻⡆⡼⠀⠀⡄⠀⡿⡆⢂⠸⡸⡇⠸⣧⠀⠀⠘⣼⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⢸⡤⠀⢀⡇⠀⠀⠀⠀⠀⢀⡞⠁⢸⠀⡇⠀⣸⠀⢠⠇⢻⡜⡆⢣⢹⡄⢹⡄⠀⠀⣧⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠀⢸⠇⠀⢸⠹⠀⠀⠀⠀⢀⡾⢦⣄⣼⢀⠇⢀⠏⠀⣿⣠⠶⣿⣾⡌⢷⢿⡘⡇⡆⠀⢹⡟⡆⠀⠀⢠⣤⠶⠶⠦⠄⣀
⠀⠀⠀⠀⠀⠀⠀⠀⡼⡸⠀⢸⠀⠀⢸⡆⠀⠀⠀⢀⣾⡁⢀⣀⢹⣸⠀⡸⠀⣸⡧⣖⣺⣿⣯⢿⡦⢿⣷⣷⢹⣦⢸⣹⡇⠀⠀⠈⠙⠳⠦⢄⣠⠀
⠀⠀⠀⠀⠀⠀⠀⢰⢳⠇⠀⢸⡄⠀⢸⡇⡘⠀⠀⣼⠛⢻⣿⣿⣿⡏⠀⢁⣶⣧⡾⠛⣿⣋⡏⠳⣷⣀⣠⣿⣬⡟⣾⡗⠇⠀⣀⣠⠤⠤⢤⣀⡄⠀
⠀⠀⠀⠀⠀⠀⢠⡏⡏⠀⠀⢸⣷⠀⣯⢣⠇⠀⢠⣃⠀⠸⠿⣿⡞⠀⠀⣿⠏⠉⠀⣀⠻⠿⣃⣴⠿⢻⣿⣿⣿⣧⣜⣧⠀⠀⠙⠻⢦⣄⣀⠈⠋⠛
⠀⠀⠀⠀⠀⠀⣸⢳⠁⠀⠀⢸⢙⠀⣼⡼⠀⠀⡜⠈⠉⠉⢉⠟⠁⢠⡾⠋⠀⠀⠀⠈⡉⣉⣀⠀⠀⣸⣧⢿⣿⣇⣿⡿⠀⠀⠀⠀⠀⠀⠈⠉⠉⠒
⠀⠀⠀⠀⠀⠀⡏⡸⠀⠀⠀⣸⡞⠀⡟⠇⠀⣸⡇⠀⠠⣄⡏⠀⣰⡿⠁⠀⠀⠀⠀⠸⠿⠾⠷⠋⠀⣿⢋⡾⡇⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡇⡇⠀⠀⠀⡟⣿⣶⢷⢀⢀⡿⣧⠀⠀⣼⡳⣰⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠿⢃⣧⠗⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡇⡇⠀⠀⠀⡇⡇⣿⡎⢸⢸⠀⡟⣧⢰⡇⣇⡏⠀⣶⣿⣿⣷⢿⣷⡄⠀⠀⠀⣼⣿⢠⡼⣿⠀⣧⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡇⡇⠀⠀⢸⠃⡇⣿⡇⡎⡎⢀⡇⠈⣿⢶⢸⠀⠀⠙⠓⠚⠓⠚⠋⠀⠀⢀⣴⢻⡇⣼⣧⢿⠸⣻⠀⢠⣧⣾⡆⠀⠀⠀⠀⠀⠂⠀
⠀⠀⠀⠀⠀⠀⢧⢳⠀⠀⣾⣶⠁⡇⢰⢡⠃⠀⣽⠀⣿⡼⢿⣄⠀⠀⠀⠀⠀⠀⠀⣠⣴⡟⢿⣜⢃⣧⣧⣆⠃⠻⣆⣸⣟⠓⠟⢀⣠⣤⣤⣶⣦⣤
⠀⠀⠀⠀⠀⠀⠘⢾⡄⠀⣿⢸⢀⢳⣼⡰⠀⣼⣿⢶⡟⣧⢸⣯⠙⠷⠦⢤⣤⣶⠟⡵⠋⠀⣼⠞⠉⢿⣿⣿⣿⣾⣿⣿⣿⣷⡟⣛⣷⣶⣦⣄⣈⣍
⠀⠀⠀⠀⠀⠀⠀⠀⠙⢾⠏⡇⣼⠂⣟⡇⠀⣇⣿⡀⣧⣯⠘⣿⠄⠀⠀⠀⠀⢸⠿⠁⣠⠞⠁⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⢀⢧⣏⣀⣿⠀⣸⣿⣿⣣⣿⣽⠀⠘⣧⡄⠀⣀⡴⠏⢀⡔⠁⠀⠀⠀⢰⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⣠⣾⣷⣿⣿⣿⡿⠙⢠⣿⢟⡿⠁⠘⣿⣧⢧⢃⠙⠮⣅⢀⡴⠋⠀⠀⠀⠀⢠⠏⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⡇⠏⢸⣾⠏⠀⠀⠰⣽⡾⡶⣧⠀⢠⣬⣿⣿⣦⡀⠀⠀⢀⡏⢀⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⣠⣾⣿⢿⣿⣿⣿⣿⣿⠁⠀⣾⠃⠆⡇⠐⡆⠙⣧⣷⣸⣴⣿⣿⣿⣿⣿⣷⡄⠀⡼⡠⠈⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⣠⣾⣿⣿⡟⣾⣿⣿⣿⣿⡿⡀⢸⡏⢠⠃⡇⠀⠘⠆⠸⣿⢟⣯⣿⣿⣿⣿⣿⡇⢻⣼⡿⠀⢰⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢀⣾⣯⣿⣿⣿⣿⣿⣿⣻⣿⣿⠇⢁⣿⣇⡏⠀⢳⠀⠀⠀⢠⡟⠀⠳⣿⣿⣯⣿⣿⠷⢋⡟⠁⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠸⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣏⡏⠀⠀⠘⠀⠀⠀⠊⠀⠀⠀⢹⣿⣿⣿⣷⣤⠟⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⡏⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⣿⢿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⣰⣿⣟⣿⣿⣿⣿⢿⣿⣿⣿⠻⠀⠻⡌⢻⣄⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
     */
    using t = uint64_t;

    class lookup {
        // Why save map when vector is a map? Sometimes my genius, it's almost frightening.
        std::vector<mask::t> pow_to_poly;
        std::unordered_map<mask::t, t> poly_to_pow;
        t n;

    public:
        lookup(t n, const mask::t &initial) : n(n), pow_to_poly(n) {
            mask::t limit(n + 1);
            mask::t modulo = initial ^ limit;
            mask::t alpha = 1;
            for (t i = 0; i != n; ++i) {
                pow_to_poly[i] = alpha;
                poly_to_pow[alpha] = i;
                alpha <<= 1;
                if ((alpha & limit) != 0) {
                    alpha ^= limit;
                    alpha ^= modulo;
                }
            }
        }

        t inverse(t pow) const {
            return (n - pow) % n;
        }

        t to_pow(const mask::t &polynomial) const {
            return poly_to_pow.find(polynomial)->second;
        }

        mask::t to_poly(t pow) const {
            return pow_to_poly[pow % n];
        }

        mask::t poly_mul(const mask::t &poly1, const mask::t &poly2) const {
            if (poly1 == 0 || poly2 == 0) {
                /*
                 * This is a special case, because [to_pow(0)] is not in our lookup table actually,
                 * and if we would add it, it would no longer roundtrip! Correct representation for this value is -inf,
                 * but that would require me to make [poly_to_pow] type optional, which is +1 word per entry,
                 * which is meh, not cool.
                 */
                return 0;
            }
            return to_poly(pow_mul(to_pow(poly1), to_pow(poly2)));
        }

        t pow_mul(t pow1, t pow2) const {
            return (pow1 + pow2) % n;
        }
    };
}

struct endecoder {
    // Many thanks to wiki: https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm (and it's links)
    mask::t g;
    uint64_t n, r, d;
    galois_field::lookup lookup;

    endecoder(size_t n, const mask::t &pi, uint64_t d) : g(1), n(n), d(d), lookup(n, pi) {
        std::unordered_set<mask::t> minimal_polynomials;
        for (size_t i = 1; i < d; i += 2) {
#ifdef DEBUG
            std::cout << "Computed min poly for " << i << ":\n";
            mask::print(n, minimal_polynomial(i));
            std::cout << std::endl;
#endif
            minimal_polynomials.insert(minimal_polynomial(i));
        }
        for (const auto &m : minimal_polynomials) {
            g = poly::mul(g, m);
        }
        r = poly::deg(g);
    }

    mask::t encode(const mask::t &a) const {
        return (a << r) ^ poly::rem(a << r, g);
    }

    mask::vector get_syndromes(const mask::t &code) const {
        mask::vector syndromes(d - 1);
        auto degree = poly::deg(code);
        for (uint64_t i = 1; i != d; ++i) { // [1; d-1]
            for (size_t p = 0; p <= degree; ++p) {
                if (code.test(p)) {
                    syndromes[i - 1] ^= lookup.to_poly(p * i);
                }
            }
        }
        return syndromes;
    }

    mask::t decode(const mask::t &code) const {
        auto result = mask::t(code);
        decode_inplace(result);
        return result;
    }

    void decode_inplace(mask::t &code) const {
        const auto syndromes = get_syndromes(code);
#ifdef DEBUG
        std::cout << "Syndromes:\n";
        for (const auto &syndrome : syndromes) {
            std::cout << '\t' << syndrome << '\n';
        }
        std::cout << std::endl;
#endif
        const auto poly = berlekamp_massey(syndromes);
#ifdef DEBUG
        std::cout << "Berlekamp-Massey application:\n";
        for (const auto &msk : poly) {
            std::cout << '\t' << msk << '\n';
        }
        std::cout << std::endl;
#endif
        std::unordered_map<uint64_t, uint64_t> lambdas;
        for (size_t i = 0; i != poly.size(); ++i) {
            if (poly[i] != 0) {
                lambdas.insert({i, lookup.to_pow(poly[i])});
            }
        }
        for (size_t i = 0; i != n; ++i) {
            auto acc = mask::t();
            for (const auto &[ind, val] : lambdas) {
                acc ^= lookup.to_poly(lookup.pow_mul(val, i * ind));
            }
            if (acc == 0) {
                code.flip(lookup.inverse(i));
            }
        }
    }

    mask::vector berlekamp_massey(const mask::vector &syndromes) const {
        auto lambda = mask::vector(1, mask::t(1)), b = mask::vector(1, mask::t(1));
        uint64_t l = 0, m = 0;

        for (uint64_t dg = 1; dg <= d - 1; ++dg) {
            auto delta_r = mask::t();
            for (size_t j = 0; j <= l; ++j) {
                delta_r ^= lookup.poly_mul(lambda[j], syndromes[dg - 1 - j]);
            }
#ifdef DEBUG
            std::cout << "delta_r on " << dg << " iter:\n";
            std::cout << '\t' << delta_r << std::endl;
#endif
            if (delta_r != 0) {
                size_t tmx = std::max(lambda.size(), b.size() + (dg - m));
                size_t tmn = lambda.size() + b.size() + dg - m - tmx;
                mask::vector t(tmx);
                for (size_t i = 0; i != tmn; ++i) { // Fill first [0; tmn]
                    t[i] = lambda[i] ^ ((i < dg - m)
                                            ? 0
                                            : lookup.poly_mul(delta_r, b[i - (dg - m)]));
                }
                for(size_t i = tmn; i != tmx; ++i) { // Fill later [tmn; tmx]
                    t[i] = i < lambda.size()
                        ? lambda[i]
                        : ((i < dg - m)
                            ? 0
                            : lookup.poly_mul(delta_r, b[i - (dg - m)]));
                }
#ifdef DEBUG
                std::cout << "t[.]:\n";
                for (const auto &msk : t) {
                    std::cout << '\t' << msk << '\n';
                }
                std::cout << std::endl;
#endif
                if (2 * l <= dg - 1) {
                    b.resize(lambda.size());
                    for (size_t i = 0; i != lambda.size(); ++i) {
                        b[i] = (lambda[i] == 0)
                           ? 0
                           : lookup.to_poly(lookup.pow_mul(lookup.inverse(lookup.to_pow(delta_r)), lookup.to_pow(lambda[i])));
                    }
                    l = dg - l;
                    m = dg;
                }
                lambda = t;
            }
#ifdef DEBUG
            std::cout << "After " << dg << " lambda:\n";
            for (const auto &msk : lambda) {
                std::cout << '\t' << msk << '\n';
            }
            std::cout << std::endl;
#endif
        }
        return lambda;
    }

    mask::t minimal_polynomial(uint64_t primitive_pow) const {
        std::vector<uint64_t> powers(1, primitive_pow);
        do {
            powers.push_back(lookup.pow_mul(powers.back(), powers.back()));
        } while (powers.back() != primitive_pow);
        powers.pop_back();
        size_t pws = powers.size();
        mask::vector poly(pws + 1);
        poly[pws] = 1;
        for (uint64_t i = 1; i != (1 << pws); ++i) {
            uint64_t ic = i, acc = 0;
            size_t bits_cnt = 0, u = 0;
            while (ic) {
                if (ic & 1) {
                    ++bits_cnt;
                    acc = lookup.pow_mul(acc, powers[u]);
                }
                ++u;
                ic >>= 1;
            }
            poly[pws - bits_cnt] ^= lookup.to_poly(acc);
        }

        auto ans = mask::t();
        for (size_t i = 0; i != poly.size(); ++i) {
            ans.set(i, poly[i][0]);
        }
        return ans;
    }

    uint64_t get_k() const {
        return n - r;
    }

    void info() const {
        std::cout << get_k() << '\n';
        mask::print(r + 1, g);
#ifdef DEBUG
        std::cout << std::endl;
#endif
    }
};

class simulator {
    size_t size;
    std::mt19937 engine;
    std::bernoulli_distribution coin;
    const endecoder &cd;

    void gen_inplace(mask::t &signal) {
        for (size_t i = 0; i != size; ++i) {
            signal.set(i, coin(engine));
        }
    }

    struct noise {
        size_t size;
        std::bernoulli_distribution stray;
        std::mt19937 &engine;

        noise(size_t size, std::mt19937 &engine, double noise_level)
            : size(size)
            , engine(engine)
            , stray(noise_level) {}

        void add_inplace(const mask::t &vector, mask::t &signal) {
            signal = vector;
            for (size_t i = 0; i != size; ++i) {
                if (stray(engine)) {
                    signal.flip(i);
                }
            }
        }
    };

public:
    simulator(size_t size, const long seed, const endecoder &cd)
        : size(size)
        , engine(seed)
        , coin(.5)
        , cd(cd) {}

    double run(double noise_level, size_t max_iterations, size_t max_errors) {
        auto ns = noise(size, engine, noise_level);

        size_t errors = 0;
        size_t iterations = 0;
        auto message = mask::t();
        auto code = mask::t();
        for (; iterations != max_iterations; ++iterations) {
            // Generate vector
            gen_inplace(message);
            // Encode it
            mask::t encoded = cd.encode(message);
            // Add noise
            ns.add_inplace(encoded, code);
            // Decode it
            mask::t decoded = cd.decode(code);
            if (encoded != decoded) {
                ++errors;
                if (errors == max_errors) {
                    ++iterations;
                    break;
                }
            }
        }

        return static_cast<double>(errors) / static_cast<double>(iterations);
    }
};

int main() {
#ifndef LOCAL
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto _input = freopen("input.txt", "r", stdin);
    auto _output = freopen("output.txt", "w", stdout);
#endif

    uint64_t n, pi, d;
    std::cin >> n >> pi >> d;

    const auto cd = endecoder(n, pi, d);

    // Print (en/de)endecoder parameters
    cd.info();

#ifdef DEBUG
    // For a predictable simulations in DEBUG mode.
    const auto seed = 42;
#else
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
#endif
    auto sim = simulator(n, seed, cd);

    // Reusable variables
    std::string command;
    double noise_level;
    uint32_t max_iterations, max_errors;

    while (std::cin >> command) {
        std::cout << "\n";

        if (command == "Encode") {
            mask::t message = mask::read(cd.get_k());
            mask::print(n, cd.encode(message));
        }

        if (command == "Decode") {
            mask::t code = mask::read(n);
            mask::print(n, cd.decode(code));
        }

        if (command == "Simulate") {
            std::cin >> noise_level >> max_iterations >> max_errors;
            std::cout << sim.run(noise_level, max_iterations, max_errors);
        }
    }

#ifndef LOCAL
    std::cout << std::endl;
    fclose(_input);
    fclose(_output);
#endif
    return 0;
}