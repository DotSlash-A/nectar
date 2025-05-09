#ifndef PROGRESSIONS_TYPES_H
#define PROGRESSIONS_TYPES_H

#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <iomanip> // For std::fixed, std::setprecision
#include <cmath>   // For std::abs, std::pow, std::round
#include <limits>  // For std::numeric_limits

namespace michu_fr {
namespace progressions {

const double EPSILON = 1e-9;

struct APResult {
    double nth_term;
    double sum_n_terms;

    APResult(double nt, double snt) : nth_term(nt), sum_n_terms(snt) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "APResult{nthTerm=" << nth_term << ", sumNTerms=" << sum_n_terms << "}";
        return oss.str();
    }
};

struct APMiddleTermResult {
    int number_of_terms;
    std::vector<int> middle_indices; // 1-based
    std::vector<double> middle_values;

    APMiddleTermResult(int num_terms, std::vector<int> indices, std::vector<double> values)
        : number_of_terms(num_terms), middle_indices(std::move(indices)), middle_values(std::move(values)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "APMiddleTermResult{numberOfTerms=" << number_of_terms << ", middleIndices=[";
        for (size_t i = 0; i < middle_indices.size(); ++i) {
            oss << middle_indices[i] << (i == middle_indices.size() - 1 ? "" : ", ");
        }
        oss << "], middleValues=[";
        for (size_t i = 0; i < middle_values.size(); ++i) {
            oss << middle_values[i] << (i == middle_values.size() - 1 ? "" : ", ");
        }
        oss << "]}";
        return oss.str();
    }
};

struct GPResult {
    double nth_term;
    double sum_n_terms;

    GPResult(double nt, double snt) : nth_term(nt), sum_n_terms(snt) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "GPResult{nthTerm=" << nth_term << ", sumNTerms=" << sum_n_terms << "}";
        return oss.str();
    }
};

struct GPInsertMeansResult {
    double common_ratio;
    std::vector<double> geometric_means;

    GPInsertMeansResult(double cr, std::vector<double> means)
        : common_ratio(cr), geometric_means(std::move(means)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "GPInsertMeansResult{commonRatio=" << common_ratio << ", geometricMeans=[";
        for (size_t i = 0; i < geometric_means.size(); ++i) {
            oss << geometric_means[i] << (i == geometric_means.size() - 1 ? "" : ", ");
        }
        oss << "]}";
        return oss.str();
    }
};

} // namespace progressions
} // namespace michu_fr

#endif // PROGRESSIONS_TYPES_H