//
// Created by covariance on 12/27/22.
//
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

/* My namespace management is an attempt to bring a bit of type safety to the chaotic world of C++ */

namespace bit {
    using t = bool;
    using vector = std::vector<t>;
    using matrix = std::vector<vector>;

    void add_inplace(vector &to, const vector& what) {
        for (size_t i = 0; i != to.size(); ++i) {
            to[i] = (to[i] ^ what[i]);
        }
    }

    vector mul(const vector &v, const matrix& m) {
        size_t k = m.size(), n = m.begin()->size();
        vector result = vector(n);
        for (size_t i = 0; i != n; ++i) {
            for (size_t j = 0; j != k; ++j) {
                result[i] = (result[i] ^ (v[j] & m[j][i]));
            }
        }
        return result;
    }

    class generator {
        std::mt19937 &engine;
        std::uniform_int_distribution<uint8_t> uniform;
    public:
        explicit generator(std::mt19937 &engine) : engine(engine), uniform(0, 1) {}

        t bit() {
            return (uniform(engine) == 1);
        }

        void fill_vector(vector &vector) {
            for (auto && b : vector) { b = bit(); }
        }
    };

    void read_vector_inplace(vector &v) {
        t tmp;
        for (auto && el : v) {
            std::cin >> tmp;
            el = tmp;
        }
    }

    void read_matrix_inplace(matrix &m) {
        for (auto &row : m) {
            read_vector_inplace(row);
        }
    }

    void print_vector(const vector &v) {
        for (const auto &element : v) {
            std::cout << (element ? 1 : 0) << ' ';
        }
    }

    void print_matrix(const matrix &m) {
        for (const auto &row : m) {
            print_vector(row);
        }
    }
}

namespace sig {
    using t = double;
    using vector = std::vector<t>;
    using matrix = std::vector<vector>;

    void read_vector_inplace(vector &vec) {
        for (auto &el : vec) {
            std::cin >> el;
        }
    }

    void print_vector(const vector &v) {
        for (const auto &element : v) {
            std::cout << element << ' ';
        }
    }

    void print_matrix(const matrix &m) {
        for (const auto &row : m) {
            print_vector(row);
        }
    }

    constexpr t min = -std::numeric_limits<t>::max();
}

namespace edge {
    using t = std::pair<size_t, bool>;
    using vector = std::vector<t>;
    using matrix = std::vector<vector>;

    void print_vector(const vector &edges) {
        for (const auto &e : edges) {
            std::cout << "(" << e.first << ", " << e.second << ") ";
        }
    }
}

namespace mask {
    // In case we need 64 bits here we would be able to easily change it (except for popcount)
    using t = uint32_t;

    t to_index(t state, t active) {
        uint32_t shift = 0;
        t value = 0;
        while (active != 0) {
            if (active & 1u) {
                t bit = state & 1u;
                value |= (bit << shift);
                ++shift;
            }
            state >>= 1u;
            active >>= 1u;
        }
        return value;
    }

    t to_state(t index, t active) {
        uint32_t shift = 0;
        t value = 0;
        while (active != 0) {
            if (active & 1u) {
                t bit = index & 1u;
                value |= (bit << shift);
                index >>= 1u;
            }
            ++shift;
            active >>= 1u;
        }
        return value;
    }

    inline size_t popcount(const t x) {
        // I just found this on codeforces and wanted to try it out.
        int count = 0;
        __asm__ volatile("POPCNT %1, %0;"
                :"=r"(count)
                :"r"(x)
                :
                );
        return static_cast<size_t>(count);
    }
}

class span_form {
public:
    using span = std::pair<size_t, size_t>;

    bit::matrix matrix;
    std::vector<span> spans;

    static span calculate_span(const bit::vector &vector) {
        bool found_one = false;
        span span = {0, 0};
        for (size_t i = 0; i != vector.size(); ++i) {
            if (vector[i]) {
                if (!found_one) {
                    found_one = true;
                    span.first = i;
                }
                span.second = i;
            }
        }
        return span;
    }

    [[maybe_unused]] void calculate_initial_spans() {
        spans.reserve(matrix.size());
        for (const auto &row : this->matrix) {
            spans.push_back(std::move(calculate_span(row)));
        }
    }

