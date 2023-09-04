#include <iostream>
#include <vector>
#include <map>

class RecommendationSystem {
public:
    // Constructor to initialize the recommendation system
    RecommendationSystem(int numUsers, int numMovies) {
        numUsers_ = numUsers;
        numMovies_ = numMovies;
        userMovieMatrix_.resize(numUsers_, std::vector<int>(numMovies_, 0));
    }

    // Record user preferences (ratings)
    void recordUserPreference(int userId, int movieId, int rating) {
        if (userId >= 0 && userId < numUsers_ && movieId >= 0 && movieId < numMovies_) {
            userMovieMatrix_[userId][movieId] = rating;
        }
    }

    // Recommend movies for a given user using collaborative filtering
    std::vector<int> recommendMovies(int userId) {
        if (userId >= 0 && userId < numUsers_) {
            std::map<int, double> movieScores;

            // Calculate movie scores based on user similarities
            for (int movieId = 0; movieId < numMovies_; ++movieId) {
                if (userMovieMatrix_[userId][movieId] == 0) {
                    double score = calculateMovieScore(userId, movieId);
                    movieScores[movieId] = score;
                }
            }

            // Sort movies by score in descending order
            std::vector<int> recommendations;
            for (const auto& pair : movieScores) {
                recommendations.push_back(pair.first);
            }
            return recommendations;
        }
        else {
            std::cerr << "Invalid user ID." << std::endl;
            return {};
        }
    }

private:
    int numUsers_;
    int numMovies_;
    std::vector<std::vector<int>> userMovieMatrix_;

    // Calculate the similarity score between two users (for simplicity, using a basic dot product)
    double calculateUserSimilarity(int user1, int user2) {
        double similarity = 0.0;
        for (int movieId = 0; movieId < numMovies_; ++movieId) {
            similarity += userMovieMatrix_[user1][movieId] * userMovieMatrix_[user2][movieId];
        }
        return similarity;
    }

    // Calculate the score of a movie for a user based on their preferences and user similarities
    double calculateMovieScore(int userId, int movieId) {
        double score = 0.0;
        for (int otherUserId = 0; otherUserId < numUsers_; ++otherUserId) {
            if (otherUserId != userId) {
                score += calculateUserSimilarity(userId, otherUserId) * userMovieMatrix_[otherUserId][movieId];
            }
        }
        return score;
    }
};

int main() {
    // Create a recommendation system with 5 users and 10 movies
    RecommendationSystem recSys(5, 10);

    // Record user preferences (ratings)
    recSys.recordUserPreference(0, 0, 5);
    recSys.recordUserPreference(0, 1, 4);
    recSys.recordUserPreference(0, 3, 3);

    recSys.recordUserPreference(1, 0, 3);
    recSys.recordUserPreference(1, 1, 5);
    recSys.recordUserPreference(1, 4, 4);

    recSys.recordUserPreference(2, 2, 4);
    recSys.recordUserPreference(2, 5, 5);

    recSys.recordUserPreference(3, 3, 4);
    recSys.recordUserPreference(3, 6, 5);

    recSys.recordUserPreference(4, 4, 5);
    recSys.recordUserPreference(4, 7, 4);

    // Recommend movies for user 2
    std::vector<int> recommendations = recSys.recommendMovies(2);

    // Display recommended movies
    std::cout << "Recommended movies for User 2:" << std::endl;
    for (int movieId : recommendations) {
        std::cout << "Movie " << movieId << std::endl;
    }

    return 0;
}