    void msf_inplace() {
        /*
         * We use this algorithm instead of two-way gauss because it's simpler and has the same
         * asymptotic size, but in reality can converge much faster.
         *
         * I think someone has already thought of this, but I invented it right here right now.
         *
         * Intuition is easy -- the fact that this algorithm constructs the MSF is trivial,
         * it's asymptotic is uh also pretty trivial -- on each iteration of the outer cycle we
         * _clear_ one new row for the span form, therefore it is not run more than O(n) times.
         */

        // We continue iterations until there are no changes on new iteration.
        bool untouched = false;
        while (!untouched) {
            untouched = true;
            for (size_t i = 0; i != matrix.size(); ++i) {
                for (size_t j = 0; j != matrix.size(); ++j) {
                    if (i != j) {
                        /*
                         * Left nested is:
                         * i -> [ . . . ]
                         * j -> [ . . . . ]
                         *
                         * Right nested is:
                         * i -> [ . . . . ]
                         * j ->   [ . . . ]
                         *
                         * We want to un-nest those, making one a strict subsegment of another.
                         */
                        const auto is_left_nested = (spans[i].first == spans[j].first &&
                                                     spans[i].second <= spans[j].second);
                        const auto is_right_nested = (spans[i].first <= spans[j].first &&
                                                      spans[i].second == spans[j].second);
                        if (is_left_nested || is_right_nested) {
                            untouched = false;
                            bit::add_inplace(matrix[i], matrix[j]);
                            spans[i] = calculate_span(matrix[i]);
                        }
                    }
                }
            }
        }
    }

    explicit span_form(bit::matrix gen_matrix) : matrix(std::move(gen_matrix)), spans(matrix.size(), {0, matrix.begin()->size() - 1}) {
        this->msf_inplace();
#ifdef DEBUG
        std::cout << "MSF matrix:\n";
        bit::print_matrix(this->matrix);
        std::cout << std::endl;
#endif
    }
};

namespace viterbi {
    namespace grid {
        class layer {
            mask::t active;
        public:
            explicit layer(mask::t active_rows = 0u) : active(active_rows), edges(size(), edge::vector()) {}

            void connect(mask::t next_active, mask::t column) {
                mask::t shared = active | next_active;
                size_t states = 1u << mask::popcount(shared);

                for (mask::t state = 0; state != states; ++state) {
                    mask::t transition = mask::to_state(state, shared);
                    mask::t from = mask::to_index(transition, active);
                    mask::t to = mask::to_index(transition, next_active);
                    bit::t edge_value = mask::popcount(transition & column) & 1u;
                    edges[static_cast<size_t>(from)].push_back(edge::t{static_cast<size_t>(to), edge_value});
                }
            }

            [[nodiscard]] size_t size() const {
                return 1u << mask::popcount(active);
            }

#ifdef DEBUG
            void print() const {
                for (size_t i = 0; i != edges.size(); ++i) {
                    std::cout << "\tvertex " << i << ": ";

                    std::cout << std::endl;
                }
            }
#endif
            std::vector<edge::vector> edges;
        };

        using t = std::vector<layer>;

#ifdef DEBUG
        void print(const t &grid) {
            for (size_t i = 0; i != grid.size(); ++i) {
                std::cout << "layer " << i << ":\n";
                grid[i].print();
            }
        }
#endif

        t build(const span_form &span_form) {
            size_t k = span_form.matrix.size();
            size_t n = span_form.matrix.begin()->size();

            t gr = t();
            gr.push_back(layer());
            for (size_t j = 0; j != n; ++j) {
                mask::t active = 0;
                mask::t column = 0;
                for (size_t i = 0; i != k; ++i) {
                    if (span_form.spans[i].first <= j && j < span_form.spans[i].second) {
                        active |= (1u << i);
                    }
                    column |= (span_form.matrix[i][j] << i);
                }
                gr.back().connect(active, column);
                gr.push_back(layer(active));
            }
#ifdef DEBUG
            print(gr);
#endif
            return gr;
        }

        void print_sizes(const t &grid) {
            for (const auto &layer : grid) {
                std::cout << layer.size() << ' ';
            }
        }
    }

    bit::vector encode(const bit::matrix &matrix, const bit::vector &input) {
        return bit::mul(input, matrix);
    }

    bit::vector decode(const grid::t &grid, const sig::vector &sig) {
#ifdef DEBUG
        std::cout << "decoding\n";
#endif
        auto cost = sig::matrix(grid.size());
        cost.front() = sig::vector(grid.front().size(), 0);

        auto path = edge::matrix(grid.size());

        for (size_t i = 1; i != grid.size(); ++i) {
            cost[i] = sig::vector(grid[i].size(), sig::min);
            path[i] = edge::vector(grid[i].size());
            for (size_t from = 0; from != grid[i - 1].size(); ++from) {
                for (const edge::t &e: grid[i - 1].edges[from]) {
                    sig::t weight = (e.second ? -1. : 1.) * (sig[i - 1]);
                    if (cost[i - 1][from] + weight > cost[i][e.first]) {
                        cost[i][e.first] = cost[i - 1][from] + weight;
                        path[i][e.first] = edge::t{from, e.second};
                    }
                }
            }
#ifdef DEBUG
            std::cout << "cost " << i << ":\n";
            sig::print_vector(cost[i]);
            std::cout << std::endl;
            std::cout << "path " << i << ":\n";
            edge::print_vector(path[i]);
            std::cout << std::endl;
#endif
        }

        auto result = bit::vector(path.size() - 1);
        size_t on_layer = 0;
        for (size_t i = path.size() - 1; i != 0; --i) {
            result[i - 1] = (path[i][on_layer].second);
            on_layer = path[i][on_layer].first;
        }
        return result;
    }
}

class simulator {
    std::mt19937 engine;
    bit::generator generator;
    const viterbi::grid::t &grid;
    const bit::matrix &matrix;

    struct noise {
        std::normal_distribution<double> gaussian;
        std::mt19937 &engine;

        noise(std::mt19937 &engine, double noise_level, size_t n, size_t k) : engine(engine) {
            double decibel = pow(10, -noise_level / 10.);
            double deviation = (0.5 * static_cast<double>(n) / static_cast<double>(k)) * decibel;

            this->gaussian = std::normal_distribution<double>(.0, sqrt(deviation));
        }

        void add_inplace(const bit::vector &vector, sig::vector &signal) {
            for (size_t i = 0; i != signal.size(); ++i) {
                signal[i] = (vector[i] ? -1.0 : 1.0) + gaussian(engine);
            }
        }
    };

public:
    simulator(const viterbi::grid::t &grid, const bit::matrix &matrix)
            : engine(std::chrono::system_clock::now().time_since_epoch().count())
            , generator(engine)
            , grid(grid)
            , matrix(matrix) {}

    double run(double noise_level, uint32_t max_iterations, uint32_t max_errors) {
        size_t k = matrix.size();
        size_t n = matrix.begin()->size();

        auto ns = noise(engine, noise_level, n, k);

        uint32_t errors = 0;
        uint32_t iterations = 0;
        auto message = bit::vector(k);
        auto code = sig::vector(n);
        for (; iterations != max_iterations; ++iterations) {
            // Generate vector
            generator.fill_vector(message);
            // Encode it
            bit::vector encoded = viterbi::encode(matrix, message);
            // Add noise
            ns.add_inplace(encoded, code);
            // Decode it
            bit::vector decoded = viterbi::decode(grid, code);

            if (decoded != encoded) {
                errors += 1;
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

    uint32_t n, k;
    std::cin >> n >> k;

    bit::matrix gen_matrix(k, bit::vector(n));
    bit::read_matrix_inplace(gen_matrix);

    // Build MSF of generative matrix and create grid for the decoder.
    const span_form sf = span_form(gen_matrix);
    const viterbi::grid::t grid = viterbi::grid::build(sf);
    simulator sim = simulator(grid, gen_matrix);

    // Layer sizes
    viterbi::grid::print_sizes(grid);

    // Reusable variables
    std::string command;
    sig::vector sv(n);
    bit::vector bv(k);
    double noise_level;
    uint32_t max_iterations, max_errors;

    while (std::cin >> command) {
        std::cout << "\n";

        if (command == "Encode") {
            bit::read_vector_inplace(bv);
            bit::print_vector(viterbi::encode(gen_matrix, bv));
        }

        if (command == "Decode") {
            sig::read_vector_inplace(sv);
            bit::print_vector(viterbi::decode(grid, sv));
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
